/*
 * File: xnrm2.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "xnrm2.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                const emxArray_real_T *x
 * Return Type  : double
 */
double xnrm2(int n, const emxArray_real_T *x)
{
  double y;
  double scale;
  int k;
  double absxk;
  double t;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  for (k = 0; k < n; k++) {
    absxk = fabs(x->data[k]);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0 + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * sqrt(y);
}

/*
 * File trailer for xnrm2.c
 *
 * [EOF]
 */
