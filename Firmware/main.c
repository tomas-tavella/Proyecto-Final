/**
 * main.c
 **/

#include "math.h"
#include "DSP2833x_Device.h"
#include "ConfigInit.h"

#define T 0.00005

// Ángulos comunes de desfase entre patas
#define DEG5 188                   // 5% del máximo desfasaje (9.024°)

extern void InitSysCtrl(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
void MyDelay(long);
void IndicatePhase(void);

__interrupt void xint1_isr(void);
__interrupt void xint2_isr(void);

Uint16 phase = 3750;       // Cada incremento es 0.048° (6.67ns) de desfase  ==>  0 es 180°, 625 es 150°, 1250 es 120°, 3750 es 0° y 1875 es 90°

void main(void)
{
    InitSysCtrl();          //Configura el DSP a 150Mhz, desahabilita el watchdog y habilita todos los clock de perifericos
    DINT;

    InitPieCtrl();
    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    //EALLOW;  // This is needed to write to EALLOW protected registers
    //PieVectTable.XINT1 = &xint1_isr;
    //PieVectTable.XINT2 = &xint2_isr;
    //EDIS;   // This is needed to disable write to EALLOW protected registers

    ConfigGPIO();
    ConfigEPWM1();
    ConfigEPWM2();
    ConfigInterrupt();
    ConfigLPM();

    EPwm2Regs.TBPHS.half.TBPHS = phase;

    while(1)
    {
        asm(" IDLE");          // Activa el Low Power Mode (LPM) configurado en LPMCR0 (Idle en este caso)
    }
}

void MyDelay(long k)
{
    do
    {
        asm(" nop");
    }while(k--);

    return;
}


// Indica el procentaje de desfase entre patas con los 4 leds (Todos apagados == Desfase completo)
void IndicatePhase(void)
{
    if (phase >= 3750){
        GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO63 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;
    }

    if (phase >= 2813  && phase < 3750){
        GpioDataRegs.GPBSET.bit.GPIO49 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO63 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;
    }

    if (phase >= 1875 && phase < 2813){
        GpioDataRegs.GPBSET.bit.GPIO49 = 1;
        GpioDataRegs.GPBSET.bit.GPIO63 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;
    }

    if (phase >= 938 && phase < 1875){
        GpioDataRegs.GPBSET.bit.GPIO49 = 1;
        GpioDataRegs.GPBSET.bit.GPIO63 = 1;
        GpioDataRegs.GPBSET.bit.GPIO61 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;
    }

    if (phase < 938){
        GpioDataRegs.GPBSET.bit.GPIO49 = 1;
        GpioDataRegs.GPBSET.bit.GPIO63 = 1;
        GpioDataRegs.GPBSET.bit.GPIO61 = 1;
        GpioDataRegs.GPBSET.bit.GPIO59 = 1;
    }

    return;
}

// --------------------------------------------------------------------------------------- //
// -------------------------------- Interrupt Subroutines -------------------------------- //
// --------------------------------------------------------------------------------------- //

__interrupt void xint1_isr(void)
{
    phase -= DEG5;
    EPwm2Regs.TBPHS.half.TBPHS = phase;

    IndicatePhase();

    // Habilita de vuelta los interrupts del Grupo 1 PIE
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    return;
}

__interrupt void xint2_isr(void)
{
    phase += DEG5;
    if (phase > 3750); phase = 3750;
    EPwm2Regs.TBPHS.half.TBPHS = phase;

    IndicatePhase();

    // Habilita de vuelta los interrupts del Grupo 1 PIE
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    return;
}
