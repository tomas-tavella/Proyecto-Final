/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'Simulacion_simscape/Solver Configuration'.
 */

#include "ne_ds.h"
#include "Simulacion_simscape_8d5561a5_1_ds_dxf.h"
#include "Simulacion_simscape_8d5561a5_1_ds_sys_struct.h"
#include "Simulacion_simscape_8d5561a5_1_ds_externals.h"
#include "Simulacion_simscape_8d5561a5_1_ds_external_struct.h"
#include "ssc_ml_fun.h"

int32_T Simulacion_simscape_8d5561a5_1_ds_dxf(const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t73, NeDsMethodOutput *t74)
{
  PmRealVector out;
  real_T t0;
  real_T t1;
  real_T t2;
  real_T t3;
  real_T t4;
  real_T t5;
  real_T t6;
  real_T t7;
  real_T t8;
  real_T t9;
  real_T t10;
  real_T t11;
  real_T t12;
  real_T t13;
  real_T t14;
  real_T t15;
  real_T t16;
  real_T t17;
  real_T t18;
  real_T t19;
  real_T t20;
  real_T t21;
  real_T t22;
  real_T t24[56];
  real_T t25[6];
  real_T t26[6];
  real_T t28[6];
  real_T t29[6];
  real_T t32[4];
  real_T t33[4];
  size_t t48;
  real_T t72;
  int32_T M_idx_0;
  int32_T M_idx_4;
  int32_T M_idx_6;
  int32_T M_idx_10;
  int32_T M_idx_8;
  int32_T M_idx_2;
  int32_T M_idx_1;
  int32_T M_idx_5;
  int32_T M_idx_7;
  int32_T M_idx_11;
  int32_T M_idx_9;
  int32_T M_idx_3;
  M_idx_0 = t73->mM.mX[0];
  M_idx_1 = t73->mM.mX[1];
  M_idx_2 = t73->mM.mX[2];
  M_idx_3 = t73->mM.mX[3];
  M_idx_4 = t73->mM.mX[4];
  M_idx_5 = t73->mM.mX[5];
  M_idx_6 = t73->mM.mX[6];
  M_idx_7 = t73->mM.mX[7];
  M_idx_8 = t73->mM.mX[8];
  M_idx_9 = t73->mM.mX[9];
  M_idx_10 = t73->mM.mX[10];
  M_idx_11 = t73->mM.mX[11];
  out = t74->mDXF;
  if (M_idx_0 != 0) {
    t0 = -333.33333333333331;
  } else {
    t0 = -3.3333333333333333E-6;
  }

  if (M_idx_4 != 0) {
    t1 = 333.33333333333331;
  } else {
    t1 = 3.3333333333333333E-6;
  }

  if (M_idx_6 != 0) {
    t2 = -1000.0;
  } else {
    t2 = -1.0E-5;
  }

  if (M_idx_10 != 0) {
    t3 = 1000.0;
  } else {
    t3 = 1.0E-5;
  }

  if (M_idx_0 != 0) {
    t4 = 333.33333333333331;
  } else {
    t4 = 3.3333333333333333E-6;
  }

  if (M_idx_4 != 0) {
    t5 = -333.33333333333331;
  } else {
    t5 = -3.3333333333333333E-6;
  }

  if (M_idx_8 != 0) {
    t6 = -1000.0;
  } else {
    t6 = -1.0E-5;
  }

  if (M_idx_2 != 0) {
    t7 = 1000.0;
  } else {
    t7 = 1.0E-5;
  }

  if (M_idx_0 != 0) {
    t8 = -0.00033333333333333332;
  } else {
    t8 = -3.3333333333333331E-12;
  }

  if (M_idx_4 != 0) {
    t9 = 0.00033333333333333332;
  } else {
    t9 = 3.3333333333333331E-12;
  }

  if (M_idx_6 != 0) {
    t10 = -1.001;
  } else {
    t10 = -1.00000000001;
  }

  if (M_idx_10 != 0) {
    t11 = 0.001;
  } else {
    t11 = 1.0000000000000001E-11;
  }

  if (M_idx_0 != 0) {
    t12 = 0.00033333333333333332;
  } else {
    t12 = 3.3333333333333331E-12;
  }

  if (M_idx_4 != 0) {
    t13 = -0.00033333333333333332;
  } else {
    t13 = -3.3333333333333331E-12;
  }

  if (M_idx_8 != 0) {
    t14 = -1.001;
  } else {
    t14 = -1.00000000001;
  }

  if (M_idx_2 != 0) {
    t15 = 0.001;
  } else {
    t15 = 1.0000000000000001E-11;
  }

  if (M_idx_0 != 0) {
    t16 = 1000.0;
  } else {
    t16 = 1.0E-5;
  }

  if (M_idx_1 != 0) {
    t17 = 1000.0;
  } else {
    t17 = 1.0E-5;
  }

  if (M_idx_0 != 0) {
    t18 = -1000.0;
  } else {
    t18 = -1.0E-5;
  }

  if (M_idx_1 != 0) {
    t19 = -1000.0;
  } else {
    t19 = -1.0E-5;
  }

  if (M_idx_4 != 0) {
    t20 = 1000.0;
  } else {
    t20 = 1.0E-5;
  }

  if (M_idx_5 != 0) {
    t21 = 1000.0;
  } else {
    t21 = 1.0E-5;
  }

  if (M_idx_0 != 0) {
    t22 = 333.33333333333331;
  } else {
    t22 = 3.3333333333333333E-6;
  }

  if (M_idx_4 != 0) {
    t72 = -333.33333333333331;
  } else {
    t72 = -3.3333333333333333E-6;
  }

  t25[0UL] = t0;
  t25[1UL] = t1;
  t25[2UL] = t2;
  t25[3UL] = -1.0E-6;
  t25[4UL] = t3;
  t25[5UL] = 1.0E-6;
  t26[0UL] = t4;
  t26[1UL] = t5;
  t26[2UL] = t6;
  t26[3UL] = -1.0E-6;
  t26[4UL] = t7;
  t26[5UL] = 1.0E-6;
  t28[0UL] = t8;
  t28[1UL] = t9;
  t28[2UL] = t10;
  t28[3UL] = -1.0E-12;
  t28[4UL] = t11;
  t28[5UL] = 1.0E-12;
  t29[0UL] = t12;
  t29[1UL] = t13;
  t29[2UL] = t14;
  t29[3UL] = -1.0E-12;
  t29[4UL] = t15;
  t29[5UL] = 1.0E-12;
  t32[0UL] = t18;
  t32[1UL] = t19;
  t32[2UL] = t20;
  t32[3UL] = t21;
  t33[0UL] = t22;
  t33[1UL] = t72;
  t33[2UL] = -1.0E-9;
  t33[3UL] = 1.0E-9;
  for (t48 = 0UL; t48 < 6UL; t48++) {
    t24[t48] = t25[t48];
  }

  for (t48 = 0UL; t48 < 6UL; t48++) {
    t24[t48 + 6UL] = t26[t48];
  }

  t24[12UL] = 1.0;
  t24[13UL] = -1.0;
  t24[14UL] = 1.0;
  t24[15UL] = 1.0;
  for (t48 = 0UL; t48 < 6UL; t48++) {
    t24[t48 + 16UL] = t28[t48];
  }

  t24[22UL] = 1.0;
  for (t48 = 0UL; t48 < 6UL; t48++) {
    t24[t48 + 23UL] = t29[t48];
  }

  t24[29UL] = t16;
  t24[30UL] = t17;
  t24[31UL] = 1.0E-9;
  t24[32UL] = -1.0;
  t24[33UL] = 1.0;
  for (t48 = 0UL; t48 < 4UL; t48++) {
    t24[t48 + 34UL] = t32[t48];
  }

  for (t48 = 0UL; t48 < 4UL; t48++) {
    t24[t48 + 38UL] = t33[t48];
  }

  out.mX[0] = t24[0];
  out.mX[1] = t24[1];
  out.mX[2] = t24[2];
  out.mX[3] = t24[3];
  out.mX[4] = t24[4];
  out.mX[5] = t24[5];
  out.mX[6] = t24[6];
  out.mX[7] = t24[7];
  out.mX[8] = t24[8];
  out.mX[9] = t24[9];
  out.mX[10] = t24[10];
  out.mX[11] = t24[11];
  out.mX[12] = t24[12];
  out.mX[13] = t24[13];
  out.mX[14] = t24[14];
  out.mX[15] = t24[15];
  out.mX[16] = t24[16];
  out.mX[17] = t24[17];
  out.mX[18] = t24[18];
  out.mX[19] = t24[19];
  out.mX[20] = t24[20];
  out.mX[21] = t24[21];
  out.mX[22] = t24[22];
  out.mX[23] = t24[23];
  out.mX[24] = t24[24];
  out.mX[25] = t24[25];
  out.mX[26] = t24[26];
  out.mX[27] = t24[27];
  out.mX[28] = t24[28];
  out.mX[29] = t24[29];
  out.mX[30] = t24[30];
  out.mX[31] = t24[31];
  out.mX[32] = t24[32];
  out.mX[33] = t24[33];
  out.mX[34] = t24[34];
  out.mX[35] = t24[35];
  out.mX[36] = t24[36];
  out.mX[37] = t24[37];
  out.mX[38] = t24[38];
  out.mX[39] = t24[39];
  out.mX[40] = t24[40];
  out.mX[41] = t24[41];
  out.mX[42] = 1.0;
  out.mX[43] = 1.0;
  out.mX[44] = 1.0;
  out.mX[45] = (M_idx_7 != 0 ? -0.01 : -1.0E+6) * 1.0E-6;
  out.mX[46] = 1.0;
  out.mX[47] = 1.0;
  out.mX[48] = -1.0;
  out.mX[49] = (M_idx_11 != 0 ? -0.01 : -1.0E+6) * 1.0E-6;
  out.mX[50] = 1.0;
  out.mX[51] = (M_idx_9 != 0 ? -0.01 : -1.0E+6) * 1.0E-6;
  out.mX[52] = 1.0;
  out.mX[53] = 1.0;
  out.mX[54] = -1.0;
  out.mX[55] = (M_idx_3 != 0 ? -0.01 : -1.0E+6) * 1.0E-6;
  (void)sys;
  (void)t74;
  return 0;
}
