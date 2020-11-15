/*
 * File: fft1.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "SoundLocation.h"
#include "fft1.h"
#include "SoundLocation_emxutil.h"
#include "bluesteinSetup.h"

/* Function Declarations */
static void b_dobluesteinfft(const emxArray_creal_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y);
static void b_generate_twiddle_tables(int nRows, bool useRadix2, emxArray_real_T
  *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv);
static void b_r2br_r2dit_trig(const emxArray_creal_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y);
static void dobluesteinfft(const emxArray_real_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y);
static void generate_twiddle_tables(int nRows, bool useRadix2, emxArray_real_T
  *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv);
static void get_algo_sizes(int n1, bool useRadix2, int *N2blue, int *nRows);
static void r2br_r2dit_trig(const emxArray_real_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y);
static void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows,
  const emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T
  *y);

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                int N2
 *                int n1
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *sintabinv
 *                emxArray_creal_T *y
 * Return Type  : void
 */
static void b_dobluesteinfft(const emxArray_creal_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y)
{
  emxArray_creal_T *wwc;
  int minNrowsNx;
  emxArray_creal_T *fv;
  int denom_re_tmp;
  int xidx;
  int k;
  double denom_re;
  double denom_im;
  emxArray_creal_T *b_fv;
  double x_re;
  double x_im;
  double b_x_im;
  double b_x_re;
  double wwc_re;
  double wwc_im;
  emxInit_creal_T(&wwc, 1);
  b_bluesteinSetup(n1, wwc);
  minNrowsNx = x->size[0];
  if (n1 < minNrowsNx) {
    minNrowsNx = n1;
  }

  emxInit_creal_T(&fv, 1);
  denom_re_tmp = fv->size[0];
  fv->size[0] = n1;
  emxEnsureCapacity_creal_T(fv, denom_re_tmp);
  if (n1 > x->size[0]) {
    xidx = fv->size[0];
    denom_re_tmp = fv->size[0];
    fv->size[0] = xidx;
    emxEnsureCapacity_creal_T(fv, denom_re_tmp);
    for (denom_re_tmp = 0; denom_re_tmp < xidx; denom_re_tmp++) {
      fv->data[denom_re_tmp].re = 0.0;
      fv->data[denom_re_tmp].im = 0.0;
    }
  }

  denom_re_tmp = y->size[0];
  y->size[0] = fv->size[0];
  emxEnsureCapacity_creal_T(y, denom_re_tmp);
  xidx = fv->size[0];
  for (denom_re_tmp = 0; denom_re_tmp < xidx; denom_re_tmp++) {
    y->data[denom_re_tmp] = fv->data[denom_re_tmp];
  }

  xidx = 0;
  for (k = 0; k < minNrowsNx; k++) {
    denom_re_tmp = (n1 + k) - 1;
    denom_re = wwc->data[denom_re_tmp].re;
    denom_im = wwc->data[denom_re_tmp].im;
    x_re = x->data[xidx].re;
    x_im = x->data[xidx].im;
    b_x_im = x->data[xidx].im;
    b_x_re = x->data[xidx].re;
    y->data[k].re = denom_re * x_re + denom_im * x_im;
    y->data[k].im = denom_re * b_x_im - denom_im * b_x_re;
    xidx++;
  }

  denom_re_tmp = minNrowsNx + 1;
  for (k = denom_re_tmp; k <= n1; k++) {
    y->data[k - 1].re = 0.0;
    y->data[k - 1].im = 0.0;
  }

  emxInit_creal_T(&b_fv, 1);
  r2br_r2dit_trig_impl(y, N2, costab, sintab, fv);
  r2br_r2dit_trig_impl(wwc, N2, costab, sintab, b_fv);
  denom_re_tmp = b_fv->size[0];
  b_fv->size[0] = fv->size[0];
  emxEnsureCapacity_creal_T(b_fv, denom_re_tmp);
  xidx = fv->size[0];
  for (denom_re_tmp = 0; denom_re_tmp < xidx; denom_re_tmp++) {
    denom_re = fv->data[denom_re_tmp].re;
    denom_im = fv->data[denom_re_tmp].im;
    x_re = b_fv->data[denom_re_tmp].re;
    x_im = b_fv->data[denom_re_tmp].im;
    b_fv->data[denom_re_tmp].re = denom_re * x_re - denom_im * x_im;
    b_fv->data[denom_re_tmp].im = denom_re * x_im + denom_im * x_re;
  }

  b_r2br_r2dit_trig(b_fv, N2, costab, sintabinv, fv);
  xidx = 0;
  denom_re_tmp = wwc->size[0];
  emxFree_creal_T(&b_fv);
  for (k = n1; k <= denom_re_tmp; k++) {
    b_x_im = wwc->data[k - 1].re;
    denom_re = fv->data[k - 1].re;
    b_x_re = wwc->data[k - 1].im;
    denom_im = fv->data[k - 1].im;
    wwc_re = wwc->data[k - 1].re;
    x_im = fv->data[k - 1].im;
    wwc_im = wwc->data[k - 1].im;
    x_re = fv->data[k - 1].re;
    y->data[xidx].re = b_x_im * denom_re + b_x_re * denom_im;
    y->data[xidx].im = wwc_re * x_im - wwc_im * x_re;
    b_x_im = wwc->data[k - 1].re;
    denom_re = fv->data[k - 1].re;
    b_x_re = wwc->data[k - 1].im;
    denom_im = fv->data[k - 1].im;
    wwc_re = wwc->data[k - 1].re;
    x_im = fv->data[k - 1].im;
    wwc_im = wwc->data[k - 1].im;
    x_re = fv->data[k - 1].re;
    y->data[xidx].re = b_x_im * denom_re + b_x_re * denom_im;
    y->data[xidx].im = wwc_re * x_im - wwc_im * x_re;
    denom_re = y->data[xidx].re;
    denom_im = y->data[xidx].im;
    if (denom_im == 0.0) {
      y->data[xidx].re = denom_re / (double)n1;
      y->data[xidx].im = 0.0;
    } else if (denom_re == 0.0) {
      y->data[xidx].re = 0.0;
      y->data[xidx].im = denom_im / (double)n1;
    } else {
      y->data[xidx].re = denom_re / (double)n1;
      y->data[xidx].im = denom_im / (double)n1;
    }

    xidx++;
  }

  emxFree_creal_T(&fv);
  emxFree_creal_T(&wwc);
}

/*
 * Arguments    : int nRows
 *                bool useRadix2
 *                emxArray_real_T *costab
 *                emxArray_real_T *sintab
 *                emxArray_real_T *sintabinv
 * Return Type  : void
 */
static void b_generate_twiddle_tables(int nRows, bool useRadix2, emxArray_real_T
  *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  int n;
  int i5;
  int nd2;
  int k;
  emxInit_real_T(&costab1q, 2);
  e = 6.2831853071795862 / (double)nRows;
  n = nRows / 2 / 2;
  i5 = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, i5);
  costab1q->data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q->data[1 + k] = cos(e * (1.0 + (double)k));
  }

  i5 = nd2 + 2;
  nd2 = n - 1;
  for (k = i5; k <= nd2; k++) {
    costab1q->data[k] = sin(e * (double)(n - k));
  }

  costab1q->data[n] = 0.0;
  if (!useRadix2) {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i5 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i5);
    i5 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i5);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    i5 = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintabinv, i5);
    for (k = 0; k < n; k++) {
      sintabinv->data[1 + k] = costab1q->data[(n - k) - 1];
    }

    i5 = costab1q->size[1];
    for (k = i5; k <= nd2; k++) {
      sintabinv->data[k] = costab1q->data[k - n];
    }

    for (k = 0; k < n; k++) {
      costab->data[1 + k] = costab1q->data[1 + k];
      sintab->data[1 + k] = -costab1q->data[(n - k) - 1];
    }

    i5 = costab1q->size[1];
    for (k = i5; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - n];
    }
  } else {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i5 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i5);
    i5 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i5);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab->data[1 + k] = costab1q->data[1 + k];
      sintab->data[1 + k] = costab1q->data[(n - k) - 1];
    }

    i5 = costab1q->size[1];
    for (k = i5; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = costab1q->data[k - n];
    }

    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }

  emxFree_real_T(&costab1q);
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int n1_unsigned
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
static void b_r2br_r2dit_trig(const emxArray_creal_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y)
{
  int j;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int iy;
  int iDelta;
  int ix;
  int ju;
  int i;
  bool tst;
  double temp_re;
  double temp_im;
  int temp_re_tmp;
  double twid_re;
  double twid_im;
  j = x->size[0];
  if (j >= n1_unsigned) {
    j = n1_unsigned;
  }

  nRowsM2 = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  nRowsD4 = nRowsD2 / 2;
  iy = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, iy);
  if (n1_unsigned > x->size[0]) {
    iDelta = y->size[0];
    iy = y->size[0];
    y->size[0] = iDelta;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < iDelta; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= j - 2; i++) {
    y->data[iy] = x->data[ix];
    iDelta = n1_unsigned;
    tst = true;
    while (tst) {
      iDelta >>= 1;
      ju ^= iDelta;
      tst = ((ju & iDelta) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (n1_unsigned > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }
  }

  iDelta = 2;
  iy = 4;
  ix = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ix; i += iy) {
      temp_re_tmp = i + iDelta;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - temp_re;
      y->data[temp_re_tmp].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ju = 1;
    for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
      twid_re = costab->data[j];
      twid_im = sintab->data[j];
      i = ju;
      nRowsM2 = ju + ix;
      while (i < nRowsM2) {
        temp_re_tmp = i + iDelta;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iy;
      }

      ju++;
    }

    nRowsD4 /= 2;
    iDelta = iy;
    iy += iy;
    ix -= iDelta;
  }

  if (y->size[0] > 1) {
    temp_re = 1.0 / (double)y->size[0];
    iy = y->size[0];
    emxEnsureCapacity_creal_T(y, iy);
    iDelta = y->size[0];
    for (iy = 0; iy < iDelta; iy++) {
      y->data[iy].re *= temp_re;
      y->data[iy].im *= temp_re;
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int N2
 *                int n1
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *sintabinv
 *                emxArray_creal_T *y
 * Return Type  : void
 */
static void dobluesteinfft(const emxArray_real_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y)
{
  emxArray_creal_T *wwc;
  int minNrowsNx;
  int a_re_tmp;
  int xidx;
  int k;
  double a_re;
  double a_im;
  emxArray_creal_T *fv;
  emxArray_creal_T *b_fv;
  double fv_re;
  double fv_im;
  double wwc_re;
  double wwc_im;
  double b_wwc_re;
  double b_wwc_im;
  emxInit_creal_T(&wwc, 1);
  bluesteinSetup(n1, wwc);
  minNrowsNx = x->size[0];
  if (n1 < minNrowsNx) {
    minNrowsNx = n1;
  }

  a_re_tmp = y->size[0];
  y->size[0] = n1;
  emxEnsureCapacity_creal_T(y, a_re_tmp);
  if (n1 > x->size[0]) {
    xidx = y->size[0];
    a_re_tmp = y->size[0];
    y->size[0] = xidx;
    emxEnsureCapacity_creal_T(y, a_re_tmp);
    for (a_re_tmp = 0; a_re_tmp < xidx; a_re_tmp++) {
      y->data[a_re_tmp].re = 0.0;
      y->data[a_re_tmp].im = 0.0;
    }
  }

  xidx = 0;
  for (k = 0; k < minNrowsNx; k++) {
    a_re_tmp = (n1 + k) - 1;
    a_re = wwc->data[a_re_tmp].re;
    a_im = wwc->data[a_re_tmp].im;
    y->data[k].re = a_re * x->data[xidx];
    y->data[k].im = a_im * -x->data[xidx];
    xidx++;
  }

  a_re_tmp = minNrowsNx + 1;
  for (k = a_re_tmp; k <= n1; k++) {
    y->data[k - 1].re = 0.0;
    y->data[k - 1].im = 0.0;
  }

  emxInit_creal_T(&fv, 1);
  emxInit_creal_T(&b_fv, 1);
  r2br_r2dit_trig_impl(y, N2, costab, sintab, fv);
  r2br_r2dit_trig_impl(wwc, N2, costab, sintab, b_fv);
  a_re_tmp = b_fv->size[0];
  b_fv->size[0] = fv->size[0];
  emxEnsureCapacity_creal_T(b_fv, a_re_tmp);
  xidx = fv->size[0];
  for (a_re_tmp = 0; a_re_tmp < xidx; a_re_tmp++) {
    a_re = fv->data[a_re_tmp].re;
    a_im = fv->data[a_re_tmp].im;
    fv_re = b_fv->data[a_re_tmp].re;
    fv_im = b_fv->data[a_re_tmp].im;
    b_fv->data[a_re_tmp].re = a_re * fv_re - a_im * fv_im;
    b_fv->data[a_re_tmp].im = a_re * fv_im + a_im * fv_re;
  }

  b_r2br_r2dit_trig(b_fv, N2, costab, sintabinv, fv);
  xidx = 0;
  a_re_tmp = wwc->size[0];
  emxFree_creal_T(&b_fv);
  for (k = n1; k <= a_re_tmp; k++) {
    wwc_re = wwc->data[k - 1].re;
    a_re = fv->data[k - 1].re;
    wwc_im = wwc->data[k - 1].im;
    a_im = fv->data[k - 1].im;
    b_wwc_re = wwc->data[k - 1].re;
    fv_im = fv->data[k - 1].im;
    b_wwc_im = wwc->data[k - 1].im;
    fv_re = fv->data[k - 1].re;
    y->data[xidx].re = wwc_re * a_re + wwc_im * a_im;
    y->data[xidx].im = b_wwc_re * fv_im - b_wwc_im * fv_re;
    xidx++;
  }

  emxFree_creal_T(&fv);
  emxFree_creal_T(&wwc);
}

/*
 * Arguments    : int nRows
 *                bool useRadix2
 *                emxArray_real_T *costab
 *                emxArray_real_T *sintab
 *                emxArray_real_T *sintabinv
 * Return Type  : void
 */
static void generate_twiddle_tables(int nRows, bool useRadix2, emxArray_real_T
  *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  int n;
  int i3;
  int nd2;
  int k;
  emxInit_real_T(&costab1q, 2);
  e = 6.2831853071795862 / (double)nRows;
  n = nRows / 2 / 2;
  i3 = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, i3);
  costab1q->data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q->data[1 + k] = cos(e * (1.0 + (double)k));
  }

  i3 = nd2 + 2;
  nd2 = n - 1;
  for (k = i3; k <= nd2; k++) {
    costab1q->data[k] = sin(e * (double)(n - k));
  }

  costab1q->data[n] = 0.0;
  if (!useRadix2) {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i3 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i3);
    i3 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i3);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    i3 = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintabinv, i3);
    for (k = 0; k < n; k++) {
      sintabinv->data[1 + k] = costab1q->data[(n - k) - 1];
    }

    i3 = costab1q->size[1];
    for (k = i3; k <= nd2; k++) {
      sintabinv->data[k] = costab1q->data[k - n];
    }

    for (k = 0; k < n; k++) {
      costab->data[1 + k] = costab1q->data[1 + k];
      sintab->data[1 + k] = -costab1q->data[(n - k) - 1];
    }

    i3 = costab1q->size[1];
    for (k = i3; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - n];
    }
  } else {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i3 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i3);
    i3 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i3);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab->data[1 + k] = costab1q->data[1 + k];
      sintab->data[1 + k] = -costab1q->data[(n - k) - 1];
    }

    i3 = costab1q->size[1];
    for (k = i3; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - n];
    }

    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }

  emxFree_real_T(&costab1q);
}

/*
 * Arguments    : int n1
 *                bool useRadix2
 *                int *N2blue
 *                int *nRows
 * Return Type  : void
 */
static void get_algo_sizes(int n1, bool useRadix2, int *N2blue, int *nRows)
{
  int n;
  int pmax;
  int pmin;
  bool exitg1;
  int p;
  int pow2p;
  *N2blue = 1;
  if (useRadix2) {
    *nRows = n1;
  } else {
    n = (n1 + n1) - 1;
    pmax = 31;
    if (n <= 1) {
      pmax = 0;
    } else {
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmax - pmin > 1)) {
        p = (pmin + pmax) >> 1;
        pow2p = 1 << p;
        if (pow2p == n) {
          pmax = p;
          exitg1 = true;
        } else if (pow2p > n) {
          pmax = p;
        } else {
          pmin = p;
        }
      }
    }

    *N2blue = 1 << pmax;
    *nRows = *N2blue;
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int n1_unsigned
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
static void r2br_r2dit_trig(const emxArray_real_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y)
{
  int j;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int iy;
  int iDelta;
  int ix;
  int ju;
  int i;
  bool tst;
  double temp_re;
  double temp_im;
  int temp_re_tmp;
  double twid_re;
  double twid_im;
  j = x->size[0];
  if (j >= n1_unsigned) {
    j = n1_unsigned;
  }

  nRowsM2 = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  nRowsD4 = nRowsD2 / 2;
  iy = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, iy);
  if (n1_unsigned > x->size[0]) {
    iDelta = y->size[0];
    iy = y->size[0];
    y->size[0] = iDelta;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < iDelta; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= j - 2; i++) {
    y->data[iy].re = x->data[ix];
    y->data[iy].im = 0.0;
    iDelta = n1_unsigned;
    tst = true;
    while (tst) {
      iDelta >>= 1;
      ju ^= iDelta;
      tst = ((ju & iDelta) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy].re = x->data[ix];
  y->data[iy].im = 0.0;
  if (n1_unsigned > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }
  }

  iDelta = 2;
  iy = 4;
  ix = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ix; i += iy) {
      temp_re_tmp = i + iDelta;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - temp_re;
      y->data[temp_re_tmp].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ju = 1;
    for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
      twid_re = costab->data[j];
      twid_im = sintab->data[j];
      i = ju;
      nRowsM2 = ju + ix;
      while (i < nRowsM2) {
        temp_re_tmp = i + iDelta;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iy;
      }

      ju++;
    }

    nRowsD4 /= 2;
    iDelta = iy;
    iy += iy;
    ix -= iDelta;
  }
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int unsigned_nRows
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
static void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows,
  const emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T
  *y)
{
  int j;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int iy;
  int iDelta;
  int ix;
  int ju;
  int i;
  bool tst;
  double temp_re;
  double temp_im;
  int temp_re_tmp;
  double twid_re;
  double twid_im;
  j = x->size[0];
  if (j >= unsigned_nRows) {
    j = unsigned_nRows;
  }

  nRowsM2 = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  nRowsD4 = nRowsD2 / 2;
  iy = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal_T(y, iy);
  if (unsigned_nRows > x->size[0]) {
    iDelta = y->size[0];
    iy = y->size[0];
    y->size[0] = iDelta;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < iDelta; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= j - 2; i++) {
    y->data[iy] = x->data[ix];
    iDelta = unsigned_nRows;
    tst = true;
    while (tst) {
      iDelta >>= 1;
      ju ^= iDelta;
      tst = ((ju & iDelta) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }
  }

  iDelta = 2;
  iy = 4;
  ix = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ix; i += iy) {
      temp_re_tmp = i + iDelta;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - temp_re;
      y->data[temp_re_tmp].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ju = 1;
    for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
      twid_re = costab->data[j];
      twid_im = sintab->data[j];
      i = ju;
      nRowsM2 = ju + ix;
      while (i < nRowsM2) {
        temp_re_tmp = i + iDelta;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iy;
      }

      ju++;
    }

    nRowsD4 /= 2;
    iDelta = iy;
    iy += iy;
    ix -= iDelta;
  }
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int n
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void c_fft(const emxArray_creal_T *x, int n, emxArray_creal_T *y)
{
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  emxArray_creal_T *b_y;
  bool useRadix2;
  int N2blue;
  int nRows;
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  emxInit_creal_T(&b_y, 1);
  if ((x->size[0] == 0) || (n == 0)) {
    N2blue = b_y->size[0];
    b_y->size[0] = n;
    emxEnsureCapacity_creal_T(b_y, N2blue);
    if (n > x->size[0]) {
      nRows = b_y->size[0];
      N2blue = b_y->size[0];
      b_y->size[0] = nRows;
      emxEnsureCapacity_creal_T(b_y, N2blue);
      for (N2blue = 0; N2blue < nRows; N2blue++) {
        b_y->data[N2blue].re = 0.0;
        b_y->data[N2blue].im = 0.0;
      }
    }

    N2blue = y->size[0];
    y->size[0] = b_y->size[0];
    emxEnsureCapacity_creal_T(y, N2blue);
    nRows = b_y->size[0];
    for (N2blue = 0; N2blue < nRows; N2blue++) {
      y->data[N2blue] = b_y->data[N2blue];
    }
  } else {
    useRadix2 = ((n & (n - 1)) == 0);
    get_algo_sizes(n, useRadix2, &N2blue, &nRows);
    b_generate_twiddle_tables(nRows, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      b_r2br_r2dit_trig(x, n, costab, sintab, b_y);
      N2blue = y->size[0];
      y->size[0] = b_y->size[0];
      emxEnsureCapacity_creal_T(y, N2blue);
      nRows = b_y->size[0];
      for (N2blue = 0; N2blue < nRows; N2blue++) {
        y->data[N2blue] = b_y->data[N2blue];
      }
    } else {
      b_dobluesteinfft(x, N2blue, n, costab, sintab, sintabinv, y);
    }
  }

  emxFree_creal_T(&b_y);
  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int n
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void fft(const emxArray_real_T *x, int n, emxArray_creal_T *y)
{
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  bool useRadix2;
  int N2blue;
  int nRows;
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  if ((x->size[0] == 0) || (n == 0)) {
    N2blue = y->size[0];
    y->size[0] = n;
    emxEnsureCapacity_creal_T(y, N2blue);
    if (n > x->size[0]) {
      nRows = y->size[0];
      N2blue = y->size[0];
      y->size[0] = nRows;
      emxEnsureCapacity_creal_T(y, N2blue);
      for (N2blue = 0; N2blue < nRows; N2blue++) {
        y->data[N2blue].re = 0.0;
        y->data[N2blue].im = 0.0;
      }
    }
  } else {
    useRadix2 = ((n & (n - 1)) == 0);
    get_algo_sizes(n, useRadix2, &N2blue, &nRows);
    generate_twiddle_tables(nRows, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      r2br_r2dit_trig(x, n, costab, sintab, y);
    } else {
      dobluesteinfft(x, N2blue, n, costab, sintab, sintabinv, y);
    }
  }

  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

/*
 * File trailer for fft1.c
 *
 * [EOF]
 */
