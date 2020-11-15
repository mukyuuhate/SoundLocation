/*
 * File: rdivide_helper.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "rdivide_helper.h"
#include "SoundLocation_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                const emxArray_real_T *y
 *                emxArray_creal_T *z
 * Return Type  : void
 */
void rdivide_helper(const emxArray_creal_T *x, const emxArray_real_T *y,
                    emxArray_creal_T *z)
{
  int i4;
  int loop_ub;
  double x_re;
  double x_im;
  double y_re;
  i4 = z->size[0] * z->size[1];
  z->size[0] = 1;
  z->size[1] = x->size[1];
  emxEnsureCapacity_creal_T(z, i4);
  loop_ub = x->size[0] * x->size[1];
  for (i4 = 0; i4 < loop_ub; i4++) {
    x_re = x->data[i4].re;
    x_im = x->data[i4].im;
    y_re = y->data[i4];
    if (x_im == 0.0) {
      z->data[i4].re = x_re / y_re;
      z->data[i4].im = 0.0;
    } else if (x_re == 0.0) {
      z->data[i4].re = 0.0;
      z->data[i4].im = x_im / y_re;
    } else {
      z->data[i4].re = x_re / y_re;
      z->data[i4].im = x_im / y_re;
    }
  }
}

/*
 * File trailer for rdivide_helper.c
 *
 * [EOF]
 */
