/*
 * File: pwchcore.h
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

#ifndef PWCHCORE_H
#define PWCHCORE_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "SoundLocation_types.h"

/* Function Declarations */
extern void b_pwchcore(const emxArray_real_T *x, const emxArray_creal_T *y, int
  yoffset, const emxArray_creal_T *s, const emxArray_real_T *dx, const
  emxArray_creal_T *divdif, emxArray_real_T *pp_breaks, emxArray_creal_T
  *pp_coefs);
extern void pwchcore(const emxArray_real_T *x, const emxArray_creal_T *y, const
                     creal_T s[2], emxArray_real_T *pp_breaks, creal_T pp_coefs
                     [4]);

#endif

/*
 * File trailer for pwchcore.h
 *
 * [EOF]
 */
