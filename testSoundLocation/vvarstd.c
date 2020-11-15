/*
 * File: vvarstd.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "vvarstd.h"
#include "isfinite.h"
#include "SoundLocation_emxutil.h"
#include "xnrm2.h"
#include "sqrt.h"
#include "combineVectorElements.h"
#include "SoundLocation_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *v
 *                int n
 * Return Type  : double
 */
double vvarstd(const emxArray_creal_T *v, int n)
{
  double s;
  emxArray_real_T *absdiff;
  creal_T b_v;
  double xbar_re;
  double xbar_im;
  int k;
  double x_re;
  double x_im;
  if (n == 0) {
    s = rtNaN;
  } else if (n == 1) {
    b_v = v->data[0];
    if (b_isfinite(b_v)) {
      s = 0.0;
    } else {
      s = rtNaN;
    }
  } else {
    emxInit_real_T(&absdiff, 1);
    b_v = combineVectorElements(v, n);
    if (b_v.im == 0.0) {
      xbar_re = b_v.re / (double)n;
      xbar_im = 0.0;
    } else if (b_v.re == 0.0) {
      xbar_re = 0.0;
      xbar_im = b_v.im / (double)n;
    } else {
      xbar_re = b_v.re / (double)n;
      xbar_im = b_v.im / (double)n;
    }

    k = absdiff->size[0];
    absdiff->size[0] = v->size[0];
    emxEnsureCapacity_real_T(absdiff, k);
    for (k = 0; k < n; k++) {
      x_re = v->data[k].re - xbar_re;
      x_im = v->data[k].im - xbar_im;
      absdiff->data[k] = rt_hypotd_snf(x_re, x_im);
    }

    xbar_re = n - 1;
    b_sqrt(&xbar_re);
    s = xnrm2(n, absdiff) / xbar_re;
    emxFree_real_T(&absdiff);
  }

  return s;
}

/*
 * File trailer for vvarstd.c
 *
 * [EOF]
 */
