// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"config.h"
#include"abstract_representation.h"
#include"stationary_state.h"
#include<utility>
namespace yDVR{
  const Matrix& AbstractRepresentation::hamiltonianMatrix() {
    if (hamiltonian_matrix_.cols() == 0){
      hamiltonian_matrix_ = kineticMatrix() + potentialMatrix();
    }
    return hamiltonian_matrix_;
  }
  Vector AbstractRepresentation::energyState(int i){
    computeEnergyLevels();
    return energy_states_.col(i);
  }
  const Matrix& AbstractRepresentation::energyStates(){
    computeEnergyLevels();
    return energy_states_;
  }
  Scalar AbstractRepresentation::energyLevel(int i){ 
    computeEnergyLevels();
    return energy_levels_[i];
  }
  const Vector& AbstractRepresentation::energyLevels(){ 
    computeEnergyLevels();
    return energy_levels_;
  }
  void AbstractRepresentation::computeEnergyLevels(){
    if(energy_levels_.size() == 0){
      SelfAdjointEigenSolver tmp(hamiltonianMatrix());
      energy_levels_ = tmp.eigenvalues();
      energy_states_ = tmp.eigenvectors();
    }
    return;
  }
}
