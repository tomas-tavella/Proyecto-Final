/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'Simulacion_simscape/Solver Configuration'.
 */

#include "ne_ds.h"
#include "Simulacion_simscape_8d5561a5_1_ds_f.h"
#include "Simulacion_simscape_8d5561a5_1_ds_sys_struct.h"
#include "Simulacion_simscape_8d5561a5_1_ds_externals.h"
#include "Simulacion_simscape_8d5561a5_1_ds_external_struct.h"
#include "ssc_ml_fun.h"

int32_T Simulacion_simscape_8d5561a5_1_ds_f(const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t25, NeDsMethodOutput *t26)
{
  PmRealVector out;
  real_T C2_n_v;
  real_T t1;
  real_T t2;
  real_T t3;
  real_T t4;
  real_T t6;
  real_T t7;
  real_T t8;
  real_T t9;
  real_T t10;
  real_T X_idx_8;
  real_T X_idx_0;
  real_T X_idx_10;
  real_T X_idx_2;
  real_T X_idx_13;
  real_T X_idx_12;
  real_T X_idx_4;
  real_T X_idx_11;
  real_T X_idx_15;
  real_T X_idx_14;
  real_T X_idx_6;
  real_T X_idx_20;
  real_T X_idx_7;
  real_T X_idx_18;
  real_T X_idx_19;
  real_T X_idx_23;
  real_T X_idx_9;
  real_T X_idx_21;
  real_T X_idx_22;
  int32_T M_idx_0;
  int32_T M_idx_1;
  int32_T M_idx_4;
  real_T X_idx_16;
  int32_T M_idx_5;
  real_T X_idx_17;
  int32_T M_idx_6;
  int32_T M_idx_7;
  int32_T M_idx_8;
  int32_T M_idx_9;
  int32_T M_idx_10;
  int32_T M_idx_11;
  int32_T M_idx_2;
  int32_T M_idx_3;
  M_idx_0 = t25->mM.mX[0];
  M_idx_1 = t25->mM.mX[1];
  M_idx_2 = t25->mM.mX[2];
  M_idx_3 = t25->mM.mX[3];
  M_idx_4 = t25->mM.mX[4];
  M_idx_5 = t25->mM.mX[5];
  M_idx_6 = t25->mM.mX[6];
  M_idx_7 = t25->mM.mX[7];
  M_idx_8 = t25->mM.mX[8];
  M_idx_9 = t25->mM.mX[9];
  M_idx_10 = t25->mM.mX[10];
  M_idx_11 = t25->mM.mX[11];
  X_idx_0 = t25->mX.mX[0];
  X_idx_2 = t25->mX.mX[2];
  X_idx_4 = t25->mX.mX[4];
  X_idx_6 = t25->mX.mX[6];
  X_idx_7 = t25->mX.mX[7];
  X_idx_8 = t25->mX.mX[8];
  X_idx_9 = t25->mX.mX[9];
  X_idx_10 = t25->mX.mX[10];
  X_idx_11 = t25->mX.mX[11];
  X_idx_12 = t25->mX.mX[12];
  X_idx_13 = t25->mX.mX[13];
  X_idx_14 = t25->mX.mX[14];
  X_idx_15 = t25->mX.mX[15];
  X_idx_16 = t25->mX.mX[16];
  X_idx_17 = t25->mX.mX[17];
  X_idx_18 = t25->mX.mX[18];
  X_idx_19 = t25->mX.mX[19];
  X_idx_20 = t25->mX.mX[20];
  X_idx_21 = t25->mX.mX[21];
  X_idx_22 = t25->mX.mX[22];
  X_idx_23 = t25->mX.mX[23];
  out = t26->mF;
  t10 = X_idx_8 * 1.0E-6 + X_idx_0;
  t6 = (-X_idx_0 + X_idx_8 * -1.0E-6) + 250.0;
  C2_n_v = X_idx_10 * 1.0E-6 + X_idx_2;
  t8 = (-X_idx_2 + X_idx_10 * -1.0E-6) + 250.0;
  t1 = (-X_idx_13 + X_idx_12 * 1.0E-9) + X_idx_4;
  t2 = (((((X_idx_0 * 0.33333333333333331 + X_idx_2 * -0.33333333333333331) +
           X_idx_8 * 3.333333333333333E-7) + X_idx_10 * -3.333333333333333E-7) +
         -X_idx_11) + X_idx_15 * -0.33333333333333331) + X_idx_14;
  t3 = -X_idx_11 + X_idx_14;
  t4 = ((((X_idx_0 * -0.33333333333333331 + X_idx_2 * 0.33333333333333331) +
          X_idx_8 * -3.333333333333333E-7) + X_idx_10 * 3.333333333333333E-7) +
        -X_idx_14) + X_idx_15 * 0.33333333333333331;
  t7 = (((((-X_idx_6 + -X_idx_8) + X_idx_15 * -1.0E-9) + -X_idx_20) + X_idx_7) +
        X_idx_18) + X_idx_19;
  t9 = (X_idx_8 * 1.0E-6 + X_idx_0) + -250.0;
  X_idx_6 = (((((-X_idx_10 + X_idx_15 * 1.0E-9) + -X_idx_23) + X_idx_9) +
              X_idx_6) + X_idx_21) + X_idx_22;
  X_idx_9 = (X_idx_10 * 1.0E-6 + X_idx_2) + -250.0;
  X_idx_7 = -X_idx_0 + X_idx_8 * -1.0E-6;
  X_idx_12 = -X_idx_2 + X_idx_10 * -1.0E-6;
  if (M_idx_0 != 0) {
    X_idx_11 = t1 - (t2 - 1.4999999849999999) / 0.001;
  } else {
    X_idx_11 = t1 - t2 * 1.0E-5;
  }

  if (M_idx_1 != 0) {
    t1 = X_idx_13 - (t3 - 1.4999999849999999) / 0.001;
  } else {
    t1 = X_idx_13 - t3 * 1.0E-5;
  }

  if (M_idx_4 != 0) {
    t2 = X_idx_16 - (t4 - 1.4999999849999999) / 0.001;
  } else {
    t2 = X_idx_16 - t4 * 1.0E-5;
  }

  if (M_idx_5 != 0) {
    t3 = X_idx_17 - (-X_idx_14 - 1.4999999849999999) / 0.001;
  } else {
    t3 = X_idx_17 - -X_idx_14 * 1.0E-5;
  }

  if (M_idx_6 != 0) {
    t4 = t7 - (t9 - 0.799999992) / 0.001;
  } else {
    t4 = t7 - t9 * 1.0E-5;
  }

  if (M_idx_7 != 0) {
    X_idx_4 = t6 - X_idx_18 * 0.01;
  } else {
    X_idx_4 = t6 - X_idx_18 / 1.0E-6;
  }

  if (M_idx_8 != 0) {
    t6 = X_idx_6 - (X_idx_9 - 0.799999992) / 0.001;
  } else {
    t6 = X_idx_6 - X_idx_9 * 1.0E-5;
  }

  if (M_idx_9 != 0) {
    t7 = t8 - X_idx_21 * 0.01;
  } else {
    t7 = t8 - X_idx_21 / 1.0E-6;
  }

  if (M_idx_10 != 0) {
    t8 = X_idx_19 - (X_idx_7 - 0.799999992) / 0.001;
  } else {
    t8 = X_idx_19 - X_idx_7 * 1.0E-5;
  }

  if (M_idx_11 != 0) {
    t9 = t10 - X_idx_20 * 0.01;
  } else {
    t9 = t10 - X_idx_20 / 1.0E-6;
  }

  if (M_idx_2 != 0) {
    t10 = X_idx_22 - (X_idx_12 - 0.799999992) / 0.001;
  } else {
    t10 = X_idx_22 - X_idx_12 * 1.0E-5;
  }

  if (M_idx_3 != 0) {
    X_idx_6 = C2_n_v - X_idx_23 * 0.01;
  } else {
    X_idx_6 = C2_n_v - X_idx_23 / 1.0E-6;
  }

  out.mX[0] = -0.0;
  out.mX[1] = -0.0;
  out.mX[2] = -0.0;
  out.mX[3] = -0.0;
  out.mX[4] = -0.0;
  out.mX[5] = -0.0;
  out.mX[6] = -0.0;
  out.mX[7] = 250.0;
  out.mX[8] = 250.0;
  out.mX[9] = 0.0;
  out.mX[10] = X_idx_11;
  out.mX[11] = t1;
  out.mX[12] = t2;
  out.mX[13] = t3;
  out.mX[14] = t4;
  out.mX[15] = X_idx_4 / 1.0E+6;
  out.mX[16] = t6;
  out.mX[17] = t7 / 1.0E+6;
  out.mX[18] = t8;
  out.mX[19] = t9 / 1.0E+6;
  out.mX[20] = t10;
  out.mX[21] = X_idx_6 / 1.0E+6;
  out.mX[22] = -0.0;
  out.mX[23] = -0.0;
  (void)sys;
  (void)t26;
  return 0;
}
