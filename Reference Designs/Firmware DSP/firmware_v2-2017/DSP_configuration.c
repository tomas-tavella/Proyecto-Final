//#include "DSP28x_Project.h"
//#include "IQmathLib.h"
#include "DSP_define.h"

/* Macros (Revisar) */
#define launch(A) {EALLOW; 					\
				   PieVectTable.TINT0 = &A;	\
				   EDIS;}

/* Definición de variables externas */
extern volatile _iq wind;
extern config cfg,cfg1,cfg2,cfg3,cfg4;
extern config cfg_Siegfried_default,cfg_PID_default,cfg_Polynomial_default;
extern volatile setup workbench;
extern int state_emu, state_cfg;
extern volatile int user_enable[13];
extern _iq u_ant;

/* Definición de funciones externas */
extern void eQEP_calculate(void);
extern void timerConfig(int,int);
extern interrupt void PID_interrupt(void);

/* Definición de funciones locales */
void select_State(config);
void initControl(config);
void cfg_Siegfried(config);
void cfg_Polynomial(config);
void cfg_PID();
void defaultmodel_init(void);
void ledinit(void);
void DIP4init(void);
void displayinit(void);

config receiveconfig(void);
void sendconfig (config cfgx);
void configuration(void);
void calibrationB(void);
void calibrationA(void);
/* Funciones globales */

/***********************************************************
** Funcion: cfg_init()                                    **
** Parametros: Ninguno.                                   **
** Descripcion: Configuración inicial de los GPIOs        **
** de configuración. Definición de configuraciones        **
** por default.                                            **
** 													      **
************************************************************/

void cfg_init(){

	   /* Inicialización de las configuraciones por default */
	   defaultmodel_init();

	   /* Inicialización del display 7 segs */
	   displayinit();

	   /* Inicialización de sw DIP */
	   DIP4init();

	   /* Incialización de leds de estados */
	   ledinit();

}

/***********************************************************
** Funcion: cfg_select()                                  **
** Parametros: Ninguno.                                   **
** Descripcion: Interrupción asignada al SW1 de usuario.  **
**  Al activarse el SW carga la configuración 		      **
**  correspondiente según la configuración SW DIP		  **
**  seleccionada.                                         **
** 													      **
************************************************************/

interrupt void cfg_select(void){
    //int last_state;
	// Enable global Interrupts and higher priority real-time debug events:
    EINT;   					// Enable Global interrupt INTM
    ERTM;  						// Enable Global realtime interrupt DBGM

	if (state_emu == WAIT || state_emu == EMU)		// Si se encuentra en estado de espera o emulando, deshabilitar SW
		return;

if (SW1_value==0){
	state_cfg = (~((GpioDataRegs.GPADAT.bit.GPIO30<<0)|   	\
			(GpioDataRegs.GPBDAT.bit.GPIO32<<1)|      		\
			(GpioDataRegs.GPADAT.bit.GPIO24<<2)|     		\
			(GpioDataRegs.GPADAT.bit.GPIO26<<3)))&0xf;


	if (state_emu == RUN)							// Si se encuentra en estado corriendo, permite cambiar state_cfg
		return;

	switch (state_cfg){
	case CFG1:
		//STOP_on;
		select_State(cfg1);
		break;
	case CFG2:
		//STOP_on;
		select_State(cfg2);
		break;
	case CFG3:
		//STOP_on;
		select_State(cfg3);
		break;
	case CFG4:
		//STOP_on;
		select_State(cfg4);
		break;
	case CALA:
		calibrationA();
		break;
	case CALB:
		calibrationB();
		break;
	case CONFIG:
		configuration();
		break;
	}
}
}

void calibrationA(void){
	u_ant= _IQ(0);
	user_enable[11] = 0;
	state_emu = EMU;
	STOP_off;
	timerConfig(0, 1);
	CpuTimer0Regs.TCR.bit.TIE = 1;	// Habilitdo interrupción de control
	EALLOW;
	PieVectTable.TINT0 = &CAL_ramp_interrupt;
	EDIS;
}

void calibrationB(void){
	u_ant= _IQ(0);
	user_enable[11] = 0;
	state_emu = EMU;
	STOP_off;
	timerConfig(0, 1);
	CpuTimer0Regs.TCR.bit.TIE = 1;	// Habilitdo interrupción de control
	EALLOW;
	PieVectTable.TINT0 = &CAL_const_interrupt;
	EDIS;
}

void configuration(void){
	CpuTimer0Regs.TCR.bit.TSS = 1;
	CpuTimer0Regs.TCR.bit.TIE = 0;	// Deshabilitdo interrupción de control
	user_enable[11] = 0;
	state_emu = CFG;
	STOP_on;
	EALLOW;
	PieVectTable.TINT0 = &configuration_interrupt;
	EDIS;
	timerConfig(0, 100);
	CpuTimer0Regs.TCR.bit.TIE = 1;	// Habilitdo interrupción de control
}

/* Funciones locales */

/***********************************************************
** Funcion: select_State()                                **
** Parametros: Ninguno.                                   **
** Descripcion: Carga la configuración dependiendo del    **
** 	estado actual del emulador.                           **
** 													      **
************************************************************/


void select_State(config cfgx){

switch (state_emu){
	case STOP:
		/* Estado STOP */
		state_emu = IDLE;			// Libero el estado
		state_cfg = UNDEF;
		break;
	case IDLE:
		/* Estado libre */

		state_emu = WAIT;			// Estado en espera
		if(cfgx.type == t_PID){
			initControl(cfgx);
		} else {
			initControl(cfg_PID_default);
		}

		break;

	case WAIT:	// Sin acción.

		/* Estado en espera */
		break;
	case OP:	// Sin acción.
		/* Punto de operación */
		break;

	case RUN:
		/* Ejecución de control */
		cfg_PID();				// Utiliza configuración PID cargada en variable "cfg"
		break;
	case EMU:					// Carga modelo de configuración.
		/* Estado de Emulador */
		wind = _IQ(0);
		switch (cfgx.type){
			case t_SIEGFRIED:
				cfg_Siegfried(cfgx);
				break;
			case t_POLYNOMIAL:
				cfg_Polynomial(cfgx);
				break;
			default:
				state_emu= WAIT;
				break;
		}
		break;
}
return;
}


/***********************************************************
** Funcion: cfg_PID()                                     **
** Parametros: Ninguno.                                   **
** Descripcion: Carga la configuración para el control    **
** PID.                                                   **
** 													      **
************************************************************/

void initControl(config cfgx){
	_iq Ts=_IQ(0);

	cfg=cfgx; 				// Asigna la Configuración Seleccionada a la Configuración Actual

	/* Inicialización de constantes de control  */
	Ts = _IQdiv((_iq) (cfg.model.PID.cfg.Ts),_IQ(1000));

	cfg.model.PID.data.KI = _IQmpy(cfg.model.PID.cfg.K,Ts);
	cfg.model.PID.data.KI = _IQdiv(cfg.model.PID.data.KI,cfg.model.PID.cfg.Ti);

	cfg.model.PID.data.KD1 = _IQmpy(cfg.model.PID.cfg.N,cfg.model.PID.cfg.K);
	cfg.model.PID.data.KD2 = _IQmpy(cfg.model.PID.cfg.N,Ts) + cfg.model.PID.cfg.Td;
	cfg.model.PID.data.KD2 = _IQdiv(cfg.model.PID.cfg.Td,cfg.model.PID.data.KD2);

	// Inicializo control
	cfg.model.PID.data.D = 0;
	cfg.model.PID.data.I = 0;
	cfg.model.PID.data.P = 0;

	/*******************************************/

	user_enable[11] = 1;	// Habilita comunicación serial

}


/* Apunta vector de interrupción a función PID */



/***********************************************************
** Funcion: cfg_PID()                               	  **
** Parametros: Config PID                                 **
** Descripcion: Carga la configuración para comenzar 	  **
** control de velocidad.                                  **
** 													      **
************************************************************/

void cfg_PID(){
	CpuTimer0Regs.TCR.bit.TSS = 1;
	EALLOW;
	PieVectTable.TINT0 = &PID_interrupt;
	EDIS;
	timerConfig(0, cfg.model.PID.cfg.Ts);
	CpuTimer0Regs.TCR.bit.TIE = 1;			// Habilitdo interrupción de control
	STOP_off
}

/***********************************************************
** Funcion: cfg_Siegfried()                               **
** Parametros: Ninguno.                                   **
** Descripcion: Carga la configuración para el emulador   **
** Siegfried.                                             **
** 													      **
************************************************************/

void cfg_Siegfried(config cfgx){
	cfg=cfgx;
	CpuTimer0Regs.TCR.bit.TSS = 1;
	EALLOW;
	PieVectTable.TINT0 = &Siegfried_interrupt;
	EDIS;
	delayms(1);
	timerConfig(0, cfg.model.Siegfried.cfg.Ts);
	CpuTimer0Regs.TCR.bit.TIE = 1;
	STOP_off
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
	/* Apunta vector de interrupción a función Siegfried */

	//launch(Siegfried_interrupt);
}

/***********************************************************
** Funcion: cfg_Polynomial()                               **
** Parametros: Ninguno.                                   **
** Descripcion: Carga la configuración para el emulador   **
** Polinomial.                                             **
** 													      **
************************************************************/

void cfg_Polynomial(config cfgx){
	cfg=cfgx;
	CpuTimer0Regs.TCR.bit.TSS = 1;
	/* Apunta vector de interrupción a función Polynomial */
	EALLOW;
	PieVectTable.TINT0 = &Polynomial_interrupt;
	EDIS;
	delayms(1);
	timerConfig(0, cfgx.model.Polynomial.cfg.Ts);
	CpuTimer0Regs.TCR.bit.TIE = 1;
	STOP_off
	user_enable[11] = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
	//launch(Polynomial_interrupt);
}



/*****************************************************************************************/
/***********************************************************
** Funcion: Varias			                              **
** Parametros: Ninguno.                                   **
** Descripcion: Configuración de puertos GPIO, para       **
** diversos módulos.                                      **
** 													      **
************************************************************/

void ledinit(){
	   EALLOW;

	   /* Init state_emu Leds */
	   GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 0;
	   GpioCtrlRegs.GPBDIR.bit.GPIO59 = 1;

	   GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;
	   GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;

	   GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 0;
	   GpioCtrlRegs.GPBDIR.bit.GPIO63 = 1;

	   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;

	   /* DSP led */
	   GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;

	   EDIS;
}

void DIP4init(){
	   EALLOW;

	   // Init GPIO SW dip 4
	   GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO30 = 0;
	   GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;

	   GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;
	   GpioCtrlRegs.GPBDIR.bit.GPIO32 = 0;
	   GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;

	   GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;
	   GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;

	   GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;
	   GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;

	   EDIS;
}

void displayinit(){
	   EALLOW;

	   /* Seg 7 - A */
	   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;

	   /* Seg 7 - B */
	   GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;

	   /* Seg 7 - C */
	   GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;

	   /* Seg 7 - D */
	   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;

	   /* Seg 7 - E */
	   GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;

	   /* Seg 7 - F */
	   GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;

	   /* Seg 7 - G */
	   GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;

	   /* Seg 7 - DP */
	   GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 0;
	   GpioCtrlRegs.GPADIR.bit.GPIO15 = 1;

	   EDIS;
}


interrupt void configuration_interrupt(){
int receive;
	if(SciaRegs.SCIFFRX.bit.RXFFST > 0){
	    receive = SciaRegs.SCIRXBUF.all;


	    if ((receive == CONFIGFRAME) || (receive == STATECONFIG)){
	    	scia_xmit(ACK);
	    	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;				// Limpieza de interrupción G1
	    	return;
	    }

	    switch(receive){
	    case (CFG1FRAME):
	    		sendconfig(cfg1);
	    		break;
	    case (CFG2FRAME):
				sendconfig(cfg2);
	    	    break;
	    case (CFG3FRAME):
				sendconfig(cfg3);
	    	    break;
	    case (CFG4FRAME):
				sendconfig(cfg4);
	    	    break;
	    case (SETUPFRAME):
				send_setup(workbench);
	    		break;
	    case (SCFG1FRAME):
	    		cfg1 = receiveconfig();
	    		scia_xmit(ACK);
	    		break;
	    case (SCFG2FRAME):
	    	    cfg2 = receiveconfig();
	    		scia_xmit(ACK);
	    	    break;
	    case (SCFG3FRAME):
	    	    cfg3 = receiveconfig();
	    		scia_xmit(ACK);
	    	    break;
	    case (SCFG4FRAME):
	    	    cfg4 = receiveconfig();
	    		scia_xmit(ACK);
	    	    break;
	    case (SUPRACFGFRAME):
	    	    	delayms(100);
	    	    	workbench = receive_setup();
	    	    	scia_xmit(ACK);
	    	    	delayms(100);
	        		cfg1 = receiveconfig();
	    	    	scia_xmit(ACK);
	    	    	delayms(100);
	        	    cfg2 = receiveconfig();
	        		scia_xmit(ACK);
	    	    	delayms(100);
	        	    cfg3 = receiveconfig();
	        		scia_xmit(ACK);
	    	    	delayms(100);
	        	    cfg4 = receiveconfig();
	        		scia_xmit(ACK);
	    	    break;
	    case (SSETUPFRAME):
				workbench = receive_setup();
	    		scia_xmit(ACK);
	    		break;
	    case (STATEIDLE):
				state_cfg = UNDEF;
	    		state_emu = IDLE;
	    		CpuTimer0Regs.TCR.bit.TIE = 0;	// Deshabilitdo interrupción de control
	    		user_enable[11] = 1;
			    scia_xmit(ACK);

	    }
	}
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;				// Limpieza de interrupción G1
}

void sendconfig (config cfgx){

	switch(cfgx.type){
	case (t_SIEGFRIED):
		send_siegfried(cfgx.model.Siegfried.cfg);
		break;
	case (t_POLYNOMIAL):
		send_polynomial(cfgx.model.Polynomial.cfg);
		break;
	case (t_PID):
		send_PID(cfgx.model.PID.cfg);
		break;
	}

}

config receiveconfig (){
config cfg;
	switch(receive16_int()){
	case (t_SIEGFRIED):
		cfg.type = t_SIEGFRIED;
		cfg.model.Siegfried.cfg = receive_siegfried();
		break;
	case (t_POLYNOMIAL):
		cfg.type = t_POLYNOMIAL;
		cfg.model.Polynomial.cfg = receive_polynomial();
		break;
	case (t_PID):
		cfg.type = t_PID;
		cfg.model.PID.cfg = receive_PID();
		break;
	}
return cfg;

}


/* Inicializa las Configuraciónes por Default */

/***********************************************************
** Funcion: defaultmodel_init()                             **
** Parametros: Ninguno.                                   **
** Descripcion: Carga las configuraciones por default.    **
** 													      **
************************************************************/

void defaultmodel_init(){

	/* Configuración Polynomial default */
    cfg_Polynomial_default.type=t_POLYNOMIAL;								// TIPO = Polinomial
    cfg_Polynomial_default.model.Polynomial.cfg.C[0] = _IQ(-0.2267);		// Coeficientes C1-C5
    cfg_Polynomial_default.model.Polynomial.cfg.C[1] = _IQ(0.0872);
    cfg_Polynomial_default.model.Polynomial.cfg.C[2] = _IQ(-0.008056);
    cfg_Polynomial_default.model.Polynomial.cfg.C[3] = _IQ(0.0001849);
    cfg_Polynomial_default.model.Polynomial.cfg.C[4] = _IQ(0.0);

    cfg_Polynomial_default.model.Polynomial.cfg.R = _IQ(2);					// Radio = 2 [m]
    cfg_Polynomial_default.model.Polynomial.cfg.Ts = 10;					// Ts = 10 [ms]
    cfg_Polynomial_default.model.Polynomial.cfg.W_lim[0] = _IQ(0);
    cfg_Polynomial_default.model.Polynomial.cfg.W_lim[1] = _IQ(200);
    cfg_Polynomial_default.model.Polynomial.cfg.Ct_on = 1;
    cfg_Polynomial_default.model.Polynomial.cfg.Kw = _IQ(2.5);
    cfg_Polynomial_default.model.Polynomial.cfg.Kt = _IQ(0.08);
    cfg_Polynomial_default.model.Polynomial.cfg.KCM = _IQ(1);

	/* Configuración Siegfried default */
    cfg_Siegfried_default.type=t_SIEGFRIED;									// TIPO = Siegfried
    cfg_Siegfried_default.model.Siegfried.cfg.C[0] = _IQ(0.648);			// Coeficientes C1-C6
    cfg_Siegfried_default.model.Siegfried.cfg.C[1] = _IQ(116);
    cfg_Siegfried_default.model.Siegfried.cfg.C[2] = _IQ(0.4);
    cfg_Siegfried_default.model.Siegfried.cfg.C[3] = _IQ(6.25);
    cfg_Siegfried_default.model.Siegfried.cfg.C[4] = _IQ(21);
    cfg_Siegfried_default.model.Siegfried.cfg.C[5] = _IQ(0.01);

    cfg_Siegfried_default.model.Siegfried.cfg.W_lim[0] = _IQ(0);
    cfg_Siegfried_default.model.Siegfried.cfg.W_lim[1] = _IQ(200);
    cfg_Siegfried_default.model.Siegfried.cfg.R = _IQ(2);					// Radio = 2 [m]
    cfg_Siegfried_default.model.Siegfried.cfg.Ts = 1;						// Ts = 1 [ms]
    cfg_Siegfried_default.model.Siegfried.cfg.Kt = _IQ(0.055);
    cfg_Siegfried_default.model.Siegfried.cfg.Kw = _IQ(0.8);
    cfg_Siegfried_default.model.Siegfried.cfg.KCM = _IQ(1);



	/* Configuración PID default */
    cfg_PID_default.type=t_PID;												// TIPO = PID
    cfg_PID_default.model.PID.cfg.K = _IQ(0.001);							// Coeficiente KP
    cfg_PID_default.model.PID.cfg.Ti = _IQ(0.05);							// Tiempo de integración Ti
    cfg_PID_default.model.PID.cfg.Td = _IQ(0);							// Tiempo de derivación Td
    cfg_PID_default.model.PID.cfg.N = _IQ(10);							// Orden de filtro derivativo N
    cfg_PID_default.model.PID.cfg.Ts = 100;								// Ts = 100 [m]
    cfg_PID_default.model.PID.cfg.reference = _IQ(100);					// Velocidad de referencia 160 [rad/s]

	cfg_PID_default.model.PID.data.I = _IQ(0);							// Valor inicial de integración 0

	cfg1 = cfg_Siegfried_default;
	cfg2 = cfg_PID_default;

	cfg3 = cfg_Polynomial_default;
	cfg4 = cfg_Polynomial_default;

	/* Workbench configuration */
	workbench.KBE = _IQ(1);
	workbench.Tp = _IQ(0);
	workbench.Ku = _IQ(0.8);
	workbench.W_sat[0] = _IQ(0);
	workbench.W_sat[1] = _IQ(157);
	workbench.u_sat[0] = _IQ(0);
	workbench.u_sat[1] = _IQ(10.0);
	workbench.N = _IQ(600);

}
