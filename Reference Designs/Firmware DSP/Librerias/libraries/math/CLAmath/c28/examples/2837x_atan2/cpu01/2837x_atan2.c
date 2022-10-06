//#############################################################################
// Description:
//
// This example calls the arc-tangent2 function(CLAatan2) of the CLA
// math library on a test vector and compares the result to the
// equivalent "math.h" routine
//
// Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
// ALL RIGHTS RESERVED
//#############################################################################
//$TI Release: CLA Math Library 4.02.00.00 $
//$Release Date: Dec 7, 2017 $
//#############################################################################
#include <stdint.h>
#include "F28x_Project.h"
#include "CLAShared.h"
#include "math.h"

#define EPSILON             1e-2

// Constants
#define WAITSTEP    asm(" RPT #255||NOP")

//Global Variables
extern int16_t pass, fail;

//Task 1 (C) Variables
#ifdef __cplusplus
#pragma DATA_SECTION("CpuToCla1MsgRAM")
float fVal1;
#pragma DATA_SECTION("CpuToCla1MsgRAM")
float fVal2;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
float fResult;
#else
#pragma DATA_SECTION(fVal1,"CpuToCla1MsgRAM")
float fVal1;
#pragma DATA_SECTION(fVal2,"CpuToCla1MsgRAM")
float fVal2;
#pragma DATA_SECTION(fResult,"Cla1ToCpuMsgRAM")
float fResult;
#endif //__cplusplus

float y[BUFFER_SIZE];
float fError[BUFFER_SIZE];

//Golden Test Values
float test_num[BUFFER_SIZE] = {
-1.224647e-16, -0.04945372, -0.09878642, -0.1478774, -0.1966064, 
-0.2448544, -0.2925031, -0.3394361, -0.3855383, -0.4306971, 
-0.4748020, -0.5177448, -0.5594208, -0.5997276, -0.6385669, 
-0.6758435, -0.7114661, -0.7453477, -0.7774054, -0.8075605, 
-0.8357394, -0.8618732, -0.8858978, -0.9077544, -0.9273896,
-0.9447554, -0.9598091, -0.9725141, -0.9828392, -0.9907590, 
-0.9962543, -0.9993117, -0.9999235, -0.9980884, -0.9938107, 
-0.9871011, -0.9779758, -0.9664573, -0.9525737, -0.9363590, 
-0.9178528, -0.8971006, -0.8741529, -0.8490661, -0.8219014, 
-0.7927254, -0.7616096, -0.7286299, -0.6938671, -0.6574063, 
-0.6193367, -0.5797516, -0.5387476, -0.4964253, -0.4528881, 
-0.4082426, -0.3625982, -0.3160663, -0.2687610, -0.2207980, 
-0.1722946, -0.1233696, -0.07414275, -0.02473443, 0.02473443, 
0.07414275, 0.1233696, 0.1722946, 0.2207980, 0.2687610, 
0.3160663, 0.3625982, 0.4082426, 0.4528881, 0.4964253, 
0.5387476, 0.5797516, 0.6193367, 0.6574063, 0.6938671, 
0.7286299, 0.7616096, 0.7927254, 0.8219014, 0.8490661, 
0.8741529, 0.8971006, 0.9178528, 0.9363590, 0.9525737, 
0.9664573, 0.9779758, 0.9871011, 0.9938107, 0.9980884, 
0.9999235, 0.9993117, 0.9962543, 0.9907590, 0.9828392, 
0.9725141, 0.9598091, 0.9447554, 0.9273896, 0.9077544, 
0.8858978, 0.8618732, 0.8357394, 0.8075605, 0.7774054, 
0.7453477, 0.7114661, 0.6758435, 0.6385669, 0.5997276, 
0.5594208, 0.5177448, 0.4748020, 0.4306971, 0.3855383, 
0.3394361, 0.2925031, 0.2448544, 0.1966064, 0.1478774, 
0.09878642, 0.04945372, 1.224647e-16    
};

float test_den[BUFFER_SIZE] = {
-1, -0.9987764, -0.9951087, -0.9890057, -0.9804825, 
-0.9695598, -0.9562646, -0.9406291, -0.9226918, -0.9024965, 
-0.8800927, -0.8555351, -0.8288838, -0.8002042, -0.7695663, 
-0.7370452, -0.7027203, -0.6666759, -0.6289999, -0.5897847, 
-0.5491262, -0.5071239, -0.4638805, -0.4195020, -0.3740968, 
-0.3277763, -0.2806535, -0.2328440, -0.1844646, -0.1356339, 
-0.08647120, -0.03709691, 0.01236816, 0.06180296, 0.1110865, 
0.1600982, 0.2087182, 0.2568273, 0.3043080, 0.3510439, 
0.3969209, 0.4418264, 0.4856508, 0.5282866, 0.5696297, 
0.6095788, 0.6480362, 0.6849077, 0.7201031, 0.7535363, 
0.7851254, 0.8147933, 0.8424672, 0.8680794, 0.8915673, 
0.9128734, 0.9319456, 0.9487371, 0.9632069, 0.9753196, 
0.9850455, 0.9923608, 0.9972476, 0.9996940, 0.9996940, 
0.9972476, 0.9923608, 0.9850455, 0.9753196, 0.9632069, 
0.9487371, 0.9319456, 0.9128734, 0.8915673, 0.8680794, 
0.8424672, 0.8147933, 0.7851254, 0.7535363, 0.7201031, 
0.6849077, 0.6480362, 0.6095788, 0.5696297, 0.5282866, 
0.4856508, 0.4418264, 0.3969209, 0.3510439, 0.3043080, 
0.2568273, 0.2087182, 0.1600982, 0.1110865, 0.06180296, 
0.01236816, -0.03709691, -0.08647120, -0.1356339, -0.1844646, 
-0.2328440, -0.2806535, -0.3277763, -0.3740968, -0.4195020, 
-0.4638805, -0.5071239, -0.5491262, -0.5897847, -0.6289999, 
-0.6666759, -0.7027203, -0.7370452, -0.7695663, -0.8002042, 
-0.8288838, -0.8555351, -0.8800927, -0.9024965, -0.9226918, 
-0.9406291, -0.9562646, -0.9695598, -0.9804825, -0.9890057, 
-0.9951087, -0.9987764, -1
};

float res_expected[BUFFER_SIZE]={
-3.141593, -3.092119, -3.042645, -2.993171, -2.943697, 
-2.894223, -2.844749, -2.795275, -2.745801, -2.696327, 
-2.646854, -2.597380, -2.547906, -2.498432, -2.448958, 
-2.399484, -2.350010, -2.300536, -2.251062, -2.201589, 
-2.152115, -2.102641, -2.053167, -2.003693, -1.954219, 
-1.904745, -1.855271, -1.805797, -1.756323, -1.706850, 
-1.657376, -1.607902, -1.558428, -1.508954, -1.459480, 
-1.410006, -1.360532, -1.311058, -1.261584, -1.212111, 
-1.162637, -1.113163, -1.063689, -1.014215, -0.9647411, 
-0.9152671, -0.8657932, -0.8163193, -0.7668455, -0.7173716, 
-0.6678976, -0.6184238, -0.5689498, -0.5194760, -0.4700021, 
-0.4205281, -0.3710543, -0.3215804, -0.2721065, -0.2226325, 
-0.1731586, -0.1236848, -0.07421085, -0.02473695, 0.02473695, 
0.07421085, 0.1236848, 0.1731586, 0.2226325, 0.2721065, 
0.3215804, 0.3710543, 0.4205281, 0.4700021, 0.5194760, 
0.5689498, 0.6184238, 0.6678976, 0.7173716, 0.7668455, 
0.8163193, 0.8657932, 0.9152671, 0.9647411, 1.014215, 
1.063689, 1.113163, 1.162637, 1.212111, 1.261584, 
1.311058, 1.360532, 1.410006, 1.459480, 1.508954, 
1.558428, 1.607902, 1.657376, 1.706850, 1.756323, 
1.805797, 1.855271, 1.904745, 1.954219, 2.003693, 
2.053167, 2.102641, 2.152115, 2.201589, 2.251062, 
2.300536, 2.350010, 2.399484, 2.448958, 2.498432, 
2.547906, 2.597380, 2.646854, 2.696327, 2.745801, 
2.795275, 2.844749, 2.894223, 2.943697, 2.993171, 
3.042645, 3.092119, 3.141593
};

//C28 C tasks
void test_run(void)
{
    int16_t i;
    
    for(i=0;i<BUFFER_SIZE;i++)
    {
     fVal1 = test_num[i];
     fVal2 = test_den[i];
     Cla1ForceTask1andWait();
     WAITSTEP;
     y[i] = fResult; 
    }   
}

void test_report(void)
{
    uint16_t i;
    
    float fErrMetric;
    for(i=0;i<BUFFER_SIZE;i++){
      fError[i] = fabs(res_expected[i]-y[i]);
      fErrMetric = fError[i];
      if( fErrMetric < 1e-4){
        pass++;
      }else{
        fail++;
      }
    }
    // if(fail) test_error(); 
}

void test_error( void )
{
    asm(" ESTOP0"); 
}

