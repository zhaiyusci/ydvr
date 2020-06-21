// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_SINCDVR_H_
#define YDVR_SINCDVR_H_
#include"dvr.h"

/* @file
 */

namespace yDVR{
  /** @brief Sinc Discrete Variable Representation
   *
   * Ref:
   * D. T. Colbert and W. H. Miller, J. Chem. Phys. 96, 1982 (1992) 
   * doi:10.1063/1.462100
   */
  class SincDVR : public DVR{
    protected:
      const Scalar a_;
      const Scalar b_;
      const int N_plus_1_;
    public:
      /** @brief Constructor.
       *
       * @param oscillator Pointer to the oscillator.
       * @param a starting point;
       * @param b end point of the coordinate.
       * @param N Number of grids.
       */
      SincDVR(const Oscillator& oscillator, Scalar a, Scalar b, int N);
      /** @brief Kinetic energy matrix.
       */
      virtual const Matrix& kineticMatrix() override;
      /** @brief Sinc DVR grids.
       */
      virtual const Vector& grids() override;
  };
}

#endif // YDVR_SINCDVR_H_
