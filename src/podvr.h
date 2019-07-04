// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PODVR_H
#define PODVR_H
#include"mathtools.h"
#include"sincdvr.h"

namespace yDVR{
  /** @brief Peform 1D PODVR calculation in given range and number of points based on sinc-DVR
   * @param m effective mass of the system
   * @param N number of sinc-DVR points used
   * @param NPO number of PODVR points used
   * @param a start point of the integral range
   * @param b end point of the integral range
   * @param x PODVR grids
   * @param E energy levels
   * @param wf wave function on PODVR 
   * @param H_PODVR Hamiltonian on PODVR
   * @param potential the potential energy
   *
   * @see 
   * @ref sinc_dvr_1d()
   *
  */
  extern int sinc_podvr_1d(double m, int N, int NPO, double a, double b, VectorXd& x, VectorXd& E, MatrixXd& wf, MatrixXd& H_PODVR, const DoubleFunction1d& potential);
}

#endif 
