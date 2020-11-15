/*
 * File: fft.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "fft.h"
#include "SoundLocation_emxutil.h"
#include "fft1.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                double varargin_1
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void b_fft(const emxArray_real_T *x, double varargin_1, emxArray_creal_T *y)
{
  emxArray_creal_T *r4;
  int x_idx_0;
  emxArray_real_T b_x;
  int c_x[1];
  int loop_ub;
  emxInit_creal_T(&r4, 1);
  x_idx_0 = x->size[1];
  b_x = *x;
  c_x[0] = x_idx_0;
  b_x.size = &c_x[0];
  b_x.numDimensions = 1;
  fft(&b_x, (int)varargin_1, r4);
  x_idx_0 = y->size[0] * y->size[1];
  y->size[0] = 1;
  loop_ub = (int)varargin_1;
  y->size[1] = loop_ub;
  emxEnsureCapacity_creal_T(y, x_idx_0);
  for (x_idx_0 = 0; x_idx_0 < loop_ub; x_idx_0++) {
    y->data[x_idx_0] = r4->data[x_idx_0];
  }

  emxFree_creal_T(&r4);
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
