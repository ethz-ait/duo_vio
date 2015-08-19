//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SLAM.h
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 19-Aug-2015 10:03:40
//
#ifndef __SLAM_H__
#define __SLAM_H__

// Include Files
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "SLAM_types.h"

// Function Declarations
extern void SLAM(double updateVect[16], const double z_all_l[32], const double
                 z_all_r[32], double dt, const double b_processNoise[4], const
                 double IMU_measurements[23], const double b_imNoise[2], double
                 b_numPointsPerAnchor, double b_numAnchors, const
                 stereoParameters *cameraParams, boolean_T resetFlag,
                 emxArray_real_T *h_u_apo_out, emxArray_real_T *xt_out,
                 emxArray_real_T *P_apo_out, emxArray_real_T *map_out);
extern void SLAM_free();
extern void SLAM_init();
extern void init_counter_not_empty_init();

#endif

//
// File trailer for SLAM.h
//
// [EOF]
//
