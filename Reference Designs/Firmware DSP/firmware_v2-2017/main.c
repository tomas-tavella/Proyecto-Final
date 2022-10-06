//#include "IQmathLib.h"
//#include "C28x_FPU_FastRTS.h"
//#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "DSP_define.h"


/* Declaración de variables globales */

// Variables de control
unsigned long int volatile speed[filtN]= {0};
_iq volatile wm = _IQ(0), wind=_IQ(0), vTA = _IQ(0), w_test = _IQ(100);
_iq pitch=_IQ(0);

_iq u_ant;

// Variables de tiempo
volatile Uint32 time_ms=0;

// Variables de configuración
volatile config cfg;
config cfg1,cfg2,cfg3,cfg4,cfg_PID_default,cfg_Siegfried_default,cfg_Polynomial_default;
volatile setup workbench;

// Variables de estado del sistema
int state_emu=IDLE,state_cfg = UNDEF;

volatile int sample = 0;
volatile int user_enable[13] = {0,0,0,0,0,0,0,0,0,0,1,0,0};


void main(void)
{
// This example function is found in the DSP2833x_SysCtrl.c file.

    InitSysCtrl();

   DINT;

   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

   InitSpiaGpio();
   InitPieVectTable();

#if TEST==1

while(1){
    user_task(11,500,1);

}
#else

   InitCpuTimers();

   EALLOW;
    PieVectTable.XINT13 = &timer1_interrupt;
    PieVectTable.EQEP1_INT= &eQEP_interrupt;
   EDIS;

   // Habilitación de las interrupciones principales 1 (Timer0)
   IER |= M_INT1;


   // Configuración de int. TINT0 en PIE: Grupo 1 int. 7
   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

   /* Configuracion de perifericos */

   scia_initialize();
   timerConfig(1,1);
   eQEPconfig();                // Configuración del Módulo eQEP (Encoder)
   //GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; //Deshabilita txb encoder
   cfg_init();                  // Inicialización de las configuraciones del Emulador
   //em_encoder_cfg();          // Configuración del Emulador de señales de Encoder
   user_configuration();        // Configuración de funciones de usuario
   dac_init();


   EINT;                    // Enable Global interrupt INTM
   ERTM;
   // Enable global Interrupts and higher priority real-time debug events:


    CpuTimer0Regs.TCR.bit.TIE = 0;  // Deshabilitdo interrupción de control

    ///
    user_enable[11] = 1;

    for(;;)
    {
        //Enable global Interrupts and higher priority real-time debug events:
        user_task(1,200,1);
        user_task(2,500,1);
        user_task(4,500,1);
        user_task(11,10,user_enable[11]);
        user_task(12,1000,1);
        //user_task(10,1,0);
        //send_siegfried(cfg_Siegfried_default.model.Siegfried.cfg);

    }
#endif
}
