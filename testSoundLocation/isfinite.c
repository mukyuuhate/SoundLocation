/*
 * File: isfinite.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "isfinite.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T x
 * Return Type  : bool
 */
bool b_isfinite(const creal_T x)
{
  return (!rtIsInf(x.re)) && (!rtIsInf(x.im)) && ((!rtIsNaN(x.re)) && (!rtIsNaN
    (x.im)));
}

/*
 * File trailer for isfinite.c
 *
 * [EOF]
 */
