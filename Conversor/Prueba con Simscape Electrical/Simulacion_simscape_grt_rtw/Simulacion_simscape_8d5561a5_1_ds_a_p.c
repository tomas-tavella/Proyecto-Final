/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'Simulacion_simscape/Solver Configuration'.
 */

#include "ne_ds.h"
#include "Simulacion_simscape_8d5561a5_1_ds_a_p.h"
#include "Simulacion_simscape_8d5561a5_1_ds_sys_struct.h"
#include "Simulacion_simscape_8d5561a5_1_ds_externals.h"
#include "Simulacion_simscape_8d5561a5_1_ds_external_struct.h"
#include "ssc_ml_fun.h"

int32_T Simulacion_simscape_8d5561a5_1_ds_a_p(const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *t2)
{
  PmSparsityPattern out;
  (void)t1;
  out = t2->mA_P;
  out.mNumCol = 24UL;
  out.mNumRow = 24UL;
  out.mJc[0] = 0;
  out.mJc[1] = 2;
  out.mJc[2] = 4;
  out.mJc[3] = 6;
  out.mJc[4] = 8;
  out.mJc[5] = 12;
  out.mJc[6] = 14;
  out.mJc[7] = 17;
  out.mJc[8] = 19;
  out.mJc[9] = 21;
  out.mJc[10] = 23;
  out.mJc[11] = 25;
  out.mJc[12] = 27;
  out.mJc[13] = 31;
  out.mJc[14] = 33;
  out.mJc[15] = 33;
  out.mJc[16] = 36;
  out.mJc[17] = 37;
  out.mJc[18] = 38;
  out.mJc[19] = 38;
  out.mJc[20] = 38;
  out.mJc[21] = 38;
  out.mJc[22] = 38;
  out.mJc[23] = 38;
  out.mJc[24] = 38;
  out.mIr[0] = 2;
  out.mIr[1] = 7;
  out.mIr[2] = 0;
  out.mIr[3] = 7;
  out.mIr[4] = 3;
  out.mIr[5] = 8;
  out.mIr[6] = 1;
  out.mIr[7] = 8;
  out.mIr[8] = 4;
  out.mIr[9] = 5;
  out.mIr[10] = 9;
  out.mIr[11] = 22;
  out.mIr[12] = 4;
  out.mIr[13] = 9;
  out.mIr[14] = 6;
  out.mIr[15] = 22;
  out.mIr[16] = 23;
  out.mIr[17] = 0;
  out.mIr[18] = 7;
  out.mIr[19] = 2;
  out.mIr[20] = 7;
  out.mIr[21] = 1;
  out.mIr[22] = 8;
  out.mIr[23] = 3;
  out.mIr[24] = 8;
  out.mIr[25] = 4;
  out.mIr[26] = 9;
  out.mIr[27] = 4;
  out.mIr[28] = 5;
  out.mIr[29] = 9;
  out.mIr[30] = 22;
  out.mIr[31] = 22;
  out.mIr[32] = 23;
  out.mIr[33] = 6;
  out.mIr[34] = 22;
  out.mIr[35] = 23;
  out.mIr[36] = 22;
  out.mIr[37] = 23;
  (void)sys;
  (void)t2;
  return 0;
}
