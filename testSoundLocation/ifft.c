/*
 * File: ifft.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "ifft.h"
#include "SoundLocation_emxutil.h"
#include "fft1.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void ifft(const emxArray_creal_T *x, emxArray_creal_T *y)
{
  emxArray_creal_T *r5;
  int x_idx_0;
  emxArray_creal_T b_x;
  int c_x[1];
  int loop_ub;
  emxInit_creal_T(&r5, 1);
  x_idx_0 = x->size[1];
  b_x = *x;
  c_x[0] = x_idx_0;
  b_x.size = &c_x[0];
  b_x.numDimensions = 1;
  c_fft(&b_x, x->size[1], r5);
  x_idx_0 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal_T(y, x_idx_0);
  loop_ub = x->size[1];
  for (x_idx_0 = 0; x_idx_0 < loop_ub; x_idx_0++) {
    y->data[x_idx_0] = r5->data[x_idx_0];
  }

  emxFree_creal_T(&r5);
}

/*
 * File trailer for ifft.c
 *
 * [EOF]
 */
