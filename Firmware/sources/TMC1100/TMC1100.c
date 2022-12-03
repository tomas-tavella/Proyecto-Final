//###########################################################################
//
// FILE:	TMC1100.c
//
// TITLE:	TMC1100 Initialization & Support Functions.
//



//
// Included Files
//

#include <Includes/TMC1100/headers/TMC1100.h>


void TMC1100_read_raw_current(void);
void TMC1100_avg_measures(void);
void TMC1100_inst_measures(void);



struct TMC1100_measures TMC1100;

void TMC1100_read_raw_current(void){
    int i;
    volatile Uint16 *adc_memory_pointer = &AdcMirror.ADCRESULT0;
    TMC1100.sum_buffer = 0;
    for (i=0;i<SAMPLES;i++){
        TMC1100.raw_buffer[i] = (adc_memory_pointer[i]);                     //Copy registers
        TMC1100.sum_buffer = TMC1100.sum_buffer + TMC1100.raw_buffer[i];        //Sum registers
    }
}

void TMC1100_avg_measures(void){
    TMC1100.avg_current = TMC1100.sum_buffer*3.0*TMC1100_GAIN/(ADC_RES*SAMPLES);
}

void TMC1100_inst_measures(void){
    int i;

    for (i=0;i<SAMPLES;i++){
        TMC1100.inst_current[i] = TMC1100.raw_buffer[i]*3.0*TMC1100_GAIN/(ADC_RES*SAMPLES);
    }

}



//
// End of file
//

