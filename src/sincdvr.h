// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DVR_H
#define DVR_H
#include"mathtools.h"

/* @file
 */

namespace yDVR{
  /** @brief Peform 1D sinc-DVR calculation in given range and number of points
   * @param m effective mass of the system
   * @param N number of DVR points used
   * @param a start point of the integral range
   * @param b end point of the integral range
   * @param x sinc-DVR grids
   * @param E energy levels
   * @param wf_sincDVR wave functions
   * @param potential the potential energy
  */
  extern int sinc_dvr_1d(double m, int N, double a, double b, Eigen::VectorXd &x, Eigen::VectorXd &E, Eigen::MatrixXd &wf_sincDVR, const DoubleFunction1d& potential);
}
// extern double potential(double);

#endif 
