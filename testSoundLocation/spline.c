/*
 * File: spline.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include <string.h>
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "spline.h"
#include "SoundLocation_emxutil.h"
#include "pwchcore.h"

/* Function Declarations */
static void degenerateSpline(const emxArray_real_T *x, const emxArray_creal_T *y,
  emxArray_real_T *pp_breaks, creal_T pp_coefs_data[], int pp_coefs_size[2]);

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_creal_T *y
 *                emxArray_real_T *pp_breaks
 *                creal_T pp_coefs_data[]
 *                int pp_coefs_size[2]
 * Return Type  : void
 */
static void degenerateSpline(const emxArray_real_T *x, const emxArray_creal_T *y,
  emxArray_real_T *pp_breaks, creal_T pp_coefs_data[], int pp_coefs_size[2])
{
  bool has_endslopes;
  int numterms;
  double d21;
  double ar;
  double y_re;
  emxArray_real_T *expl_temp;
  double ai;
  creal_T endslopes[2];
  double dvdf1_re;
  creal_T pp1_coefs[4];
  double dvdf1_im;
  int pp_coefs_idx_1;
  double br;
  has_endslopes = (y->size[1] == x->size[1] + 2);
  if (x->size[1] <= 2) {
    if (has_endslopes) {
      numterms = 4;
    } else {
      numterms = 2;
    }
  } else {
    numterms = 3;
  }

  pp_coefs_size[0] = 1;
  pp_coefs_size[1] = numterms;
  if (x->size[1] <= 2) {
    if (has_endslopes) {
      emxInit_real_T(&expl_temp, 2);
      endslopes[0] = y->data[0];
      endslopes[1] = y->data[y->size[1] - 1];
      pwchcore(x, y, endslopes, expl_temp, pp1_coefs);
      emxFree_real_T(&expl_temp);
      numterms = pp_coefs_size[0];
      pp_coefs_idx_1 = pp_coefs_size[1];
      pp_coefs_size[0] = 1;
      pp_coefs_size[1] = pp_coefs_idx_1;
      numterms *= pp_coefs_idx_1;
      if (0 <= numterms - 1) {
        memcpy(&pp_coefs_data[0], &pp1_coefs[0], (unsigned int)(numterms * (int)
                sizeof(creal_T)));
      }
    } else {
      y_re = y->data[1].re - y->data[0].re;
      ai = y->data[1].im - y->data[0].im;
      ar = x->data[1] - x->data[0];
      if (ai == 0.0) {
        pp_coefs_data[0].re = y_re / ar;
        pp_coefs_data[0].im = 0.0;
      } else if (y_re == 0.0) {
        pp_coefs_data[0].re = 0.0;
        pp_coefs_data[0].im = ai / ar;
      } else {
        pp_coefs_data[0].re = y_re / ar;
        pp_coefs_data[0].im = ai / ar;
      }

      pp_coefs_data[1] = y->data[0];
    }

    pp_coefs_idx_1 = x->size[1];
    numterms = pp_breaks->size[0] * pp_breaks->size[1];
    pp_breaks->size[0] = 1;
    pp_breaks->size[1] = pp_coefs_idx_1;
    emxEnsureCapacity_real_T(pp_breaks, numterms);
    for (numterms = 0; numterms < pp_coefs_idx_1; numterms++) {
      pp_breaks->data[numterms] = x->data[numterms];
    }
  } else {
    d21 = x->data[1] - x->data[0];
    ar = y->data[1].re - y->data[0].re;
    ai = y->data[1].im - y->data[0].im;
    if (ai == 0.0) {
      dvdf1_re = ar / d21;
      dvdf1_im = 0.0;
    } else if (ar == 0.0) {
      dvdf1_re = 0.0;
      dvdf1_im = ai / d21;
    } else {
      dvdf1_re = ar / d21;
      dvdf1_im = ai / d21;
    }

    ar = y->data[2].re - y->data[1].re;
    ai = y->data[2].im - y->data[1].im;
    br = x->data[2] - x->data[1];
    if (ai == 0.0) {
      y_re = ar / br;
      ai = 0.0;
    } else if (ar == 0.0) {
      y_re = 0.0;
      ai /= br;
    } else {
      y_re = ar / br;
      ai /= br;
    }

    y_re -= dvdf1_re;
    ai -= dvdf1_im;
    ar = x->data[2] - x->data[0];
    if (ai == 0.0) {
      pp_coefs_data[0].re = y_re / ar;
      pp_coefs_data[0].im = 0.0;
    } else if (y_re == 0.0) {
      pp_coefs_data[0].re = 0.0;
      pp_coefs_data[0].im = ai / ar;
    } else {
      pp_coefs_data[0].re = y_re / ar;
      pp_coefs_data[0].im = ai / ar;
    }

    pp_coefs_data[1].re = dvdf1_re - pp_coefs_data[0].re * d21;
    pp_coefs_data[1].im = dvdf1_im - pp_coefs_data[0].im * d21;
    pp_coefs_data[2] = y->data[0];
    ar = x->data[0];
    ai = x->data[2];
    numterms = pp_breaks->size[0] * pp_breaks->size[1];
    pp_breaks->size[0] = 1;
    pp_breaks->size[1] = 2;
    emxEnsureCapacity_real_T(pp_breaks, numterms);
    pp_breaks->data[0] = ar;
    pp_breaks->data[1] = ai;
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_creal_T *y
 *                emxArray_real_T *output_breaks
 *                emxArray_creal_T *output_coefs
 * Return Type  : void
 */
void spline(const emxArray_real_T *x, const emxArray_creal_T *y, emxArray_real_T
            *output_breaks, emxArray_creal_T *output_coefs)
{
  bool has_endslopes;
  emxArray_creal_T *s;
  emxArray_creal_T *dvdf;
  emxArray_real_T *dx;
  emxArray_real_T *md;
  emxArray_creal_T *t2_coefs;
  int nxm1;
  creal_T t1_coefs_data[4];
  int t1_coefs_size[2];
  int y_re_tmp;
  int szdvdf_idx_1;
  int szs_idx_1;
  int yoffset;
  double dx_re;
  double d31;
  double y_im;
  double r;
  double dnnm2;
  has_endslopes = (y->size[1] == x->size[1] + 2);
  emxInit_creal_T(&s, 2);
  emxInit_creal_T(&dvdf, 2);
  emxInit_real_T(&dx, 2);
  emxInit_real_T(&md, 2);
  emxInit_creal_T(&t2_coefs, 2);
  if ((x->size[1] <= 2) || ((x->size[1] <= 3) && (!has_endslopes))) {
    degenerateSpline(x, y, output_breaks, t1_coefs_data, t1_coefs_size);
    y_re_tmp = output_coefs->size[0] * output_coefs->size[1];
    output_coefs->size[0] = 1;
    output_coefs->size[1] = t1_coefs_size[1];
    emxEnsureCapacity_creal_T(output_coefs, y_re_tmp);
    szdvdf_idx_1 = t1_coefs_size[0] * t1_coefs_size[1];
    for (y_re_tmp = 0; y_re_tmp < szdvdf_idx_1; y_re_tmp++) {
      output_coefs->data[y_re_tmp] = t1_coefs_data[y_re_tmp];
    }
  } else {
    nxm1 = x->size[1] - 1;
    if (has_endslopes) {
      szdvdf_idx_1 = y->size[1] - 3;
      szs_idx_1 = y->size[1] - 2;
      yoffset = 1;
    } else {
      szdvdf_idx_1 = y->size[1] - 1;
      szs_idx_1 = y->size[1];
      yoffset = 0;
    }

    y_re_tmp = s->size[0] * s->size[1];
    s->size[0] = 1;
    s->size[1] = szs_idx_1;
    emxEnsureCapacity_creal_T(s, y_re_tmp);
    y_re_tmp = dvdf->size[0] * dvdf->size[1];
    dvdf->size[0] = 1;
    dvdf->size[1] = szdvdf_idx_1;
    emxEnsureCapacity_creal_T(dvdf, y_re_tmp);
    y_re_tmp = x->size[1] - 1;
    szdvdf_idx_1 = dx->size[0] * dx->size[1];
    dx->size[0] = 1;
    dx->size[1] = y_re_tmp;
    emxEnsureCapacity_real_T(dx, szdvdf_idx_1);
    for (szdvdf_idx_1 = 0; szdvdf_idx_1 < nxm1; szdvdf_idx_1++) {
      dx->data[szdvdf_idx_1] = x->data[szdvdf_idx_1 + 1] - x->data[szdvdf_idx_1];
      szs_idx_1 = yoffset + szdvdf_idx_1;
      y_re_tmp = szs_idx_1 + 1;
      r = y->data[y_re_tmp].re - y->data[szs_idx_1].re;
      y_im = y->data[y_re_tmp].im - y->data[szs_idx_1].im;
      dx_re = dx->data[szdvdf_idx_1];
      if (y_im == 0.0) {
        dvdf->data[szdvdf_idx_1].re = r / dx_re;
        dvdf->data[szdvdf_idx_1].im = 0.0;
      } else if (r == 0.0) {
        dvdf->data[szdvdf_idx_1].re = 0.0;
        dvdf->data[szdvdf_idx_1].im = y_im / dx_re;
      } else {
        dvdf->data[szdvdf_idx_1].re = r / dx_re;
        dvdf->data[szdvdf_idx_1].im = y_im / dx_re;
      }
    }

    for (szdvdf_idx_1 = 2; szdvdf_idx_1 <= nxm1; szdvdf_idx_1++) {
      dx_re = dx->data[szdvdf_idx_1 - 1] * dvdf->data[szdvdf_idx_1 - 2].re +
        dx->data[szdvdf_idx_1 - 2] * dvdf->data[szdvdf_idx_1 - 1].re;
      y_im = dx->data[szdvdf_idx_1 - 1] * dvdf->data[szdvdf_idx_1 - 2].im +
        dx->data[szdvdf_idx_1 - 2] * dvdf->data[szdvdf_idx_1 - 1].im;
      s->data[szdvdf_idx_1 - 1].re = 3.0 * dx_re;
      s->data[szdvdf_idx_1 - 1].im = 3.0 * y_im;
    }

    if (has_endslopes) {
      d31 = 0.0;
      dnnm2 = 0.0;
      s->data[0].re = dx->data[1] * y->data[0].re;
      s->data[0].im = dx->data[1] * y->data[0].im;
      s->data[x->size[1] - 1].re = dx->data[x->size[1] - 3] * y->data[x->size[1]
        + 1].re;
      s->data[x->size[1] - 1].im = dx->data[x->size[1] - 3] * y->data[x->size[1]
        + 1].im;
    } else {
      d31 = x->data[2] - x->data[0];
      dnnm2 = x->data[x->size[1] - 1] - x->data[x->size[1] - 3];
      dx_re = (dx->data[0] + 2.0 * d31) * dx->data[1] * dvdf->data[0].re +
        dx->data[0] * dx->data[0] * dvdf->data[1].re;
      y_im = (dx->data[0] + 2.0 * d31) * dx->data[1] * dvdf->data[0].im +
        dx->data[0] * dx->data[0] * dvdf->data[1].im;
      if (y_im == 0.0) {
        s->data[0].re = dx_re / d31;
        s->data[0].im = 0.0;
      } else if (dx_re == 0.0) {
        s->data[0].re = 0.0;
        s->data[0].im = y_im / d31;
      } else {
        s->data[0].re = dx_re / d31;
        s->data[0].im = y_im / d31;
      }

      dx_re = (dx->data[x->size[1] - 2] + 2.0 * dnnm2) * dx->data[x->size[1] - 3]
        * dvdf->data[x->size[1] - 2].re + dx->data[x->size[1] - 2] * dx->data
        [x->size[1] - 2] * dvdf->data[x->size[1] - 3].re;
      y_im = (dx->data[x->size[1] - 2] + 2.0 * dnnm2) * dx->data[x->size[1] - 3]
        * dvdf->data[x->size[1] - 2].im + dx->data[x->size[1] - 2] * dx->data
        [x->size[1] - 2] * dvdf->data[x->size[1] - 3].im;
      if (y_im == 0.0) {
        s->data[x->size[1] - 1].re = dx_re / dnnm2;
        s->data[x->size[1] - 1].im = 0.0;
      } else if (dx_re == 0.0) {
        s->data[x->size[1] - 1].re = 0.0;
        s->data[x->size[1] - 1].im = y_im / dnnm2;
      } else {
        s->data[x->size[1] - 1].re = dx_re / dnnm2;
        s->data[x->size[1] - 1].im = y_im / dnnm2;
      }
    }

    y_re_tmp = md->size[0] * md->size[1];
    md->size[0] = x->size[0];
    md->size[1] = x->size[1];
    emxEnsureCapacity_real_T(md, y_re_tmp);
    md->data[0] = dx->data[1];
    md->data[x->size[1] - 1] = dx->data[x->size[1] - 3];
    for (szdvdf_idx_1 = 2; szdvdf_idx_1 <= nxm1; szdvdf_idx_1++) {
      md->data[szdvdf_idx_1 - 1] = 2.0 * (dx->data[szdvdf_idx_1 - 1] + dx->
        data[szdvdf_idx_1 - 2]);
    }

    r = dx->data[1] / md->data[0];
    md->data[1] -= r * d31;
    s->data[1].re -= r * s->data[0].re;
    s->data[1].im -= r * s->data[0].im;
    for (szdvdf_idx_1 = 3; szdvdf_idx_1 <= nxm1; szdvdf_idx_1++) {
      r = dx->data[szdvdf_idx_1 - 1] / md->data[szdvdf_idx_1 - 2];
      md->data[szdvdf_idx_1 - 1] -= r * dx->data[szdvdf_idx_1 - 3];
      s->data[szdvdf_idx_1 - 1].re -= r * s->data[szdvdf_idx_1 - 2].re;
      s->data[szdvdf_idx_1 - 1].im -= r * s->data[szdvdf_idx_1 - 2].im;
    }

    r = dnnm2 / md->data[x->size[1] - 2];
    md->data[x->size[1] - 1] -= r * dx->data[x->size[1] - 3];
    s->data[x->size[1] - 1].re -= r * s->data[x->size[1] - 2].re;
    s->data[x->size[1] - 1].im -= r * s->data[x->size[1] - 2].im;
    y_im = s->data[x->size[1] - 1].re;
    r = s->data[x->size[1] - 1].im;
    dnnm2 = md->data[x->size[1] - 1];
    if (r == 0.0) {
      s->data[x->size[1] - 1].re = y_im / dnnm2;
      s->data[x->size[1] - 1].im = 0.0;
    } else if (y_im == 0.0) {
      s->data[x->size[1] - 1].re = 0.0;
      s->data[x->size[1] - 1].im = r / dnnm2;
    } else {
      s->data[x->size[1] - 1].re = y_im / dnnm2;
      s->data[x->size[1] - 1].im = r / dnnm2;
    }

    for (szdvdf_idx_1 = nxm1; szdvdf_idx_1 >= 2; szdvdf_idx_1--) {
      y_im = s->data[szdvdf_idx_1 - 1].re - dx->data[szdvdf_idx_1 - 2] * s->
        data[szdvdf_idx_1].re;
      r = s->data[szdvdf_idx_1 - 1].im - dx->data[szdvdf_idx_1 - 2] * s->
        data[szdvdf_idx_1].im;
      dnnm2 = md->data[szdvdf_idx_1 - 1];
      if (r == 0.0) {
        s->data[szdvdf_idx_1 - 1].re = y_im / dnnm2;
        s->data[szdvdf_idx_1 - 1].im = 0.0;
      } else if (y_im == 0.0) {
        s->data[szdvdf_idx_1 - 1].re = 0.0;
        s->data[szdvdf_idx_1 - 1].im = r / dnnm2;
      } else {
        s->data[szdvdf_idx_1 - 1].re = y_im / dnnm2;
        s->data[szdvdf_idx_1 - 1].im = r / dnnm2;
      }
    }

    y_im = s->data[0].re - d31 * s->data[1].re;
    r = s->data[0].im - d31 * s->data[1].im;
    dnnm2 = md->data[0];
    if (r == 0.0) {
      s->data[0].re = y_im / dnnm2;
      s->data[0].im = 0.0;
    } else if (y_im == 0.0) {
      s->data[0].re = 0.0;
      s->data[0].im = r / dnnm2;
    } else {
      s->data[0].re = y_im / dnnm2;
      s->data[0].im = r / dnnm2;
    }

    b_pwchcore(x, y, yoffset, s, dx, dvdf, output_breaks, t2_coefs);
    y_re_tmp = output_coefs->size[0] * output_coefs->size[1];
    output_coefs->size[0] = t2_coefs->size[0];
    output_coefs->size[1] = 4;
    emxEnsureCapacity_creal_T(output_coefs, y_re_tmp);
    szdvdf_idx_1 = t2_coefs->size[0] * t2_coefs->size[1];
    for (y_re_tmp = 0; y_re_tmp < szdvdf_idx_1; y_re_tmp++) {
      output_coefs->data[y_re_tmp] = t2_coefs->data[y_re_tmp];
    }
  }

  emxFree_creal_T(&t2_coefs);
  emxFree_real_T(&md);
  emxFree_real_T(&dx);
  emxFree_creal_T(&dvdf);
  emxFree_creal_T(&s);
}

/*
 * File trailer for spline.c
 *
 * [EOF]
 */
