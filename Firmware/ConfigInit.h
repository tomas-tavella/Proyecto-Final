// ========================================================================== //
//              Funciones de Configuración de DSP y Periféricos               //
// ========================================================================== //

#include "DSP2833x_Device.h"

// Configuración de pines GPIO //
void ConfigGPIO(void)
{
   EALLOW;
   //GpioCtrlRegs.GPBMUX1.bit.GPIO32= 0; //funcion GPIO - Este es el puerto I2C, no hay que configurarlo como GPIO (GpioCtrlRegs.GPBMUX1.bit.GPIO32= 1)
   //GpioCtrlRegs.GPBDIR.bit.GPIO32  = 1; //Salida

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

   //Configuracion de pines GPIO00-GPIO03  como PWM1A, 1B, 2A y 2B

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

// Configuración de módulo ePWM1 //
void ConfigEPWM1(void)
{
    //Configuramos el prescaler para el clock que impulsa el Counter del PWM
    EPwm1Regs.TBCTL.bit.CLKDIV=0; //divide por 1    -   CLK de PWM de 150MHz (prescaler = 1)
    EPwm1Regs.TBCTL.bit.HSPCLKDIV=0;//divide por 1
    EPwm1Regs.TBCTL.bit.CTRMODE = 2; //up-down counter - Como el ciclo de trabajo es fijo y en realidad se controla con la fase entre ramas, se usa el up-down
    EPwm1Regs.TBCTL.bit.FREE_SOFT=3; // free run


    EPwm1Regs.TBCTL.bit.SYNCOSEL = 1;

    EPwm1Regs.TBPRD = 3750; //20khz -  3750/150MHz = 25us (40kHz)  ==> Es la mitad por usar counter up-down

    // ePWM1A ===> PWM1
    EPwm1Regs.AQCTLA.bit.CAU = 2;   //Set at CMP when count up  ----  Caso de onda simétrica con contador up-down de la página 247 del reference manual
    EPwm1Regs.AQCTLA.bit.CAD = 1;   //Clear at CMP when count down

    // ePWM1B ===> /PWM3
    EPwm1Regs.AQCTLB.bit.CBU = 2;   // Igual que ePWM1A, porque el optoacoplador niega la señal PWM de abajo
    EPwm1Regs.AQCTLB.bit.CBD = 1;


    //-----Modo de entrada ePmwA
    //EPwm1Regs.DBCTL.bit.IN_MODE=0;
    //------Modo salida
    //EPwm1Regs.DBCTL.bit.OUT_MODE=3;

    //Active low complementary - por el inversor que tiene antes del IR2110
    //EPwm1Regs.DBCTL.bit.POLSEL = 1;//low complementary


    //--------------------200nSeg DeadTime---
    //EPwm1Regs.DBFED = 30;                   // DBFED y DBRED son registros de delay de dead-band
    //EPwm1Regs.DBRED = 30;                   // Si cuenta hasta 30, el dead-band es 30/150MHz = 200 ns
    //-------------------------------------

    EPwm1Regs.CMPA.half.CMPA = 1875; //50% duty cycle

    //EPwm1Regs.ETSEL.bit.INTSEL = 2;//selecciona generar interrupcion
    //EPwm1Regs.ETSEL.bit.INTEN =  1;           //habilita la interrupcion del PWM1
    //EPwm1Regs.ETPS.bit.INTPRD =  1;      //ET_1ST = 0x01  dispara la interrupcion

    //Configuraci�n del envio de la se�al de inicio de conversi�n ADC  SOC
    //EPwm1Regs.ETSEL.bit.SOCAEN  = 1;  //habilitamos SOCA
    //EPwm1Regs.ETSEL.bit.SOCASEL = 2; //envio de SOCA en el periodo de PWM
    //EPwm1Regs.ETPS.bit.SOCAPRD  = 1; //Envia SOCA en el primer evento de periodo de pwm

}

// Configuración de módulo ePWM2 //
void ConfigEPWM2(void)
{
    //Configuramos el prescaler para el clock que impulsa el Counter del PWM
    EPwm2Regs.TBCTL.bit.CLKDIV=0; //divide por 1    -   CLK de PWM de 150MHz (prescaler = 1)
    EPwm2Regs.TBCTL.bit.HSPCLKDIV=0;//divide por 1
    EPwm2Regs.TBCTL.bit.CTRMODE = 2; //up-down counter - Como el ciclo de trabajo es fijo y en realidad se controla con la fase entre ramas, se usa el up-down
    EPwm2Regs.TBCTL.bit.FREE_SOFT=3; // free run

    EPwm2Regs.TBCTL.bit.PHSEN = 1;
    EPwm2Regs.TBPHS.half.TBPHS = 0;


    EPwm2Regs.TBPRD = 3750; //20khz -  3750/150MHz = 25us (40kHz)  ==> Es la mitad por usar counter up-down

    // ePWM2A ===> /PWM4
    EPwm2Regs.AQCTLA.bit.CAU = 2;   //Set at CMP when count up  ----  Caso de onda simétrica con contador up-down de la página 247 del reference manual
    EPwm2Regs.AQCTLA.bit.CAD = 1;   //Clear at CMP when count down

    // ePWM2B ===> PWM2
    EPwm1Regs.AQCTLB.bit.CBU = 2;   // Igual que ePWM2A, porque el optoacoplador niega la señal PWM de abajo
    EPwm1Regs.AQCTLB.bit.CBD = 1;

    //-----Modo de entrada ePmwA
    //EPwm2Regs.DBCTL.bit.IN_MODE=0;
    //------Modo salida
    //EPwm2Regs.DBCTL.bit.OUT_MODE=3;

    //Active low complementary - por el inversor que tiene antes del IR2110
    //EPwm2Regs.DBCTL.bit.POLSEL = 1;//low complementary


    //--------------------200nSeg DeadTime---
    //EPwm2Regs.DBFED = 30;                   // DBFED y DBRED son registros de delay de dead-band
    //EPwm2Regs.DBRED = 30;                   // Si cuenta hasta 30, el dead-band es 30/150MHz = 200 ns
    //-------------------------------------

    EPwm2Regs.CMPA.half.CMPA = 1875; //50% duty cycle
}
