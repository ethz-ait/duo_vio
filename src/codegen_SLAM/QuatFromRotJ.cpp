//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: QuatFromRotJ.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 15-Jul-2015 17:00:42
//

// Include Files
#include "rt_nonfinite.h"
#include "SLAM.h"
#include "QuatFromRotJ.h"
#include "SLAM_rtwutil.h"
#include <stdio.h>

// Function Definitions

//
// THIS IS OK, It is according to the NASA memo found
//  https://claraty.jpl.nasa.gov/man/software/development/conventions/standards_docs/unadopted/JPL_Quaternions_Breckenridge.pdf
// QUATFROMROTJ Get equivalent quaternion of the rotation matrix R
//    Returns a quaternion in JPL notation
//  The implementation is copied from qGetQ(R), but we are careful about the
//  ordering of the output vector
// Arguments    : const double R[9]
//                double b_Q[4]
// Return Type  : void
//
void QuatFromRotJ(const double R[9], double b_Q[4])
{
  double b_T;
  double x;
  double pivot[4];
  int ixstart;
  double mtmp;
  int idx;
  boolean_T exitg2;
  signed char ii_data[4];
  boolean_T exitg1;
  boolean_T guard1 = false;
  int loop_ub;
  int i1;
  signed char i_data[4];
  signed char index_data[4];

  //  if( r ~= 3 || c ~= 3 )
  //      error( 'R must be a 3x3 matrix\n\r' );
  //  end
  b_T = (R[0] + R[4]) + R[8];
  x = sqrt((1.0 + 2.0 * R[0]) - b_T);
  pivot[0] = x / 2.0;
  pivot[1] = sqrt((1.0 + 2.0 * R[4]) - b_T) / 2.0;
  pivot[2] = sqrt((1.0 + 2.0 * R[8]) - b_T) / 2.0;
  pivot[3] = sqrt(1.0 + b_T) / 2.0;
  ixstart = 1;
  mtmp = x / 2.0;
  if (rtIsNaN(x / 2.0)) {
    idx = 2;
    exitg2 = false;
    while ((!exitg2) && (idx < 5)) {
      ixstart = idx;
      if (!rtIsNaN(pivot[idx - 1])) {
        mtmp = pivot[idx - 1];
        exitg2 = true;
      } else {
        idx++;
      }
    }
  }

  if (ixstart < 4) {
    while (ixstart + 1 < 5) {
      if (pivot[ixstart] > mtmp) {
        mtmp = pivot[ixstart];
      }

      ixstart++;
    }
  }

  idx = 0;
  ixstart = 1;
  exitg1 = false;
  while ((!exitg1) && (ixstart < 5)) {
    guard1 = false;
    if (pivot[ixstart - 1] == mtmp) {
      idx++;
      ii_data[idx - 1] = (signed char)ixstart;
      if (idx >= 4) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ixstart++;
    }
  }

  if (1 > idx) {
    loop_ub = 0;
  } else {
    loop_ub = idx;
  }

  for (i1 = 0; i1 < loop_ub; i1++) {
    i_data[i1] = ii_data[i1];
  }

  if (1 > idx) {
    ixstart = 0;
  } else {
    ixstart = idx;
  }

  for (i1 = 0; i1 < ixstart; i1++) {
    index_data[i1] = i_data[i1];
  }

  for (ixstart = 0; ixstart < loop_ub; ixstart++) {
    index_data[ixstart] = (signed char)rt_roundd_snf((double)index_data[ixstart]);
  }

  if (index_data[0] == 1) {
    x = sqrt((1.0 + 2.0 * R[0]) - b_T);
    mtmp = x / 2.0;
    b_Q[0] = x / 2.0;
    b_Q[1] = (R[3] + R[1]) / (4.0 * mtmp);
    b_Q[2] = (R[6] + R[2]) / (4.0 * mtmp);
    b_Q[3] = (R[7] - R[5]) / (4.0 * mtmp);
  } else if (index_data[0] == 2) {
    x = sqrt((1.0 + 2.0 * R[4]) - b_T);
    mtmp = x / 2.0;
    b_Q[1] = x / 2.0;
    b_Q[0] = (R[3] + R[1]) / (4.0 * mtmp);
    b_Q[2] = (R[7] + R[5]) / (4.0 * mtmp);
    b_Q[3] = (R[2] - R[6]) / (4.0 * mtmp);
  } else if (index_data[0] == 3) {
    x = sqrt((1.0 + 2.0 * R[8]) - b_T);
    mtmp = x / 2.0;
    b_Q[2] = x / 2.0;
    b_Q[0] = (R[6] + R[2]) / (4.0 * mtmp);
    b_Q[1] = (R[7] + R[5]) / (4.0 * mtmp);
    b_Q[3] = (R[3] - R[1]) / (4.0 * mtmp);
  } else {
    x = sqrt(1.0 + b_T);
    mtmp = x / 2.0;
    b_Q[3] = x / 2.0;
    b_Q[0] = (R[7] - R[5]) / (4.0 * mtmp);
    b_Q[1] = (R[2] - R[6]) / (4.0 * mtmp);
    b_Q[2] = (R[3] - R[1]) / (4.0 * mtmp);
  }
}

//
// File trailer for QuatFromRotJ.cpp
//
// [EOF]
//