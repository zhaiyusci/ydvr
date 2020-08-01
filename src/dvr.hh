// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_DVR_H_
#define YDVR_DVR_H_

#include<iostream>
#include"config.hh"
#include"representation.hh"

/* @file
 */


namespace yDVR{

  /** @brief Pure virtual class define the Discrete Variable Representation.
  */
  class DVR: public Representation{
    protected:
      Vector grids_;
    public:
      /** @brief Returns the potential matrix.
       *
       * Potential matrix on DVR is a diagonal matrix, 
       * whose diagonal elements are potential energy of DVR grids
       */
      virtual const Matrix& potentialMatrix() override;
      /** @brief Returns the DVR grids.
       */
      virtual const Vector& grids() = 0; 
      /** @brief Returns the coordinate matrix.
       *
       * Just return the grids as diagonal matrix.
       * Implement of a `DiscreteVariableRepresentation` should implement 
       * `Grids()` instead of implement this function.
       */
      virtual const Matrix coordinateMatrix();
      /** @brief Distructor.
       */
      virtual ~DVR(){}
      /** @brief Constructor.
       *
       * @param oscillator Pointer to oscillator of which the representation is.
       */
      DVR(const Oscillator& oscillator):
        Representation(oscillator),
        grids_(0) {};

  };
}
#endif // YDVR_DVR_H_
