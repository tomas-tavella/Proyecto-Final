//#include "IQmathLib.h"
//#include "C28x_FPU_FastRTS.h"
#include "DSP_define.h"
//#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

extern _iq volatile wm, wg, wind, pitch, vTA;
extern _iq u_ant;
extern config cfg;
extern setup workbench;
extern int state_emu,state_cfg;

_iq PID_control(PID*,_iq);
_iq Cp_Siegfried(Siegfried, _iq, _iq);
_iq Cp_Polynomial(Polynomial);
_iq cal_Cupla(_iq, _iq, _iq, _iq, int);


/***********************************************************
 **            Cálculo de Cupla (en Baja)                 **
 **                                                       **
 ***********************************************************/

_iq cal_Cupla(_iq Cp_Ct, _iq tsr, _iq wind, _iq radio, int Ct_on){
	_iq temp,temp2;
	_iq TB;

	temp = _IQmpy(radio,radio);
	temp = _IQmpy(temp,radio);

	temp = _IQmpy(temp,_IQ(0.5));
	temp = _IQmpy(temp,PW);
	temp = _IQmpy(temp,PI);

	temp2 = _IQmpy(wind,wind);
	temp2 = _IQmpy(temp2,Cp_Ct);
	if (Ct_on ==0){
		temp2 = _IQdiv(temp2,tsr);
	}
	TB = _IQmpy(temp2,temp);

	return TB;	// Devuelve cupla de la turbina en el lado de baja
}


/***********************************************************
 **                  Modelo Siegfried                     **
 **                                                       **
 ***********************************************************/

/*	Resumen de implementación
 *  -> Uso de Configuración cfg.Siegfried
 *	-> Medición de velocidad
 *	-> Cálculo del TSR + sat
 *	-> Cálculo del Cp
 *	-> Cálculo de cupla + saturación
 *	-> Cálculo del control + saturación
 *	-> Carga del DAC
 */

interrupt void Siegfried_interrupt(void){
	_iq Cp, u, u_rstion, tsrB, wA, wB, wg, TA, TB, Tm, Tg, sat;

	/* Medición de velocidad */
	readVelocity

	/* Velocidad de rotación en el lado de alta de la turbina */
	// wg -> Velocidad de rotación REAL del generador (Lado de alta de la turbina)

	wg = _IQsat(wm,cfg.model.Siegfried.cfg.W_lim[1],cfg.model.Siegfried.cfg.W_lim[0]);	// Saturación del modelo

	wg = _IQmpy(wg,workbench.KBE); 	    // Constante de engranajes wm = KBE * wg
	wA = _IQmpy(wg,cfg.model.Siegfried.cfg.Kw);			// Factor de escala: Vel. real (rwA) -> vel. modelo (wA)

	/* Velocidad de rotación en el lado de baja de la turbina */
	wB = _IQdiv(wA,cfg.model.Siegfried.cfg.KCM);

	// Si viendo igual a cero, saltear cálculo de modelo
	if (wind == _IQ(0)){
		PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
		return;// Si no existe condición inicial, saltear control
	}

	/* Cálculo del TSR en baja */
	wind = _IQsat(wind,_IQ(INFINITY),_IQ(0.01));

	tsrB = _IQmpy(cfg.model.Siegfried.cfg.R,wB);
	tsrB = _IQdiv(tsrB,wind);

    cfg.model.Siegfried.data.TSRB = _IQsat(tsrB,_IQ(INFINITY),_IQ(0.0000001));   	//TSR != 0

// NOTA: TSR y Cp siempre son calculadas en el lado de baja

	/* Cálculo de Cp y cupla en lado de baja */
	Cp= Cp_Siegfried(cfg.model.Siegfried,pitch,wind);

	TB = cal_Cupla(Cp,cfg.model.Siegfried.data.TSRB,wind,cfg.model.Siegfried.cfg.R,0);

	/* Càlculo de la cupla en el lado de alta */
	TA = _IQdiv(TB,cfg.model.Siegfried.cfg.KCM);
	Tg = _IQmpy(TA,cfg.model.Siegfried.cfg.Kt);


	Tm = _IQmpy(Tg,workbench.KBE);

	/* Cálculo de control */
	u_rstion  = _IQdiv(_IQ(65535),_IQ(10)); //resolución del DAC

	Tm = Tm + workbench.Tp;
	u = _IQdiv(Tm,workbench.Ku);										    // Constante del motor Tm = Kt * u
	u = _IQsat(u,workbench.u_sat[1],workbench.u_sat[0]);					// Saturación del control
	u_ant = u;
	u = _IQmpy(u_rstion,u);													// u_dac = u * (65535/umax)


	/* Actualización del DAC */
	SET_control((Uint16)(u));

	sat = workbench.u_sat[1] - _IQdiv(workbench.Tp,workbench.Ku);
	sat = _IQmpy(sat,workbench.Ku);
	sat = _IQdiv(sat, cfg.model.Siegfried.cfg.Kt);
 	sat = _IQdiv(sat,workbench.KBE);
	vTA = _IQsat(TA,sat,_IQ(0));

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

}

/***********************************************************
 **                  Modelo Polynomial                    **
 **                                                       **
 ***********************************************************/
/*	Resumen de implementación
 *  -> Uso de Configuración cfg.Polynomial
 *	-> Medición de velocidad + saturación
 *	-> Cálculo del TSR
 *	-> Cálculo del Cp
 *	-> Cálculo de cupla + saturación
 *	-> Cálculo del control + saturación
 *	-> Carga del DAC
 */


interrupt void Polynomial_interrupt(void){
	_iq Cp, u, u_rstion, tsrB, wA, wB, wg, TA, TB, Tm, Tg, sat;

		/* Medición de velocidad */
		readVelocity

		/* Velocidad de rotación en el lado de alta de la turbina */
		// wg -> Velocidad de rotación REAL en el lado de alta de la turbina
		wg = _IQsat(wm,cfg.model.Polynomial.cfg.W_lim[1],cfg.model.Polynomial.cfg.W_lim[0]);	// Saturación del modelo

		wg = _IQmpy(wg,workbench.KBE); 	    // Constante de engranajes wm = KBE * wg
		wA = _IQmpy(wg,cfg.model.Polynomial.cfg.Kw);			// Factor de escala de velocidad real en lado de alta.

		/* Velocidad de rotación en el lado de baja de la turbina */
		wB = _IQdiv(wA,cfg.model.Polynomial.cfg.KCM);

		// Si viendo igual a cero, saltear cálculo de modelo
		if (wind == _IQ(0)){
			PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
			return;// Si no existe condición inicial, saltear control
		}

		/* Cálculo del TSR en baja */
		wind = _IQsat(wind,_IQ(INFINITY),_IQ(0.01));

		tsrB = _IQmpy(cfg.model.Polynomial.cfg.R,wB);
		tsrB = _IQdiv(tsrB,wind);

	    cfg.model.Polynomial.data.TSRB = _IQsat(tsrB,_IQ(INFINITY),_IQ(0.0000001));   	//TSR != 0

	// NOTA: TSR y Cp siempre son calculadas en el lado de baja

		/* Cálculo de Cp y cupla en lado de baja */
		Cp= Cp_Polynomial(cfg.model.Polynomial);

		TB = cal_Cupla(Cp,cfg.model.Polynomial.data.TSRB,wind,cfg.model.Polynomial.cfg.R,cfg.model.Polynomial.cfg.Ct_on);

		/* Càlculo de la cupla en el lado de alta */
		TA = _IQdiv(TB,cfg.model.Polynomial.cfg.KCM);
	    Tg = _IQmpy(TA,cfg.model.Polynomial.cfg.Kt);

		Tm = _IQmpy(Tg,workbench.KBE);

		/* Cálculo de control */
		u_rstion  = _IQdiv(_IQ(65535),_IQ(10)); //resolución del DAC

		Tm = Tm + workbench.Tp;
		u = _IQdiv(Tm,workbench.Ku);										    // Constante del motor Tm = Kt * u
		u = _IQsat(u,workbench.u_sat[1],workbench.u_sat[0]);					// Saturación del control
		u_ant = u;
		u = _IQmpy(u_rstion,u);													// u_dac = u * (65535/umax)


		/* Actualización del DAC */
		SET_control((Uint16)(u));

		sat = workbench.u_sat[1] - _IQdiv(workbench.Tp,workbench.Ku);
		sat = _IQmpy(sat,workbench.Ku);
		sat = _IQdiv(sat, cfg.model.Siegfried.cfg.Kt);
	 	sat = _IQdiv(sat,workbench.KBE);
		vTA = _IQsat(TA,sat,_IQ(0));
		PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


/***********************************************************
 **                  Controlador PID                      **
 **                                                       **
 ***********************************************************/

/*	Resumen de implementación
 *  -> Uso de Configuración cfg.PID
 *	-> Medición de velocidad + saturación
 *	-> Cálculo del control + saturación
 *	-> Carga del DAC
 */
interrupt void PID_interrupt(void){
	_iq u, u_temp;

	/* Medición de velocidad */
	readVelocity

	if(state_emu == STOP){
		PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;				// Limpieza de interrupción G1
		return;
	}

	/* Cálculo de control */
	u = _IQtoF(PID_control(&cfg.model.PID,wm));		// Acción de control.
	u_ant = u;
	u_temp  = _IQdiv(_IQ(65535),_IQ(10));
	u = _IQmpy(u_temp,u);								// Mapeo de u_max => 65535

	/* Actualización del DAC */
	SET_control(_IQint(u));								// Actualización de DAC

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;				// Limpieza de interrupción G1
}

/***********************************************************
 **                  Calibración                          **
 **                                                       **
 ***********************************************************/

interrupt void CAL_ramp_interrupt(){
	_iq u;
	/* Medición de velocidad */
	readVelocity

	u  = _IQdiv(_IQ(65535),workbench.W_sat[1]);
	u = _IQmpy(u,wm);
	u = _IQ(65535) - u;                                  // Mapeo de u_max => 65535
	SET_control(_IQint(u));
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;				// Limpieza de interrupción G1
}

interrupt void CAL_const_interrupt(){
	_iq u,temp;
    //float a;
	int receive;
	if(SciaRegs.SCIFFRX.bit.RXFFST > 0){
		    receive = SciaRegs.SCIRXBUF.all;
		    switch (receive){
		    		case CALFRAME:
	    				scia_xmit(ACK);
	    				break;
		    		case UPFRAME:
		    			temp  = _IQdiv(_IQ(65535),workbench.u_sat[1]);
		    			u = u_ant + _IQ(0.5);
		    			u = _IQsat(u,workbench.u_sat[1],workbench.u_sat[0]);
		    			u_ant = u;
		    			u = _IQmpy(u,temp);

		    			SET_control(_IQint(u));
		    			break;
		    		case DOWNFRAME:
		    			temp  = _IQdiv(_IQ(65535),workbench.u_sat[1]);
		    			u = u_ant - _IQ(0.5);
		    			u = _IQsat(u,workbench.u_sat[1],workbench.u_sat[0]);
		    			u_ant = u;
		    			u = _IQmpy(u,temp);

		    			SET_control(_IQint(u));
		    			break;
		    		case STOPFRAME:
		    			STOP_on
						state_emu = STOP;
		    			state_cfg = UNDEF;
		    			SciaRegs.SCIFFRX.bit.RXFIFORESET = 0; 	// Reinicio buffer de entrada
		    			delayms(100);
		    			SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
		    			CpuTimer0Regs.TCR.bit.TIE = 0;	// Deshabilito interrupción de control
		    			scia_xmit(STOP_ACK);
		    			break;
		    }
	}
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;				// Limpieza de interrupción G1
}



/***********************************************************
 **               Ecuaciones de modelado                  **
 **                                                       **
 ***********************************************************/

///////////////////
///  Siegfried  ///
///////////////////


_iq Cp_Siegfried(Siegfried cfg, _iq pitch, _iq wind){
	_iq temp,temp2;
	_iq inv_tsr_i,Cp;

    /* Calculo de 1/tsr_i */
	temp = cfg.data.TSRB + _IQmpy(_IQ(0.08),pitch);
	temp = _IQdiv(_IQ(1),temp);


	temp2 = _IQmpy(pitch,pitch);
	temp2 = _IQmpy(temp,pitch) + _IQ(1);
	temp2 = _IQdiv(_IQ(0.035),temp2);

	inv_tsr_i = temp - temp2; 			// 1/tsr_i

	temp=_IQ(0);temp2=_IQ(0); 			//Limpio variables auxiliares

	/* Ec. Cp = C[0]*(C[1]*inv_tsr_i - C[2]*pitch - C[3])*exp(-C[4]*inv_tsr_i) + C[5]*tsr */
	temp = _IQmpy(cfg.cfg.C[1],inv_tsr_i) - _IQmpy(cfg.cfg.C[2],pitch) - cfg.cfg.C[3];
	temp = _IQmpy(temp,cfg.cfg.C[0]);

	temp2 = -_IQmpy(cfg.cfg.C[4],inv_tsr_i);
	temp2 = _IQexp(temp2);

	Cp = _IQmpy(temp,temp2) + _IQmpy(cfg.cfg.C[5],cfg.data.TSRB);

	Cp = _IQsat(Cp,_IQ(0.7),_IQ(0));

	return Cp;
}


///////////////////
///  Polynomial ///
///////////////////

_iq Cp_Polynomial(Polynomial cfg){
	_iq Cp,tsr_pol;

	/* Ec. Cp = C[4]*tsr^4 + C[3]*tsr^3 + C[2]*tsr^2 + C[1]*tsr + C[0] */

	Cp = cfg.cfg.C[0];
	Cp = Cp + _IQmpy(cfg.cfg.C[1],cfg.data.TSRB);

	tsr_pol = _IQmpy(cfg.data.TSRB,cfg.data.TSRB);
	Cp = Cp + _IQmpy(tsr_pol,cfg.cfg.C[2]);

	tsr_pol = _IQmpy(tsr_pol,cfg.data.TSRB);
	Cp = Cp + _IQmpy(tsr_pol,cfg.cfg.C[3]);

	tsr_pol = _IQmpy(tsr_pol,cfg.data.TSRB);
	Cp = Cp + _IQmpy(tsr_pol,cfg.cfg.C[4]);

	Cp = _IQsat(Cp,_IQ(0.7),_IQ(0));

	return Cp;

}


///////////////////
/// Control PID ///
///////////////////
_iq PID_control(PID* pid,_iq speed){

	_iq aux_d,error;
	_iq u;

	/* Acción proporcional */
	error = pid->cfg.reference - speed;

	if(_IQabs(error) < _IQmpy(pid->cfg.reference,_IQ(0.05))){				// Punto de operación
		state_emu = OP;
	} else {
		state_emu = RUN;
	}

	pid->data.P = _IQmpy(error,pid->cfg.K);

	/* Acción derivativa filtrada */
	aux_d = speed - pid->data.speed;
	aux_d = pid->data.D - _IQmpy(aux_d,pid->data.KD1);
	pid->data.D = _IQmpy(aux_d,pid->data.KD2);

	/* Acción de control*/
	u= pid->data.P + pid->data.D + pid->data.I;
	u = _IQsat(u,workbench.u_sat[1],workbench.u_sat[0]);					// Saturación de control
	/* Acción integral */
	pid->data.I = pid->data.I + _IQmpy(error,pid->data.KI); 				//Retardada Ts

	pid->data.speed = speed;


	return u;
}
