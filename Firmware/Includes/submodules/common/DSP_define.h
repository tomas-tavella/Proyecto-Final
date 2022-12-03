#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h"

///////////////////////////////////////////////////////////////////////
/* Definición de Macros */

// Macros de control
#define SET_control(x)      EPwm2Regs.TBPHS.half.TBPHS = x;

// Macros de Switches
#define SW1_value           GpioDataRegs.GPADAT.bit.GPIO5
#define SW2_value           GpioDataRegs.GPADAT.bit.GPIO7
#define SW3_value           GpioDataRegs.GPADAT.bit.GPIO9
#define SW4_value           GpioDataRegs.GPADAT.bit.GPIO11

// Macros de leds

#define LedGreen_on  	    GpioDataRegs.GPBSET.bit.GPIO61 = 1;
#define LedGreen_toggle  	GpioDataRegs.GPBTOGGLE.bit.GPIO61 = 1;
#define LedGreen_off  	    GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
#define LedRed_on  		    GpioDataRegs.GPBSET.bit.GPIO59 = 1;
#define LedRed_off  	    GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;
#define LedState1_on  	    GpioDataRegs.GPBSET.bit.GPIO63 = 1;
#define LedState1_off 	    GpioDataRegs.GPBCLEAR.bit.GPIO63 = 1;
#define LedState1_toggle  	GpioDataRegs.GPBTOGGLE.bit.GPIO63 = 1;
#define LedState2_on  	    GpioDataRegs.GPASET.bit.GPIO1 = 1;
#define LedState2_off  	    GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
#define Leds_off		    GpioDataRegs.GPBCLEAR.all = 0xA8000000;

// Constantes matemáticas
#define PI                  float(3.14159265359)




/////////////////////////////////////////////////////////////////////////
/* Declaración de estructuras */


/* Definición de estructura de control PID */
typedef struct {
	float K;
	float Td;
	float Ti;
	float N;
	float reference;
    int Ts;
} PID_cfg;

typedef struct {
	float P;
	float I;
	float D;
	float speed;
	float KD1;
	float KD2;
	float KI;
} PID_data;

typedef struct {
	PID_cfg cfg;
	PID_data data;
} PID;
/***********************************************/


/******************************/
