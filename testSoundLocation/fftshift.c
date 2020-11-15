/*
 * File: fftshift.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "fftshift.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *x
 * Return Type  : void
 */
void fftshift(emxArray_creal_T *x)
{
  int a;
  int vlend2;
  int npages;
  int k;
  int i2;
  int i;
  int i1;
  int j;
  int ia;
  int ib;
  double xtmp_re;
  double xtmp_im;
  a = x->size[0] - 1;
  if (x->size[0] > 1) {
    vlend2 = x->size[0] / 2;
    npages = 1;
    for (k = 2; k < 3; k++) {
      npages *= x->size[1];
    }

    if (vlend2 << 1 == x->size[0]) {
      i2 = 0;
      for (i = 0; i < npages; i++) {
        i1 = i2 - 1;
        i2 += a;
        for (j = 0; j < 1; j++) {
          i1++;
          i2++;
          ia = i1;
          ib = i1 + vlend2;
          for (k = 0; k < vlend2; k++) {
            xtmp_re = x->data[ia].re;
            xtmp_im = x->data[ia].im;
            x->data[ia] = x->data[ib];
            x->data[ib].re = xtmp_re;
            x->data[ib].im = xtmp_im;
            ia++;
            ib++;
          }
        }
      }
    } else {
      i2 = 0;
      for (i = 0; i < npages; i++) {
        i1 = i2 - 1;
        i2 += a;
        for (j = 0; j < 1; j++) {
          i1++;
          i2++;
          ia = i1;
          ib = i1 + vlend2;
          xtmp_re = x->data[ib].re;
          xtmp_im = x->data[ib].im;
          for (k = 0; k < vlend2; k++) {
            x->data[ib] = x->data[ia];
            x->data[ia] = x->data[ib + 1];
            ia++;
            ib++;
          }

          x->data[ib].re = xtmp_re;
          x->data[ib].im = xtmp_im;
        }
      }
    }
  }

  a = x->size[1] - 1;
  if (x->size[1] > 1) {
    vlend2 = x->size[1] / 2;
    if (vlend2 << 1 == x->size[1]) {
      i2 = 0;
      for (i = 0; i < 1; i++) {
        i1 = i2 - 1;
        i2 += a;
        for (j = 0; j < 1; j++) {
          i1++;
          i2++;
          ia = i1;
          ib = i1 + vlend2;
          for (k = 0; k < vlend2; k++) {
            xtmp_re = x->data[ia].re;
            xtmp_im = x->data[ia].im;
            x->data[ia] = x->data[ib];
            x->data[ib].re = xtmp_re;
            x->data[ib].im = xtmp_im;
            ia++;
            ib++;
          }
        }
      }
    } else {
      i2 = 0;
      for (i = 0; i < 1; i++) {
        i1 = i2 - 1;
        i2 += a;
        for (j = 0; j < 1; j++) {
          i1++;
          i2++;
          ia = i1;
          ib = i1 + vlend2;
          xtmp_re = x->data[ib].re;
          xtmp_im = x->data[ib].im;
          for (k = 0; k < vlend2; k++) {
            x->data[ib] = x->data[ia];
            x->data[ia] = x->data[ib + 1];
            ia++;
            ib++;
          }

          x->data[ib].re = xtmp_re;
          x->data[ib].im = xtmp_im;
        }
      }
    }
  }
}

/*
 * File trailer for fftshift.c
 *
 * [EOF]
 */
