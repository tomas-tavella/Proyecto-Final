/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'Simulacion_simscape/Solver Configuration'.
 */

#include "ne_ds.h"
#include "Simulacion_simscape_8d5561a5_1_ds_dxf_p.h"
#include "Simulacion_simscape_8d5561a5_1_ds_sys_struct.h"
#include "Simulacion_simscape_8d5561a5_1_ds_externals.h"
#include "Simulacion_simscape_8d5561a5_1_ds_external_struct.h"
#include "ssc_ml_fun.h"

int32_T Simulacion_simscape_8d5561a5_1_ds_dxf_p(const NeDynamicSystem *sys,
  const NeDynamicSystemInput *t1, NeDsMethodOutput *t2)
{
  PmSparsityPattern out;
  (void)t1;
  out = t2->mDXF_P;
  out.mNumCol = 24UL;
  out.mNumRow = 24UL;
  out.mJc[0] = 0;
  out.mJc[1] = 6;
  out.mJc[2] = 6;
  out.mJc[3] = 12;
  out.mJc[4] = 12;
  out.mJc[5] = 13;
  out.mJc[6] = 13;
  out.mJc[7] = 15;
  out.mJc[8] = 16;
  out.mJc[9] = 22;
  out.mJc[10] = 23;
  out.mJc[11] = 29;
  out.mJc[12] = 31;
  out.mJc[13] = 32;
  out.mJc[14] = 34;
  out.mJc[15] = 38;
  out.mJc[16] = 42;
  out.mJc[17] = 43;
  out.mJc[18] = 44;
  out.mJc[19] = 46;
  out.mJc[20] = 48;
  out.mJc[21] = 50;
  out.mJc[22] = 52;
  out.mJc[23] = 54;
  out.mJc[24] = 56;
  out.mIr[0] = 10;
  out.mIr[1] = 12;
  out.mIr[2] = 14;
  out.mIr[3] = 15;
  out.mIr[4] = 18;
  out.mIr[5] = 19;
  out.mIr[6] = 10;
  out.mIr[7] = 12;
  out.mIr[8] = 16;
  out.mIr[9] = 17;
  out.mIr[10] = 20;
  out.mIr[11] = 21;
  out.mIr[12] = 10;
  out.mIr[13] = 14;
  out.mIr[14] = 16;
  out.mIr[15] = 14;
  out.mIr[16] = 10;
  out.mIr[17] = 12;
  out.mIr[18] = 14;
  out.mIr[19] = 15;
  out.mIr[20] = 18;
  out.mIr[21] = 19;
  out.mIr[22] = 16;
  out.mIr[23] = 10;
  out.mIr[24] = 12;
  out.mIr[25] = 16;
  out.mIr[26] = 17;
  out.mIr[27] = 20;
  out.mIr[28] = 21;
  out.mIr[29] = 10;
  out.mIr[30] = 11;
  out.mIr[31] = 10;
  out.mIr[32] = 10;
  out.mIr[33] = 11;
  out.mIr[34] = 10;
  out.mIr[35] = 11;
  out.mIr[36] = 12;
  out.mIr[37] = 13;
  out.mIr[38] = 10;
  out.mIr[39] = 12;
  out.mIr[40] = 14;
  out.mIr[41] = 16;
  out.mIr[42] = 12;
  out.mIr[43] = 13;
  out.mIr[44] = 14;
  out.mIr[45] = 15;
  out.mIr[46] = 14;
  out.mIr[47] = 18;
  out.mIr[48] = 14;
  out.mIr[49] = 19;
  out.mIr[50] = 16;
  out.mIr[51] = 17;
  out.mIr[52] = 16;
  out.mIr[53] = 20;
  out.mIr[54] = 16;
  out.mIr[55] = 21;
  (void)sys;
  (void)t2;
  return 0;
}
