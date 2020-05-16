// This file is part of ydvr.
//
// Copyright (C) 2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_REPRESENTATION_H_
#define YDVR_REPRESENTATION_H_

#include<iostream>
#include<string>
#include"config.h"
#include"oscillator.h"

/* @file
 */

namespace yDVR{
  /** @brief Pure virtual class define the interface of a representation.
  */
  class Representation{
    protected:
      Matrix kinetic_matrix_;
      Matrix potential_matrix_;
      Matrix hamiltonian_matrix_;
      Oscillator* const oscillator_;
    public:
      Representation(Oscillator* oscillator): oscillator_(oscillator){}
  /** @brief Return the kinetic energy matrix. 
  */
      virtual Matrix KineticMatrix() = 0;
  /** @brief Return the potential energy matrix. 
  */
      virtual Matrix PotentialMatrix() = 0;
  /** @brief Return the energy matrix. 
  */
      virtual Matrix HamiltonianMatrix(); 
      virtual inline ~Representation(){}
  };
}
#endif //  YDVR_REPRESENTATION_H_
