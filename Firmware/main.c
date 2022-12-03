/**
 * main.c
 **/


#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "math.h"

#include "TMC1100.h"
#include "LM5056_I2C.h"
#include "LM5056.h"


/* Local functions declaration */
void MyDelay(long);

/* Extern functions declaration */
extern void InitSysCtrl(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void scia_initialize(void);
extern void user_task(int, Uint32, int);
extern void timerConfig(int, int);
extern void user_configuration(void);
extern void LM5056_I2CA_Init(void);
extern void ADC_Init(void);
extern void ConfigEPWM1(void);
extern void ConfigEPWM2(void);


__interrupt void xint1_isr(void);
__interrupt void xint2_isr(void);


/* Extern variables declaration */

extern struct I2Cmsg *CurrentMsgPtr;
extern Uint16 data[12];

void main(void)
{

    /**********************************************/
    /* Configuración del DSP general: CLK,WD, etc */
    /**********************************************/

    InitSysCtrl();          //Configura el DSP a 150Mhz, desahabilita el watchdog y habilita todos los clock de perifericos

    // High-Speed Peripheral clock HSPCLK = SYSCLK_OUT/(2*HISPCP)
    EALLOW;
    SysCtrlRegs.HISPCP.all = 0x3;
    EDIS;
    /**********************************************/
    /********** FIN CONFIG DSP GENERAL ************/
    /**********************************************/

/*************************************************************/
    EPwm1Regs.TBCTL.bit.CTRMODE = 3; //En RST on, no desactiva PWM. Razon?
    /**********************************************/
    /* Configuración del vector de interrupciones */
    /**********************************************/
    DINT;
    InitPieCtrl();

    PieCtrlRegs.PIEIER8.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    /**********************************************/
    /********* FIN CONFIG INTERRUPCIONES **********/
    /**********************************************/

/*************************************************************/

    /**********************************************/
    /**** Inicialización de módulos/periféricos ***/
    /**********************************************/

    /* Inicialización del Timer 1 como contador de milisegundos - "time_ms" variable */
    InitCpuTimers();
    timerConfig(1,1);

    /* Inicialización del puerto Serie */
    scia_initialize();

    /* Configuración del I2C para monitor de energía LM5056 */
    LM5056_I2CA_Init();

    /* Inicialización de funciones de usuario de propósito general - Leds, SWs, funciones de baja latencia, etc. */
    user_configuration();

    /* Inicialización del módulo ADC para lectura de Iout */
    ADC_Init();


    /* Inicialización del módulo ePWM1 y ePWM2 */
    ConfigEPWM1();
    ConfigEPWM2();


    /**********************************************/
    /******* FIN CONFIG MODULOS/PERIFÉRICOS *******/
    /**********************************************/

/*************************************************************/


    //
    // Enable CPU INT8 which is connected to PIE group 8
    //


    // Enable XINT1 and XINT2 in the PIE: Group 1 interrupt 4 & 5
    // Enable int1 which is connected to WAKEINT:
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
                           // Enable Global Interrupts
    IER |= M_INT8;
    IER |= M_INT3;
    IER |= M_INT1;      // Enable CPU Interrupt 1
    EINT;

/*************************************************************/

    /**********************************************/
    /************ COMIENZO DE PROGRAMA ************/
    /**********************************************/

    for(;;)
    {

       /* Programas de usuario, low latency applications */
       ////////////////////////////////////////////////////


       // User Task 1: Read power monitor LM5056 y TMC1100
            user_task(1,10,1);

       // User Task 10: Set ePWM phase from buttons GPIO5 and GPIO 7
            user_task(10,250,1);

       // User Task 11: Serial Interface
            user_task(11,3000,1);

       // User Task 12: Blink - 0.5s
            user_task(12,500,1);
   }

    /**********************************************/
    /*************** FIN DE PROGRAMA **************/
    /**********************************************/

/*************************************************************/
}

