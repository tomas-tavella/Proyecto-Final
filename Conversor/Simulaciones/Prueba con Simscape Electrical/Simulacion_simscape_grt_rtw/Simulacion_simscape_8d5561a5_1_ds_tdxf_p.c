/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'Simulacion_simscape/Solver Configuration'.
 */

#include "ne_ds.h"
#include "Simulacion_simscape_8d5561a5_1_ds_tdxf_p.h"
#include "Simulacion_simscape_8d5561a5_1_ds_sys_struct.h"
#include "Simulacion_simscape_8d5561a5_1_ds_externals.h"
#include "Simulacion_simscape_8d5561a5_1_ds_external_struct.h"
#include "ssc_ml_fun.h"

int32_T Simulacion_simscape_8d5561a5_1_ds_tdxf_p(const NeDynamicSystem *sys,
  const NeDynamicSystemInput *t1, NeDsMethodOutput *t2)
{
  PmSparsityPattern out;
  (void)t1;
  out = t2->mTDXF_P;
  out.mNumCol = 24UL;
  out.mNumRow = 24UL;
  out.mJc[0] = 0;
  out.mJc[1] = 8;
  out.mJc[2] = 10;
  out.mJc[3] = 18;
  out.mJc[4] = 20;
  out.mJc[5] = 25;
  out.mJc[6] = 27;
  out.mJc[7] = 32;
  out.mJc[8] = 35;
  out.mJc[9] = 43;
  out.mJc[10] = 46;
  out.mJc[11] = 54;
  out.mJc[12] = 58;
  out.mJc[13] = 63;
  out.mJc[14] = 67;
  out.mJc[15] = 71;
  out.mJc[16] = 78;
  out.mJc[17] = 80;
  out.mJc[18] = 82;
  out.mJc[19] = 84;
  out.mJc[20] = 86;
  out.mJc[21] = 88;
  out.mJc[22] = 90;
  out.mJc[23] = 92;
  out.mJc[24] = 94;
  out.mIr[0] = 2;
  out.mIr[1] = 7;
  out.mIr[2] = 10;
  out.mIr[3] = 12;
  out.mIr[4] = 14;
  out.mIr[5] = 15;
  out.mIr[6] = 18;
  out.mIr[7] = 19;
  out.mIr[8] = 0;
  out.mIr[9] = 7;
  out.mIr[10] = 3;
  out.mIr[11] = 8;
  out.mIr[12] = 10;
  out.mIr[13] = 12;
  out.mIr[14] = 16;
  out.mIr[15] = 17;
  out.mIr[16] = 20;
  out.mIr[17] = 21;
  out.mIr[18] = 1;
  out.mIr[19] = 8;
  out.mIr[20] = 4;
  out.mIr[21] = 5;
  out.mIr[22] = 9;
  out.mIr[23] = 10;
  out.mIr[24] = 22;
  out.mIr[25] = 4;
  out.mIr[26] = 9;
  out.mIr[27] = 6;
  out.mIr[28] = 14;
  out.mIr[29] = 16;
  out.mIr[30] = 22;
  out.mIr[31] = 23;
  out.mIr[32] = 0;
  out.mIr[33] = 7;
  out.mIr[34] = 14;
  out.mIr[35] = 2;
  out.mIr[36] = 7;
  out.mIr[37] = 10;
  out.mIr[38] = 12;
  out.mIr[39] = 14;
  out.mIr[40] = 15;
  out.mIr[41] = 18;
  out.mIr[42] = 19;
  out.mIr[43] = 1;
  out.mIr[44] = 8;
  out.mIr[45] = 16;
  out.mIr[46] = 3;
  out.mIr[47] = 8;
  out.mIr[48] = 10;
  out.mIr[49] = 12;
  out.mIr[50] = 16;
  out.mIr[51] = 17;
  out.mIr[52] = 20;
  out.mIr[53] = 21;
  out.mIr[54] = 4;
  out.mIr[55] = 9;
  out.mIr[56] = 10;
  out.mIr[57] = 11;
  out.mIr[58] = 4;
  out.mIr[59] = 5;
  out.mIr[60] = 9;
  out.mIr[61] = 10;
  out.mIr[62] = 22;
  out.mIr[63] = 10;
  out.mIr[64] = 11;
  out.mIr[65] = 22;
  out.mIr[66] = 23;
  out.mIr[67] = 10;
  out.mIr[68] = 11;
  out.mIr[69] = 12;
  out.mIr[70] = 13;
  out.mIr[71] = 6;
  out.mIr[72] = 10;
  out.mIr[73] = 12;
  out.mIr[74] = 14;
  out.mIr[75] = 16;
  out.mIr[76] = 22;
  out.mIr[77] = 23;
  out.mIr[78] = 12;
  out.mIr[79] = 22;
  out.mIr[80] = 13;
  out.mIr[81] = 23;
  out.mIr[82] = 14;
  out.mIr[83] = 15;
  out.mIr[84] = 14;
  out.mIr[85] = 18;
  out.mIr[86] = 14;
  out.mIr[87] = 19;
  out.mIr[88] = 16;
  out.mIr[89] = 17;
  out.mIr[90] = 16;
  out.mIr[91] = 20;
  out.mIr[92] = 16;
  out.mIr[93] = 21;
  (void)sys;
  (void)t2;
  return 0;
}
