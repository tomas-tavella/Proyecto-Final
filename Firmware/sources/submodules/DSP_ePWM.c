//#include "DSP2833x_Device.h"     // Headerfile Include File
//#include "DSP2833x_Examples.h"   // Examples Include File

//#include "math.h"



#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h"

#define DELAY_DB 30                 // 30*6.67ns = 200ns
#define PERIOD_PWM 3600              // 7200/2 = 3750 (por usar modo counter up-down) // Sync con ADC = 20.83kHz
#define DUTY_CYCLE PERIOD_PWM/2     // 50% DC

void ConfigEPWM1(void);
void ConfigEPWM2(void);

__interrupt void epwm1_isr(void);
// Configuraci√≥n de m√≥dulo ePWM1 //
void ConfigEPWM1(void)
{
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_INT = &epwm1_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

    // Time base 150Mhz -> 7500 bit count to 20kHz -> 3750 if up-down count
    EPwm1Regs.TBCTL.bit.CLKDIV = 0;         // divide por 1    -   CLK de PWM de 150MHz (prescaler = 1)
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;      // divide por 1


    EPwm1Regs.TBCTL.bit.FREE_SOFT = 0;      // free run
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 1;       // Configura la seÒal de salida de sincronizaciÛn (envia seÒal cuando en contador esta en 0)

    // Timings
    EPwm1Regs.TBPRD = PERIOD_PWM;           // 20khz -  3750/150MHz = 25us (40kHz)  ==> Es la mitad por usar counter up-down
    EPwm1Regs.CMPA.half.CMPA = DUTY_CYCLE;  // 50% duty cycle

    // Acciones al llegar a CMPA
    EPwm1Regs.AQCTLA.bit.CAU = 2;           //Set at CMP when count up  ----  Caso de onda simetrica con contador up-down de la pag. 247 del reference manual
    EPwm1Regs.AQCTLA.bit.CAD = 1;           //Clear at CMP when count down

    // Seteo de Dead-Band
    EPwm1Regs.DBCTL.bit.IN_MODE = 0;        // ePWM1A es la fuente de delay de rising y falling edge
    EPwm1Regs.DBCTL.bit.OUT_MODE = 3;       // Se aplican delay de Rising Edge y Falling Edge a ePWM1A y ePWM1B respectivamente
    EPwm1Regs.DBCTL.bit.POLSEL = 0;         // Se setea en Active High (fig. 3.30 del Technical Reference Manual)

    EPwm1Regs.DBFED = DELAY_DB;             // Delay de rising edge (ePWM1A) [200ns]
    EPwm1Regs.DBRED = DELAY_DB;             // Delay de falling edge (ePWM1B), igual a RE

    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 1; //funcion PWM1A
    GpioCtrlRegs.GPADIR.bit.GPIO0   = 1; //Salida

    GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 1; //funcion PWM1B
    GpioCtrlRegs.GPADIR.bit.GPIO1   = 1; //Salida
    EDIS;

    EPwm1Regs.TBCTR = 0x0;
    EPwm1Regs.TBCTL.bit.CTRMODE = 2;        // up-down counter - Como el ciclo de trabajo es fijo y en realidad se controla con la fase entre ramas, se usa el up-down
    IFR = 0x0000;
        AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;
        AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;         // Clear INT SEQ1 bit
        AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
        AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
        PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;     // Acknowledge interrupt to PIE
        GpioDataRegs.GPBTOGGLE.bit.GPIO62 = 1;
        AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;         // Clear INT SEQ1 bit
    EPwm1Regs.ETPS.bit.INTPRD =  1;       // ET_1ST = 0x01  dispara la interrupcion
    EPwm1Regs.ETSEL.bit.INTSEL = 1;       // selecciona generar interrupcion
    EPwm1Regs.ETSEL.bit.INTEN =  1;       // habilita la interrupcion del PWM1

}

void ConfigEPWM2(void)
{
    EPwm2Regs.TBCTL.bit.CLKDIV = 0;         // divide por 1    -   CLK de PWM de 150MHz (prescaler = 1)
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;      // divide por 1
    EPwm2Regs.TBCTL.bit.CTRMODE = 2;        // up-down counter - Como el ciclo de trabajo es fijo y en realidad se controla con la fase entre ramas, se usa el up-down
    EPwm2Regs.TBCTL.bit.FREE_SOFT = 3;      // free run
    EPwm2Regs.TBCTL.bit.PHSEN = 1;          // Hablitia la sincronizacion por la entrada SYNC (proveniente del ePWM1)

    // Timings
    EPwm2Regs.TBPRD = PERIOD_PWM;           // 20khz -  3750/150MHz = 25us (40kHz)  ==> Es la mitad por usar counter up-down
    EPwm2Regs.CMPA.half.CMPA = DUTY_CYCLE;  // 50% duty cycle
    EPwm2Regs.TBPHS.half.TBPHS = 0;         // Fase inicial 0

    // Acciones al llegar a CMPA
    EPwm2Regs.AQCTLA.bit.CAU = 2;           // Set at CMP when count up  ----  Caso de onda sim√©trica con contador up-down de la p√°gina 247 del reference manual
    EPwm2Regs.AQCTLA.bit.CAD = 1;           // Clear at CMP when count down

    // Seteo de Dead-Band
    EPwm2Regs.DBCTL.bit.IN_MODE = 0;        // ePWM2A es la fuente de delay de rising y falling edge
    EPwm2Regs.DBCTL.bit.OUT_MODE = 3;       // Se aplican delay de Rising Edge y Falling Edge a ePWM2A y ePWM2B respectivamente
    EPwm2Regs.DBCTL.bit.POLSEL = 0;         // Se setea en Active High (fig. 3.30 del Technical Reference Manual)

    EPwm2Regs.DBFED = DELAY_DB;             // Delay de rising edge (ePWM2A) [200ns]
    EPwm2Regs.DBRED = DELAY_DB;             // Delay de falling edge (ePWM2B), igual a RED

    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 1; //funcion PWM1A
    GpioCtrlRegs.GPADIR.bit.GPIO2   = 1; //Salida

    GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 1; //funcion PWM1B
    GpioCtrlRegs.GPADIR.bit.GPIO3   = 1; //Salida
    EDIS;

    EPwm2Regs.TBPHS.half.TBPHS = 0;
}

__interrupt void epwm1_isr(void){

    //
    // Clear INT flag for this timer
    //
    GpioDataRegs.GPBTOGGLE.bit.GPIO60 = 1;

    EPwm1Regs.ETCLR.bit.INT = 1;
    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
