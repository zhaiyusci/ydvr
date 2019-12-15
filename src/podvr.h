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
#include"iotools.h"

namespace yDVR{
  /** @brief Peform 1D PODVR calculation in given range and number of points based on sinc-DVR
   * @param[in] m effective mass of the system
   * @param[in] N number of sinc-DVR points used
   * @param[in] NPO number of PODVR points used
   * @param[in] a start point of the integral range
   * @param[in] b end point of the integral range
   * @param[in] potential the potential energy
   * @param[out] x PODVR grids
   * @param[out] E energy levels
   * @param[out] wf wave function on PODVR 
   * @param[out] H_PODVR Hamiltonian on PODVR
   *
   * @see 
   * @ref sinc_dvr_1d()
   *
  */
  extern int sincPODVR1d(yScalar m, int N, int NPO, yScalar a, yScalar b, const DoubleFunction1d& potential,
      yVector& x, yVector& E, yMatrix& wf, yMatrix& H_PODVR);
}

#endif 
