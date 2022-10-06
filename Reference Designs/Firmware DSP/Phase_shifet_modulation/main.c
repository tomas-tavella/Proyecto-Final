/*
 * main.c
 */
#include "math.h"
#include "DSP2833x_Device.h"
#include "IQmathLib.h"
#include "pi_reg4.h"


#define T 0.00005  //20kHz
#define N_PI  3.1415926535897932384626433832795
#define N_SAMPLES 512

//--------------------*********************************
unsigned short vector[N_SAMPLES];
unsigned short Ioffset = 3150;  //offset de la corriente
unsigned short duty= 375;  // ciclo de trabajo al 50%
int Iref=300;  // referencia de 0.5A +-
int Imed=0; //Corriente medida actual en entero de 16bits
int Vmed=0; //Voltaje medido actual en entero de 16bits
float Vmed_float=0.0; //Voltaje en la carga medido en voltios
float Vref_float=6.0;//Referencia que queremos regular (para este circuito usarlo entre 5 y 7.0V)

float K_i=0.00473000016; //ganancia que nos da en voltios la salida al multiplicarla por la muestra del canal A1
float errorV=0.0; //error de tensi�n (flotante)

int errorI=0; //error de corriente (entero 16bits)
int control=0; //activa desactiva el control a lazo cerrado
//--------------------*********************************

long acum=0;
int i=0;
unsigned int phase = 0;

extern void InitSysCtrl(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void InitAdc(void);

interrupt void epwm1_period_match_isr(void);
interrupt void ADC_isr(void);

void ConfigGPIOs(void);
void MiDelay(long i);
void Config_ePWM1(void);
void Config_ePWM2(void);
void Setup_ADC(void);

PI_CONTROLLER pi_current = PI_CONTROLLER_DEFAULTS;


int main(void) {

    InitSysCtrl(); //Configure el DSP a 150Mhz y desahabilite el wachdog y habilita todos los clock de perifericos
    DINT;

    Config_ePWM2(); //configuramos el modulo de ePWM1A
    Config_ePWM1();
    MiDelay(100000);
    ConfigGPIOs();

    InitPieCtrl();
    InitPieVectTable();

    InitAdc();
    Setup_ADC();
    MiDelay(100000);

    EALLOW;
        PieVectTable.EPWM1_INT = &epwm1_period_match_isr;
        PieVectTable.ADCINT = &ADC_isr;
    EDIS;

    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;      // interrupcion del grupo3 -  PWM1
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1; //ADC

    IER |= 4;                                // Nivel 2 -> Habilita INT3 en IER
    IER |= 1;
    EINT;                          // Nivel 3 -> Habilita interrupciones de control
    ERTM;

    while(1)
    {
        if (GpioDataRegs.GPBDAT.bit.GPIO62 == 0){
            if(phase>=3750){
                phase = 3750;
            } else{
                phase += 1;
            }
            EPwm2Regs.TBPHS.half.TBPHS = phase;

        }

        if (GpioDataRegs.GPBDAT.bit.GPIO63 == 0){
            if(phase<=0){
                phase = 0;
            } else{
                phase -= 1;
            }
            EPwm2Regs.TBPHS.half.TBPHS = phase;
        }
        if(phase > 1875){
            GpioDataRegs.GPBSET.bit.GPIO32 = 1;
        } else{
            GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;
        }
        EPwm2Regs.TBPHS.half.TBPHS = phase;
        MiDelay(5000);
    }

}

void ConfigGPIOs(void)
{
   EALLOW;
   GpioCtrlRegs.GPBMUX1.bit.GPIO32= 0; //funcion GPIO - Este es el puerto I2C, no hay que configurarlo como GPIO (GpioCtrlRegs.GPBMUX1.bit.GPIO32= 1)
   GpioCtrlRegs.GPBDIR.bit.GPIO32  = 1; //Salida

   GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 0; //funcion BUTT1
   GpioCtrlRegs.GPBDIR.bit.GPIO62  = 0; //entrada
   GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0; //Pull up enabled

   GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 0; //funcion BUTT2
   GpioCtrlRegs.GPBDIR.bit.GPIO63  = 0; //entrada
   GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0; //Pull up enabled

   //configuramos el pin GPIO00  como PWM
   GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 1; //funcion PWM1A
   GpioCtrlRegs.GPADIR.bit.GPIO0   = 1; //Salida

   GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 1; //funcion PWM1B
   GpioCtrlRegs.GPADIR.bit.GPIO1   = 1; //Salida

   GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 1; //funcion PWM2A
   GpioCtrlRegs.GPADIR.bit.GPIO2  = 1; //Salida

   GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 1; //funcion PWM2B
   GpioCtrlRegs.GPADIR.bit.GPIO3   = 1; //Salida
   EDIS;
}

void Config_ePWM1(void)
{
    //Configuramos el prescaler para el clock que impulsa el Counter del PWM
    EPwm1Regs.TBCTL.bit.CLKDIV=0; //divide por 1    -   CLK de PWM de 150MHz (prescaler = 1)
    EPwm1Regs.TBCTL.bit.HSPCLKDIV=0;//divide por 1
    EPwm1Regs.TBCTL.bit.CTRMODE = 2; //up-down counter - Como el ciclo de trabajo es fijo y en realidad se controla con la fase entre ramas, se usa el up-down
    EPwm1Regs.TBCTL.bit.FREE_SOFT=3; // free run


    EPwm1Regs.TBCTL.bit.SYNCOSEL = 1;

    EPwm1Regs.TBPRD = 3750; //20khz -  3750/150MHz = 25us (40kHz)  ==> Es la mitad por usar counter up-down

    EPwm1Regs.AQCTLA.bit.CAU = 2;   //Set at CMP when count up  ----  Caso de onda simétrica con contador up-down de la página 247 del reference manual
    EPwm1Regs.AQCTLA.bit.CAD = 1;   //Clear at CMP when count down

    //EPwm1Regs.AQCTLB.bit.CBU = 2;
    //EPwm1Regs.AQCTLB.bit.CBD = 1;


    //-----Modo de entrada ePmwA
    EPwm1Regs.DBCTL.bit.IN_MODE=0;
    //------Modo salida
    EPwm1Regs.DBCTL.bit.OUT_MODE=3;

    //Active low complementary - por el inversor que tiene antes del IR2110
    EPwm1Regs.DBCTL.bit.POLSEL = 1;//low complementary


    //--------------------200nSeg DeadTime---
    EPwm1Regs.DBFED = 30;
    EPwm1Regs.DBRED = 30;
    //-------------------------------------

    EPwm1Regs.CMPA.half.CMPA = 1875; //50% duty cycle on each colum

    EPwm1Regs.ETSEL.bit.INTSEL = 2;//selecciona generar interrupcion
    EPwm1Regs.ETSEL.bit.INTEN =  1;           //habilita la interrupcion del PWM1
    EPwm1Regs.ETPS.bit.INTPRD =  1;      //ET_1ST = 0x01  dispara la interrupcion

    //Configuraci�n del envio de la se�al de inicio de conversi�n ADC  SOC
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;  //habilitamos SOCA
    EPwm1Regs.ETSEL.bit.SOCASEL = 2; //envio de SOCA en el periodo de PWM
    EPwm1Regs.ETPS.bit.SOCAPRD  = 1; //Envia SOCA en el primer evento de periodo de pwm

}

void Config_ePWM2(void)
{
    //Configuramos el prescaler para el clock que impulsa el Counter del PWM
    EPwm2Regs.TBCTL.bit.CLKDIV=0; //divide por 1    -   CLK de PWM de 150MHz (prescaler = 1)
    EPwm2Regs.TBCTL.bit.HSPCLKDIV=0;//divide por 1
    EPwm2Regs.TBCTL.bit.CTRMODE = 2; //up-down counter - Como el ciclo de trabajo es fijo y en realidad se controla con la fase entre ramas, se usa el up-down
    EPwm2Regs.TBCTL.bit.FREE_SOFT=3; // free run

    EPwm2Regs.TBCTL.bit.PHSEN = 1;
    EPwm2Regs.TBPHS.half.TBPHS = 0;


    EPwm2Regs.TBPRD = 3750; //20khz -  3750/150MHz = 25us (40kHz)  ==> Es la mitad por usar counter up-down

    EPwm2Regs.AQCTLA.bit.CAU = 2;   //Set at CMP when count up  ----  Caso de onda simétrica con contador up-down de la página 247 del reference manual
    EPwm2Regs.AQCTLA.bit.CAD = 1;   //Clear at CMP when count down


    //-----Modo de entrada ePmwA
    EPwm2Regs.DBCTL.bit.IN_MODE=0;
    //------Modo salida
    EPwm2Regs.DBCTL.bit.OUT_MODE=3;

    //Active low complementary - por el inversor que tiene antes del IR2110
    EPwm2Regs.DBCTL.bit.POLSEL = 1;//low complementary


    //--------------------200nSeg DeadTime---
    EPwm2Regs.DBFED = 30;
    EPwm2Regs.DBRED = 30;
    //-------------------------------------

    EPwm2Regs.CMPA.half.CMPA = 1875; //50% duty cycle on each column
}

void Setup_ADC(void)
{
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1; // Secuenciador en modo cascada
    //Probar Continuos mode sampling!!!!!!!
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0; // Modo de ejecuci�n simple(single Run Mode)
    AdcRegs.ADCTRL1.bit.ACQ_PS = 7; // 8 x ADC-Clock
    AdcRegs.ADCTRL1.bit.CPS = 0; //divide por 1

    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1; // ePWM_SOCA trigger
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1; // enable ADC int for seq1
    AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0; // interrupt after every EOS  For register ADCTRL3:

    AdcRegs.ADCTRL3.bit.ADCCLKPS =12 ; //%6 Configura la frecuencia del clock del ADC a 12.5 MHz si sysc es 150Mhz

    AdcRegs.ADCMAXCONV.all = 0; // 1 conversion

    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0; // 1st channel ADCINA0
}



interrupt void epwm1_period_match_isr(void)
{

    if(control == 1){
        PI_REG4(pi_current)
    }
    EPwm1Regs.ETCLR.bit.INT = 1; //borra el flag de interrupcion
    PieCtrlRegs.PIEACK.all = 4;  //reconoce la interupcion de grupo

}
interrupt void ADC_isr(void)
{
    vector[i] = AdcMirror.ADCRESULT0;
    Imed = Ioffset - AdcMirror.ADCRESULT0;

    pi_current.Fbk = K_i*Imed;

    i++;
    if(i>=N_SAMPLES) i=0;

    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;//reseteamos el secuenciador para comenzar de nuevo con el canal ADC_IN0
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1; //borramos la bandera
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;//reconocemos la int del grupo
}





void MiDelay(long k)
{
  do{
      asm(" nop");

  }while(k--);


}
