/*
 * File: diff.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "diff.h"

/* Function Definitions */

/*
 * Arguments    : const double x[4]
 *                double y[3]
 * Return Type  : void
 */
void b_diff(const double x[4], double y[3])
{
  y[0] = x[1] - x[0];
  y[1] = x[2] - x[1];
  y[2] = x[3] - x[2];
}

/*
 * Arguments    : const double x[5]
 *                double y[4]
 * Return Type  : void
 */
void diff(const double x[5], double y[4])
{
  y[0] = x[1] - x[0];
  y[1] = x[2] - x[1];
  y[2] = x[3] - x[2];
  y[3] = x[4] - x[3];
}

/*
 * File trailer for diff.c
 *
 * [EOF]
 */
