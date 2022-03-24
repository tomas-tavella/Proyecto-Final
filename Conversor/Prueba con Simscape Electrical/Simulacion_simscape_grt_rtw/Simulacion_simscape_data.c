/*
 * Simulacion_simscape_data.c
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

/* Block parameters (default storage) */
P_Simulacion_simscape_T Simulacion_simscape_P = {
  /* Mask Parameter: PIDController_D
   * Referenced by: '<S2>/Derivative Gain'
   */
  0.0,

  /* Mask Parameter: PIDController_I
   * Referenced by: '<S2>/Integral Gain'
   */
  1.0,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S2>/Filter Coefficient'
   */
  100.0,

  /* Expression: 2
   * Referenced by: '<S1>/Constant'
   */
  2.0,

  /* Expression: 50
   * Referenced by: '<S1>/Constant1'
   */
  50.0,

  /* Expression: 0
   * Referenced by: '<S1>/Delay'
   */
  0.0,

  /* Expression: 10
   * Referenced by: '<S1>/Pulse Generator'
   */
  10.0,

  /* Computed Parameter: PulseGenerator_Period
   * Referenced by: '<S1>/Pulse Generator'
   */
  100.0,

  /* Computed Parameter: PulseGenerator_Duty
   * Referenced by: '<S1>/Pulse Generator'
   */
  49.0,

  /* Expression: 0
   * Referenced by: '<S1>/Pulse Generator'
   */
  0.0,

  /* Expression: 100
   * Referenced by: '<Root>/Constant'
   */
  100.0,

  /* Expression: 0
   * Referenced by: '<S1>/Delay1'
   */
  0.0,

  /* Expression: InitialConditionForFilter
   * Referenced by: '<S2>/Filter'
   */
  0.0,

  /* Expression: InitialConditionForIntegrator
   * Referenced by: '<S2>/Integrator'
   */
  0.0,

  /* Computed Parameter: Delay_DelayLength
   * Referenced by: '<S1>/Delay'
   */
  50U,

  /* Computed Parameter: Delay1_DiagnosticForDelayLength
   * Referenced by: '<S1>/Delay1'
   */
  0U
};
