// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_REPRESENTATION_H_
#define YDVR_REPRESENTATION_H_

#include<iostream>
#include<vector>
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
      void ComputeEnergyLevels();
      std::vector<StationaryState*> stationary_states_;
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
      virtual ~Representation();
      inline Oscillator* const oscillator(){return oscillator_;}
      Scalar EnergyLevel(unsigned i);
      StationaryState EnergyState(unsigned i);
  };
}
#endif //  YDVR_REPRESENTATION_H_
