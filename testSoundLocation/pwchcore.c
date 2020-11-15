/*
 * File: pwchcore.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "pwchcore.h"
#include "SoundLocation_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_creal_T *y
 *                int yoffset
 *                const emxArray_creal_T *s
 *                const emxArray_real_T *dx
 *                const emxArray_creal_T *divdif
 *                emxArray_real_T *pp_breaks
 *                emxArray_creal_T *pp_coefs
 * Return Type  : void
 */
void b_pwchcore(const emxArray_real_T *x, const emxArray_creal_T *y, int yoffset,
                const emxArray_creal_T *s, const emxArray_real_T *dx, const
                emxArray_creal_T *divdif, emxArray_real_T *pp_breaks,
                emxArray_creal_T *pp_coefs)
{
  int nxm1;
  int cpage;
  int i8;
  int j;
  double dzdxdx_im;
  double ai;
  double br;
  double dzzdx_re;
  double dzzdx_im;
  double dzdxdx_re;
  double dx_re;
  nxm1 = x->size[1];
  cpage = x->size[1];
  i8 = pp_breaks->size[0] * pp_breaks->size[1];
  pp_breaks->size[0] = 1;
  pp_breaks->size[1] = cpage;
  emxEnsureCapacity_real_T(pp_breaks, i8);
  for (i8 = 0; i8 < cpage; i8++) {
    pp_breaks->data[i8] = x->data[i8];
  }

  cpage = s->size[1] - 1;
  i8 = pp_coefs->size[0] * pp_coefs->size[1];
  pp_coefs->size[0] = s->size[1] - 1;
  pp_coefs->size[1] = 4;
  emxEnsureCapacity_creal_T(pp_coefs, i8);
  for (j = 0; j <= nxm1 - 2; j++) {
    dzdxdx_im = divdif->data[j].re - s->data[j].re;
    ai = divdif->data[j].im - s->data[j].im;
    br = dx->data[j];
    if (ai == 0.0) {
      dzzdx_re = dzdxdx_im / br;
      dzzdx_im = 0.0;
    } else if (dzdxdx_im == 0.0) {
      dzzdx_re = 0.0;
      dzzdx_im = ai / br;
    } else {
      dzzdx_re = dzdxdx_im / br;
      dzzdx_im = ai / br;
    }

    dzdxdx_im = s->data[j + 1].re - divdif->data[j].re;
    ai = s->data[j + 1].im - divdif->data[j].im;
    br = dx->data[j];
    if (ai == 0.0) {
      dzdxdx_re = dzdxdx_im / br;
      dzdxdx_im = 0.0;
    } else if (dzdxdx_im == 0.0) {
      dzdxdx_re = 0.0;
      dzdxdx_im = ai / br;
    } else {
      dzdxdx_re = dzdxdx_im / br;
      dzdxdx_im = ai / br;
    }

    ai = dzdxdx_re - dzzdx_re;
    br = dzdxdx_im - dzzdx_im;
    dx_re = dx->data[j];
    if (br == 0.0) {
      pp_coefs->data[j].re = ai / dx_re;
      pp_coefs->data[j].im = 0.0;
    } else if (ai == 0.0) {
      pp_coefs->data[j].re = 0.0;
      pp_coefs->data[j].im = br / dx_re;
    } else {
      pp_coefs->data[j].re = ai / dx_re;
      pp_coefs->data[j].im = br / dx_re;
    }

    i8 = cpage + j;
    pp_coefs->data[i8].re = 2.0 * dzzdx_re - dzdxdx_re;
    pp_coefs->data[i8].im = 2.0 * dzzdx_im - dzdxdx_im;
    pp_coefs->data[(cpage << 1) + j] = s->data[j];
    pp_coefs->data[3 * cpage + j] = y->data[yoffset + j];
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_creal_T *y
 *                const creal_T s[2]
 *                emxArray_real_T *pp_breaks
 *                creal_T pp_coefs[4]
 * Return Type  : void
 */
void pwchcore(const emxArray_real_T *x, const emxArray_creal_T *y, const creal_T
              s[2], emxArray_real_T *pp_breaks, creal_T pp_coefs[4])
{
  int nxm1;
  int x_idx_0;
  int i7;
  double dxj;
  double dzzdx_im;
  double ai;
  double divdifij_re;
  double divdifij_im;
  double dzzdx_re;
  double b_divdifij_im;
  nxm1 = x->size[1];
  x_idx_0 = x->size[1];
  i7 = pp_breaks->size[0] * pp_breaks->size[1];
  pp_breaks->size[0] = 1;
  pp_breaks->size[1] = x_idx_0;
  emxEnsureCapacity_real_T(pp_breaks, i7);
  for (i7 = 0; i7 < x_idx_0; i7++) {
    pp_breaks->data[i7] = x->data[i7];
  }

  for (x_idx_0 = 0; x_idx_0 <= nxm1 - 2; x_idx_0++) {
    dxj = x->data[x_idx_0 + 1] - x->data[x_idx_0];
    dzzdx_im = y->data[x_idx_0 + 2].re - y->data[x_idx_0 + 1].re;
    ai = y->data[x_idx_0 + 2].im - y->data[x_idx_0 + 1].im;
    if (ai == 0.0) {
      divdifij_re = dzzdx_im / dxj;
      divdifij_im = 0.0;
    } else if (dzzdx_im == 0.0) {
      divdifij_re = 0.0;
      divdifij_im = ai / dxj;
    } else {
      divdifij_re = dzzdx_im / dxj;
      divdifij_im = ai / dxj;
    }

    dzzdx_im = divdifij_re - s[x_idx_0].re;
    ai = divdifij_im - s[x_idx_0].im;
    if (ai == 0.0) {
      dzzdx_re = dzzdx_im / dxj;
      dzzdx_im = 0.0;
    } else if (dzzdx_im == 0.0) {
      dzzdx_re = 0.0;
      dzzdx_im = ai / dxj;
    } else {
      dzzdx_re = dzzdx_im / dxj;
      dzzdx_im = ai / dxj;
    }

    divdifij_re = s[1].re - divdifij_re;
    divdifij_im = s[1].im - divdifij_im;
    if (divdifij_im == 0.0) {
      divdifij_re /= dxj;
      divdifij_im = 0.0;
    } else if (divdifij_re == 0.0) {
      divdifij_re = 0.0;
      divdifij_im /= dxj;
    } else {
      divdifij_re /= dxj;
      divdifij_im /= dxj;
    }

    ai = divdifij_re - dzzdx_re;
    b_divdifij_im = divdifij_im - dzzdx_im;
    if (b_divdifij_im == 0.0) {
      pp_coefs[x_idx_0].re = ai / dxj;
      pp_coefs[x_idx_0].im = 0.0;
    } else if (ai == 0.0) {
      pp_coefs[x_idx_0].re = 0.0;
      pp_coefs[x_idx_0].im = b_divdifij_im / dxj;
    } else {
      pp_coefs[x_idx_0].re = ai / dxj;
      pp_coefs[x_idx_0].im = b_divdifij_im / dxj;
    }

    pp_coefs[x_idx_0 + 1].re = 2.0 * dzzdx_re - divdifij_re;
    pp_coefs[x_idx_0 + 1].im = 2.0 * dzzdx_im - divdifij_im;
    pp_coefs[x_idx_0 + 2] = s[x_idx_0];
    pp_coefs[3] = y->data[x_idx_0 + 1];
  }
}

/*
 * File trailer for pwchcore.c
 *
 * [EOF]
 */
