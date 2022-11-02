/**
 * main.c
 **/

#include "math.h"
#include "DSP2833x_Device.h"
#include "ConfigInit.h"

#define T 0.00005

// Ángulos comunes de desfase entre patas
#define DEG0 0
#define DEG30 625
#define DEG60 1250
#define DEG90 1875
#define DEG120 2500
#define DEG150 3125
#define DEG180 3750

extern void InitSysCtrl(void);
void MyDelay(long);

void main(void)
{
    InitSysCtrl();          //Configura el DSP a 150Mhz, desahabilita el watchdog y habilita todos los clock de perifericos
    DINT;

    ConfigGPIO();
    ConfigEPWM1();
    ConfigEPWM2();

    Uint16 phase = DEG0;       // Cada incremento es 0.048° (6.67ns) de desfase  ==>  0 es 0°, 625 es 30°, 1250 es 60°, 3750 es 180° y 1875 es 90°
    Uint16 flag = 1;

    while(1)
    {
        // Oscila entre fase 0° y fase 180° (ida y vuelta)
        //switch (flag){
        //    case 0 :
        //        EPwm2Regs.TBPHS.half.TBPHS = phase--;
        //       break;
        //    case 1 :
        //        EPwm2Regs.TBPHS.half.TBPHS = phase++;
        //        break;
        //    default :
        //        break;
        //}
        EPwm2Regs.TBPHS.half.TBPHS = phase;
        if (flag){
            phase += DEG30;
        }else{
            phase -= DEG30;
        }
        MyDelay(200000000);
        if(phase == DEG180) flag = 0;
        if(phase == DEG0) flag = 1;
    }
}



void MyDelay(long k)
{
    do
    {
        asm(" nop");
    }while(k--);
}
