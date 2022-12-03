//#include "IQmathLib.h"
#include <Includes/submodules/common/DSP_define.h>
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

float PID_control(PID*,float);

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
	float u, u_temp, u_ant;


	/* Cálculo de control */
	//u = PID_control(&cfg.model.PID,wm);		// Acción de control.
	u_ant = u;
	u_temp  = 6553.5;
	u = u_temp*u;								// Mapeo de u_max => 65535

	/* Actualización del DAC */
	SET_control(u);								// Actualización de DAC


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

	/* Acción proporcional */
	error = pid->cfg.reference - speed;

	pid->data.P = error*pid->cfg.K;

	/* Acción derivativa filtrada */
	aux_d = speed - pid->data.speed;
	aux_d = pid->data.D - aux_d*pid->data.KD1;
	pid->data.D = aux_d*pid->data.KD2;

	/* Acción de control*/
	u= pid->data.P + pid->data.D + pid->data.I;
	//u = _IQsat(u,workbench.u_sat[1],workbench.u_sat[0]);					// Saturación de control
	/* Acción integral */
	pid->data.I = pid->data.I + error*pid->data.KI; 				//Retardada Ts

	pid->data.speed = speed;


	return u;
}
