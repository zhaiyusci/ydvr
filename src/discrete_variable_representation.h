// This file is part of ydvr.
//
// Copyright (C) 2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_DISCRETE_VARIABLE_REPRESENTATION_H_
#define YDVR_DISCRETE_VARIABLE_REPRESENTATION_H_

#include<iostream>
#include<string>
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
      virtual Matrix KineticMatrix() = 0;
      virtual Matrix PotentialMatrix();
      virtual Vector Grids() = 0; 
      virtual ~DiscreteVariableRepresentation(){}
      DiscreteVariableRepresentation(Oscillator* oscillator):
        Representation(oscillator){};
  };
}
#endif // YDVR_DISCRETE_VARIABLE_REPRESENTATION_H_
