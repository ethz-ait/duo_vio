//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Att_upd.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 19-Aug-2015 10:03:40
//

// Include Files
#include "rt_nonfinite.h"
#include "SLAM.h"
#include "Att_upd.h"
#include "quatPlusThetaJ.h"
#include <stdio.h>

// Function Definitions

//
// ATT_UPD Update step of the attitude estimator
//    INPUT ARGUMENTS:
//    - SLAM_data
//    - z:  The current accelerometer measurement (3 x 1)
//    - dt: The time step
// Arguments    : struct_T *b_SLAM_data
//                const double z[3]
//                double dt
// Return Type  : void
//
void Att_upd(struct_T *b_SLAM_data, const double z[3], double dt)
{
  double c_SLAM_data[9];
  double b_P[9];
  int rtemp;
  int k;
  double z_pred[3];
  double H[9];
  double maxval;
  int r1;
  double d_SLAM_data;
  double S[9];
  double a21;
  static const signed char a[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

  double y[9];
  int r2;
  int r3;
  double K[9];
  double b_K[3];
  double b_z[3];
  double q[4];
  double e_SLAM_data;
  double f_SLAM_data;
  double g_SLAM_data;
  double h_SLAM_data;
  double i_SLAM_data;
  double j_SLAM_data;
  double k_SLAM_data;
  double l_SLAM_data;
  double m_SLAM_data;
  double n_SLAM_data;
  double o_SLAM_data;
  double p_SLAM_data;
  double q_SLAM_data;
  double r_SLAM_data[16];
  double b_q[4];

  //  predicted measurement
  //  if ~all(size(q) == [4, 1])
  //      error('q does not have the size of a quaternion')
  //  end
  //  if abs(norm(q) - 1) > 1e-3
  //      error('The provided quaternion is not a valid rotation quaternion because it does not have norm 1') 
  //  end
  c_SLAM_data[0] = ((b_SLAM_data->xt->data[3] * b_SLAM_data->xt->data[3] -
                     b_SLAM_data->xt->data[4] * b_SLAM_data->xt->data[4]) -
                    b_SLAM_data->xt->data[5] * b_SLAM_data->xt->data[5]) +
    b_SLAM_data->xt->data[6] * b_SLAM_data->xt->data[6];
  c_SLAM_data[3] = 2.0 * (b_SLAM_data->xt->data[3] * b_SLAM_data->xt->data[4] +
    b_SLAM_data->xt->data[5] * b_SLAM_data->xt->data[6]);
  c_SLAM_data[6] = 2.0 * (b_SLAM_data->xt->data[3] * b_SLAM_data->xt->data[5] -
    b_SLAM_data->xt->data[4] * b_SLAM_data->xt->data[6]);
  c_SLAM_data[1] = 2.0 * (b_SLAM_data->xt->data[3] * b_SLAM_data->xt->data[4] -
    b_SLAM_data->xt->data[5] * b_SLAM_data->xt->data[6]);
  c_SLAM_data[4] = ((-(b_SLAM_data->xt->data[3] * b_SLAM_data->xt->data[3]) +
                     b_SLAM_data->xt->data[4] * b_SLAM_data->xt->data[4]) -
                    b_SLAM_data->xt->data[5] * b_SLAM_data->xt->data[5]) +
    b_SLAM_data->xt->data[6] * b_SLAM_data->xt->data[6];
  c_SLAM_data[7] = 2.0 * (b_SLAM_data->xt->data[4] * b_SLAM_data->xt->data[5] +
    b_SLAM_data->xt->data[3] * b_SLAM_data->xt->data[6]);
  c_SLAM_data[2] = 2.0 * (b_SLAM_data->xt->data[3] * b_SLAM_data->xt->data[5] +
    b_SLAM_data->xt->data[4] * b_SLAM_data->xt->data[6]);
  c_SLAM_data[5] = 2.0 * (b_SLAM_data->xt->data[4] * b_SLAM_data->xt->data[5] -
    b_SLAM_data->xt->data[3] * b_SLAM_data->xt->data[6]);
  c_SLAM_data[8] = ((-(b_SLAM_data->xt->data[3] * b_SLAM_data->xt->data[3]) -
                     b_SLAM_data->xt->data[4] * b_SLAM_data->xt->data[4]) +
                    b_SLAM_data->xt->data[5] * b_SLAM_data->xt->data[5]) +
    b_SLAM_data->xt->data[6] * b_SLAM_data->xt->data[6];
  for (rtemp = 0; rtemp < 3; rtemp++) {
    for (k = 0; k < 3; k++) {
      b_P[k + 3 * rtemp] = b_SLAM_data->P->data[(k + b_SLAM_data->P->size[0] *
        (3 + rtemp)) + 3];
    }

    z_pred[rtemp] = c_SLAM_data[6 + rtemp] * 9.81;
  }

  H[0] = 0.0;
  H[3] = -z_pred[2];
  H[6] = z_pred[1];
  H[1] = z_pred[2];
  H[4] = 0.0;
  H[7] = -z_pred[0];
  H[2] = -z_pred[1];
  H[5] = z_pred[0];
  H[8] = 0.0;
  maxval = dt * dt;
  for (rtemp = 0; rtemp < 3; rtemp++) {
    for (k = 0; k < 3; k++) {
      c_SLAM_data[rtemp + 3 * k] = 0.0;
      for (r1 = 0; r1 < 3; r1++) {
        c_SLAM_data[rtemp + 3 * k] += H[rtemp + 3 * r1] * b_P[r1 + 3 * k];
      }
    }
  }

  d_SLAM_data = b_SLAM_data->processNoise[0];
  for (rtemp = 0; rtemp < 3; rtemp++) {
    for (k = 0; k < 3; k++) {
      a21 = 0.0;
      for (r1 = 0; r1 < 3; r1++) {
        a21 += c_SLAM_data[rtemp + 3 * r1] * H[k + 3 * r1];
      }

      S[rtemp + 3 * k] = a21 + (double)a[rtemp + 3 * k] * d_SLAM_data * maxval;
    }
  }

  for (rtemp = 0; rtemp < 3; rtemp++) {
    for (k = 0; k < 3; k++) {
      y[rtemp + 3 * k] = 0.0;
      for (r1 = 0; r1 < 3; r1++) {
        y[rtemp + 3 * k] += b_P[rtemp + 3 * r1] * H[k + 3 * r1];
      }
    }
  }

  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabs(S[0]);
  a21 = fabs(S[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (fabs(S[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  S[r2] /= S[r1];
  S[r3] /= S[r1];
  S[3 + r2] -= S[r2] * S[3 + r1];
  S[3 + r3] -= S[r3] * S[3 + r1];
  S[6 + r2] -= S[r2] * S[6 + r1];
  S[6 + r3] -= S[r3] * S[6 + r1];
  if (fabs(S[3 + r3]) > fabs(S[3 + r2])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  S[3 + r3] /= S[3 + r2];
  S[6 + r3] -= S[3 + r3] * S[6 + r2];
  for (k = 0; k < 3; k++) {
    K[k + 3 * r1] = y[k] / S[r1];
    K[k + 3 * r2] = y[3 + k] - K[k + 3 * r1] * S[3 + r1];
    K[k + 3 * r3] = y[6 + k] - K[k + 3 * r1] * S[6 + r1];
    K[k + 3 * r2] /= S[3 + r2];
    K[k + 3 * r3] -= K[k + 3 * r2] * S[6 + r2];
    K[k + 3 * r3] /= S[6 + r3];
    K[k + 3 * r2] -= K[k + 3 * r3] * S[3 + r3];
    K[k + 3 * r1] -= K[k + 3 * r3] * S[r3];
    K[k + 3 * r1] -= K[k + 3 * r2] * S[r2];
    b_z[k] = z[k] - z_pred[k];
  }

  for (rtemp = 0; rtemp < 3; rtemp++) {
    b_K[rtemp] = 0.0;
    for (k = 0; k < 3; k++) {
      b_K[rtemp] += K[rtemp + 3 * k] * b_z[k];
    }
  }

  quatPlusThetaJ(b_K, q);
  d_SLAM_data = b_SLAM_data->xt->data[6];
  maxval = b_SLAM_data->xt->data[5];
  a21 = b_SLAM_data->xt->data[4];
  e_SLAM_data = b_SLAM_data->xt->data[3];
  f_SLAM_data = b_SLAM_data->xt->data[5];
  g_SLAM_data = b_SLAM_data->xt->data[6];
  h_SLAM_data = b_SLAM_data->xt->data[3];
  i_SLAM_data = b_SLAM_data->xt->data[4];
  j_SLAM_data = b_SLAM_data->xt->data[4];
  k_SLAM_data = b_SLAM_data->xt->data[3];
  l_SLAM_data = b_SLAM_data->xt->data[6];
  m_SLAM_data = b_SLAM_data->xt->data[5];
  n_SLAM_data = b_SLAM_data->xt->data[3];
  o_SLAM_data = b_SLAM_data->xt->data[4];
  p_SLAM_data = b_SLAM_data->xt->data[5];
  q_SLAM_data = b_SLAM_data->xt->data[6];
  r_SLAM_data[0] = d_SLAM_data;
  r_SLAM_data[4] = -maxval;
  r_SLAM_data[8] = a21;
  r_SLAM_data[12] = e_SLAM_data;
  r_SLAM_data[1] = f_SLAM_data;
  r_SLAM_data[5] = g_SLAM_data;
  r_SLAM_data[9] = -h_SLAM_data;
  r_SLAM_data[13] = i_SLAM_data;
  r_SLAM_data[2] = -j_SLAM_data;
  r_SLAM_data[6] = k_SLAM_data;
  r_SLAM_data[10] = l_SLAM_data;
  r_SLAM_data[14] = m_SLAM_data;
  r_SLAM_data[3] = -n_SLAM_data;
  r_SLAM_data[7] = -o_SLAM_data;
  r_SLAM_data[11] = -p_SLAM_data;
  r_SLAM_data[15] = q_SLAM_data;
  b_q[0] = q[0];
  b_q[1] = q[1];
  b_q[2] = q[2];
  b_q[3] = q[3];
  for (rtemp = 0; rtemp < 4; rtemp++) {
    q[rtemp] = 0.0;
    for (k = 0; k < 4; k++) {
      q[rtemp] += r_SLAM_data[rtemp + (k << 2)] * b_q[k];
    }
  }

  for (rtemp = 0; rtemp < 4; rtemp++) {
    b_SLAM_data->xt->data[3 + rtemp] = q[rtemp];
  }

  memset(&S[0], 0, 9U * sizeof(double));
  for (k = 0; k < 3; k++) {
    S[k + 3 * k] = 1.0;
  }

  for (rtemp = 0; rtemp < 3; rtemp++) {
    for (k = 0; k < 3; k++) {
      a21 = 0.0;
      for (r1 = 0; r1 < 3; r1++) {
        a21 += K[rtemp + 3 * r1] * H[r1 + 3 * k];
      }

      c_SLAM_data[rtemp + 3 * k] = S[rtemp + 3 * k] - a21;
    }
  }

  for (rtemp = 0; rtemp < 3; rtemp++) {
    for (k = 0; k < 3; k++) {
      b_SLAM_data->P->data[(rtemp + b_SLAM_data->P->size[0] * (3 + k)) + 3] =
        0.0;
      for (r1 = 0; r1 < 3; r1++) {
        b_SLAM_data->P->data[(rtemp + b_SLAM_data->P->size[0] * (3 + k)) + 3] +=
          c_SLAM_data[rtemp + 3 * r1] * b_P[r1 + 3 * k];
      }
    }
  }
}

//
// File trailer for Att_upd.cpp
//
// [EOF]
//
