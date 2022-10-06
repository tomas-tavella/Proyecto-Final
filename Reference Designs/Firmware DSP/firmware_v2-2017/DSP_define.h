#include "IQmathLib.h"
#include "C28x_FPU_FastRTS.h"
//#include "DSP28x_Project.h"
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h"

///////////////////////////////////////////////////////////////////////
/* Definición de Macros */
#define readConfig {(~((GpioDataRegs.GPADAT.bit.GPIO30<<0)|(GpioDataRegs.GPBDAT.bit.GPIO32<<1)|(GpioDataRegs.GPADAT.bit.GPIO24<<2)|(GpioDataRegs.GPADAT.bit.GPIO26<<3)))&0xf}

#define SW1_value GpioDataRegs.GPADAT.bit.GPIO3
#define SW2_value GpioDataRegs.GPADAT.bit.GPIO5
#define SW3_value GpioDataRegs.GPADAT.bit.GPIO7
#define SW4_value GpioDataRegs.GPADAT.bit.GPIO9

// Macros de leds

#define LedGreen_on  	GpioDataRegs.GPBSET.bit.GPIO61 = 1;
#define LedGreen_toggle  	GpioDataRegs.GPBTOGGLE.bit.GPIO61 = 1;
#define LedGreen_off  	GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
#define LedRed_on  		GpioDataRegs.GPBSET.bit.GPIO59 = 1;
#define LedRed_off  	GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1;
#define LedState1_on  	GpioDataRegs.GPBSET.bit.GPIO63 = 1;
#define LedState1_off 	GpioDataRegs.GPBCLEAR.bit.GPIO63 = 1;
#define LedState1_toggle  	GpioDataRegs.GPBTOGGLE.bit.GPIO63 = 1;
#define LedState2_on  	GpioDataRegs.GPASET.bit.GPIO1 = 1;
#define LedState2_off  	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
#define Leds_off		GpioDataRegs.GPBCLEAR.all = 0xA8000000;

// Macros del DAC
#define STOP_on			   GpioDataRegs.GPASET.bit.GPIO27 = 1;
#define STOP_off		   GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;
#define SET_control(A)	   dac_write(COMMAND_DATA,A);

// Macros y definiciones del ENCODER
#define readVelocity	   eQEP_calculate();
#define filtN 		128
#define divN		7
#define qep_UPPS		0		//Si se modifican estos valores, debe modificarse eQEP_calculate()
#define qep_CCPS		0

/////////////////////////////////////////////////////////////////////////
/* Definiciones */
#define COMMAND_CONTROL 	0X55
#define COMMAND_DATA 		0x01
#define COMMAND_GAIN		0X58
#define COMMAND_ZERO		0x59
#define COMMAND_WDRESET 	0x95
#define COMMAND_CONFIG      0x57
#define COMMAND_RESET	    0x56
#define COMMAND_READ		0x02

#define TEST 0

#define CFG1 0x1
#define CFG2 0x2
#define CFG3 0x4
#define CFG4 0x8
#define CONFIG 0x00
#define UNDEF 0x10
#define CALA 0x3
#define CALB 0xC

#define PI _IQ(3.14159265359)
#define PW _IQ(1.225)

/* Indicadores de configuración */
#define disp_MASK 0x9555
#define disp_CFG1 0x0014
#define disp_CFG2 0x1145
#define disp_CFG3 0x1055
#define disp_CFG4 0x1414
#define disp_CALA 0x1515
#define disp_CALB 0x1555
#define disp_CONFIG 0x541

/* Estados del emulador */
#define IDLE 	0
#define WAIT 	1
#define RUN		2
#define OP	    3
#define EMU 	4
#define STOP	5
#define CFG		6

#define t_PID 		 	 0
#define t_SIEGFRIED 	 1
#define t_POLYNOMIAL	 2
#define t_SETUP			 3

/* Frames de com. Serial */
#define CFGSELFRAME 0x3E
#define WINDFRAME 0x3f
#define SWINDFRAME 0x40
#define ENDFRAME 0x10

#define SENDFRAME_FLOAT 0x11
#define SENDFRAME_INT 0x12

#define STATECONFIG 0x70
#define STATEIDLE 	0x71
#define STATECFG1	0x72
#define STATECFG2	0x73
#define STATECFG3	0x74
#define STATECFG4	0x75
#define STATECALB   0x76

#define SUPRACFGFRAME 0x90
#define CONFIGFRAME 0x80
#define CFG1FRAME 0x81
#define CFG2FRAME 0x82
#define CFG3FRAME 0x83
#define CFG4FRAME 0x84
#define SCFG1FRAME 0x85
#define SCFG2FRAME 0x86
#define SCFG3FRAME 0x87
#define SCFG4FRAME 0x88
#define SETUPFRAME 0x89
#define SSETUPFRAME 0x8A


#define SPEEDFRAME		0xDF
#define STARTFRAME  	0xE0
#define CONTROLFRAME 	0xE1
#define STOPFRAME		0xE2
#define EMUFRAME		0xE3
#define STOP_ACK		0xFC
#define CONTROL_ACK		0xFD
#define START_ACK 		0xFE
#define ACK 			0xFF

#define UPFRAME			0x20
#define DOWNFRAME		0x21
#define CALFRAME		0x22
/////////////////////////////////////////////////////////////////////////
/* Declaración de funciones globales*/
interrupt void signal_A(void);
interrupt void signal_B(void);
interrupt void cfg1_control(void),cfg2_control(void),cfg3_control(void),cfg4_control(void),cfg_select(void);
interrupt void timer1_interrupt(void);
interrupt void PID_interrupt(void);
interrupt void Siegfried_interrupt(void);
interrupt void Polynomial_interrupt(void);
interrupt void stop(void);
interrupt void controlLeds(void);
interrupt void CAL_ramp_interrupt(void);
interrupt void CAL_const_interrupt(void);
interrupt void configuration_interrupt(void);
interrupt void blinkLed(void);
interrupt void testEncoder(void);
interrupt void serialInterface(void);
extern void scia_xmit(int);

/* Declaración de Funciones externas */
extern interrupt void eQEP_interrupt(void);

// Funciones del DAC
extern void dac_write(Uint16,Uint16);
extern void dac_init(void);

extern void eQEP_calculate();
extern void eQEPconfig(void);
extern void timerConfig(int, int);
extern void cfg_init(void);
extern void user_configuration(void);
extern void em_encoder_cfg(void);
extern void user_task(int, Uint32,int);
extern void scia_initialize(void);
extern void send16_int(int);
extern void send32_float(float);
extern int receive16_int(void);
extern float receive32_float(void);
extern void delayms(Uint32);

/////////////////////////////////////////////////////////////////////////
/* Declaración de estructuras */

/* Definición de estructura de control Siegfried */
typedef struct{
	_iq C[6];
	_iq R;
	int Ts;
	_iq W_lim[2];	// Saturación de velocidad

	_iq Kw;		// Constante de proporcionalidad de W
	_iq Kt;		// Constante de proporcionalidad de T

	_iq KCM;     // Constane de caja de engranajes del modelo de turbina (relaciona CpA -> CpB)
} Siegfried_cfg;

typedef struct{
	_iq TSRB;
	_iq TB;
} Siegfried_data;

typedef struct {
	Siegfried_cfg cfg;
	Siegfried_data data;
} Siegfried;

/* Definición de estructura de control Polynomial */

typedef struct {
	_iq C[5];
	_iq W_lim[2];	// Saturación de velocidad
	_iq R;
    int Ts;
	int Ct_on;

	_iq Kw;		// Constante de proporcionalidad de W
	_iq Kt;		// Constante de proporcionalidad de T

	_iq KCM;     // Constane de caja de engranajes del modelo de turbina (relaciona CpA -> CpB)

} Polynomial_cfg;

typedef struct{
	_iq TSRB;
	_iq TB;
} Polynomial_data;

typedef struct {
	Polynomial_cfg cfg;
	Polynomial_data data;
} Polynomial;


/* Definición de estructura de control PID */
typedef struct {
	_iq K;
	_iq Td;
	_iq Ti;
	_iq N;
	_iq reference;
    int Ts;
} PID_cfg;

typedef struct {
	_iq P;
	_iq I;
	_iq D;
	_iq speed;
	_iq KD1;
	_iq KD2;
	_iq KI;
} PID_data;

typedef struct {
	PID_cfg cfg;
	PID_data data;
} PID;
/***********************************************/

typedef union{
	Polynomial Polynomial;
	Siegfried Siegfried;
	PID PID;
} u_model;

typedef struct{
	int type;
	u_model model;
} config;


/******************************/

typedef struct{
	_iq W_sat[2];	// Saturación de velocidad
	_iq u_sat[2];   // Saturación de control
	_iq Ku;			// Conv. corriente => Cupla
	_iq KBE;		// Constante de caja de engranajes auxiliar del Banco de Emulación
	_iq Tp;
	_iq N;			// Constante de encoder.
} setup;

extern Polynomial_cfg receive_polynomial(void);
extern Siegfried_cfg receive_siegfried(void);
extern PID_cfg receive_PID(void);
extern void send_polynomial(Polynomial_cfg);
extern void send_siegfried(Siegfried_cfg);
extern setup receive_setup(void);
extern void send_setup(setup);
extern void send_PID(PID_cfg);

