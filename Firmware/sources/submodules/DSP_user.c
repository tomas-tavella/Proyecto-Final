/*********************************************************************
 ******   Funciones para la ejecución de tareas de usuario     *******
 ****** 													   *******
 ******  Descripcion general: Ejecución de tareas de usuario   *******
 ******  de baja latencia, de forma periódica a través de 	   *******
 ******  llamados a interrupciones. La tarea a ejecutar 	   *******
 ******  se almacena en el vector de interrupción (Variable    *******
 ******  PieVectTable.USERX), con un total de 12 tareas        *******
 ******  de usuario posible.                           	  	   *******
 ****** 													   *******
 ******            EVITAR EJECUTAR TAREAS CRITICAS             *******
 *********************************************************************/

#include <Includes/TMC1100/headers/TMC1100.h>
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "LM5056.h"

/* Definición de funciones globales */
void user_configuration(void);
void user_task(int, Uint32, int);
void ConfigGPIO(void);

/* Definición de funciones de usuario */
interrupt void powerMonitor(void);
interrupt void blinkLed(void);
interrupt void serialInterface(void);
interrupt void setEPWMPhase(void);

/* Definición de variables externas */
extern volatile Uint32 time_ms;
extern struct LM5056_avg_measures avg_measures;
extern struct TMC1100_measures TMC1100;

/* Definición de funciones externas */
extern void scia_msg(char*);
extern void floattoa(float, char *, int);
extern void LM5056_measures(void);
extern void LM5056_Read_avg_block(void);
extern void TMC1100_avg_measures(void);

/* Definición de variables globales */
Uint32 ms_user[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
volatile int user_enable[12];

/* User local variables */
Uint16 phase = 0;       // Cada incremento es 0.048 (6.67ns) de desfase




/* Funciones globales */

/***********************************************************
 ** Función: user_configuration()                         **
 ** Parámetros: Ninguno                                   **
 ** Descripcion: Configuración de las tareas de usuario   **
 ** a ejecutar. Almacena la función en el vector de       **
 ** interrupciones.           							  **
 ***********************************************************/


void user_configuration(void){

    /* Tareas de usuario: USER1 +prio -> USER12 -prio */
	EALLOW;
	PieVectTable.USER1 = &powerMonitor;
	//PieVectTable.USER2
	//PieVectTable.USER3
	//PieVectTable.USER4
	//PieVectTable.USER5
	//PieVectTable.USER6
	//PieVectTable.USER7
	//PieVectTable.USER8
	//PieVectTable.USER9
	PieVectTable.USER10 = &setEPWMPhase;
	PieVectTable.USER11 = &serialInterface;
	PieVectTable.USER12 = &blinkLed;
	EDIS;

	/* Inicialización de GPIO de usuario - SWs & Leds */
	ConfigGPIO();

	////////////////////////////////////
}

void ConfigGPIO(void)
{
   EALLOW;      // Permite escritura de registros protegidos

   // LEDs de proposito general

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

   // Pulsadores de proposito general

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
   GpioDataRegs.GPACLEAR.bit.GPIO13 = 1;

   GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;
   GpioCtrlRegs.GPADIR.bit.GPIO14 = 0;
   GpioDataRegs.GPACLEAR.bit.GPIO14 = 1;

   GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;
   GpioCtrlRegs.GPBDIR.bit.GPIO58 = 0;
   GpioDataRegs.GPBCLEAR.bit.GPIO58 = 1;

   GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0; // LED GP
   GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1;  // Salida
   GpioCtrlRegs.GPBPUD.bit.GPIO60 = 1;  // Pull up desactivado
   GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1;

   GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 0; // LED GP
   GpioCtrlRegs.GPBDIR.bit.GPIO62 = 1;  // Salida
   GpioCtrlRegs.GPBPUD.bit.GPIO62 = 1;  // Pull up desactivado
   GpioDataRegs.GPBCLEAR.bit.GPIO62 = 1;

   GpioCtrlRegs.GPCMUX2.bit.GPIO85 = 0;
   GpioCtrlRegs.GPCDIR.bit.GPIO85 = 0;
   GpioDataRegs.GPCCLEAR.bit.GPIO85 = 1;

   EDIS;        // Saca el EALLOW
}


/***********************************************************
 ** Función: user_task()                                  **
 ** Parámetros: user = Número de tarea (1 a 12).          **
 ** 			ms = Periódo de ejecución de tarea.       **
 ** Descripcion: Llamado a tarea de usuario, cada         **
 **  "ms" milisegundos.									  **
 ***********************************************************/


void user_task(int user, Uint32 ms, int enable){
if (enable == 0)
	return;

if (time_ms-ms_user[user-1] >= ms){
	switch (user){
	case 1:
		asm("        TRAP #20");
		break;
	case 2:
		asm("        TRAP #21");
		break;
	case 3:
		asm("        TRAP #22");
		break;
	case 4:
		asm("        TRAP #23");
		break;
	case 5:
		asm("        TRAP #24");
		break;
	case 6:
		asm("        TRAP #25");
		break;
	case 7:
		asm("        TRAP #26");
		break;
	case 8:
		asm("        TRAP #27");
		break;
	case 9:
		asm("        TRAP #28");
		break;
	case 10:
		asm("        TRAP #29");
		break;
	case 11:
		asm("        TRAP #30");
		break;
	case 12:
		asm("        TRAP #31");
		break;
	}

	ms_user[user-1] = time_ms;
}
}


/* Interrupciones de usuario */

/***********************************************************
 **                Funciones de Usuario                   **
 **                                                       **
 ***********************************************************/

// USER 1
interrupt void powerMonitor(){
    EINT;
    ERTM;

    // Call Average Block read function
    LM5056_Read_avg_block();
}

// USER 10
interrupt void setEPWMPhase(){
    if ( GpioDataRegs.GPADAT.bit.GPIO5 == 0){
        if(phase >= 200){
            phase -= 200;
        }else{
            phase = 0;
        }
        EPwm2Regs.TBPHS.half.TBPHS = phase;
    }
    if ( GpioDataRegs.GPADAT.bit.GPIO7 == 0){
        if (phase <= (3600-200)){
            phase += 200;
        }else{
            phase = 3600;
        }
        EPwm2Regs.TBPHS.half.TBPHS = phase;
    }

}

// USER 11
interrupt void serialInterface(){
    EINT;
    ERTM;
    char word[50];
    // Convert to current, voltage and power measures
    LM5056_measures();
    TMC1100_avg_measures();

    scia_msg("************ POWER MONITOR ************\r\n\r\n");
    scia_msg("La tensión de entrada es: ");
    floattoa(avg_measures.AVG_VIN,&word[0],3);
    scia_msg(word); scia_msg(" V.\r\n");

    scia_msg("La corriente de entrada es: ");
    floattoa(abs(avg_measures.AVG_IIN),&word[0],3);
    scia_msg(word); scia_msg(" A.\r\n");

    scia_msg("La Potencia de entrada es: ");
    floattoa(avg_measures.AVG_PIN,&word[0],3);
    scia_msg(word); scia_msg(" W.\r\n");

    scia_msg("La tension de salida es: ");
    floattoa(avg_measures.AVG_VOUT,&word[0],3);
    scia_msg(word); scia_msg(" V.\r\n");

    scia_msg("La corriente de salida es: ");
    floattoa(TMC1100.avg_current,&word[0],3);
    scia_msg(word); scia_msg(" A.\r\n");

    scia_msg("***************************************\r\n\r\n");
}

// USER 12
interrupt void blinkLed(){
    EINT;   					// Enable Global interrupt INTM
    ERTM;  						// Enable Global realtime interrupt DBGM
    GpioDataRegs.GPBTOGGLE.bit.GPIO63 = 1;
}






