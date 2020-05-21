// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_ABSTRACT_REPRESENTATION_H_
#define YDVR_ABSTRACT_REPRESENTATION_H_

#include<iostream>
#include<vector>
#include"config.h"
#include"stationary_state.h"

/* @file
 */

namespace yDVR{
  /** @brief Pure virtual class define the interface of a representation.
  */
  class AbstractRepresentation{
    protected:
      Matrix kinetic_matrix_;
      Matrix potential_matrix_;
      Matrix hamiltonian_matrix_;
      void ComputeEnergyLevels();
      std::vector<StationaryState> stationary_states_;
    public:
      /** @brief Constructor
      */
      AbstractRepresentation(): 
        kinetic_matrix_(Matrix::Zero(0,0)),
        potential_matrix_(Matrix::Zero(0,0)),
        hamiltonian_matrix_(Matrix::Zero(0,0)){}
      /** @brief Return the kinetic energy matrix. 
      */
      virtual const Matrix& KineticMatrix() = 0;
      /** @brief Return the potential energy matrix. 
      */
      virtual const Matrix& PotentialMatrix() = 0;
      /** @brief Return the hamiltonian matrix. 
      */
      virtual const Matrix& HamiltonianMatrix(); 
      /** @brief Distructor.
      */
      virtual ~AbstractRepresentation(){}
      /** @brief Energy of its i'th energy level.
       *
       * @param i Quantum number of the vibrational
       */
      Scalar EnergyLevel(std::vector<StationaryState>::size_type i);
      /** @brief i'th energy state.
       *
       * @param i Quantum number of the vibrational
       */
      const StationaryState& EnergyState(std::vector<StationaryState>::size_type i);
  };
}
#endif //  YDVR_REPRESENTATION_H_
