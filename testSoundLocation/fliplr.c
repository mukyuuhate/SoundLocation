/*
 * File: fliplr.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "fliplr.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *x
 * Return Type  : void
 */
void fliplr(emxArray_creal_T *x)
{
  int n;
  int nd2;
  int b_j1;
  int j2;
  double xtmp_re;
  double xtmp_im;
  n = x->size[1] - 1;
  nd2 = x->size[1] >> 1;
  for (b_j1 = 0; b_j1 < nd2; b_j1++) {
    j2 = n - b_j1;
    xtmp_re = x->data[b_j1].re;
    xtmp_im = x->data[b_j1].im;
    x->data[b_j1] = x->data[j2];
    x->data[j2].re = xtmp_re;
    x->data[j2].im = xtmp_im;
  }
}

/*
 * File trailer for fliplr.c
 *
 * [EOF]
 */
