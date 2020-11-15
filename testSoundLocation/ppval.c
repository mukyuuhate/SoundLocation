/*
 * File: ppval.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "ppval.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *pp_breaks
 *                const emxArray_creal_T *pp_coefs
 *                double x
 * Return Type  : creal_T
 */
creal_T ppval(const emxArray_real_T *pp_breaks, const emxArray_creal_T *pp_coefs,
              double x)
{
  creal_T v;
  int numTerms;
  int high_i;
  int low_i;
  int low_ip1;
  double xloc;
  int mid_i;
  numTerms = pp_coefs->size[1];
  if (rtIsNaN(x)) {
    v.re = x;
    v.im = 0.0;
  } else {
    high_i = pp_breaks->size[1];
    low_i = 1;
    low_ip1 = 2;
    while (high_i > low_ip1) {
      mid_i = (low_i >> 1) + (high_i >> 1);
      if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
        mid_i++;
      }

      if (x >= pp_breaks->data[mid_i - 1]) {
        low_i = mid_i;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }

    xloc = x - pp_breaks->data[low_i - 1];
    v = pp_coefs->data[low_i - 1];
    for (high_i = 2; high_i <= numTerms; high_i++) {
      v.re = xloc * v.re + pp_coefs->data[(low_i + (high_i - 1) *
        (pp_breaks->size[1] - 1)) - 1].re;
      v.im = xloc * v.im + pp_coefs->data[(low_i + (high_i - 1) *
        (pp_breaks->size[1] - 1)) - 1].im;
    }
  }

  return v;
}

/*
 * File trailer for ppval.c
 *
 * [EOF]
 */
