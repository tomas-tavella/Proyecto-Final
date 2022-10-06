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
 ****** 													   *******
 *********************************************************************/

//#include "IQmathLib.h"
#include "DSP_define.h"
//#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File


/* Definición de funciones globales */
void user_configuration(void);
void user_task(int, Uint32, int);
extern void configuration(void);
extern void calibrationB(void);

extern void select_State(config);
extern void cfg_PID(void);
/* Definición de funciones de usuario */
interrupt void test(void);
interrupt void refreshW(void);



/* Definición de variables externas */
extern volatile Uint32 time_ms;
extern volatile _iq wm, wind, vTA, w_test;
extern int state_emu,state_cfg;
extern setup workbench;
extern config cfg,cfg1,cfg2,cfg3,cfg4,cfg_PID_default;
/* Definición de variables locales (VER) */
Uint32 ms_user[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
extern volatile int user_enable[13];

/* Funciones globales */

/***********************************************************
 ** Función: user_configuration()                         **
 ** Parámetros: Ninguno                                   **
 ** Descripcion: Configuración de las tareas de usuario   **
 ** a ejecutar. Almacena la función en el vector de       **
 ** interrupciones.           							  **
 ***********************************************************/


void user_configuration(void){
	EALLOW;
	PieVectTable.USER1 = &stop;
	PieVectTable.USER2 = &cfg_select;
	PieVectTable.USER3 = &test;
	PieVectTable.USER4 = &controlLeds;
	//PieVectTable.USER5
	//PieVectTable.USER6
	//PieVectTable.USER7
	//PieVectTable.USER8
	//PieVectTable.USER9
	//PieVectTable.USER10 = &refreshW;
	PieVectTable.USER11 = &serialInterface;
	PieVectTable.USER12 = &blinkLed;
	EDIS;

	/* Inicialización de GPIO de usuario */
	// Init user SW

	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO3 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;

	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO5 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;

	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;

	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO9 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;

	////////////////////////////////////
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


/* Funciones locales */

/***********************************************************
 **                Funciones de Usuario                   **
 **                                                       **
 ***********************************************************/

interrupt void test(){
    EINT;   					// Enable Global interrupt INTM
    ERTM;  						// Enable Global realtime interrupt DBGM
	if (SW2_value==0){
		GpioDataRegs.GPBTOGGLE.bit.GPIO59 = 1;
	//	speed = _IQ(155.0);
	}
	if (SW1_value==0){
		GpioDataRegs.GPBTOGGLE.bit.GPIO61 = 1;
	//	speed = _IQ(155.0);
	}
	if (SW3_value==0){
		GpioDataRegs.GPBTOGGLE.bit.GPIO63 = 1;
	//	speed = _IQ(155.0);
	}
	if (SW4_value==0){
		GpioDataRegs.GPATOGGLE.bit.GPIO1 = 1;
	//	speed = _IQ(155.0);
	}

	return;
}


interrupt void stop(){
    EINT;   					// Enable Global interrupt INTM
    ERTM;  						// Enable Global realtime interrupt DBGM
	if(SW4_value == 0){
		if(state_emu != IDLE && state_emu != CFG){
			STOP_on
			state_emu = STOP;
			state_cfg = UNDEF ;
			CpuTimer0Regs.TCR.bit.TIE = 0;	// Deshabilitdo interrupción de control
			return;
		} else{
			CpuTimer0Regs.TCR.bit.TIE = 0;	// Deshabilitdo interrupción de control
			state_emu = IDLE;
			state_cfg = UNDEF ;
		}
	}
}

interrupt void controlLeds(){
    EINT;   					// Enable Global interrupt INTM
    ERTM;  						// Enable Global realtime interrupt DBGM
	/* Indicadores de estado del sistema */
	//Leds_off
	switch(state_emu){
	case (IDLE):
		LedState1_on
		LedGreen_off
		LedRed_off
		break;
	case (WAIT):
		LedState1_toggle
		LedGreen_off
		LedRed_off
		break;
	case (RUN):
		LedState1_toggle
		LedGreen_on
		LedRed_off
		break;
	case (OP):
		LedState1_off
		LedGreen_toggle
		LedRed_off
		break;
	case (EMU):
		LedGreen_on
		LedState1_off
		LedRed_off
		break;
	case (STOP):
		LedRed_on
		LedState1_off
		LedGreen_off
		break;
	case (CFG):
		LedRed_on
		LedGreen_on
		break;


	}


	/* Indicadores de configuración */
	int a = readConfig;
	GpioDataRegs.GPASET.all = disp_MASK;
switch (a){
	case CFG1:

			GpioDataRegs.GPATOGGLE.all = disp_CFG1;
			break;
	case CFG2:
			GpioDataRegs.GPATOGGLE.all = disp_CFG2;
			break;
	case CFG3:
			GpioDataRegs.GPATOGGLE.all = disp_CFG3;
			break;
	case CFG4:
			GpioDataRegs.GPATOGGLE.all = disp_CFG4;
			break;
	case CALA:
			GpioDataRegs.GPATOGGLE.all = disp_CALA;
			break;
	case CALB:
			GpioDataRegs.GPATOGGLE.all = disp_CALB;
			break;
	case CONFIG:
			GpioDataRegs.GPATOGGLE.all = disp_CONFIG;
			break;
}

if (a == state_cfg){ 					// Indica con DP "." que configuración fue seleccionada
	GpioDataRegs.GPACLEAR.bit.GPIO15 = 1;
	return;
}
GpioDataRegs.GPASET.bit.GPIO15 = 1;

}

interrupt void blinkLed(){
    EINT;   					// Enable Global interrupt INTM
    ERTM;  						// Enable Global realtime interrupt DBGM
GpioDataRegs.GPATOGGLE.bit.GPIO1= 1;

}


interrupt void refreshW(){
    EINT;   					// Enable Global interrupt INTM
    ERTM;  						// Enable Global realtime interrupt DBGM
    _iq temp;

    temp = _IQdiv(workbench.W_sat[1],_IQ(1000));
    wm = w_test;
    if(wm > _IQ(10000))//workbench.W_sat[1])
    	wm = _IQ(0);

}

interrupt void serialInterface(){
    EINT;   					// Enable Global interrupt INTM
    ERTM;  						// Enable Global realtime interrupt DBGM
    float a;
	int receive;
	if(state_cfg == CONFIG){
		return;
	}
	if(SciaRegs.SCIFFRX.bit.RXFFST > 0){
		    receive = SciaRegs.SCIRXBUF.all;

		    switch (receive){
		    		/////////////////////////////////////////////////////////////////////////////
		    		///////////////////////// SELECCIÓN DE ESTADOS //////////////////////////////
					/////////////////////////////////////////////////////////////////////////////
		    		case STATECONFIG:
		    			state_cfg = CONFIG;
	    				scia_xmit(ACK);
	    				configuration();
	    				break;
		    		case STATECFG1:
		    			if (state_emu == WAIT || state_emu == EMU)		// Si se encuentra en estado de espera o emulando, deshabilitar SW
		    				break;

		    			state_cfg = CFG1;
		    			scia_xmit(ACK);
		    			if(state_emu == RUN)
		    				break;
		    			select_State(cfg1);
		    			break;
		    		case STATECFG2:
		    			if (state_emu == WAIT || state_emu == EMU)		// Si se encuentra en estado de espera o emulando, deshabilitar SW
		    				break;
		    			state_cfg = CFG2;
		    			scia_xmit(ACK);
		    			if(state_emu == RUN)
		    				break;
		    			select_State(cfg2);
		    		    break;
		    		case STATECFG3:
		    			if (state_emu == WAIT || state_emu == EMU || state_emu == STOP)		// Si se encuentra en estado de espera o emulando, deshabilitar SW
		    				break;
		    			state_cfg = CFG3;
		    		    scia_xmit(ACK);
		    			if(state_emu == RUN)
		    				break;
		    		    select_State(cfg3);
		    			break;
		    		case STATECFG4:
		    			if (state_emu == WAIT || state_emu == EMU)		// Si se encuentra en estado de espera o emulando, deshabilitar SW
		    				break;
		    			state_cfg = CFG4;
		    			scia_xmit(ACK);
		    			if(state_emu == RUN)
		    				break;
		    			select_State(cfg4);
		    		    break;
		    	    case STATEIDLE:
						state_cfg = UNDEF;
			    		state_emu = IDLE;
			    		CpuTimer0Regs.TCR.bit.TIE = 0;	// Deshabilitdo interrupción de control
			    		user_enable[11] = 1;
					    scia_xmit(ACK);
					    break;
		    	    case STATECALB:
		    	    	state_cfg = CALB;
		    	    	calibrationB();
		    	    	scia_xmit(ACK);
			    		user_enable[11] = 1;
		    	    	break;
				    /////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////

			    	/////////////////////////////////////////////////////////////////////////////
			    	/////////////////////////////// CONTROL DE EMU //////////////////////////////
					/////////////////////////////////////////////////////////////////////////////
		    		case CONTROLFRAME:
		    			if(state_emu == WAIT){
		    				cfg_PID();
		    			}
		    			state_emu = RUN;
	    				scia_xmit(CONTROL_ACK);
	    				break;
		    		case STARTFRAME:
		    			if(state_emu == OP){
			    			state_emu = EMU;
			    			switch (state_cfg){
			    				case CFG1:
			    					select_State(cfg1);
			    					break;
			    				case CFG2:
			    					select_State(cfg2);
			    					break;
			    				case CFG3:
			    					select_State(cfg3);
			    					break;
			    				case CFG4:
			    					select_State(cfg4);
			    					break;
			    			}
		    				scia_xmit(START_ACK);
		    			}
		    			break;
		    		case EMUFRAME:
		    			if(state_emu == EMU){
		    				scia_xmit(START_ACK);
		    			}
	    				break;
		    		case STOPFRAME:
		    			CpuTimer0Regs.TCR.bit.TIE = 0;	// Deshabilito interrupción de control
		    			STOP_on
						state_emu = STOP;
		    			state_cfg = UNDEF;
		    			user_enable[11] = 0;
		    			SciaRegs.SCIFFRX.bit.RXFIFORESET = 0; 	// Reinicio buffer de entrada
		    			delayms(100);
		    			SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
		    			CpuTimer0Regs.TCR.bit.TIE = 0;	// Deshabilito interrupción de control
		    			user_enable[11] = 1;
		    			scia_xmit(STOP_ACK);
		    			break;
		    		case WINDFRAME:						// Notifico modo de emulación
		    			scia_xmit(ACK);
		    			break;
					/////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////



		    		case CFGSELFRAME: 					// Aviso que configuración se encuentra activa
		    			switch (state_cfg){
		    				case CFG1:
				    			scia_xmit(CFG1FRAME);
		    					break;
		    				case CFG2:
				    			scia_xmit(CFG2FRAME);
		    					break;
		    				case CFG3:
				    			scia_xmit(CFG3FRAME);
		    					break;
		    				case CFG4:
				    			scia_xmit(CFG4FRAME);
		    					break;
		    			}
		    			break;

		    		case SPEEDFRAME:
	    				delayms(1);
	    				send32_float(wm);
	    				break;

		    		case SWINDFRAME:			// Recibe y envia: Viento, velocidad, cupla
		    			if (state_emu == EMU){
		    				a = receive32_float();
		    				if (a != INFINITY){
		    					delayms(1);
		    					send32_float(wm);
		    					delayms(1);
		    					send32_float(vTA);
		    					wind = _IQ(a);
		    					break;
		    				}
		    				LedRed_on
							break;
		    			}
		    }
	}
}

