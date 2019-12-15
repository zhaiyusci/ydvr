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
  extern int sincDVR1d(yScalar m, int N, yScalar a, yScalar b, const DoubleFunction1d& potential,
      yVector &x, yVector &E, yMatrix &wf_sincDVR, yMatrix &H_sincDVR);
}
// extern yScalar potential(yScalar);

#endif // SINCDVR_H
