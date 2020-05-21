// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_DISCRETE_VARIABLE_REPRESENTATION_H_
#define YDVR_DISCRETE_VARIABLE_REPRESENTATION_H_

#include<iostream>
#include"config.h"
#include"representation.h"

/* @file
 */


namespace yDVR{

  /** @brief Pure virtual class define the Discrete Variable Representation.
  */
  class DiscreteVariableRepresentation: public Representation{
    protected:
      Vector grids_;
    public:
      /** @brief Returns the potential matrix.
       *
       * Potential matrix on DVR is a diagonal matrix, 
       * whose diagonal elements are potential energy of DVR grids
       */
      virtual const Matrix& PotentialMatrix();
      /** @brief Returns the DVR grids.
       */
      virtual const Vector& Grids() = 0; 
      /** @brief Returns the coordinate matrix.
       *
       * Just return the grids as diagonal matrix.
       * Implement of a `DiscreteVariableRepresentation` should implement 
       * `Grids()` instead of implement this function.
       */
      virtual const Matrix CoordinateMatrix();
      /** @brief Distructor.
       */
      virtual ~DiscreteVariableRepresentation(){}
      /** @brief Constructor.
       *
       * @param oscillator Pointer to oscillator of which the representation is.
       */
      DiscreteVariableRepresentation(const Oscillator& oscillator):
        Representation(oscillator),
        grids_(0) {};
  };
}
#endif // YDVR_DISCRETE_VARIABLE_REPRESENTATION_H_
