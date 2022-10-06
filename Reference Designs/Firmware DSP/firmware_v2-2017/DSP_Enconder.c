/*********************************************************************
 ****** Funciones para el manejo del Modulo eQEP del DSP2833x  *******
 ****** 													   *******
 ******  Descripcion general: Configuracion del modulo para	   *******
 ******  generacion de interrupcion periodica cada 0.5 ms.     *******
 ******   La velocidad sin procesar se almacena en la variable *******
 ******  global "speed" en cada interrupcion.  			  	   *******
 ****** 													   *******
 ****** 													   *******
 *********************************************************************/



//#include "IQmathLib.h"
//#include "DSP28x_Project.h"
#include "DSP_define.h"

interrupt void eQEP_interrupt(void);
extern unsigned long int volatile speed[filtN];
extern _iq volatile wm, wg, vTA;
void eQEPconfig(void);
void eQEP_calculate(void);
extern volatile config cfg;
extern setup workbench;

extern int state_emu,state_cfg;
extern volatile int sample;
extern int user_enable[13];
/***********************************************************
 ** Funcion: eQEPconfig()                                 **
 ** Parametros: Ninguno.                                  **
 ** Descripcion: Inicializacion general del modulo.       **
 ** 													  **
 ***********************************************************/

void eQEPconfig(){
    InitEQep1Gpio();

    EQep1Regs.QUPRD=75000;       //15000       // Generacion periodica de eventos cada 0.5 mseg.
	EQep1Regs.QDECCTL.bit.QSRC=2;		// QEP quadrature count mode

	EQep1Regs.QEPCTL.bit.FREE_SOFT=2;   // Units unaffected by emulated suspend V
	EQep1Regs.QEPCTL.bit.PCRM=00;		// PCRM=00 mode - QPOSCNT reset on index event
	EQep1Regs.QEPCTL.bit.UTE=1; 		// Unit Timeout Enable
	EQep1Regs.QEPCTL.bit.QCLM=1; 		// Latch on Unit Timeout (interrupt) V
	EQep1Regs.QPOSMAX=0xffffffff;       // Not used
	EQep1Regs.QEPCTL.bit.QPEN=1; 		// QEP enable

	EQep1Regs.QDECCTL.bit.XCR=1; 		// QEP enable

	EQep1Regs.QCAPCTL.bit.UPPS=qep_UPPS;   	// 4 QCLK
	EQep1Regs.QCAPCTL.bit.CCPS=qep_CCPS;    	// 1/16 for CAP clock
	EQep1Regs.QCAPCTL.bit.CEN=1; 		// QEP Capture Enable
	EQep1Regs.QEINT.bit.UTO=1;

	IER |= M_INT5;
	EALLOW;
	/* Encoder OE */
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
	EDIS;
	GpioDataRegs.GPBSET.bit.GPIO34 = 1;
	PieCtrlRegs.PIEIER5.bit.INTx1 = 1;
}

/***********************************************************
** Funcion: eQEP_interrupt()                              **
** Parametros: Ninguno.                                   **
** Descripcion: Cada 0.1ms almacena velocidad sin         **
** procesar en variable global "speed".                   **
** 													      **
************************************************************/

interrupt void eQEP_interrupt(void){
	unsigned long int temp;
	if(sample > (filtN-1))
		sample = 0;


	if(EQep1Regs.QEPSTS.bit.UPEVNT == 1){
		if(EQep1Regs.QEPSTS.bit.COEF==0){
			temp = EQep1Regs.QCPRDLAT;
			if (temp != 0xffff){
				speed[sample]=temp;  // No Capture overflow
				sample++;

			}             // temp1 = t2-t1
		}else{
			speed[sample]=0xFFFF;// Capture overflow, saturate the result
			sample++;
		}
	}

	if(EQep1Regs.QEPSTS.bit.COEF==1){
		speed[sample]=0xFFFF;// Capture overflow, saturate the result
		sample++;
	}


EQep1Regs.QEPSTS.all=0x88;					       // Clear Unit position event flag.
EQep1Regs.QCLR.all = 0xfff;  					   // Clear interrupt.
PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
}

/***********************************************************
** Funcion: eQEP_calculate()                              **
** Parametros: Ninguno.                                   **
** Descripcion: Procesamiento de la velocidad,            **
** devuelve velocidad en Hertz.                           **
** 													      **
************************************************************/

void eQEP_calculate(){
	//w = _IQmpy(128.0,_IQ(speed));
	//w = _IQdiv(_IQ(150000000),w);
	//rwA = _IQdiv(_IQ(1171875.0),_IQ(speed));	// Módulo eQEP CCPS 128
	int i;
	long unsigned int sp = 0;
	for(i=0;i<filtN;i++){
		sp = sp + speed[i];
	}
	sp = (sp>>divN);

	wm = _IQdiv(_IQ(150000000),_IQ(sp));	// Módulo eQEP CCPS 16 9375000

	wm= _IQdiv(wm,workbench.N); 			// Constante de Encoder.

	wm = _IQmpy(wm,_IQ(PI));				// Conversión de [Hz] => [rad/s]
	wm = _IQmpy(wm,_IQ(2));

	//wm = _IQ(150);
	//rwA= _IQ(150);
	if (_IQtoF(wm) > _IQtoF(workbench.W_sat[1])){	// Detención automática del motor
		wm = _IQ(0);
		vTA = _IQ(0);
		STOP_on
		state_emu = STOP;
		state_cfg = UNDEF;
		CpuTimer0Regs.TCR.bit.TIE = 0;	// Deshabilitdo interrupción de control
	}
}

/***********************************************************
 **        Emulador de señal de Encoder                   **
 **                                                       **
 ***********************************************************/


void em_encoder_cfg(){

	   EALLOW;
	   GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 0;
	   GpioCtrlRegs.GPBDIR.bit.GPIO58 = 1;
	   GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0;
	   GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1;
	   EDIS;

}

interrupt void signal_A(void)
{
    EINT;   // Enable Global interrupt INTM
    ERTM;

	EALLOW;
	PieVectTable.USER1 = &signal_B;
	EDIS;
    GpioDataRegs.GPBTOGGLE.bit.GPIO58 = 1;
}

interrupt void signal_B(void)
{
       EINT;   // Enable Global interrupt INTM
       ERTM;

	   EALLOW;
	   PieVectTable.USER1 = &signal_A;
	   EDIS;

	   GpioDataRegs.GPBTOGGLE.bit.GPIO60 = 1;
}
