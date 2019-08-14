// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SINCDVR_H
#define SINCDVR_H
#include"mathtools.h"
#include"iotools.h"

/* @file
 */

namespace yDVR{
  /** @brief Peform 1D sinc-DVR calculation in given range and number of points
   * @param[in] m effective mass of the system
   * @param[in] N number of DVR points used
   * @param[in] a start point of the integral range
   * @param[in] b end point of the integral range
   * @param[in] potential the potential energy
   * @param[out] x sinc-DVR grids
   * @param[out] E energy levels
   * @param[out] wf_sincDVR wave functions
   * @param[out] H_sincDVR Hamiltonian in sincDVR
  */
  extern int sincDVR1d(double m, int N, double a, double b, const DoubleFunction1d& potential,
      Eigen::VectorXd &x, Eigen::VectorXd &E, Eigen::MatrixXd &wf_sincDVR, Eigen::MatrixXd &H_sincDVR);
}
// extern double potential(double);

#endif // SINCDVR_H
