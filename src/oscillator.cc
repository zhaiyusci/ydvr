#include"oscillator.h"
#include"stationary_state.h"
#include"representation.h"

namespace yDVR {
  void Oscillator::ComputeEnergyLevels(){
    SelfAdjointEigenSolver tmp(representation_->HamiltonianMatrix());
    Vector energy_levels = tmp.eigenvalues();
    Matrix wave_functions = tmp.eigenvectors();
    unsigned s = energy_levels.size();
    for(unsigned i = 0; i < s; ++i){
      stationary_states_
        .push_back(
            new StationaryState(
              energy_levels(i),
              wave_functions.col(i),
              representation_)  // remember to delete them
            );
    }
    return;
  }
  void Oscillator::UseRepresentation(Representation* representation){
    representation_ = representation;
    for(auto&& i : stationary_states_){
      delete i;
    }
    stationary_states_.clear();
  }
  StationaryState Oscillator::EnergyState(unsigned i){
        if(stationary_states_.size() == 0){
          ComputeEnergyLevels();
        }
        return *(stationary_states_[i]);
  }
  Scalar Oscillator::EnergyLevel(unsigned i){ 
    if(stationary_states_.size() == 0){
      ComputeEnergyLevels();
    }
    return stationary_states_[i]->energy();
  }
}
