/*
 * File: spline.h
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

#ifndef SPLINE_H
#define SPLINE_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "SoundLocation_types.h"

/* Function Declarations */
extern void spline(const emxArray_real_T *x, const emxArray_creal_T *y,
                   emxArray_real_T *output_breaks, emxArray_creal_T
                   *output_coefs);

#endif

/*
 * File trailer for spline.h
 *
 * [EOF]
 */
