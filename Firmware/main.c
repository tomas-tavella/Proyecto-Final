/**
 * main.c
 **/

#include "math.h"
#include "DSP2833x_Device.h"
#include "ConfigInit.h"

#define T 0.00005

extern void InitSysCtrl(void);
void MyDelay(long);

void main(void)
{
    InitSysCtrl();          //Configura el DSP a 150Mhz, desahabilita el watchdog y habilita todos los clock de perifericos
    DINT;

    ConfigGPIO();
    ConfigEPWM1();
    ConfigEPWM2();

    Uint16 phase = 0;       // Cada incremento es 0.048° (6.67ns) de desfase  ==>  7500 es 360°, 3750 es 180° y 1875 es 90°
    Uint16 flag = 1;

    while(1)
    {
        // Oscila entre fase 0° y fase 180° (ida y vuelta)
        switch (flag){
            case 0 :
                EPwm2Regs.TBPHS.half.TBPHS = phase--;
                break;
            case 1 :
                EPwm2Regs.TBPHS.half.TBPHS = phase++;
                break;
            default :
                break;
        }
        //EPwm2Regs.TBPHS.half.TBPHS = phase;
        MyDelay(100000);
        if(phase > 3750) flag = 0;
        if(phase < 1) flag = 1;
    }
}



void MyDelay(long k)
{
    do
    {
        asm(" nop");
    }while(k--);
}
