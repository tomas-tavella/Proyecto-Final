/*
 * Simulacion_simscape.c
 *
 * Code generation for model "Simulacion_simscape".
 *
 * Model version              : 1.19
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 * C source code generated on : Thu Mar 24 15:16:48 2022
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Simulacion_simscape.h"
#include "Simulacion_simscape_private.h"

/* Block signals (default storage) */
B_Simulacion_simscape_T Simulacion_simscape_B;

/* Continuous states */
X_Simulacion_simscape_T Simulacion_simscape_X;

/* Block states (default storage) */
DW_Simulacion_simscape_T Simulacion_simscape_DW;

/* Real-time model */
RT_MODEL_Simulacion_simscape_T Simulacion_simscape_M_;
RT_MODEL_Simulacion_simscape_T *const Simulacion_simscape_M =
  &Simulacion_simscape_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Simulacion_simscape_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  Simulacion_simscape_step();
  Simulacion_simscape_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  Simulacion_simscape_step();
  Simulacion_simscape_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Simulacion_simscape_step(void)
{
  /* local block i/o variables */
  real_T rtb_TmpSignalConversionAtDelay1[2];
  real_T rtb_OUTPUT_1_0[4];
  real_T rtb_Pout;
  if (rtmIsMajorTimeStep(Simulacion_simscape_M)) {
    /* set solver stop time */
    if (!(Simulacion_simscape_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Simulacion_simscape_M->solverInfo,
                            ((Simulacion_simscape_M->Timing.clockTickH0 + 1) *
        Simulacion_simscape_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Simulacion_simscape_M->solverInfo,
                            ((Simulacion_simscape_M->Timing.clockTick0 + 1) *
        Simulacion_simscape_M->Timing.stepSize0 +
        Simulacion_simscape_M->Timing.clockTickH0 *
        Simulacion_simscape_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Simulacion_simscape_M)) {
    Simulacion_simscape_M->Timing.t[0] = rtsiGetT
      (&Simulacion_simscape_M->solverInfo);
  }

  {
    NeslSimulationData *simulationData;
    real_T time;
    boolean_T tmp;
    real_T tmp_0[16];
    int_T tmp_1[5];
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    char *msg;
    real_T time_0;
    real_T tmp_2[52];
    int_T tmp_3[6];
    real_T rtb_Sum;
    int32_T rtb_Sum_0;
    if (rtmIsMajorTimeStep(Simulacion_simscape_M)) {
      /* Delay: '<S1>/Delay' */
      Simulacion_simscape_B.Delay = Simulacion_simscape_DW.Delay_DSTATE[0];

      /* DiscretePulseGenerator: '<S1>/Pulse Generator' */
      Simulacion_simscape_B.PulseGenerator =
        (Simulacion_simscape_DW.clockTickCounter <
         Simulacion_simscape_P.PulseGenerator_Duty) &&
        (Simulacion_simscape_DW.clockTickCounter >= 0) ?
        Simulacion_simscape_P.PulseGenerator_Amp : 0.0;
      if (Simulacion_simscape_DW.clockTickCounter >=
          Simulacion_simscape_P.PulseGenerator_Period - 1.0) {
        Simulacion_simscape_DW.clockTickCounter = 0;
      } else {
        Simulacion_simscape_DW.clockTickCounter++;
      }

      /* End of DiscretePulseGenerator: '<S1>/Pulse Generator' */

      /* SignalConversion: '<S1>/TmpSignal ConversionAtDelay1Inport1' */
      rtb_TmpSignalConversionAtDelay1[0] = Simulacion_simscape_B.Delay;
      rtb_TmpSignalConversionAtDelay1[1] = Simulacion_simscape_B.PulseGenerator;

      /* Sum: '<S1>/Sum' incorporates:
       *  Constant: '<Root>/Constant'
       *  Constant: '<S1>/Constant'
       *  Constant: '<S1>/Constant1'
       *  Product: '<S1>/Divide'
       */
      rtb_Sum = Simulacion_simscape_P.Constant1_Value -
        Simulacion_simscape_P.Constant_Value_e /
        Simulacion_simscape_P.Constant_Value;

      /* Delay: '<S1>/Delay1' */
      if ((rtb_Sum < 1.0) || rtIsNaN(rtb_Sum)) {
        Simulacion_simscape_B.Delay1[0] = rtb_TmpSignalConversionAtDelay1[0];
        Simulacion_simscape_B.Delay1[1] = rtb_TmpSignalConversionAtDelay1[1];
      } else {
        if (rtb_Sum > 100.0) {
          rtb_Sum_0 = 100;
        } else {
          rtb_Sum = trunc(rtb_Sum);
          if (rtIsNaN(rtb_Sum)) {
            rtb_Sum_0 = 0;
          } else {
            rtb_Sum_0 = (int32_T)(uint32_T)fmod(rtb_Sum, 4.294967296E+9);
          }
        }

        rtb_Sum_0 = (int32_T)(100U - rtb_Sum_0) << 1;
        Simulacion_simscape_B.Delay1[0] =
          Simulacion_simscape_DW.Delay1_DSTATE[rtb_Sum_0];
        Simulacion_simscape_B.Delay1[1] = Simulacion_simscape_DW.Delay1_DSTATE[1
          + rtb_Sum_0];
      }

      /* End of Delay: '<S1>/Delay1' */

      /* Gain: '<S2>/Derivative Gain' */
      Simulacion_simscape_B.DerivativeGain =
        Simulacion_simscape_P.PIDController_D * 0.0;
    }

    /* Gain: '<S2>/Filter Coefficient' incorporates:
     *  Integrator: '<S2>/Filter'
     *  Sum: '<S2>/SumD'
     */
    Simulacion_simscape_B.FilterCoefficient =
      (Simulacion_simscape_B.DerivativeGain -
       Simulacion_simscape_X.Filter_CSTATE) *
      Simulacion_simscape_P.PIDController_N;
    if (rtmIsMajorTimeStep(Simulacion_simscape_M)) {
      /* Gain: '<S2>/Integral Gain' */
      Simulacion_simscape_B.IntegralGain = Simulacion_simscape_P.PIDController_I
        * 0.0;

      /* SimscapeInputBlock: '<S20>/INPUT_2_1_1' */
      if (rtmIsMajorTimeStep(Simulacion_simscape_M)) {
        Simulacion_simscape_B.INPUT_2_1_1[0] =
          Simulacion_simscape_B.PulseGenerator;
        Simulacion_simscape_B.INPUT_2_1_1[1] = 0.0;
        Simulacion_simscape_B.INPUT_2_1_1[2] = 0.0;
        Simulacion_simscape_DW.INPUT_2_1_1_discrete[0] =
          !(Simulacion_simscape_B.INPUT_2_1_1[0] ==
            Simulacion_simscape_DW.INPUT_2_1_1_discrete[1]);
        Simulacion_simscape_DW.INPUT_2_1_1_discrete[1] =
          Simulacion_simscape_B.INPUT_2_1_1[0];
        Simulacion_simscape_B.INPUT_2_1_1[0] =
          Simulacion_simscape_DW.INPUT_2_1_1_discrete[1];
        Simulacion_simscape_B.INPUT_2_1_1[3] =
          Simulacion_simscape_DW.INPUT_2_1_1_discrete[0];

        /* SimscapeInputBlock: '<S20>/INPUT_3_1_1' */
        Simulacion_simscape_B.INPUT_3_1_1[0] = Simulacion_simscape_B.Delay1[0];
        Simulacion_simscape_B.INPUT_3_1_1[1] = 0.0;
        Simulacion_simscape_B.INPUT_3_1_1[2] = 0.0;
        Simulacion_simscape_DW.INPUT_3_1_1_discrete[0] =
          !(Simulacion_simscape_B.INPUT_3_1_1[0] ==
            Simulacion_simscape_DW.INPUT_3_1_1_discrete[1]);
        Simulacion_simscape_DW.INPUT_3_1_1_discrete[1] =
          Simulacion_simscape_B.INPUT_3_1_1[0];
        Simulacion_simscape_B.INPUT_3_1_1[0] =
          Simulacion_simscape_DW.INPUT_3_1_1_discrete[1];
        Simulacion_simscape_B.INPUT_3_1_1[3] =
          Simulacion_simscape_DW.INPUT_3_1_1_discrete[0];

        /* SimscapeInputBlock: '<S20>/INPUT_1_1_1' */
        Simulacion_simscape_B.INPUT_1_1_1[0] = Simulacion_simscape_B.Delay;
        Simulacion_simscape_B.INPUT_1_1_1[1] = 0.0;
        Simulacion_simscape_B.INPUT_1_1_1[2] = 0.0;
        Simulacion_simscape_DW.INPUT_1_1_1_discrete[0] =
          !(Simulacion_simscape_B.INPUT_1_1_1[0] ==
            Simulacion_simscape_DW.INPUT_1_1_1_discrete[1]);
        Simulacion_simscape_DW.INPUT_1_1_1_discrete[1] =
          Simulacion_simscape_B.INPUT_1_1_1[0];
        Simulacion_simscape_B.INPUT_1_1_1[0] =
          Simulacion_simscape_DW.INPUT_1_1_1_discrete[1];
        Simulacion_simscape_B.INPUT_1_1_1[3] =
          Simulacion_simscape_DW.INPUT_1_1_1_discrete[0];

        /* SimscapeInputBlock: '<S20>/INPUT_4_1_1' */
        Simulacion_simscape_B.INPUT_4_1_1[0] = Simulacion_simscape_B.Delay1[1];
        Simulacion_simscape_B.INPUT_4_1_1[1] = 0.0;
        Simulacion_simscape_B.INPUT_4_1_1[2] = 0.0;
        Simulacion_simscape_DW.INPUT_4_1_1_discrete[0] =
          !(Simulacion_simscape_B.INPUT_4_1_1[0] ==
            Simulacion_simscape_DW.INPUT_4_1_1_discrete[1]);
        Simulacion_simscape_DW.INPUT_4_1_1_discrete[1] =
          Simulacion_simscape_B.INPUT_4_1_1[0];
        Simulacion_simscape_B.INPUT_4_1_1[0] =
          Simulacion_simscape_DW.INPUT_4_1_1_discrete[1];
        Simulacion_simscape_B.INPUT_4_1_1[3] =
          Simulacion_simscape_DW.INPUT_4_1_1_discrete[0];
      }

      /* End of SimscapeInputBlock: '<S20>/INPUT_2_1_1' */

      /* SimscapeExecutionBlock: '<S20>/STATE_1' */
      simulationData = (NeslSimulationData *)
        Simulacion_simscape_DW.STATE_1_SimulationData;
      time = Simulacion_simscape_M->Timing.t[0];
      simulationData->mData->mTime.mN = 1;
      simulationData->mData->mTime.mX = &time;
      simulationData->mData->mContStates.mN = 0;
      simulationData->mData->mContStates.mX = NULL;
      simulationData->mData->mDiscStates.mN = 24;
      simulationData->mData->mDiscStates.mX = (real_T *)
        &Simulacion_simscape_DW.STATE_1_DiscStates;
      simulationData->mData->mModeVector.mN = 12;
      simulationData->mData->mModeVector.mX = (int32_T *)
        &Simulacion_simscape_DW.STATE_1_Modes;
      tmp = false;
      simulationData->mData->mFoundZcEvents = tmp;
      simulationData->mData->mIsMajorTimeStep = true;
      tmp = false;
      simulationData->mData->mIsSolverAssertCheck = tmp;
      simulationData->mData->mIsSolverCheckingCIC = false;
      simulationData->mData->mIsComputingJacobian = false;
      simulationData->mData->mIsEvaluatingF0 = false;
      simulationData->mData->mIsSolverRequestingReset = false;
      tmp_1[0] = 0;
      tmp_0[0] = Simulacion_simscape_B.INPUT_2_1_1[0];
      tmp_0[1] = Simulacion_simscape_B.INPUT_2_1_1[1];
      tmp_0[2] = Simulacion_simscape_B.INPUT_2_1_1[2];
      tmp_0[3] = Simulacion_simscape_B.INPUT_2_1_1[3];
      tmp_1[1] = 4;
      tmp_0[4] = Simulacion_simscape_B.INPUT_3_1_1[0];
      tmp_0[5] = Simulacion_simscape_B.INPUT_3_1_1[1];
      tmp_0[6] = Simulacion_simscape_B.INPUT_3_1_1[2];
      tmp_0[7] = Simulacion_simscape_B.INPUT_3_1_1[3];
      tmp_1[2] = 8;
      tmp_0[8] = Simulacion_simscape_B.INPUT_1_1_1[0];
      tmp_0[9] = Simulacion_simscape_B.INPUT_1_1_1[1];
      tmp_0[10] = Simulacion_simscape_B.INPUT_1_1_1[2];
      tmp_0[11] = Simulacion_simscape_B.INPUT_1_1_1[3];
      tmp_1[3] = 12;
      tmp_0[12] = Simulacion_simscape_B.INPUT_4_1_1[0];
      tmp_0[13] = Simulacion_simscape_B.INPUT_4_1_1[1];
      tmp_0[14] = Simulacion_simscape_B.INPUT_4_1_1[2];
      tmp_0[15] = Simulacion_simscape_B.INPUT_4_1_1[3];
      tmp_1[4] = 16;
      simulationData->mData->mInputValues.mN = 16;
      simulationData->mData->mInputValues.mX = &tmp_0[0];
      simulationData->mData->mInputOffsets.mN = 5;
      simulationData->mData->mInputOffsets.mX = &tmp_1[0];
      simulationData->mData->mOutputs.mN = 36;
      simulationData->mData->mOutputs.mX = &Simulacion_simscape_B.STATE_1[0];
      simulationData->mData->mSampleHits.mN = 0;
      simulationData->mData->mSampleHits.mX = NULL;
      tmp = rtmIsMajorTimeStep(Simulacion_simscape_M);
      simulationData->mData->mIsFundamentalSampleHit = tmp;
      simulationData->mData->mTolerances.mN = 0;
      simulationData->mData->mTolerances.mX = NULL;
      simulationData->mData->mCstateHasChanged = false;
      diagnosticManager = (NeuDiagnosticManager *)
        Simulacion_simscape_DW.STATE_1_DiagnosticManager;
      diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
      rtb_Sum_0 = ne_simulator_method((NeslSimulator *)
        Simulacion_simscape_DW.STATE_1_Simulator, NESL_SIM_OUTPUTS,
        simulationData, diagnosticManager);
      if (rtb_Sum_0 != 0) {
        tmp = error_buffer_is_empty(rtmGetErrorStatus(Simulacion_simscape_M));
        if (tmp) {
          msg = rtw_diagnostics_msg(diagnosticTree);
          rtmSetErrorStatus(Simulacion_simscape_M, msg);
        }
      }

      /* End of SimscapeExecutionBlock: '<S20>/STATE_1' */

      /* SimscapeExecutionBlock: '<S20>/OUTPUT_1_0' */
      simulationData = (NeslSimulationData *)
        Simulacion_simscape_DW.OUTPUT_1_0_SimulationData;
      time_0 = Simulacion_simscape_M->Timing.t[0];
      simulationData->mData->mTime.mN = 1;
      simulationData->mData->mTime.mX = &time_0;
      simulationData->mData->mContStates.mN = 0;
      simulationData->mData->mContStates.mX = NULL;
      simulationData->mData->mDiscStates.mN = 0;
      simulationData->mData->mDiscStates.mX = NULL;
      simulationData->mData->mModeVector.mN = 0;
      simulationData->mData->mModeVector.mX = NULL;
      tmp = false;
      simulationData->mData->mFoundZcEvents = tmp;
      simulationData->mData->mIsMajorTimeStep = true;
      tmp = false;
      simulationData->mData->mIsSolverAssertCheck = tmp;
      simulationData->mData->mIsSolverCheckingCIC = false;
      simulationData->mData->mIsComputingJacobian = false;
      simulationData->mData->mIsEvaluatingF0 = false;
      simulationData->mData->mIsSolverRequestingReset = false;
      tmp_3[0] = 0;
      tmp_2[0] = Simulacion_simscape_B.INPUT_2_1_1[0];
      tmp_2[1] = Simulacion_simscape_B.INPUT_2_1_1[1];
      tmp_2[2] = Simulacion_simscape_B.INPUT_2_1_1[2];
      tmp_2[3] = Simulacion_simscape_B.INPUT_2_1_1[3];
      tmp_3[1] = 4;
      tmp_2[4] = Simulacion_simscape_B.INPUT_3_1_1[0];
      tmp_2[5] = Simulacion_simscape_B.INPUT_3_1_1[1];
      tmp_2[6] = Simulacion_simscape_B.INPUT_3_1_1[2];
      tmp_2[7] = Simulacion_simscape_B.INPUT_3_1_1[3];
      tmp_3[2] = 8;
      tmp_2[8] = Simulacion_simscape_B.INPUT_1_1_1[0];
      tmp_2[9] = Simulacion_simscape_B.INPUT_1_1_1[1];
      tmp_2[10] = Simulacion_simscape_B.INPUT_1_1_1[2];
      tmp_2[11] = Simulacion_simscape_B.INPUT_1_1_1[3];
      tmp_3[3] = 12;
      tmp_2[12] = Simulacion_simscape_B.INPUT_4_1_1[0];
      tmp_2[13] = Simulacion_simscape_B.INPUT_4_1_1[1];
      tmp_2[14] = Simulacion_simscape_B.INPUT_4_1_1[2];
      tmp_2[15] = Simulacion_simscape_B.INPUT_4_1_1[3];
      tmp_3[4] = 16;
      memcpy(&tmp_2[16], &Simulacion_simscape_B.STATE_1[0], 36U * sizeof(real_T));
      tmp_3[5] = 52;
      simulationData->mData->mInputValues.mN = 52;
      simulationData->mData->mInputValues.mX = &tmp_2[0];
      simulationData->mData->mInputOffsets.mN = 6;
      simulationData->mData->mInputOffsets.mX = &tmp_3[0];
      simulationData->mData->mOutputs.mN = 4;
      simulationData->mData->mOutputs.mX = &rtb_OUTPUT_1_0[0];
      simulationData->mData->mSampleHits.mN = 0;
      simulationData->mData->mSampleHits.mX = NULL;
      tmp = rtmIsMajorTimeStep(Simulacion_simscape_M);
      simulationData->mData->mIsFundamentalSampleHit = tmp;
      simulationData->mData->mTolerances.mN = 0;
      simulationData->mData->mTolerances.mX = NULL;
      simulationData->mData->mCstateHasChanged = false;
      diagnosticManager = (NeuDiagnosticManager *)
        Simulacion_simscape_DW.OUTPUT_1_0_DiagnosticManager;
      diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
      rtb_Sum_0 = ne_simulator_method((NeslSimulator *)
        Simulacion_simscape_DW.OUTPUT_1_0_Simulator, NESL_SIM_OUTPUTS,
        simulationData, diagnosticManager);
      if (rtb_Sum_0 != 0) {
        tmp = error_buffer_is_empty(rtmGetErrorStatus(Simulacion_simscape_M));
        if (tmp) {
          msg = rtw_diagnostics_msg(diagnosticTree);
          rtmSetErrorStatus(Simulacion_simscape_M, msg);
        }
      }

      /* End of SimscapeExecutionBlock: '<S20>/OUTPUT_1_0' */

      /* Product: '<Root>/Product' */
      rtb_Pout = rtb_OUTPUT_1_0[1] * rtb_OUTPUT_1_0[0];

      /* ToWorkspace: '<Root>/To Workspace' */
      if (rtmIsMajorTimeStep(Simulacion_simscape_M)) {
        rt_UpdateLogVar((LogVar *)(LogVar*)
                        (Simulacion_simscape_DW.ToWorkspace_PWORK.LoggedData),
                        &rtb_OUTPUT_1_0[3], 0);
      }

      /* ToWorkspace: '<Root>/To Workspace1' */
      if (rtmIsMajorTimeStep(Simulacion_simscape_M)) {
        rt_UpdateLogVar((LogVar *)(LogVar*)
                        (Simulacion_simscape_DW.ToWorkspace1_PWORK.LoggedData),
                        &rtb_OUTPUT_1_0[1], 0);
      }

      /* ToWorkspace: '<Root>/To Workspace2' */
      if (rtmIsMajorTimeStep(Simulacion_simscape_M)) {
        rt_UpdateLogVar((LogVar *)(LogVar*)
                        (Simulacion_simscape_DW.ToWorkspace2_PWORK.LoggedData),
                        &rtb_OUTPUT_1_0[2], 0);
      }
    }
  }

  if (rtmIsMajorTimeStep(Simulacion_simscape_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(Simulacion_simscape_M->rtwLogInfo,
                        (Simulacion_simscape_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Simulacion_simscape_M)) {
    int_T idxDelay;
    NeslSimulationData *simulationData;
    real_T time;
    boolean_T tmp;
    real_T tmp_0[16];
    int_T tmp_1[5];
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    char *msg;
    if (rtmIsMajorTimeStep(Simulacion_simscape_M)) {
      /* Update for Delay: '<S1>/Delay' */
      for (idxDelay = 0; idxDelay < 49; idxDelay++) {
        Simulacion_simscape_DW.Delay_DSTATE[idxDelay] =
          Simulacion_simscape_DW.Delay_DSTATE[idxDelay + 1];
      }

      Simulacion_simscape_DW.Delay_DSTATE[49] =
        Simulacion_simscape_B.PulseGenerator;

      /* End of Update for Delay: '<S1>/Delay' */

      /* Update for Delay: '<S1>/Delay1' */
      for (idxDelay = 0; idxDelay < 99; idxDelay++) {
        Simulacion_simscape_DW.Delay1_DSTATE[idxDelay << 1] =
          Simulacion_simscape_DW.Delay1_DSTATE[(idxDelay + 1) << 1];
        Simulacion_simscape_DW.Delay1_DSTATE[(idxDelay << 1) + 1] =
          Simulacion_simscape_DW.Delay1_DSTATE[((idxDelay + 1) << 1) + 1];
      }

      Simulacion_simscape_DW.Delay1_DSTATE[198] =
        rtb_TmpSignalConversionAtDelay1[0];
      Simulacion_simscape_DW.Delay1_DSTATE[199] =
        rtb_TmpSignalConversionAtDelay1[1];

      /* End of Update for Delay: '<S1>/Delay1' */

      /* Update for SimscapeExecutionBlock: '<S20>/STATE_1' */
      simulationData = (NeslSimulationData *)
        Simulacion_simscape_DW.STATE_1_SimulationData;
      time = Simulacion_simscape_M->Timing.t[0];
      simulationData->mData->mTime.mN = 1;
      simulationData->mData->mTime.mX = &time;
      simulationData->mData->mContStates.mN = 0;
      simulationData->mData->mContStates.mX = NULL;
      simulationData->mData->mDiscStates.mN = 24;
      simulationData->mData->mDiscStates.mX = (real_T *)
        &Simulacion_simscape_DW.STATE_1_DiscStates;
      simulationData->mData->mModeVector.mN = 12;
      simulationData->mData->mModeVector.mX = (int32_T *)
        &Simulacion_simscape_DW.STATE_1_Modes;
      tmp = false;
      simulationData->mData->mFoundZcEvents = tmp;
      simulationData->mData->mIsMajorTimeStep = true;
      tmp = false;
      simulationData->mData->mIsSolverAssertCheck = tmp;
      simulationData->mData->mIsSolverCheckingCIC = false;
      simulationData->mData->mIsComputingJacobian = false;
      simulationData->mData->mIsEvaluatingF0 = false;
      simulationData->mData->mIsSolverRequestingReset = false;
      tmp_1[0] = 0;
      tmp_0[0] = Simulacion_simscape_B.INPUT_2_1_1[0];
      tmp_0[1] = Simulacion_simscape_B.INPUT_2_1_1[1];
      tmp_0[2] = Simulacion_simscape_B.INPUT_2_1_1[2];
      tmp_0[3] = Simulacion_simscape_B.INPUT_2_1_1[3];
      tmp_1[1] = 4;
      tmp_0[4] = Simulacion_simscape_B.INPUT_3_1_1[0];
      tmp_0[5] = Simulacion_simscape_B.INPUT_3_1_1[1];
      tmp_0[6] = Simulacion_simscape_B.INPUT_3_1_1[2];
      tmp_0[7] = Simulacion_simscape_B.INPUT_3_1_1[3];
      tmp_1[2] = 8;
      tmp_0[8] = Simulacion_simscape_B.INPUT_1_1_1[0];
      tmp_0[9] = Simulacion_simscape_B.INPUT_1_1_1[1];
      tmp_0[10] = Simulacion_simscape_B.INPUT_1_1_1[2];
      tmp_0[11] = Simulacion_simscape_B.INPUT_1_1_1[3];
      tmp_1[3] = 12;
      tmp_0[12] = Simulacion_simscape_B.INPUT_4_1_1[0];
      tmp_0[13] = Simulacion_simscape_B.INPUT_4_1_1[1];
      tmp_0[14] = Simulacion_simscape_B.INPUT_4_1_1[2];
      tmp_0[15] = Simulacion_simscape_B.INPUT_4_1_1[3];
      tmp_1[4] = 16;
      simulationData->mData->mInputValues.mN = 16;
      simulationData->mData->mInputValues.mX = &tmp_0[0];
      simulationData->mData->mInputOffsets.mN = 5;
      simulationData->mData->mInputOffsets.mX = &tmp_1[0];
      diagnosticManager = (NeuDiagnosticManager *)
        Simulacion_simscape_DW.STATE_1_DiagnosticManager;
      diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
      idxDelay = ne_simulator_method((NeslSimulator *)
        Simulacion_simscape_DW.STATE_1_Simulator, NESL_SIM_UPDATE,
        simulationData, diagnosticManager);
      if (idxDelay != 0) {
        tmp = error_buffer_is_empty(rtmGetErrorStatus(Simulacion_simscape_M));
        if (tmp) {
          msg = rtw_diagnostics_msg(diagnosticTree);
          rtmSetErrorStatus(Simulacion_simscape_M, msg);
        }
      }

      /* End of Update for SimscapeExecutionBlock: '<S20>/STATE_1' */
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Simulacion_simscape_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(Simulacion_simscape_M)!=-1) &&
          !((rtmGetTFinal(Simulacion_simscape_M)-
             (((Simulacion_simscape_M->Timing.clockTick1+
                Simulacion_simscape_M->Timing.clockTickH1* 4294967296.0)) *
              1.0E-7)) > (((Simulacion_simscape_M->Timing.clockTick1+
                            Simulacion_simscape_M->Timing.clockTickH1*
                            4294967296.0)) * 1.0E-7) * (DBL_EPSILON))) {
        rtmSetErrorStatus(Simulacion_simscape_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&Simulacion_simscape_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Simulacion_simscape_M->Timing.clockTick0)) {
      ++Simulacion_simscape_M->Timing.clockTickH0;
    }

    Simulacion_simscape_M->Timing.t[0] = rtsiGetSolverStopTime
      (&Simulacion_simscape_M->solverInfo);

    {
      /* Update absolute timer for sample time: [1.0E-7s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 1.0E-7, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      Simulacion_simscape_M->Timing.clockTick1++;
      if (!Simulacion_simscape_M->Timing.clockTick1) {
        Simulacion_simscape_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Simulacion_simscape_derivatives(void)
{
  XDot_Simulacion_simscape_T *_rtXdot;
  _rtXdot = ((XDot_Simulacion_simscape_T *) Simulacion_simscape_M->derivs);

  /* Derivatives for Integrator: '<S2>/Filter' */
  _rtXdot->Filter_CSTATE = Simulacion_simscape_B.FilterCoefficient;

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE = Simulacion_simscape_B.IntegralGain;
}

/* Model initialize function */
void Simulacion_simscape_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Simulacion_simscape_M, 0,
                sizeof(RT_MODEL_Simulacion_simscape_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Simulacion_simscape_M->solverInfo,
                          &Simulacion_simscape_M->Timing.simTimeStep);
    rtsiSetTPtr(&Simulacion_simscape_M->solverInfo, &rtmGetTPtr
                (Simulacion_simscape_M));
    rtsiSetStepSizePtr(&Simulacion_simscape_M->solverInfo,
                       &Simulacion_simscape_M->Timing.stepSize0);
    rtsiSetdXPtr(&Simulacion_simscape_M->solverInfo,
                 &Simulacion_simscape_M->derivs);
    rtsiSetContStatesPtr(&Simulacion_simscape_M->solverInfo, (real_T **)
                         &Simulacion_simscape_M->contStates);
    rtsiSetNumContStatesPtr(&Simulacion_simscape_M->solverInfo,
      &Simulacion_simscape_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Simulacion_simscape_M->solverInfo,
      &Simulacion_simscape_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Simulacion_simscape_M->solverInfo,
      &Simulacion_simscape_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Simulacion_simscape_M->solverInfo,
      &Simulacion_simscape_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Simulacion_simscape_M->solverInfo,
                          (&rtmGetErrorStatus(Simulacion_simscape_M)));
    rtsiSetRTModelPtr(&Simulacion_simscape_M->solverInfo, Simulacion_simscape_M);
  }

  rtsiSetSimTimeStep(&Simulacion_simscape_M->solverInfo, MAJOR_TIME_STEP);
  Simulacion_simscape_M->intgData.y = Simulacion_simscape_M->odeY;
  Simulacion_simscape_M->intgData.f[0] = Simulacion_simscape_M->odeF[0];
  Simulacion_simscape_M->intgData.f[1] = Simulacion_simscape_M->odeF[1];
  Simulacion_simscape_M->intgData.f[2] = Simulacion_simscape_M->odeF[2];
  Simulacion_simscape_M->contStates = ((X_Simulacion_simscape_T *)
    &Simulacion_simscape_X);
  rtsiSetSolverData(&Simulacion_simscape_M->solverInfo, (void *)
                    &Simulacion_simscape_M->intgData);
  rtsiSetSolverName(&Simulacion_simscape_M->solverInfo,"ode3");
  rtmSetTPtr(Simulacion_simscape_M, &Simulacion_simscape_M->Timing.tArray[0]);
  rtmSetTFinal(Simulacion_simscape_M, 0.024999999999999998);
  Simulacion_simscape_M->Timing.stepSize0 = 1.0E-7;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    Simulacion_simscape_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Simulacion_simscape_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Simulacion_simscape_M->rtwLogInfo, (NULL));
    rtliSetLogT(Simulacion_simscape_M->rtwLogInfo, "tout");
    rtliSetLogX(Simulacion_simscape_M->rtwLogInfo, "");
    rtliSetLogXFinal(Simulacion_simscape_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Simulacion_simscape_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Simulacion_simscape_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(Simulacion_simscape_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Simulacion_simscape_M->rtwLogInfo, 1);
    rtliSetLogY(Simulacion_simscape_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Simulacion_simscape_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Simulacion_simscape_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &Simulacion_simscape_B), 0,
                sizeof(B_Simulacion_simscape_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Simulacion_simscape_X, 0,
                  sizeof(X_Simulacion_simscape_T));
  }

  /* states (dwork) */
  (void) memset((void *)&Simulacion_simscape_DW, 0,
                sizeof(DW_Simulacion_simscape_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Simulacion_simscape_M->rtwLogInfo, 0.0,
    rtmGetTFinal(Simulacion_simscape_M), Simulacion_simscape_M->Timing.stepSize0,
    (&rtmGetErrorStatus(Simulacion_simscape_M)));

  {
    NeslSimulator *tmp;
    boolean_T tmp_0;
    NeuDiagnosticManager *diagnosticManager;
    NeModelParameters modelParameters;
    real_T tmp_1;
    NeuDiagnosticTree *diagnosticTree;
    char *msg;
    NeslSimulationData *simulationData;
    real_T time;
    NeModelParameters modelParameters_0;
    real_T time_0;
    int32_T Ns;
    NeParameterBundle expl_temp;

    /* Start for DiscretePulseGenerator: '<S1>/Pulse Generator' */
    Simulacion_simscape_DW.clockTickCounter = 0;

    /* Start for SimscapeExecutionBlock: '<S20>/STATE_1' */
    tmp = nesl_lease_simulator("Simulacion_simscape/Solver Configuration_1", 0,
      0);
    Simulacion_simscape_DW.STATE_1_Simulator = (void *)tmp;
    tmp_0 = pointer_is_null(Simulacion_simscape_DW.STATE_1_Simulator);
    if (tmp_0) {
      Simulacion_simscape_8d5561a5_1_gateway();
      tmp = nesl_lease_simulator("Simulacion_simscape/Solver Configuration_1", 0,
        0);
      Simulacion_simscape_DW.STATE_1_Simulator = (void *)tmp;
    }

    simulationData = nesl_create_simulation_data();
    Simulacion_simscape_DW.STATE_1_SimulationData = (void *)simulationData;
    diagnosticManager = rtw_create_diagnostics();
    Simulacion_simscape_DW.STATE_1_DiagnosticManager = (void *)diagnosticManager;
    modelParameters.mSolverType = NE_SOLVER_TYPE_DAE;
    modelParameters.mSolverTolerance = 0.001;
    modelParameters.mVariableStepSolver = false;
    modelParameters.mFixedStepSize = 1.0E-7;
    modelParameters.mStartTime = 0.0;
    modelParameters.mLoadInitialState = false;
    modelParameters.mUseSimState = false;
    modelParameters.mLinTrimCompile = false;
    modelParameters.mLoggingMode = SSC_LOGGING_NONE;
    modelParameters.mRTWModifiedTimeStamp = 5.7003578E+8;
    tmp_1 = 0.001;
    modelParameters.mSolverTolerance = tmp_1;
    tmp_1 = 1.0E-7;
    modelParameters.mFixedStepSize = tmp_1;
    tmp_0 = false;
    modelParameters.mVariableStepSolver = tmp_0;
    diagnosticManager = (NeuDiagnosticManager *)
      Simulacion_simscape_DW.STATE_1_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    Ns = nesl_initialize_simulator((NeslSimulator *)
      Simulacion_simscape_DW.STATE_1_Simulator, &modelParameters,
      diagnosticManager);
    if (Ns != 0) {
      tmp_0 = error_buffer_is_empty(rtmGetErrorStatus(Simulacion_simscape_M));
      if (tmp_0) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(Simulacion_simscape_M, msg);
      }
    }

    expl_temp.mRealParameters.mN = 0;
    expl_temp.mRealParameters.mX = NULL;
    expl_temp.mLogicalParameters.mN = 0;
    expl_temp.mLogicalParameters.mX = NULL;
    expl_temp.mIntegerParameters.mN = 0;
    expl_temp.mIntegerParameters.mX = NULL;
    expl_temp.mIndexParameters.mN = 0;
    expl_temp.mIndexParameters.mX = NULL;
    nesl_simulator_set_rtps((NeslSimulator *)
      Simulacion_simscape_DW.STATE_1_Simulator, expl_temp);
    simulationData = (NeslSimulationData *)
      Simulacion_simscape_DW.STATE_1_SimulationData;
    time = Simulacion_simscape_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 24;
    simulationData->mData->mDiscStates.mX = (real_T *)
      &Simulacion_simscape_DW.STATE_1_DiscStates;
    simulationData->mData->mModeVector.mN = 12;
    simulationData->mData->mModeVector.mX = (int32_T *)
      &Simulacion_simscape_DW.STATE_1_Modes;
    tmp_0 = false;
    simulationData->mData->mFoundZcEvents = tmp_0;
    simulationData->mData->mIsMajorTimeStep = true;
    tmp_0 = false;
    simulationData->mData->mIsSolverAssertCheck = tmp_0;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    diagnosticManager = (NeuDiagnosticManager *)
      Simulacion_simscape_DW.STATE_1_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    Ns = ne_simulator_method((NeslSimulator *)
      Simulacion_simscape_DW.STATE_1_Simulator, NESL_SIM_INITIALIZEONCE,
      simulationData, diagnosticManager);
    if (Ns != 0) {
      tmp_0 = error_buffer_is_empty(rtmGetErrorStatus(Simulacion_simscape_M));
      if (tmp_0) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(Simulacion_simscape_M, msg);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S20>/STATE_1' */

    /* Start for SimscapeExecutionBlock: '<S20>/OUTPUT_1_0' */
    tmp = nesl_lease_simulator("Simulacion_simscape/Solver Configuration_1", 2,
      0);
    Simulacion_simscape_DW.OUTPUT_1_0_Simulator = (void *)tmp;
    tmp_0 = pointer_is_null(Simulacion_simscape_DW.OUTPUT_1_0_Simulator);
    if (tmp_0) {
      Simulacion_simscape_8d5561a5_1_gateway();
      tmp = nesl_lease_simulator("Simulacion_simscape/Solver Configuration_1", 2,
        0);
      Simulacion_simscape_DW.OUTPUT_1_0_Simulator = (void *)tmp;
    }

    simulationData = nesl_create_simulation_data();
    Simulacion_simscape_DW.OUTPUT_1_0_SimulationData = (void *)simulationData;
    diagnosticManager = rtw_create_diagnostics();
    Simulacion_simscape_DW.OUTPUT_1_0_DiagnosticManager = (void *)
      diagnosticManager;
    modelParameters_0.mSolverType = NE_SOLVER_TYPE_DAE;
    modelParameters_0.mSolverTolerance = 0.001;
    modelParameters_0.mVariableStepSolver = false;
    modelParameters_0.mFixedStepSize = 1.0E-7;
    modelParameters_0.mStartTime = 0.0;
    modelParameters_0.mLoadInitialState = false;
    modelParameters_0.mUseSimState = false;
    modelParameters_0.mLinTrimCompile = false;
    modelParameters_0.mLoggingMode = SSC_LOGGING_NONE;
    modelParameters_0.mRTWModifiedTimeStamp = 5.7003578E+8;
    tmp_1 = 0.001;
    modelParameters_0.mSolverTolerance = tmp_1;
    tmp_1 = 1.0E-7;
    modelParameters_0.mFixedStepSize = tmp_1;
    tmp_0 = false;
    modelParameters_0.mVariableStepSolver = tmp_0;
    diagnosticManager = (NeuDiagnosticManager *)
      Simulacion_simscape_DW.OUTPUT_1_0_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    Ns = nesl_initialize_simulator((NeslSimulator *)
      Simulacion_simscape_DW.OUTPUT_1_0_Simulator, &modelParameters_0,
      diagnosticManager);
    if (Ns != 0) {
      tmp_0 = error_buffer_is_empty(rtmGetErrorStatus(Simulacion_simscape_M));
      if (tmp_0) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(Simulacion_simscape_M, msg);
      }
    }

    simulationData = (NeslSimulationData *)
      Simulacion_simscape_DW.OUTPUT_1_0_SimulationData;
    time_0 = Simulacion_simscape_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_0;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = NULL;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = NULL;
    tmp_0 = false;
    simulationData->mData->mFoundZcEvents = tmp_0;
    simulationData->mData->mIsMajorTimeStep = true;
    tmp_0 = false;
    simulationData->mData->mIsSolverAssertCheck = tmp_0;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    diagnosticManager = (NeuDiagnosticManager *)
      Simulacion_simscape_DW.OUTPUT_1_0_DiagnosticManager;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    Ns = ne_simulator_method((NeslSimulator *)
      Simulacion_simscape_DW.OUTPUT_1_0_Simulator, NESL_SIM_INITIALIZEONCE,
      simulationData, diagnosticManager);
    if (Ns != 0) {
      tmp_0 = error_buffer_is_empty(rtmGetErrorStatus(Simulacion_simscape_M));
      if (tmp_0) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(Simulacion_simscape_M, msg);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S20>/OUTPUT_1_0' */
    /* Start for ToWorkspace: '<Root>/To Workspace' */
    {
      int_T dimensions[1] = { 1 };

      Simulacion_simscape_DW.ToWorkspace_PWORK.LoggedData = rt_CreateLogVar(
        Simulacion_simscape_M->rtwLogInfo,
        0.0,
        rtmGetTFinal(Simulacion_simscape_M),
        Simulacion_simscape_M->Timing.stepSize0,
        (&rtmGetErrorStatus(Simulacion_simscape_M)),
        "V1",
        SS_DOUBLE,
        0,
        0,
        0,
        1,
        1,
        dimensions,
        NO_LOGVALDIMS,
        (NULL),
        (NULL),
        0,
        1,
        1.0E-7,
        1);
      if (Simulacion_simscape_DW.ToWorkspace_PWORK.LoggedData == (NULL))
        return;
    }

    /* Start for ToWorkspace: '<Root>/To Workspace1' */
    {
      int_T dimensions[1] = { 1 };

      Simulacion_simscape_DW.ToWorkspace1_PWORK.LoggedData = rt_CreateLogVar(
        Simulacion_simscape_M->rtwLogInfo,
        0.0,
        rtmGetTFinal(Simulacion_simscape_M),
        Simulacion_simscape_M->Timing.stepSize0,
        (&rtmGetErrorStatus(Simulacion_simscape_M)),
        "Vout",
        SS_DOUBLE,
        0,
        0,
        0,
        1,
        1,
        dimensions,
        NO_LOGVALDIMS,
        (NULL),
        (NULL),
        0,
        1,
        1.0E-7,
        1);
      if (Simulacion_simscape_DW.ToWorkspace1_PWORK.LoggedData == (NULL))
        return;
    }

    /* Start for ToWorkspace: '<Root>/To Workspace2' */
    {
      int_T dimensions[1] = { 1 };

      Simulacion_simscape_DW.ToWorkspace2_PWORK.LoggedData = rt_CreateLogVar(
        Simulacion_simscape_M->rtwLogInfo,
        0.0,
        rtmGetTFinal(Simulacion_simscape_M),
        Simulacion_simscape_M->Timing.stepSize0,
        (&rtmGetErrorStatus(Simulacion_simscape_M)),
        "Vrect",
        SS_DOUBLE,
        0,
        0,
        0,
        1,
        1,
        dimensions,
        NO_LOGVALDIMS,
        (NULL),
        (NULL),
        0,
        1,
        1.0E-7,
        1);
      if (Simulacion_simscape_DW.ToWorkspace2_PWORK.LoggedData == (NULL))
        return;
    }
  }

  {
    int32_T i;

    /* InitializeConditions for Delay: '<S1>/Delay' */
    for (i = 0; i < 50; i++) {
      Simulacion_simscape_DW.Delay_DSTATE[i] =
        Simulacion_simscape_P.Delay_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<S1>/Delay' */

    /* InitializeConditions for Delay: '<S1>/Delay1' */
    for (i = 0; i < 200; i++) {
      Simulacion_simscape_DW.Delay1_DSTATE[i] =
        Simulacion_simscape_P.Delay1_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<S1>/Delay1' */

    /* InitializeConditions for Integrator: '<S2>/Filter' */
    Simulacion_simscape_X.Filter_CSTATE = Simulacion_simscape_P.Filter_IC;

    /* InitializeConditions for Integrator: '<S2>/Integrator' */
    Simulacion_simscape_X.Integrator_CSTATE =
      Simulacion_simscape_P.Integrator_IC;
  }
}

/* Model terminate function */
void Simulacion_simscape_terminate(void)
{
  /* Terminate for SimscapeExecutionBlock: '<S20>/STATE_1' */
  neu_destroy_diagnostic_manager((NeuDiagnosticManager *)
    Simulacion_simscape_DW.STATE_1_DiagnosticManager);
  nesl_destroy_simulation_data((NeslSimulationData *)
    Simulacion_simscape_DW.STATE_1_SimulationData);
  nesl_erase_simulator("Simulacion_simscape/Solver Configuration_1");

  /* Terminate for SimscapeExecutionBlock: '<S20>/OUTPUT_1_0' */
  neu_destroy_diagnostic_manager((NeuDiagnosticManager *)
    Simulacion_simscape_DW.OUTPUT_1_0_DiagnosticManager);
  nesl_destroy_simulation_data((NeslSimulationData *)
    Simulacion_simscape_DW.OUTPUT_1_0_SimulationData);
  nesl_erase_simulator("Simulacion_simscape/Solver Configuration_1");
}
