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

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
/* Funciones globales */

__interrupt void adc_isr(void);
void ADC_Init(void);

void ADC_Init(void){


    AdcRegs.ADCTRL1.bit.RESET = 1;
    AdcRegs.ADCTRL1.bit.SUSMOD = 1;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0;
    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;  // This is needed to write to EALLOW protected register
    PieVectTable.ADCINT = &adc_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers



    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2833x_InitPeripherals.c
    //
    // InitPeripherals(); // Not required for this example
    InitAdc();  // For this example, init the ADC

    //
    // Step 5. User specific code, enable interrupts:
    //




    //
    // Configure ADC for oversampling 10 conversions for 20kHz
    //

    AdcRegs.ADCMAXCONV.all = 0x0007;            // Setup 8 conv's on cascade
    AdcRegs.ADCCHSELSEQ1.all = 0x0;             // Setup ADCINA0 as 1-4  SEQ1 conv.
    AdcRegs.ADCCHSELSEQ2.all= 0x0;              // Setup ADCINA0 as 5-6  SEQ2 conv.
    AdcRegs.ADCCHSELSEQ3.all = 0x0;             // Setup ADCINA0 as 7-10 SEQ3 conv.
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 0x5;         // ADCLK = HSPCLK/8; => ADCLK = 3.125MHz
    AdcRegs.ADCTRL1.bit.CPS = 0x0;
    AdcRegs.ADCTRL1.bit.ACQ_PS = 0xD;           // 14 pulses por Aq windows + 1 of conversion => fq of conversion 200.8 kHz (10 samples por PWM freq)
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0x1;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0;
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    //
    // Enable SOCA from ePWM to start SEQ1
    //
    //Configuración del envio de la señal de inicio de conversión (SOC) de ADC desde el ePWM
   // EPwm1Regs.ETSEL.bit.SOCAEN  = 1;      // habilitamos SOCB
    //EPwm1Regs.ETSEL.bit.SOCASEL = 1;      // envio de SOCB cuando counter equal to zero
    //EPwm1Regs.ETPS.bit.SOCAPRD  = 1;      // Envia SOCB en el primer evento de periodo de pwm


   //AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
     // Enable SEQ1==SEQ interrupt (every EOS) in cascade mode

   AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
   delayms(1000);
   AdcRegs.ADCTRL1.bit.CONT_RUN = 0x1;

}


//
// adc_isr -
//
__interrupt void
adc_isr(void)
{

    GpioDataRegs.GPBTOGGLE.bit.GPIO62 = 1;
    TMC1100_read_raw_current();
    // Reinitialize for next ADC sequence
    //
    //AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;         // Clear INT SEQ1 bit
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;     // Acknowledge interrupt to PIE

    return;
}
