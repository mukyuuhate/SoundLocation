/*
 * File: SoundLocation.h
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

#ifndef SOUNDLOCATION_H
#define SOUNDLOCATION_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "SoundLocation_types.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "SoundLocation_emxutil.h"
#include "diff.h"
#include "interp1.h"
#include "fftshift.h"
#include "ifft.h"
#include "rdivide_helper.h"
#include "abs.h"
#include "fft.h"
#include "vvarstd.h"
#include "fft1.h"
#include "SoundLocation_rtwutil.h"

/* Function Declarations */
extern void SoundLocation(const double rxsignal[3600000], double fs, double T,
  const double Mic_Loc_H[15], const double Mic_Loc_L[15], emxArray_real_T
  *LocEst1);

#endif

/*
 * File trailer for SoundLocation.h
 *
 * [EOF]
 */
