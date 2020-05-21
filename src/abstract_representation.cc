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
  const Matrix& AbstractRepresentation::HamiltonianMatrix() {
    if (hamiltonian_matrix_.cols() == 0){
      hamiltonian_matrix_ = KineticMatrix() + PotentialMatrix();
    }
    return hamiltonian_matrix_;
  }
  const StationaryState& AbstractRepresentation::EnergyState(
      std::vector<StationaryState>::size_type i){
        if(stationary_states_.size() == 0){
          ComputeEnergyLevels();
        }
        return stationary_states_[i];
  }
  Scalar AbstractRepresentation::EnergyLevel(
      std::vector<StationaryState>::size_type i){ 
    if(stationary_states_.size() == 0){
      ComputeEnergyLevels();
    }
    return stationary_states_[i].energy();
  }
  void AbstractRepresentation::ComputeEnergyLevels(){
    SelfAdjointEigenSolver tmp(HamiltonianMatrix());
    Vector energy_levels = tmp.eigenvalues();
    Matrix wave_functions = tmp.eigenvectors();
    int s = energy_levels.size();
    for(int i = 0; i < s; ++i){
      stationary_states_
        .push_back(
            StationaryState(
              energy_levels(i),
              wave_functions.col(i),
              this) 
            );
    }
    return;
  }
}
