/**
 * main.c
 **/

#include "math.h"
#include "DSP2833x_Device.h"
#include "ConfigInit.h"

#define T 0.00005

extern void InitSysCtrl(void);

int main(void)
{
    InitSysCtrl();          //Configura el DSP a 150Mhz, desahabilita el watchdog y habilita todos los clock de perifericos
    DINT;

    ConfigGPIO();
    ConfigEPWM1();
    ConfigEPWM2();

	return 0;
}
