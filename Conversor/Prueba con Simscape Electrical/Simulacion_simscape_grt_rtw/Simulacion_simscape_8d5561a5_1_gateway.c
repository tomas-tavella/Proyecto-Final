/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'Simulacion_simscape/Solver Configuration'.
 */

#ifdef MATLAB_MEX_FILE
#include "tmwtypes.h"
#else
#include "rtwtypes.h"
#endif

#include "nesl_rtw.h"
#include "Simulacion_simscape_8d5561a5_1.h"

void Simulacion_simscape_8d5561a5_1_gateway(void)
{
  NeModelParameters modelparams = { (NeSolverType) 0, 0.001, 0, 1e-07, 0, 0, 0,
    0, (SscLoggingSetting) 0, 570035780, };

  NeSolverParameters solverparams = { 0, 0, 1, 0, 0, 0.001, 1e-06, 1e-09, 0, 0,
    100, 0, 1, 0, 1e-07, 1, (NeLocalSolverChoice) 0, 1e-07, 1, 3, 2,
    (NeLinearAlgebraChoice) 0, (NeEquationFormulationChoice) 0, 1024, 1, 0.001,
  };

  const NeOutputParameters* outputparameters = NULL;
  NeDae* dae;
  size_t numOutputs = 0;

  {
    static const NeOutputParameters outputparameters_init[] = { { 0, 0,
        "Simulacion_simscape/Solver\nConfiguration", }, };

    outputparameters = outputparameters_init;
    numOutputs = sizeof(outputparameters_init)/sizeof(outputparameters_init[0]);
  }

  Simulacion_simscape_8d5561a5_1_dae(&dae,
    &modelparams,
    &solverparams);
  nesl_register_simulator_group("Simulacion_simscape/Solver Configuration_1",
    1,
    &dae,
    &solverparams,
    &modelparams,
    numOutputs,
    outputparameters,
    0);
}
