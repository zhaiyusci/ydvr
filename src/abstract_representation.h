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
      void computeEnergyLevels();
      Vector energy_levels_;
      Matrix energy_states_;
    public:
      /** @brief Constructor
      */
      AbstractRepresentation(): 
        kinetic_matrix_(Matrix::Zero(0,0)),
        potential_matrix_(Matrix::Zero(0,0)),
        hamiltonian_matrix_(Matrix::Zero(0,0)){}
      /** @brief Calculate and return the kinetic energy matrix. 
       *
       * In some cases, not directly used, only return a zero metrix.
       */
      virtual const Matrix& kineticMatrix() = 0;
      /** @brief Calculate and return the potential energy matrix. 
       *
       * In some cases, not directly used, only return a zero metrix.
       */
      virtual const Matrix& potentialMatrix() = 0;
      /** @brief Calculate and return the hamiltonian matrix. 
       *
       * Typically, hamiltonian matrix is calculate from the kinetic matrix (T)
       * and potential matrix (V). However, in some cases, 
       * the hamiltonian can be get directly without knowing the T and V.
       * Thus, the user should call hamiltonianMatrix() directly unless you want to
       * analysis something.
       */
      virtual const Matrix& hamiltonianMatrix(); 
      /** @brief Distructor.
      */
      virtual ~AbstractRepresentation(){}
      /** @brief Energy of its i'th energy level.
       *
       * @param i Quantum number of the vibrational
       */
      Scalar energyLevel(int i);
      /** @brief all energy levels.
       */
      const Vector& energyLevels();
      /** @brief i'th energy state.
       *
       * @param i Quantum number of the vibrational
       */
      Vector energyState(int i);
      /** @brief All energy states.
       */
      const Matrix& energyStates();
  };
}
#endif //  YDVR_REPRESENTATION_H_
