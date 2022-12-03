// TI File $Revision: /main/2 $
// Checkin $Date: March 22, 2007   10:40:22 $
//###########################################################################
//
// FILE:   TMC1100.h
//
// TITLE:  TMC1100 header
//
//###########################################################################

#ifndef TMC1100_H
#define TMC1100_H


#ifdef __cplusplus
extern "C" {
#endif

#include "DSP28x_Project.h"

#define SAMPLES         8
#define SAMPLES_BITS    3
#define ADC_RES         4096.0
#define SENSIBILITY     0.4          // Sensibility mV/A
#define TMC1100_GAIN            1.367
struct TMC1100_measures
{
    Uint16 raw_buffer[SAMPLES];
    Uint32 sum_buffer;
    float avg_current;
    float inst_current[SAMPLES];
};

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of TMC1100_H definition

//
// End of file
//

