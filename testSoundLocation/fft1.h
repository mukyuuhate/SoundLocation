/*
 * File: fft1.h
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

#ifndef FFT1_H
#define FFT1_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "SoundLocation_types.h"

/* Function Declarations */
extern void c_fft(const emxArray_creal_T *x, int n, emxArray_creal_T *y);
extern void fft(const emxArray_real_T *x, int n, emxArray_creal_T *y);

#endif

/*
 * File trailer for fft1.h
 *
 * [EOF]
 */
