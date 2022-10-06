/*********************************************************************
 ****** Funciones para el manejo del Modulo Timer del DSP2833x *******
 ****** 													   *******
 ******  Descripcion general: Configuracion del modulo para	   *******
 ******  generacion de interrupcion periodica cada X ms.       *******
 ******                                     			  	   *******
 *********************************************************************/



//#include "DSP28x_Project.h"
#include "DSP_define.h"

void timerConfig(int, int);
void delayms(Uint32);
extern volatile Uint32 time_ms;

/***********************************************************
** Funcion: timerConfig()                                 **
** Parametros: NumTimer => 0 o 1.						  **
** 			   ms 		=> Tiempo en interrupción en ms.  **
** Descripcion: Configuracion general de los modulos      **
** Timer 0 y Timer 1.                                     **
** 	Módulo Timer 0 es utilizado como contador de tiempo,  **
** cada 1 ms.                                             **
** 	Módulo Timer 1 es utilizado para las tareas de control**
** específicas.                                           **
** 													      **
************************************************************/


void timerConfig(int numTimer, int ms){
	   // Configuración de Timer0 y Timer1
	   IFR = 0x0000;
	   if (numTimer == 0){
		   CpuTimer0Regs.TCR.bit.TSS = 1;      // 1 = Stop timer, 0 = Start/Restart Timer

		   ConfigCpuTimer(&CpuTimer0, 150, 1000.0*ms);


		   CpuTimer0Regs.TCR.all = 0x4001;
		   CpuTimer0Regs.TCR.bit.TIE = 0;	// Deshabilitdo interrupción de control

	   }
	   if (numTimer == 1){
		   ConfigCpuTimer(&CpuTimer1, 150, 1000.0*ms); 		// Interrupción Timer1 cada ms [ms]

		   CpuTimer1Regs.TCR.all = 0x4001;
		   // Habilitación de las interrupciones principales 13 (Timer1)
		   IER |= M_INT13;

	   }
	    // Enable global Interrupts and higher priority real-time debug events:
	    EINT;   					// Enable Global interrupt INTM
	    ERTM;  						// Enable Global realtime interrupt DBGM
}


/* Contador de milisegundos */

void delayms(Uint32 ms){
	Uint32 timenow = time_ms;

    EINT;   					// Enable Global interrupt INTM
    ERTM;  						// Enable Global realtime interrupt DBGM
	while(time_ms - timenow < ms){}
}

interrupt void timer1_interrupt(void){
	time_ms++;
}

