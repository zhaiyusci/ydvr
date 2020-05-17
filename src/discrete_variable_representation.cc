#include"config.h"
#include"discrete_variable_representation.h"
namespace yDVR{
  Matrix DiscreteVariableRepresentation::PotentialMatrix(){
    Grids(); // grids must available before potential energy matrix element are done
    if ( potential_matrix_.cols() == 0){
      unsigned s = grids_.size();
      potential_matrix_.resize(s,s);
      for ( unsigned i = 0; i< s; ++i){
        potential_matrix_(i,i) = oscillator_->Potential(grids_(i));
      }
    }
    return potential_matrix_;
  }

  Matrix DiscreteVariableRepresentation::CoordinateMatrix(){
    return Grids().asDiagonal();
  }
}
