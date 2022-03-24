/*
 * Simulacion_simscape.h
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

#ifndef RTW_HEADER_Simulacion_simscape_h_
#define RTW_HEADER_Simulacion_simscape_h_
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <float.h>
#ifndef Simulacion_simscape_COMMON_INCLUDES_
# define Simulacion_simscape_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "nesl_rtw.h"
#include "Simulacion_simscape_8d5561a5_1_gateway.h"
#endif                                 /* Simulacion_simscape_COMMON_INCLUDES_ */

#include "Simulacion_simscape_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Delay;                        /* '<S1>/Delay' */
  real_T PulseGenerator;               /* '<S1>/Pulse Generator' */
  real_T Delay1[2];                    /* '<S1>/Delay1' */
  real_T DerivativeGain;               /* '<S2>/Derivative Gain' */
  real_T FilterCoefficient;            /* '<S2>/Filter Coefficient' */
  real_T IntegralGain;                 /* '<S2>/Integral Gain' */
  real_T INPUT_2_1_1[4];               /* '<S20>/INPUT_2_1_1' */
  real_T INPUT_3_1_1[4];               /* '<S20>/INPUT_3_1_1' */
  real_T INPUT_1_1_1[4];               /* '<S20>/INPUT_1_1_1' */
  real_T INPUT_4_1_1[4];               /* '<S20>/INPUT_4_1_1' */
  real_T STATE_1[36];                  /* '<S20>/STATE_1' */
} B_Simulacion_simscape_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Delay_DSTATE[50];             /* '<S1>/Delay' */
  real_T Delay1_DSTATE[200];           /* '<S1>/Delay1' */
  real_T INPUT_2_1_1_discrete[2];      /* '<S20>/INPUT_2_1_1' */
  real_T INPUT_3_1_1_discrete[2];      /* '<S20>/INPUT_3_1_1' */
  real_T INPUT_1_1_1_discrete[2];      /* '<S20>/INPUT_1_1_1' */
  real_T INPUT_4_1_1_discrete[2];      /* '<S20>/INPUT_4_1_1' */
  real_T STATE_1_DiscStates[24];       /* '<S20>/STATE_1' */
  void* STATE_1_Simulator;             /* '<S20>/STATE_1' */
  void* STATE_1_SimulationData;        /* '<S20>/STATE_1' */
  void* STATE_1_DiagnosticManager;     /* '<S20>/STATE_1' */
  void* STATE_1_VariableLogger;        /* '<S20>/STATE_1' */
  void* STATE_1_ZeroCrossingLogger;    /* '<S20>/STATE_1' */
  void* STATE_1_SampleTimeIdx;         /* '<S20>/STATE_1' */
  void* OUTPUT_1_0_Simulator;          /* '<S20>/OUTPUT_1_0' */
  void* OUTPUT_1_0_SimulationData;     /* '<S20>/OUTPUT_1_0' */
  void* OUTPUT_1_0_DiagnosticManager;  /* '<S20>/OUTPUT_1_0' */
  void* OUTPUT_1_0_VariableLogger;     /* '<S20>/OUTPUT_1_0' */
  void* OUTPUT_1_0_ZeroCrossingLogger; /* '<S20>/OUTPUT_1_0' */
  void* OUTPUT_1_0_SampleTimeIdx;      /* '<S20>/OUTPUT_1_0' */
  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  struct {
    void *LoggedData[3];
  } Scope2_PWORK;                      /* '<Root>/Scope2' */

  struct {
    void *LoggedData;
  } ToWorkspace_PWORK;                 /* '<Root>/To Workspace' */

  struct {
    void *LoggedData;
  } ToWorkspace1_PWORK;                /* '<Root>/To Workspace1' */

  struct {
    void *LoggedData;
  } ToWorkspace2_PWORK;                /* '<Root>/To Workspace2' */

  int32_T clockTickCounter;            /* '<S1>/Pulse Generator' */
  int_T STATE_1_Modes[12];             /* '<S20>/STATE_1' */
  boolean_T STATE_1_CallSimulatorOutput;/* '<S20>/STATE_1' */
  boolean_T OUTPUT_1_0_CallSimulatorOutput;/* '<S20>/OUTPUT_1_0' */
} DW_Simulacion_simscape_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Filter_CSTATE;                /* '<S2>/Filter' */
  real_T Integrator_CSTATE;            /* '<S2>/Integrator' */
} X_Simulacion_simscape_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Filter_CSTATE;                /* '<S2>/Filter' */
  real_T Integrator_CSTATE;            /* '<S2>/Integrator' */
} XDot_Simulacion_simscape_T;

/* State disabled  */
typedef struct {
  boolean_T Filter_CSTATE;             /* '<S2>/Filter' */
  boolean_T Integrator_CSTATE;         /* '<S2>/Integrator' */
} XDis_Simulacion_simscape_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (default storage) */
struct P_Simulacion_simscape_T_ {
  real_T PIDController_D;              /* Mask Parameter: PIDController_D
                                        * Referenced by: '<S2>/Derivative Gain'
                                        */
  real_T PIDController_I;              /* Mask Parameter: PIDController_I
                                        * Referenced by: '<S2>/Integral Gain'
                                        */
  real_T PIDController_N;              /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S2>/Filter Coefficient'
                                        */
  real_T Constant_Value;               /* Expression: 2
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 50
                                        * Referenced by: '<S1>/Constant1'
                                        */
  real_T Delay_InitialCondition;       /* Expression: 0
                                        * Referenced by: '<S1>/Delay'
                                        */
  real_T PulseGenerator_Amp;           /* Expression: 10
                                        * Referenced by: '<S1>/Pulse Generator'
                                        */
  real_T PulseGenerator_Period;        /* Computed Parameter: PulseGenerator_Period
                                        * Referenced by: '<S1>/Pulse Generator'
                                        */
  real_T PulseGenerator_Duty;          /* Computed Parameter: PulseGenerator_Duty
                                        * Referenced by: '<S1>/Pulse Generator'
                                        */
  real_T PulseGenerator_PhaseDelay;    /* Expression: 0
                                        * Referenced by: '<S1>/Pulse Generator'
                                        */
  real_T Constant_Value_e;             /* Expression: 100
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Delay1_InitialCondition;      /* Expression: 0
                                        * Referenced by: '<S1>/Delay1'
                                        */
  real_T Filter_IC;                    /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
  real_T Integrator_IC;                /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S2>/Integrator'
                                        */
  uint32_T Delay_DelayLength;          /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<S1>/Delay'
                                        */
  uint8_T Delay1_DiagnosticForDelayLength;/* Computed Parameter: Delay1_DiagnosticForDelayLength
                                           * Referenced by: '<S1>/Delay1'
                                           */
};

/* Real-time Model Data Structure */
struct tag_RTM_Simulacion_simscape_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;
  X_Simulacion_simscape_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[2];
  real_T odeF[3][2];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_Simulacion_simscape_T Simulacion_simscape_P;

/* Block signals (default storage) */
extern B_Simulacion_simscape_T Simulacion_simscape_B;

/* Continuous states (default storage) */
extern X_Simulacion_simscape_T Simulacion_simscape_X;

/* Block states (default storage) */
extern DW_Simulacion_simscape_T Simulacion_simscape_DW;

/* Model entry point functions */
extern void Simulacion_simscape_initialize(void);
extern void Simulacion_simscape_step(void);
extern void Simulacion_simscape_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Simulacion_simscape_T *const Simulacion_simscape_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Simulacion_simscape'
 * '<S1>'   : 'Simulacion_simscape/Generacion PWM'
 * '<S2>'   : 'Simulacion_simscape/PID Controller'
 * '<S3>'   : 'Simulacion_simscape/PS-Simulink Converter'
 * '<S4>'   : 'Simulacion_simscape/PS-Simulink Converter1'
 * '<S5>'   : 'Simulacion_simscape/PS-Simulink Converter2'
 * '<S6>'   : 'Simulacion_simscape/PS-Simulink Converter3'
 * '<S7>'   : 'Simulacion_simscape/Solver Configuration'
 * '<S8>'   : 'Simulacion_simscape/Generacion PWM/Simulink-PS Converter'
 * '<S9>'   : 'Simulacion_simscape/Generacion PWM/Simulink-PS Converter1'
 * '<S10>'  : 'Simulacion_simscape/Generacion PWM/Simulink-PS Converter2'
 * '<S11>'  : 'Simulacion_simscape/Generacion PWM/Simulink-PS Converter3'
 * '<S12>'  : 'Simulacion_simscape/Generacion PWM/Simulink-PS Converter/EVAL_KEY'
 * '<S13>'  : 'Simulacion_simscape/Generacion PWM/Simulink-PS Converter1/EVAL_KEY'
 * '<S14>'  : 'Simulacion_simscape/Generacion PWM/Simulink-PS Converter2/EVAL_KEY'
 * '<S15>'  : 'Simulacion_simscape/Generacion PWM/Simulink-PS Converter3/EVAL_KEY'
 * '<S16>'  : 'Simulacion_simscape/PS-Simulink Converter/EVAL_KEY'
 * '<S17>'  : 'Simulacion_simscape/PS-Simulink Converter1/EVAL_KEY'
 * '<S18>'  : 'Simulacion_simscape/PS-Simulink Converter2/EVAL_KEY'
 * '<S19>'  : 'Simulacion_simscape/PS-Simulink Converter3/EVAL_KEY'
 * '<S20>'  : 'Simulacion_simscape/Solver Configuration/EVAL_KEY'
 */
#endif                                 /* RTW_HEADER_Simulacion_simscape_h_ */
