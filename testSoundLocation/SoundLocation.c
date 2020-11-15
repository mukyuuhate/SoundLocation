/*
 * File: SoundLocation.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/* Include Files */
#include "SoundLocation.h"

/* Function Declarations */
static double GccInterp(const emxArray_real_T *sigMicA, const emxArray_real_T
  *sigMicB, double vf);
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */

/*
 * sigMicA = sigMicA-mean(sigMicA);
 * sigMicB = sigMicB-mean(sigMicB);
 * Arguments    : const emxArray_real_T *sigMicA
 *                const emxArray_real_T *sigMicB
 *                double vf
 * Return Type  : double
 */
static double GccInterp(const emxArray_real_T *sigMicA, const emxArray_real_T
  *sigMicB, double vf)
{
  double diff_len;
  emxArray_creal_T *FA;
  emxArray_creal_T *FB;
  emxArray_real_T *r1;
  emxArray_real_T *r2;
  emxArray_creal_T *b_FA;
  int k;
  int istop;
  emxArray_real_T *r3;
  double Mb;
  double absbr;
  double absbi;
  double br;
  int iidx;
  double ex_re;
  double ex_im;
  emxArray_real_T *ori_x;
  bool SCALEA;
  double ma;
  emxArray_real_T *up_x;
  bool SCALEB;
  int u1;
  emxArray_creal_T *c_FA;
  int ndbl;
  double Ma;
  emxArray_creal_T *R_ab_sf_up;
  emxInit_creal_T(&FA, 2);
  emxInit_creal_T(&FB, 2);
  emxInit_real_T(&r1, 2);
  emxInit_real_T(&r2, 2);
  emxInit_creal_T(&b_FA, 2);
  b_fft(sigMicA, sigMicA->size[1], FA);

  /* 傅里叶变换 */
  b_fft(sigMicB, sigMicB->size[1], FB);

  /* 求互功率谱 */
  /* 求幅度 */
  /* 去除幅度信息 */
  b_abs(FA, r1);
  b_abs(FB, r2);
  k = b_FA->size[0] * b_FA->size[1];
  b_FA->size[0] = 1;
  b_FA->size[1] = FA->size[1];
  emxEnsureCapacity_creal_T(b_FA, k);
  istop = FA->size[0] * FA->size[1];
  for (k = 0; k < istop; k++) {
    Mb = FB->data[k].re;
    absbr = -FB->data[k].im;
    absbi = FA->data[k].re;
    br = FA->data[k].im;
    b_FA->data[k].re = absbi * Mb - br * absbr;
    b_FA->data[k].im = absbi * absbr + br * Mb;
  }

  emxInit_real_T(&r3, 2);
  k = r3->size[0] * r3->size[1];
  r3->size[0] = 1;
  r3->size[1] = r1->size[1];
  emxEnsureCapacity_real_T(r3, k);
  istop = r1->size[0] * r1->size[1];
  for (k = 0; k < istop; k++) {
    r3->data[k] = r1->data[k] * r2->data[k];
  }

  emxFree_real_T(&r2);
  emxFree_real_T(&r1);
  rdivide_helper(b_FA, r3, FA);
  ifft(FA, FB);
  k = FA->size[0] * FA->size[1];
  FA->size[0] = 1;
  FA->size[1] = FB->size[1];
  emxEnsureCapacity_creal_T(FA, k);
  istop = FB->size[0] * FB->size[1];
  emxFree_real_T(&r3);
  emxFree_creal_T(&b_FA);
  for (k = 0; k < istop; k++) {
    FA->data[k] = FB->data[k];
  }

  fftshift(FA);
  istop = FA->size[1];
  iidx = 1;
  ex_re = FA->data[0].re;
  ex_im = FA->data[0].im;
  for (k = 2; k <= istop; k++) {
    if (rtIsNaN(FA->data[k - 1].re) || rtIsNaN(FA->data[k - 1].im)) {
      SCALEA = false;
    } else if (rtIsNaN(ex_re) || rtIsNaN(ex_im)) {
      SCALEA = true;
    } else {
      ma = fabs(ex_re);
      if ((ma > 8.9884656743115785E+307) || (fabs(ex_im) >
           8.9884656743115785E+307)) {
        SCALEA = true;
      } else {
        SCALEA = false;
      }

      if ((fabs(FA->data[k - 1].re) > 8.9884656743115785E+307) || (fabs(FA->
            data[k - 1].im) > 8.9884656743115785E+307)) {
        SCALEB = true;
      } else {
        SCALEB = false;
      }

      if (SCALEA || SCALEB) {
        absbi = rt_hypotd_snf(ex_re / 2.0, ex_im / 2.0);
        br = rt_hypotd_snf(FA->data[k - 1].re / 2.0, FA->data[k - 1].im / 2.0);
      } else {
        absbi = rt_hypotd_snf(ex_re, ex_im);
        br = rt_hypotd_snf(FA->data[k - 1].re, FA->data[k - 1].im);
      }

      if (absbi == br) {
        Mb = fabs(ex_im);
        absbr = fabs(FA->data[k - 1].re);
        absbi = fabs(FA->data[k - 1].im);
        if (ma > Mb) {
          Ma = ma;
          ma = Mb;
        } else {
          Ma = Mb;
        }

        if (absbr > absbi) {
          Mb = absbr;
          absbr = absbi;
        } else {
          Mb = absbi;
        }

        if (Ma > Mb) {
          if (ma < absbr) {
            absbi = Ma - Mb;
            br = (ma / 2.0 + absbr / 2.0) / (Ma / 2.0 + Mb / 2.0) * (absbr - ma);
          } else {
            absbi = Ma;
            br = Mb;
          }
        } else if (Ma < Mb) {
          if (ma > absbr) {
            br = Mb - Ma;
            absbi = (ma / 2.0 + absbr / 2.0) / (Ma / 2.0 + Mb / 2.0) * (ma -
              absbr);
          } else {
            absbi = Ma;
            br = Mb;
          }
        } else {
          absbi = ma;
          br = absbr;
        }

        if (absbi == br) {
          absbi = rt_atan2d_snf(ex_im, ex_re);
          br = rt_atan2d_snf(FA->data[k - 1].im, FA->data[k - 1].re);
          if (absbi == br) {
            br = FA->data[k - 1].re;
            absbr = FA->data[k - 1].im;
            if (absbi > 0.78539816339744828) {
              if (absbi > 2.3561944901923448) {
                absbi = -ex_im;
                br = -absbr;
              } else {
                absbi = -ex_re;
                br = -br;
              }
            } else if (absbi > -0.78539816339744828) {
              absbi = ex_im;
              br = absbr;
            } else if (absbi > -2.3561944901923448) {
              absbi = ex_re;
            } else {
              absbi = -ex_im;
              br = -absbr;
            }

            if (absbi == br) {
              absbi = 0.0;
              br = 0.0;
            }
          }
        }
      }

      SCALEA = (absbi < br);
    }

    if (SCALEA) {
      ex_re = FA->data[k - 1].re;
      ex_im = FA->data[k - 1].im;
      iidx = k;
    }
  }

  /* 互相关最大值的位置体现了延迟差。 */
  emxInit_real_T(&ori_x, 2);
  if (iidx + 2 < iidx - 2) {
    ori_x->size[0] = 1;
    ori_x->size[1] = 0;
  } else {
    k = ori_x->size[0] * ori_x->size[1];
    ori_x->size[0] = 1;
    ori_x->size[1] = 5;
    emxEnsureCapacity_real_T(ori_x, k);
    for (k = 0; k < 5; k++) {
      ori_x->data[k] = (iidx + k) - 2;
    }
  }

  emxInit_real_T(&up_x, 2);
  if (iidx + 2 < iidx - 2) {
    up_x->size[0] = 1;
    up_x->size[1] = 0;
  } else {
    k = (int)fabs((double)iidx - 2.0);
    u1 = iidx + 2;
    if (k > u1) {
      u1 = k;
    }

    if (0.0 < 4.4408920985006262E-16 * (double)u1) {
      ndbl = 41;
      Mb = (double)iidx + 2.0;
    } else {
      ndbl = 41;
      Mb = ((double)iidx - 2.0) + 4.0;
    }

    k = up_x->size[0] * up_x->size[1];
    up_x->size[0] = 1;
    up_x->size[1] = ndbl;
    emxEnsureCapacity_real_T(up_x, k);
    up_x->data[0] = (double)iidx - 2.0;
    up_x->data[ndbl - 1] = Mb;
    istop = (ndbl - 1) / 2;
    for (k = 0; k <= istop - 2; k++) {
      absbr = (1.0 + (double)k) * 0.1;
      up_x->data[1 + k] = ((double)iidx - 2.0) + absbr;
      up_x->data[(ndbl - k) - 2] = Mb - absbr;
    }

    if (istop << 1 == ndbl - 1) {
      up_x->data[istop] = (((double)iidx - 2.0) + Mb) / 2.0;
    } else {
      absbr = (double)istop * 0.1;
      up_x->data[istop] = ((double)iidx - 2.0) + absbr;
      up_x->data[istop + 1] = Mb - absbr;
    }
  }

  emxInit_creal_T(&c_FA, 2);
  k = c_FA->size[0] * c_FA->size[1];
  c_FA->size[0] = 1;
  c_FA->size[1] = ori_x->size[1];
  emxEnsureCapacity_creal_T(c_FA, k);
  istop = ori_x->size[0] * ori_x->size[1];
  for (k = 0; k < istop; k++) {
    c_FA->data[k] = FA->data[(int)ori_x->data[k] - 1];
  }

  emxFree_creal_T(&FA);
  emxInit_creal_T(&R_ab_sf_up, 2);
  interp1(ori_x, c_FA, up_x, R_ab_sf_up);
  istop = R_ab_sf_up->size[1];
  iidx = 1;
  ex_re = R_ab_sf_up->data[0].re;
  ex_im = R_ab_sf_up->data[0].im;
  emxFree_creal_T(&c_FA);
  emxFree_real_T(&ori_x);
  for (k = 2; k <= istop; k++) {
    if (rtIsNaN(R_ab_sf_up->data[k - 1].re) || rtIsNaN(R_ab_sf_up->data[k - 1].
         im)) {
      SCALEA = false;
    } else if (rtIsNaN(ex_re) || rtIsNaN(ex_im)) {
      SCALEA = true;
    } else {
      ma = fabs(ex_re);
      if ((ma > 8.9884656743115785E+307) || (fabs(ex_im) >
           8.9884656743115785E+307)) {
        SCALEA = true;
      } else {
        SCALEA = false;
      }

      if ((fabs(R_ab_sf_up->data[k - 1].re) > 8.9884656743115785E+307) || (fabs
           (R_ab_sf_up->data[k - 1].im) > 8.9884656743115785E+307)) {
        SCALEB = true;
      } else {
        SCALEB = false;
      }

      if (SCALEA || SCALEB) {
        absbi = rt_hypotd_snf(ex_re / 2.0, ex_im / 2.0);
        br = rt_hypotd_snf(R_ab_sf_up->data[k - 1].re / 2.0, R_ab_sf_up->data[k
                           - 1].im / 2.0);
      } else {
        absbi = rt_hypotd_snf(ex_re, ex_im);
        br = rt_hypotd_snf(R_ab_sf_up->data[k - 1].re, R_ab_sf_up->data[k - 1].
                           im);
      }

      if (absbi == br) {
        Mb = fabs(ex_im);
        absbr = fabs(R_ab_sf_up->data[k - 1].re);
        absbi = fabs(R_ab_sf_up->data[k - 1].im);
        if (ma > Mb) {
          Ma = ma;
          ma = Mb;
        } else {
          Ma = Mb;
        }

        if (absbr > absbi) {
          Mb = absbr;
          absbr = absbi;
        } else {
          Mb = absbi;
        }

        if (Ma > Mb) {
          if (ma < absbr) {
            absbi = Ma - Mb;
            br = (ma / 2.0 + absbr / 2.0) / (Ma / 2.0 + Mb / 2.0) * (absbr - ma);
          } else {
            absbi = Ma;
            br = Mb;
          }
        } else if (Ma < Mb) {
          if (ma > absbr) {
            br = Mb - Ma;
            absbi = (ma / 2.0 + absbr / 2.0) / (Ma / 2.0 + Mb / 2.0) * (ma -
              absbr);
          } else {
            absbi = Ma;
            br = Mb;
          }
        } else {
          absbi = ma;
          br = absbr;
        }

        if (absbi == br) {
          absbi = rt_atan2d_snf(ex_im, ex_re);
          br = rt_atan2d_snf(R_ab_sf_up->data[k - 1].im, R_ab_sf_up->data[k - 1]
                             .re);
          if (absbi == br) {
            br = R_ab_sf_up->data[k - 1].re;
            absbr = R_ab_sf_up->data[k - 1].im;
            if (absbi > 0.78539816339744828) {
              if (absbi > 2.3561944901923448) {
                absbi = -ex_im;
                br = -absbr;
              } else {
                absbi = -ex_re;
                br = -br;
              }
            } else if (absbi > -0.78539816339744828) {
              absbi = ex_im;
              br = absbr;
            } else if (absbi > -2.3561944901923448) {
              absbi = ex_re;
            } else {
              absbi = -ex_im;
              br = -absbr;
            }

            if (absbi == br) {
              absbi = 0.0;
              br = 0.0;
            }
          }
        }
      }

      SCALEA = (absbi < br);
    }

    if (SCALEA) {
      ex_re = R_ab_sf_up->data[k - 1].re;
      ex_im = R_ab_sf_up->data[k - 1].im;
      iidx = k;
    }
  }

  emxFree_creal_T(&R_ab_sf_up);
  diff_len = (up_x->data[iidx - 1] - (double)FB->size[1] / 2.0) * vf;
  emxFree_real_T(&up_x);
  emxFree_creal_T(&FB);
  return diff_len;
}

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2(b_u0, b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/*
 * Arguments    : const double rxsignal[3600000]
 *                double fs
 *                double T
 *                const double Mic_Loc_H[15]
 *                const double Mic_Loc_L[15]
 *                emxArray_real_T *LocEst1
 * Return Type  : void
 */
void SoundLocation(const double rxsignal[3600000], double fs, double T, const
                   double Mic_Loc_H[15], const double Mic_Loc_L[15],
                   emxArray_real_T *LocEst1)
{
  double DataNum;
  int i0;
  int i1;
  int loop_ub;
  double angH;
  double angL;
  emxArray_creal_T *y;
  emxArray_creal_T *r0;
  emxArray_real_T *b_rxsignal;
  emxArray_real_T *c_rxsignal;
  emxArray_real_T *d_rxsignal;
  int ii;
  double diff_len_H_tmp;
  double b_diff_len_H_tmp;
  int i2;
  int b_loop_ub;
  int k;
  emxArray_creal_T b_y;
  int c_y[1];
  double diff_len_H[4];
  double dv0[3];
  double diff_len_H_d[4];
  double diff_len_L_d[4];
  double L;
  double diffH_mean;
  bool exitg1;
  double ex;
  DataNum = floor(T * fs);
  i0 = LocEst1->size[0] * LocEst1->size[1];
  i1 = (int)floor(360000.0 / fs / T);
  LocEst1->size[0] = i1;
  LocEst1->size[1] = 5;
  emxEnsureCapacity_real_T(LocEst1, i0);
  loop_ub = i1 * 5;
  for (i0 = 0; i0 < loop_ub; i0++) {
    LocEst1->data[i0] = 0.0;
  }

  angH = 0.0;
  angL = 0.0;
  emxInit_creal_T(&y, 2);
  emxInit_creal_T(&r0, 1);
  emxInit_real_T(&b_rxsignal, 1);
  emxInit_real_T(&c_rxsignal, 2);
  emxInit_real_T(&d_rxsignal, 2);
  for (ii = 0; ii < i1; ii++) {
    diff_len_H_tmp = ((1.0 + (double)ii) - 1.0) * DataNum + 1.0;
    b_diff_len_H_tmp = (1.0 + (double)ii) * DataNum;
    if (diff_len_H_tmp > b_diff_len_H_tmp) {
      i0 = 0;
      i2 = -1;
    } else {
      i0 = (int)diff_len_H_tmp - 1;
      i2 = (int)b_diff_len_H_tmp - 1;
    }

    /* 判断是否是噪声 */
    loop_ub = i2 - i0;
    b_loop_ub = loop_ub + 1;
    k = b_rxsignal->size[0];
    b_rxsignal->size[0] = b_loop_ub;
    emxEnsureCapacity_real_T(b_rxsignal, k);
    for (k = 0; k < b_loop_ub; k++) {
      b_rxsignal->data[k] = rxsignal[10 * (i0 + k)];
    }

    fft(b_rxsignal, (i2 - i0) + 1, r0);
    k = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = b_loop_ub;
    emxEnsureCapacity_creal_T(y, k);
    for (k = 0; k < b_loop_ub; k++) {
      y->data[k] = r0->data[k];
    }

    b_loop_ub = y->size[1];
    b_y = *y;
    c_y[0] = b_loop_ub;
    b_y.size = &c_y[0];
    b_y.numDimensions = 1;
    double ju = vvarstd(&b_y, (i2 - i0) + 1);
    if (ju < 1.0) {
      if (1U + ii != 1U) {
        diff_len_H[0] = LocEst1->data[ii - 1];
        diff_len_H[1] = LocEst1->data[(ii + LocEst1->size[0]) - 1];
        diff_len_H[2] = LocEst1->data[(ii + (LocEst1->size[0] << 1)) - 1];
        diff_len_H[3] = LocEst1->data[(ii + LocEst1->size[0] * 3) - 1];
        LocEst1->data[ii] = diff_len_H[0];
        LocEst1->data[ii + LocEst1->size[0]] = diff_len_H[1];
        LocEst1->data[ii + (LocEst1->size[0] << 1)] = diff_len_H[2];
        LocEst1->data[ii + LocEst1->size[0] * 3] = diff_len_H[3];
        LocEst1->data[ii + (LocEst1->size[0] << 2)] = b_diff_len_H_tmp / fs;
      }
    } else {
      /* 先做垂直方向 GCC 广义互相关函数 */
      i2 = c_rxsignal->size[0] * c_rxsignal->size[1];
      c_rxsignal->size[0] = 1;
      c_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(c_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        c_rxsignal->data[i2] = rxsignal[10 * (i0 + i2)];
      }

      i2 = d_rxsignal->size[0] * d_rxsignal->size[1];
      d_rxsignal->size[0] = 1;
      d_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(d_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        d_rxsignal->data[i2] = rxsignal[10 * (i0 + i2) + 1];
      }

      diff_len_H[0] = GccInterp(c_rxsignal, d_rxsignal, 340.0 / fs);
      i2 = c_rxsignal->size[0] * c_rxsignal->size[1];
      c_rxsignal->size[0] = 1;
      c_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(c_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        c_rxsignal->data[i2] = rxsignal[10 * (i0 + i2)];
      }

      i2 = d_rxsignal->size[0] * d_rxsignal->size[1];
      d_rxsignal->size[0] = 1;
      d_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(d_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        d_rxsignal->data[i2] = rxsignal[10 * (i0 + i2) + 2];
      }

      diff_len_H[1] = GccInterp(c_rxsignal, d_rxsignal, 340.0 / fs);
      i2 = c_rxsignal->size[0] * c_rxsignal->size[1];
      c_rxsignal->size[0] = 1;
      c_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(c_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        c_rxsignal->data[i2] = rxsignal[10 * (i0 + i2)];
      }

      i2 = d_rxsignal->size[0] * d_rxsignal->size[1];
      d_rxsignal->size[0] = 1;
      d_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(d_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        d_rxsignal->data[i2] = rxsignal[10 * (i0 + i2) + 3];
      }

      diff_len_H[2] = GccInterp(c_rxsignal, d_rxsignal, 340.0 / fs);
      i2 = c_rxsignal->size[0] * c_rxsignal->size[1];
      c_rxsignal->size[0] = 1;
      c_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(c_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        c_rxsignal->data[i2] = rxsignal[10 * (i0 + i2)];
      }

      i2 = d_rxsignal->size[0] * d_rxsignal->size[1];
      d_rxsignal->size[0] = 1;
      d_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(d_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        d_rxsignal->data[i2] = rxsignal[10 * (i0 + i2) + 4];
      }

      diff_len_H[3] = GccInterp(c_rxsignal, d_rxsignal, 340.0 / fs);
      b_diff(diff_len_H, dv0);
      diff_len_H_d[0] = diff_len_H[0];
      diff_len_H_d[1] = dv0[0];
      diff_len_H_d[2] = dv0[1];
      diff_len_H_d[3] = dv0[2];

      /* 在做垂直方向 GCC 广义互相关函数 */
      i2 = c_rxsignal->size[0] * c_rxsignal->size[1];
      c_rxsignal->size[0] = 1;
      c_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(c_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        c_rxsignal->data[i2] = rxsignal[5 + 10 * (i0 + i2)];
      }

      i2 = d_rxsignal->size[0] * d_rxsignal->size[1];
      d_rxsignal->size[0] = 1;
      d_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(d_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        d_rxsignal->data[i2] = rxsignal[10 * (i0 + i2) + 6];
      }

      diff_len_H[0] = GccInterp(c_rxsignal, d_rxsignal, 340.0 / fs);
      i2 = c_rxsignal->size[0] * c_rxsignal->size[1];
      c_rxsignal->size[0] = 1;
      c_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(c_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        c_rxsignal->data[i2] = rxsignal[5 + 10 * (i0 + i2)];
      }

      i2 = d_rxsignal->size[0] * d_rxsignal->size[1];
      d_rxsignal->size[0] = 1;
      d_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(d_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        d_rxsignal->data[i2] = rxsignal[10 * (i0 + i2) + 7];
      }

      diff_len_H[1] = GccInterp(c_rxsignal, d_rxsignal, 340.0 / fs);
      i2 = c_rxsignal->size[0] * c_rxsignal->size[1];
      c_rxsignal->size[0] = 1;
      c_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(c_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        c_rxsignal->data[i2] = rxsignal[5 + 10 * (i0 + i2)];
      }

      i2 = d_rxsignal->size[0] * d_rxsignal->size[1];
      d_rxsignal->size[0] = 1;
      d_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(d_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        d_rxsignal->data[i2] = rxsignal[10 * (i0 + i2) + 8];
      }

      diff_len_H[2] = GccInterp(c_rxsignal, d_rxsignal, 340.0 / fs);
      i2 = c_rxsignal->size[0] * c_rxsignal->size[1];
      c_rxsignal->size[0] = 1;
      c_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(c_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        c_rxsignal->data[i2] = rxsignal[5 + 10 * (i0 + i2)];
      }

      i2 = d_rxsignal->size[0] * d_rxsignal->size[1];
      d_rxsignal->size[0] = 1;
      d_rxsignal->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(d_rxsignal, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        d_rxsignal->data[i2] = rxsignal[10 * (i0 + i2) + 9];
      }

      diff_len_H[3] = GccInterp(c_rxsignal, d_rxsignal, 340.0 / fs);
      b_diff(diff_len_H, dv0);
      diff_len_L_d[0] = diff_len_H[0];
      diff_len_L_d[1] = dv0[0];
      diff_len_L_d[2] = dv0[1];
      diff_len_L_d[3] = dv0[2];

      /* 方式一 基于几何方式 求解最优角度 */
      L = fabs(diff_len_H_d[0]);
      diff_len_H[0] = L;
      b_diff_len_H_tmp = fabs(diff_len_H_d[1]);
      diff_len_H[1] = b_diff_len_H_tmp;
      diffH_mean = fabs(diff_len_H_d[2]);
      diff_len_H[2] = diffH_mean;
      diff_len_H_tmp = fabs(diff_len_H_d[3]);
      diff_len_H[3] = diff_len_H_tmp;
      if (!rtIsNaN(L)) {
        b_loop_ub = 1;
      } else {
        b_loop_ub = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k < 5)) {
          if (!rtIsNaN(diff_len_H[k - 1])) {
            b_loop_ub = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (b_loop_ub == 0) {
        b_loop_ub = 1;
      } else {
        ex = diff_len_H[b_loop_ub - 1];
        i0 = b_loop_ub + 1;
        for (k = i0; k < 5; k++) {
          if (ex > diff_len_H[k - 1]) {
            ex = diff_len_H[k - 1];
            b_loop_ub = k;
          }
        }
      }

      diff_len_H[0] = L;
      diff_len_H[1] = b_diff_len_H_tmp;
      diff_len_H[2] = diffH_mean;
      diff_len_H[3] = diff_len_H_tmp;
      if (!rtIsNaN(L)) {
        loop_ub = 1;
      } else {
        loop_ub = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k < 5)) {
          if (!rtIsNaN(diff_len_H[k - 1])) {
            loop_ub = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (loop_ub == 0) {
        loop_ub = 1;
      } else {
        ex = diff_len_H[loop_ub - 1];
        i0 = loop_ub + 1;
        for (k = i0; k < 5; k++) {
          diff_len_H_tmp = diff_len_H[k - 1];
          if (ex < diff_len_H_tmp) {
            ex = diff_len_H_tmp;
            loop_ub = k;
          }
        }
      }

      b_diff_len_H_tmp = diff_len_H_d[b_loop_ub - 1];
      L = diff_len_H_d[loop_ub - 1];
      diffH_mean = (((((diff_len_H_d[0] + diff_len_H_d[1]) + diff_len_H_d[2]) +
                      diff_len_H_d[3]) - b_diff_len_H_tmp) - L) / 2.0;
      diff_len_H_tmp = fabs(diffH_mean);
      if ((fabs(diffH_mean - b_diff_len_H_tmp) / diff_len_H_tmp > 0.5) || (fabs
           (diffH_mean - L) / diff_len_H_tmp > 0.5)) {
        /* 排除异常解 */
      } else {
        diff(*(double (*)[5])&Mic_Loc_H[10], diff_len_H);
        diff_len_H_d[0] = -diff_len_H_d[0] / diff_len_H[0];
        diff_len_H_d[1] = -diff_len_H_d[1] / diff_len_H[1];
        diff_len_H_d[2] = -diff_len_H_d[2] / diff_len_H[2];
        diff_len_H_d[3] = -diff_len_H_d[3] / diff_len_H[3];
        angH = acos((((diff_len_H_d[0] + diff_len_H_d[1]) + diff_len_H_d[2]) +
                     diff_len_H_d[3]) / 4.0);
      }

      L = fabs(diff_len_L_d[0]);
      diff_len_H[0] = L;
      b_diff_len_H_tmp = fabs(dv0[0]);
      diff_len_H[1] = b_diff_len_H_tmp;
      diffH_mean = fabs(dv0[1]);
      diff_len_H[2] = diffH_mean;
      diff_len_H_tmp = fabs(dv0[2]);
      diff_len_H[3] = diff_len_H_tmp;
      if (!rtIsNaN(L)) {
        b_loop_ub = 1;
      } else {
        b_loop_ub = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k < 5)) {
          if (!rtIsNaN(diff_len_H[k - 1])) {
            b_loop_ub = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (b_loop_ub == 0) {
        b_loop_ub = 1;
      } else {
        ex = diff_len_H[b_loop_ub - 1];
        i0 = b_loop_ub + 1;
        for (k = i0; k < 5; k++) {
          if (ex > diff_len_H[k - 1]) {
            ex = diff_len_H[k - 1];
            b_loop_ub = k;
          }
        }
      }

      diff_len_H[0] = L;
      diff_len_H[1] = b_diff_len_H_tmp;
      diff_len_H[2] = diffH_mean;
      diff_len_H[3] = diff_len_H_tmp;
      if (!rtIsNaN(L)) {
        loop_ub = 1;
      } else {
        loop_ub = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k < 5)) {
          if (!rtIsNaN(diff_len_H[k - 1])) {
            loop_ub = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (loop_ub == 0) {
        loop_ub = 1;
      } else {
        ex = diff_len_H[loop_ub - 1];
        i0 = loop_ub + 1;
        for (k = i0; k < 5; k++) {
          diff_len_H_tmp = diff_len_H[k - 1];
          if (ex < diff_len_H_tmp) {
            ex = diff_len_H_tmp;
            loop_ub = k;
          }
        }
      }

      L = diff_len_L_d[b_loop_ub - 1];
      b_diff_len_H_tmp = diff_len_L_d[loop_ub - 1];
      diffH_mean = (((((diff_len_L_d[0] + dv0[0]) + dv0[1]) + dv0[2]) - L) -
                    b_diff_len_H_tmp) / 2.0;
      diff_len_H_tmp = fabs(diffH_mean);
      if ((fabs(diffH_mean - L) / diff_len_H_tmp > 0.5) || (fabs(diffH_mean -
            b_diff_len_H_tmp) / diff_len_H_tmp > 0.5)) {
        /* 排除异常解 */
      } else {
        diff(*(double (*)[5])&Mic_Loc_L[0], diff_len_H);
        diff_len_L_d[0] = -diff_len_L_d[0] / diff_len_H[0];
        angL = acos((((diff_len_L_d[0] + -dv0[0] / diff_len_H[1]) + -dv0[1] /
                      diff_len_H[2]) + -dv0[2] / diff_len_H[3]) / 4.0);
      }

      b_diff_len_H_tmp = tan(angH) * tan(1.5707963267948966 - angL);
      L = 1.0 / cos(angH);
      b_diff_len_H_tmp = acos(1.0 / sqrt(b_diff_len_H_tmp * b_diff_len_H_tmp + L
        * L));
      L = Mic_Loc_H[10] / cos(b_diff_len_H_tmp);
      diffH_mean = sin(b_diff_len_H_tmp);
      LocEst1->data[ii] = b_diff_len_H_tmp;
      LocEst1->data[ii + LocEst1->size[0]] = angL;
      LocEst1->data[ii + LocEst1->size[0] * 2] = -L * diffH_mean * cos(angL) +
        Mic_Loc_H[0];
      LocEst1->data[ii + LocEst1->size[0] * 3] = L * diffH_mean * sin(angL) +
        Mic_Loc_H[5];
      LocEst1->data[ii + (LocEst1->size[0] << 2)] = (1.0 + (double)ii) * DataNum
        / fs;
    }
  }

  emxFree_real_T(&d_rxsignal);
  emxFree_real_T(&c_rxsignal);
  emxFree_real_T(&b_rxsignal);
  emxFree_creal_T(&r0);
  emxFree_creal_T(&y);
}

/*
 * File trailer for SoundLocation.c
 *
 * [EOF]
 */
