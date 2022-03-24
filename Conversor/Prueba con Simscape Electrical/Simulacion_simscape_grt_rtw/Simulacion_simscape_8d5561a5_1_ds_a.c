/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'Simulacion_simscape/Solver Configuration'.
 */

#include "ne_ds.h"
#include "Simulacion_simscape_8d5561a5_1_ds_a.h"
#include "Simulacion_simscape_8d5561a5_1_ds_sys_struct.h"
#include "Simulacion_simscape_8d5561a5_1_ds_externals.h"
#include "Simulacion_simscape_8d5561a5_1_ds_external_struct.h"
#include "ssc_ml_fun.h"

int32_T Simulacion_simscape_8d5561a5_1_ds_a(const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *t2)
{
  PmRealVector out;
  (void)t1;
  out = t2->mA;
  out.mX[0] = -0.0;
  out.mX[1] = -1.0;
  out.mX[2] = -0.0;
  out.mX[3] = -1.0;
  out.mX[4] = -0.0;
  out.mX[5] = -1.0;
  out.mX[6] = -0.0;
  out.mX[7] = -1.0;
  out.mX[8] = -1.0;
  out.mX[9] = -0.0;
  out.mX[10] = -1.0E-6;
  out.mX[11] = 0.33333333333333331;
  out.mX[12] = -0.0;
  out.mX[13] = -1.0;
  out.mX[14] = -0.0;
  out.mX[15] = -1.0;
  out.mX[16] = 1.0;
  out.mX[17] = -1.0;
  out.mX[18] = -1.0E-6;
  out.mX[19] = -1.0;
  out.mX[20] = -1.0E-6;
  out.mX[21] = -1.0;
  out.mX[22] = -1.0E-6;
  out.mX[23] = -1.0;
  out.mX[24] = -1.0E-6;
  out.mX[25] = 0.18518518518518517;
  out.mX[26] = 1.0000001851851852;
  out.mX[27] = -0.18518518618518517;
  out.mX[28] = -1.0;
  out.mX[29] = -1.0000001851851861;
  out.mX[30] = 3.3333333333333332E-10;
  out.mX[31] = -0.33333333333333331;
  out.mX[32] = 0.33333333333333331;
  out.mX[33] = -1.0;
  out.mX[34] = -1.0E-9;
  out.mX[35] = 1.0E-9;
  out.mX[36] = -0.33333333333333331;
  out.mX[37] = -0.33333333333333331;
  (void)sys;
  (void)t2;
  return 0;
}
