// TI File $Revision: /main/2 $
// Checkin $Date: March 22, 2007   10:40:22 $
//###########################################################################
//
// FILE:   LM5056.h
//
// TITLE:  LM5056 header
//
//###########################################################################

#ifndef LM5056_H
#define LM5056_H


#ifdef __cplusplus
extern "C" {
#endif

#include "DSP28x_Project.h"
#include "LM5056_defines.h"

struct LM5056_avg_measures
{
    float AVG_IIN;
    float AVG_VOUT;
    float AVG_VIN;
    float AVG_PIN;
    float TEMPERATURE;
};

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of LM5056_H definition

//
// End of file
//

