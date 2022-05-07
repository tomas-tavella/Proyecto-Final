/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'Simulacion_simscape/Solver Configuration'.
 */

#include "ne_ds.h"
#include "Simulacion_simscape_8d5561a5_1_ds_mode.h"
#include "Simulacion_simscape_8d5561a5_1_ds_sys_struct.h"
#include "Simulacion_simscape_8d5561a5_1_ds_externals.h"
#include "Simulacion_simscape_8d5561a5_1_ds_external_struct.h"
#include "ssc_ml_fun.h"

int32_T Simulacion_simscape_8d5561a5_1_ds_mode(const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *t2)
{
  PmIntVector out;
  real_T X_idx_0;
  real_T X_idx_2;
  real_T X_idx_8;
  real_T X_idx_10;
  real_T X_idx_11;
  real_T X_idx_15;
  real_T X_idx_14;
  real_T U_idx_3;
  real_T U_idx_0;
  real_T U_idx_1;
  real_T U_idx_2;
  U_idx_0 = t1->mU.mX[0];
  U_idx_1 = t1->mU.mX[1];
  U_idx_2 = t1->mU.mX[2];
  U_idx_3 = t1->mU.mX[3];
  X_idx_0 = t1->mX.mX[0];
  X_idx_2 = t1->mX.mX[2];
  X_idx_8 = t1->mX.mX[8];
  X_idx_10 = t1->mX.mX[10];
  X_idx_11 = t1->mX.mX[11];
  X_idx_14 = t1->mX.mX[14];
  X_idx_15 = t1->mX.mX[15];
  out = t2->mMODE;
  out.mX[0] = (int32_T)((((((X_idx_0 * 0.33333333333333331 + X_idx_2 *
    -0.33333333333333331) + X_idx_8 * 3.333333333333333E-7) + X_idx_10 *
    -3.333333333333333E-7) + -X_idx_11) + X_idx_15 * -0.33333333333333331) +
                        X_idx_14 > 1.5);
  out.mX[1] = (int32_T)(-X_idx_11 + X_idx_14 > 1.5);
  out.mX[2] = (int32_T)(-X_idx_2 + X_idx_10 * -1.0E-6 > 0.8);
  out.mX[3] = (int32_T)(U_idx_3 > 2.0);
  out.mX[4] = (int32_T)(((((X_idx_0 * -0.33333333333333331 + X_idx_2 *
    0.33333333333333331) + X_idx_8 * -3.333333333333333E-7) + X_idx_10 *
    3.333333333333333E-7) + -X_idx_14) + X_idx_15 * 0.33333333333333331 > 1.5);
  out.mX[5] = (int32_T)(-X_idx_14 > 1.5);
  out.mX[6] = (int32_T)((X_idx_8 * 1.0E-6 + X_idx_0) + -250.0 > 0.8);
  out.mX[7] = (int32_T)(U_idx_0 > 2.0);
  out.mX[8] = (int32_T)((X_idx_10 * 1.0E-6 + X_idx_2) + -250.0 > 0.8);
  out.mX[9] = (int32_T)(U_idx_1 > 2.0);
  out.mX[10] = (int32_T)(-X_idx_0 + X_idx_8 * -1.0E-6 > 0.8);
  out.mX[11] = (int32_T)(U_idx_2 > 2.0);
  (void)sys;
  (void)t2;
  return 0;
}
