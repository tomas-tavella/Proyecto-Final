//#include "IQmathLib.h"
#include <Includes/submodules/common/DSP_define.h>
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

float PID_control(PID*,float);

/***********************************************************
 **                  Controlador PID                      **
 **                                                       **
 ***********************************************************/

/*	Resumen de implementaci�n
 *  -> Uso de Configuraci�n cfg.PID
 *	-> Medici�n de velocidad + saturaci�n
 *	-> C�lculo del control + saturaci�n
 *	-> Carga del DAC
 */
interrupt void PID_interrupt(void){
	float u, u_temp, u_ant;


	/* C�lculo de control */
	//u = PID_control(&cfg.model.PID,wm);		// Acci�n de control.
	u_ant = u;
	u_temp  = 6553.5;
	u = u_temp*u;								// Mapeo de u_max => 65535

	/* Actualizaci�n del DAC */
	SET_control(u);								// Actualizaci�n de DAC


    EPwm1Regs.ETCLR.bit.INT = 1;
    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}



///////////////////
/// Control PID ///
///////////////////
float PID_control(PID* pid,float speed){

	float aux_d,error;
	float  u;

	/* Acci�n proporcional */
	error = pid->cfg.reference - speed;

	pid->data.P = error*pid->cfg.K;

	/* Acci�n derivativa filtrada */
	aux_d = speed - pid->data.speed;
	aux_d = pid->data.D - aux_d*pid->data.KD1;
	pid->data.D = aux_d*pid->data.KD2;

	/* Acci�n de control*/
	u= pid->data.P + pid->data.D + pid->data.I;
	//u = _IQsat(u,workbench.u_sat[1],workbench.u_sat[0]);					// Saturaci�n de control
	/* Acci�n integral */
	pid->data.I = pid->data.I + error*pid->data.KI; 				//Retardada Ts

	pid->data.speed = speed;


	return u;
}
