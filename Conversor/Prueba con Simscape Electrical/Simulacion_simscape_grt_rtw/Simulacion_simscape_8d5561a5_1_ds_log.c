/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'Simulacion_simscape/Solver Configuration'.
 */

#include "ne_ds.h"
#include "Simulacion_simscape_8d5561a5_1_ds_log.h"
#include "Simulacion_simscape_8d5561a5_1_ds_sys_struct.h"
#include "Simulacion_simscape_8d5561a5_1_ds_externals.h"
#include "Simulacion_simscape_8d5561a5_1_ds_external_struct.h"
#include "ssc_ml_fun.h"

int32_T Simulacion_simscape_8d5561a5_1_ds_log(const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t27, NeDsMethodOutput *t28)
{
  PmRealVector out;
  real_T C1_n_v;
  real_T C2_n_v;
  real_T Cf_p_v;
  real_T Diode_i;
  real_T Diode_p_v;
  real_T Diode_v;
  real_T Ideal_Transformer_p1_v;
  real_T Ideal_Transformer_v1;
  real_T Q1_diode_v;
  real_T Q2_diode_v;
  real_T t0[162];
  real_T t1;
  real_T t2;
  real_T t4;
  real_T t5;
  real_T t6;
  real_T t7;
  real_T t9;
  real_T t11;
  real_T t14;
  real_T t17;
  real_T t20;
  real_T t23;
  real_T t24;
  real_T t25;
  int32_T b;
  real_T X_idx_8;
  real_T X_idx_0;
  real_T X_idx_7;
  real_T X_idx_10;
  real_T X_idx_2;
  real_T X_idx_9;
  real_T X_idx_11;
  real_T X_idx_12;
  real_T X_idx_4;
  real_T X_idx_13;
  real_T X_idx_15;
  real_T X_idx_14;
  real_T X_idx_16;
  real_T X_idx_17;
  real_T X_idx_6;
  real_T X_idx_20;
  real_T X_idx_18;
  real_T X_idx_19;
  real_T U_idx_0;
  real_T X_idx_23;
  real_T X_idx_21;
  real_T X_idx_22;
  real_T U_idx_1;
  real_T U_idx_2;
  real_T U_idx_3;
  real_T X_idx_1;
  real_T X_idx_3;
  real_T X_idx_5;
  U_idx_0 = t27->mU.mX[0];
  U_idx_1 = t27->mU.mX[1];
  U_idx_2 = t27->mU.mX[2];
  U_idx_3 = t27->mU.mX[3];
  X_idx_0 = t27->mX.mX[0];
  X_idx_1 = t27->mX.mX[1];
  X_idx_2 = t27->mX.mX[2];
  X_idx_3 = t27->mX.mX[3];
  X_idx_4 = t27->mX.mX[4];
  X_idx_5 = t27->mX.mX[5];
  X_idx_6 = t27->mX.mX[6];
  X_idx_7 = t27->mX.mX[7];
  X_idx_8 = t27->mX.mX[8];
  X_idx_9 = t27->mX.mX[9];
  X_idx_10 = t27->mX.mX[10];
  X_idx_11 = t27->mX.mX[11];
  X_idx_12 = t27->mX.mX[12];
  X_idx_13 = t27->mX.mX[13];
  X_idx_14 = t27->mX.mX[14];
  X_idx_15 = t27->mX.mX[15];
  X_idx_16 = t27->mX.mX[16];
  X_idx_17 = t27->mX.mX[17];
  X_idx_18 = t27->mX.mX[18];
  X_idx_19 = t27->mX.mX[19];
  X_idx_20 = t27->mX.mX[20];
  X_idx_21 = t27->mX.mX[21];
  X_idx_22 = t27->mX.mX[22];
  X_idx_23 = t27->mX.mX[23];
  out = t28->mLOG;
  C1_n_v = X_idx_8 * 1.0E-6 + X_idx_0;
  t1 = (-X_idx_0 + X_idx_8 * -1.0E-6) + 250.0;
  C2_n_v = X_idx_10 * 1.0E-6 + X_idx_2;
  t2 = (-X_idx_2 + X_idx_10 * -1.0E-6) + 250.0;
  t4 = (X_idx_11 * -0.18518518518518517 + X_idx_12 * 0.18518518618518517) +
    X_idx_4;
  Cf_p_v = -X_idx_12 + X_idx_11;
  t5 = X_idx_11 * 0.18518518518518517 + X_idx_12 * -0.18518518518518517;
  Diode_i = (-X_idx_13 + X_idx_12 * 1.0E-9) + X_idx_4;
  Diode_p_v = ((((X_idx_0 * 0.33333333333333331 + X_idx_2 * -0.33333333333333331)
                 + X_idx_8 * 3.333333333333333E-7) + X_idx_10 *
                -3.333333333333333E-7) + X_idx_15 * -0.33333333333333331) +
    X_idx_14;
  Diode_v = (((((X_idx_0 * 0.33333333333333331 + X_idx_2 * -0.33333333333333331)
                + X_idx_8 * 3.333333333333333E-7) + X_idx_10 *
               -3.333333333333333E-7) + -X_idx_11) + X_idx_15 *
             -0.33333333333333331) + X_idx_14;
  t6 = -X_idx_11 + X_idx_14;
  t7 = ((((X_idx_0 * -0.33333333333333331 + X_idx_2 * 0.33333333333333331) +
          X_idx_8 * -3.333333333333333E-7) + X_idx_10 * 3.333333333333333E-7) +
        -X_idx_14) + X_idx_15 * 0.33333333333333331;
  t9 = X_idx_15 * 1.0E-9 + X_idx_6;
  Ideal_Transformer_p1_v = (X_idx_8 * 1.0E-6 + -X_idx_15) + X_idx_0;
  Ideal_Transformer_v1 = (((-X_idx_2 + X_idx_8 * 1.0E-6) + X_idx_10 * -1.0E-6) +
    -X_idx_15) + X_idx_0;
  t11 = (((((-X_idx_6 + -X_idx_8) + X_idx_15 * -1.0E-9) + -X_idx_20) + X_idx_7)
         + X_idx_18) + X_idx_19;
  Q1_diode_v = (X_idx_8 * 1.0E-6 + X_idx_0) + -250.0;
  t14 = (((((-X_idx_10 + X_idx_15 * 1.0E-9) + -X_idx_23) + X_idx_9) + X_idx_6) +
         X_idx_21) + X_idx_22;
  Q2_diode_v = (X_idx_10 * 1.0E-6 + X_idx_2) + -250.0;
  t17 = -X_idx_0 + X_idx_8 * -1.0E-6;
  t20 = -X_idx_2 + X_idx_10 * -1.0E-6;
  t23 = -Cf_p_v / -1.0;
  t24 = -X_idx_11 / -1.0;
  t25 = -(C1_n_v - C2_n_v) / -1.0;
  t0[0UL] = X_idx_7;
  t0[1UL] = C1_n_v;
  t0[2UL] = 250.0;
  t0[3UL] = -(X_idx_7 * X_idx_7 * 1.0E-9) / -1.0 * 1000.0;
  t0[4UL] = t1;
  t0[5UL] = X_idx_1;
  t0[6UL] = X_idx_9;
  t0[7UL] = C2_n_v;
  t0[8UL] = 250.0;
  t0[9UL] = -(X_idx_9 * X_idx_9 * 1.0E-9) / -1.0 * 1000.0;
  t0[10UL] = t2;
  t0[11UL] = X_idx_3;
  t0[12UL] = X_idx_8;
  t0[13UL] = 0.0;
  t0[14UL] = C1_n_v;
  t0[15UL] = -(X_idx_8 * X_idx_8 * 1.0E-9) / -1.0 * 1000.0;
  t0[16UL] = C1_n_v;
  t0[17UL] = X_idx_0;
  t0[18UL] = X_idx_10;
  t0[19UL] = 0.0;
  t0[20UL] = C2_n_v;
  t0[21UL] = -(X_idx_10 * X_idx_10 * 1.0E-9) / -1.0 * 1000.0;
  t0[22UL] = C2_n_v;
  t0[23UL] = X_idx_2;
  t0[24UL] = t4;
  t0[25UL] = 0.0;
  t0[26UL] = Cf_p_v;
  t0[27UL] = -(t4 * t4 * 1.0E-9) / -1.0 * 1000.0;
  t0[28UL] = Cf_p_v;
  t0[29UL] = X_idx_5;
  t0[30UL] = t5;
  t0[31UL] = t5;
  t0[32UL] = 0.0;
  t0[33UL] = 0.0;
  t0[34UL] = 0.0;
  t0[35UL] = Diode_i;
  t0[36UL] = X_idx_11;
  t0[37UL] = Diode_p_v;
  t0[38UL] = -(Diode_i * Diode_v * 0.001) / -1.0 * 1000.0;
  t0[39UL] = Diode_v;
  t0[40UL] = X_idx_13;
  t0[41UL] = X_idx_11;
  t0[42UL] = X_idx_14;
  t0[43UL] = -(X_idx_13 * t6 * 0.001) / -1.0 * 1000.0;
  t0[44UL] = t6;
  t0[45UL] = X_idx_16;
  t0[46UL] = Diode_p_v;
  t0[47UL] = 0.0;
  t0[48UL] = -(X_idx_16 * t7 * 0.001) / -1.0 * 1000.0;
  t0[49UL] = t7;
  t0[50UL] = X_idx_17;
  t0[51UL] = X_idx_14;
  t0[52UL] = 0.0;
  t0[53UL] = -(X_idx_17 * -X_idx_14 * 0.001) / -1.0 * 1000.0;
  t0[54UL] = -X_idx_14;
  t0[55UL] = 0.0;
  t0[56UL] = 0.0;
  t0[57UL] = 0.0;
  t0[58UL] = 0.0;
  t0[59UL] = t9;
  t0[60UL] = t9 * -3.0;
  t0[61UL] = C2_n_v;
  t0[62UL] = X_idx_14;
  t0[63UL] = Ideal_Transformer_p1_v;
  t0[64UL] = Diode_p_v;
  t0[65UL] = Ideal_Transformer_v1;
  t0[66UL] = Ideal_Transformer_v1 * 0.33333333333333331;
  t0[67UL] = X_idx_12 * 1.0E-9 + X_idx_4;
  t0[68UL] = X_idx_4;
  t0[69UL] = Cf_p_v;
  t0[70UL] = X_idx_11;
  t0[71UL] = -(X_idx_12 * X_idx_12 * 1.0000000000000002E-12) / -1.0 * 1000.0;
  t0[72UL] = X_idx_12;
  t0[73UL] = t9;
  t0[74UL] = X_idx_6;
  t0[75UL] = Ideal_Transformer_p1_v;
  t0[76UL] = C1_n_v;
  t0[77UL] = -(X_idx_15 * X_idx_15 * 1.0000000000000002E-12) / -1.0 * 1000.0;
  t0[78UL] = X_idx_15;
  t0[79UL] = 250.0;
  t0[80UL] = U_idx_0;
  t0[81UL] = C1_n_v;
  t0[82UL] = t11;
  t0[83UL] = 250.0;
  t0[84UL] = C1_n_v;
  t0[85UL] = -(t11 * Q1_diode_v * 0.001) / -1.0 * 1000.0;
  t0[86UL] = Q1_diode_v;
  t0[87UL] = U_idx_0;
  t0[88UL] = X_idx_18;
  t0[89UL] = (-U_idx_0 + 2.0) / -1.0;
  t0[90UL] = C1_n_v;
  t0[91UL] = 250.0;
  t0[92UL] = -(t1 * X_idx_18 * 0.001) / -1.0 * 1000.0;
  t0[93UL] = t1;
  t0[94UL] = 250.0;
  t0[95UL] = U_idx_1;
  t0[96UL] = C2_n_v;
  t0[97UL] = t14;
  t0[98UL] = 250.0;
  t0[99UL] = C2_n_v;
  t0[100UL] = -(t14 * Q2_diode_v * 0.001) / -1.0 * 1000.0;
  t0[101UL] = Q2_diode_v;
  t0[102UL] = U_idx_1;
  t0[103UL] = X_idx_21;
  t0[104UL] = (-U_idx_1 + 2.0) / -1.0;
  t0[105UL] = C2_n_v;
  t0[106UL] = 250.0;
  t0[107UL] = -(t2 * X_idx_21 * 0.001) / -1.0 * 1000.0;
  t0[108UL] = t2;
  t0[109UL] = C1_n_v;
  t0[110UL] = U_idx_2;
  t0[111UL] = 0.0;
  t0[112UL] = X_idx_19;
  t0[113UL] = C1_n_v;
  t0[114UL] = 0.0;
  t0[115UL] = -(X_idx_19 * t17 * 0.001) / -1.0 * 1000.0;
  t0[116UL] = t17;
  t0[117UL] = U_idx_2;
  t0[118UL] = X_idx_20;
  t0[119UL] = (-U_idx_2 + 2.0) / -1.0;
  t0[120UL] = 0.0;
  t0[121UL] = C1_n_v;
  t0[122UL] = -(C1_n_v * X_idx_20 * 0.001) / -1.0 * 1000.0;
  t0[123UL] = C1_n_v;
  t0[124UL] = C2_n_v;
  t0[125UL] = U_idx_3;
  t0[126UL] = 0.0;
  t0[127UL] = X_idx_22;
  t0[128UL] = C2_n_v;
  t0[129UL] = 0.0;
  t0[130UL] = -(X_idx_22 * t20 * 0.001) / -1.0 * 1000.0;
  t0[131UL] = t20;
  t0[132UL] = U_idx_3;
  t0[133UL] = X_idx_23;
  t0[134UL] = (-U_idx_3 + 2.0) / -1.0;
  t0[135UL] = 0.0;
  t0[136UL] = C2_n_v;
  t0[137UL] = -(C2_n_v * X_idx_23 * 0.001) / -1.0 * 1000.0;
  t0[138UL] = C2_n_v;
  t0[139UL] = t5;
  t0[140UL] = 0.0;
  t0[141UL] = Cf_p_v;
  t0[142UL] = t5 * 5.4;
  t0[143UL] = t23;
  t0[144UL] = 0.0;
  t0[145UL] = 0.0;
  t0[146UL] = Cf_p_v;
  t0[147UL] = t23;
  t0[148UL] = t24;
  t0[149UL] = 0.0;
  t0[150UL] = 0.0;
  t0[151UL] = X_idx_11;
  t0[152UL] = t24;
  t0[153UL] = t25;
  t0[154UL] = 0.0;
  t0[155UL] = C2_n_v;
  t0[156UL] = C1_n_v;
  t0[157UL] = t25;
  t0[158UL] = ((((-X_idx_8 + -X_idx_10) + -X_idx_20) + -X_idx_23) + X_idx_19) +
    X_idx_22;
  t0[159UL] = 0.0;
  t0[160UL] = 250.0;
  t0[161UL] = 250.0;
  for (b = 0; b < 162; b++) {
    out.mX[b] = t0[b];
  }

  (void)sys;
  (void)t28;
  return 0;
}
