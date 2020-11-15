/*
 * File: combineVectorElements.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "combineVectorElements.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                int vlen
 * Return Type  : creal_T
 */
creal_T combineVectorElements(const emxArray_creal_T *x, int vlen)
{
  creal_T y;
  int k;
  if (x->size[0] == 0) {
    y.re = 0.0;
    y.im = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= vlen; k++) {
      y.re += x->data[k - 1].re;
      y.im += x->data[k - 1].im;
    }
  }

  return y;
}

/*
 * File trailer for combineVectorElements.c
 *
 * [EOF]
 */
