// ========================================================================== //
//              Funciones de Configuración de DSP y Periféricos               //
// ========================================================================== //

#include "DSP2833x_Device.h"

#define DELAY_DB 30                 // 30*6.67ns = 200ns
#define PERIOD_PWM 3750             // 7500/2 = 3750 (por usar modo counter up-down)
#define DUTY_CYCLE PERIOD_PWM/2     // 50% DC


// Configuración de pines GPIO //
void ConfigGPIO(void)
{
   EALLOW;      // Permite escritura de registros protegidos

   // Puertos PWM

   GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 1; //funcion PWM1A
   GpioCtrlRegs.GPADIR.bit.GPIO0   = 1; //Salida

   GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 1; //funcion PWM1B
   GpioCtrlRegs.GPADIR.bit.GPIO1   = 1; //Salida

   GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 1; //funcion PWM2A
   GpioCtrlRegs.GPADIR.bit.GPIO2  = 1; //Salida

   GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 1; //funcion PWM2B
   GpioCtrlRegs.GPADIR.bit.GPIO3   = 1; //Salida

   // Puertos I2C

   GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;     // Datos
   GpioCtrlRegs.GPBPUD.bit.GPIO32 = 1;      // Desactivar pull-up
   GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;    // Input qualification asincrónica (Sección 11.2 del Technical Reference Manual)
   GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;     // Clock
   GpioCtrlRegs.GPBPUD.bit.GPIO33 = 1;      // Desactivar pull-up
   GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;

   // LEDs de propósito general

   GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0; // LED GP
   GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1;  // Salida
   GpioCtrlRegs.GPBPUD.bit.GPIO49 = 1;  // Pull up desactivado

   GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 0; // LED GP
   GpioCtrlRegs.GPBDIR.bit.GPIO59 = 1;  // Salida
   GpioCtrlRegs.GPBPUD.bit.GPIO59 = 1;  // Pull up desactivado

   GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0; // LED GP
   GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;  // Salida
   GpioCtrlRegs.GPBPUD.bit.GPIO61 = 1;  // Pull up desactivado

   GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 0; // LED GP
   GpioCtrlRegs.GPBDIR.bit.GPIO63 = 1;  // Salida
   GpioCtrlRegs.GPBPUD.bit.GPIO63 = 1;  // Pull up desactivado

   // Pulsadores de propósito general

   GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0; // Pulsador GP
   GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;  // Entrada
   GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;  // Pull up desactivado

   GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0; // Pulsador GP
   GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;  // Entrada
   GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;  // Pull up desactivado

   GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0; // Pulsador GP
   GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;  // Entrada
   GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;  // Pull up desactivado

   GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0; // Pulsador GP
   GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;  // Entrada
   GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;  // Pull up desactivado

   // Puertos Header GPIO

   GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO13 = 0;

   GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;

   GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;
   GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0;

   GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0;
   GpioCtrlRegs.GPBDIR.bit.GPIO60 = 0;

   GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 0;
   GpioCtrlRegs.GPBDIR.bit.GPIO62 = 0;

   GpioCtrlRegs.GPCMUX2.bit.GPIO85 = 0;
   GpioCtrlRegs.GPCDIR.bit.GPIO85 = 0;

   EDIS;        // Saca el EALLOW
}

// Configuración de módulo ePWM1 //
void ConfigEPWM1(void)
{
    EPwm1Regs.TBCTL.bit.CLKDIV = 0;         // divide por 1    -   CLK de PWM de 150MHz (prescaler = 1)
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;      // divide por 1
    EPwm1Regs.TBCTL.bit.CTRMODE = 2;        // up-down counter - Como el ciclo de trabajo es fijo y en realidad se controla con la fase entre ramas, se usa el up-down
    EPwm1Regs.TBCTL.bit.FREE_SOFT = 3;      // free run
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 1;       // Configura la señal de salida de sincronización (envia señal cuando en contador está en 0)

    // Timings
    EPwm1Regs.TBPRD = PERIOD_PWM;           // 20khz -  3750/150MHz = 25us (40kHz)  ==> Es la mitad por usar counter up-down
    EPwm1Regs.CMPA.half.CMPA = DUTY_CYCLE;  // 50% duty cycle

    // Acciones al llegar a CMPA
    EPwm1Regs.AQCTLA.bit.CAU = 2;           //Set at CMP when count up  ----  Caso de onda simétrica con contador up-down de la página 247 del reference manual
    EPwm1Regs.AQCTLA.bit.CAD = 1;           //Clear at CMP when count down

    // Seteo de Dead-Band
    EPwm1Regs.DBCTL.bit.IN_MODE = 0;        // ePWM1A es la fuente de delay de rising y falling edge
    EPwm1Regs.DBCTL.bit.OUT_MODE = 3;       // Se aplican delay de Rising Edge y Falling Edge a ePWM1A y ePWM1B respectivamente
    EPwm1Regs.DBCTL.bit.POLSEL = 0;         // Se setea en Active High (fig. 3.30 del Technical Reference Manual)

    EPwm1Regs.DBFED = DELAY_DB;             // Delay de rising edge (ePWM1A) [200ns]
    EPwm1Regs.DBRED = DELAY_DB;             // Delay de falling edge (ePWM1B), igual a RE

    //EPwm1Regs.ETSEL.bit.INTSEL = 2;       // selecciona generar interrupcion
    //EPwm1Regs.ETSEL.bit.INTEN =  1;       // habilita la interrupcion del PWM1
    //EPwm1Regs.ETPS.bit.INTPRD =  1;       // ET_1ST = 0x01  dispara la interrupcion

    //Configuración del envio de la señal de inicio de conversión ADC  SOC
    //EPwm1Regs.ETSEL.bit.SOCAEN  = 1;      // habilitamos SOCA
    //EPwm1Regs.ETSEL.bit.SOCASEL = 2;      // envio de SOCA en el periodo de PWM
    //EPwm1Regs.ETPS.bit.SOCAPRD  = 1;      // Envia SOCA en el primer evento de periodo de pwm
}

// Configuración de módulo ePWM2 //
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
    EPwm2Regs.AQCTLA.bit.CAU = 2;           // Set at CMP when count up  ----  Caso de onda simétrica con contador up-down de la página 247 del reference manual
    EPwm2Regs.AQCTLA.bit.CAD = 1;           // Clear at CMP when count down

    // Seteo de Dead-Band
    EPwm2Regs.DBCTL.bit.IN_MODE = 0;        // ePWM2A es la fuente de delay de rising y falling edge
    EPwm2Regs.DBCTL.bit.OUT_MODE = 3;       // Se aplican delay de Rising Edge y Falling Edge a ePWM2A y ePWM2B respectivamente
    EPwm2Regs.DBCTL.bit.POLSEL = 0;         // Se setea en Active High (fig. 3.30 del Technical Reference Manual)

    EPwm2Regs.DBFED = DELAY_DB;             // Delay de rising edge (ePWM2A) [200ns]
    EPwm2Regs.DBRED = DELAY_DB;             // Delay de falling edge (ePWM2B), igual a RED
}
