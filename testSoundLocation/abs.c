/*
 * File: abs.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "abs.h"
#include "SoundLocation_emxutil.h"
#include "SoundLocation_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void b_abs(const emxArray_creal_T *x, emxArray_real_T *y)
{
  int nx;
  int k;
  nx = x->size[1];
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1];
  emxEnsureCapacity_real_T(y, k);
  for (k = 0; k < nx; k++) {
    y->data[k] = rt_hypotd_snf(x->data[k].re, x->data[k].im);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
