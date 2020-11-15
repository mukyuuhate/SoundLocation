/*
 * File: interp1.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "interp1.h"
#include "SoundLocation_emxutil.h"
#include "ppval.h"
#include "spline.h"
#include "fliplr.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *varargin_1
 *                const emxArray_creal_T *varargin_2
 *                const emxArray_real_T *varargin_3
 *                emxArray_creal_T *Vq
 * Return Type  : void
 */
void interp1(const emxArray_real_T *varargin_1, const emxArray_creal_T
             *varargin_2, const emxArray_real_T *varargin_3, emxArray_creal_T
             *Vq)
{
  emxArray_creal_T *y;
  int i6;
  int outsize_idx_1;
  emxArray_real_T *x;
  int nx;
  emxArray_real_T *pp_breaks;
  emxArray_creal_T *pp_coefs;
  emxArray_creal_T *b_y;
  int exitg1;
  int nxi;
  double xtmp;
  emxInit_creal_T(&y, 2);
  i6 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = varargin_2->size[1];
  emxEnsureCapacity_creal_T(y, i6);
  outsize_idx_1 = varargin_2->size[0] * varargin_2->size[1];
  for (i6 = 0; i6 < outsize_idx_1; i6++) {
    y->data[i6] = varargin_2->data[i6];
  }

  emxInit_real_T(&x, 2);
  i6 = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = varargin_1->size[1];
  emxEnsureCapacity_real_T(x, i6);
  outsize_idx_1 = varargin_1->size[0] * varargin_1->size[1];
  for (i6 = 0; i6 < outsize_idx_1; i6++) {
    x->data[i6] = varargin_1->data[i6];
  }

  nx = varargin_1->size[1] - 1;
  outsize_idx_1 = varargin_3->size[1];
  i6 = Vq->size[0] * Vq->size[1];
  Vq->size[0] = 1;
  Vq->size[1] = outsize_idx_1;
  emxEnsureCapacity_creal_T(Vq, i6);
  for (i6 = 0; i6 < outsize_idx_1; i6++) {
    Vq->data[i6].re = 0.0;
    Vq->data[i6].im = 0.0;
  }

  if (varargin_3->size[1] != 0) {
    outsize_idx_1 = 0;
    emxInit_real_T(&pp_breaks, 2);
    emxInit_creal_T(&pp_coefs, 2);
    emxInit_creal_T(&b_y, 2);
    do {
      exitg1 = 0;
      if (outsize_idx_1 <= nx) {
        if (rtIsNaN(varargin_1->data[outsize_idx_1])) {
          exitg1 = 1;
        } else {
          outsize_idx_1++;
        }
      } else {
        if (varargin_1->data[1] < varargin_1->data[0]) {
          i6 = (nx + 1) >> 1;
          for (outsize_idx_1 = 0; outsize_idx_1 < i6; outsize_idx_1++) {
            xtmp = x->data[outsize_idx_1];
            nxi = nx - outsize_idx_1;
            x->data[outsize_idx_1] = x->data[nxi];
            x->data[nxi] = xtmp;
          }

          fliplr(y);
        }

        nxi = varargin_3->size[1];
        outsize_idx_1 = y->size[1];
        i6 = b_y->size[0] * b_y->size[1];
        b_y->size[0] = 1;
        b_y->size[1] = outsize_idx_1;
        emxEnsureCapacity_creal_T(b_y, i6);
        for (i6 = 0; i6 < outsize_idx_1; i6++) {
          b_y->data[i6] = y->data[i6];
        }

        spline(x, b_y, pp_breaks, pp_coefs);
        for (outsize_idx_1 = 0; outsize_idx_1 < nxi; outsize_idx_1++) {
          if (rtIsNaN(varargin_3->data[outsize_idx_1])) {
            Vq->data[outsize_idx_1].re = rtNaN;
            Vq->data[outsize_idx_1].im = 0.0;
          } else {
            Vq->data[outsize_idx_1] = ppval(pp_breaks, pp_coefs,
              varargin_3->data[outsize_idx_1]);
          }
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);

    emxFree_creal_T(&b_y);
    emxFree_creal_T(&pp_coefs);
    emxFree_real_T(&pp_breaks);
  }

  emxFree_real_T(&x);
  emxFree_creal_T(&y);
}

/*
 * File trailer for interp1.c
 *
 * [EOF]
 */
