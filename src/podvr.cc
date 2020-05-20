// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"podvr.h"
#include"stationary_state.h"
#include"log.h"

namespace yDVR{
  PODVR::PODVR(Oscillator* oscillator, 
      DiscreteVariableRepresentation* primitive_representation,
      int N):
    DiscreteVariableRepresentation(oscillator),
    primitive_representation_(primitive_representation),
    N_(N)
  {
    LOG << std::endl;
    LOG << "============================= class PODVR ============================="<<std::endl;
    LOG << std::endl;
    LOG << "Reference: "<<std::endl;
    LOG << "  J. Echave and D. C. Clary, Chem. Phys. Lett. 190, 225 (1992) doi:10.1016/0009-2614(92)85330-D"<<std::endl;
    LOG << std::endl;
  }

  Vector PODVR::Grids(){
    if(grids_.size() == 0){
      Log::indent();
      LOG << "Calculate PO-DVR grids..." << std::endl;
      grids_.resize(N_);
      Matrix coordinate_matrix(N_,N_);
      Matrix pri_coord = primitive_representation_->CoordinateMatrix();
      for(int i=0; i<N_; ++i){
        for(int j=i; j<N_; ++j){
          coordinate_matrix(i,j)=
            Matrix(primitive_representation_->EnergyState(i).bra()
                *pri_coord
                *primitive_representation_->EnergyState(j).ket())(0,0);
          coordinate_matrix(j,i)=coordinate_matrix(i,j);
        }
      }
      SelfAdjointEigenSolver tmp(coordinate_matrix);
      grids_=tmp.eigenvalues();
      LOG << "done." << std::endl;
      LOG << "Calculate PO-DVR against states of primitive representation..." << std::endl;
      // eigenfunction of coordinate on energy representation
      primitive_to_po_=tmp.eigenvectors(); 

      // Well... at this state you may find this just OK because the way we transform 
      // energy representation to PODVR representation is straight forward...
      // It is not true because you see that both Psi and -Psi are quasi-eigenvector of X
      // That is a severe problem when you represent the final wavefunction in PODVR 
      // Here I prefer to let all the parameters for ground state to be positive

      for(int i=0; i < N_; ++i){
        primitive_to_po_.col(i)*=primitive_to_po_(0,i)>0?1:-1;
      }
      LOG << "done." << std::endl;
      Log::unindent();
    }
    return grids_;
  }

  Matrix PODVR::KineticMatrix(){
    // Kinetic energy here is **not** kinetic energy but the hamiltonian 
    // of primitive representation
    if(kinetic_matrix_.cols() == 0){
      Log::indent();
      LOG << "Calculate PO-DVR primitive hamiltonian..." << std::endl;
      kinetic_matrix_.resize(N_,N_);
      Grids(); // make sure that primitive_to_po_ calculated
      for(int i = 0; i<N_; ++i){
        kinetic_matrix_(i,i) = primitive_representation_->EnergyLevel(i);
      }
      kinetic_matrix_ = 
        primitive_to_po_.adjoint()
        *kinetic_matrix_
        *primitive_to_po_; 
      LOG << "done." << std::endl;
      Log::unindent();
    }
    return kinetic_matrix_;
  }

  Matrix PODVR::PotentialMatrix(){
    // Potential energy here is **not** potential energy but the 
    // change in potential energy from the one of primitive representation
    if(potential_matrix_.cols() == 0){
      Log::indent();
      LOG << "Calculate PO-DVR potential correction..." << std::endl;
      potential_matrix_ = Matrix::Zero(N_,N_);
      if (this->oscillator_ != primitive_representation_->oscillator()){
        LOG << "Different oscillators, calculating..." << std::endl;
        for(int i = 0; i < N_; ++i){
          potential_matrix_(i,i) = 
            this->oscillator_->Potential(Grids()(i))
            - primitive_representation_->oscillator()->Potential(Grids()(i));
        }
        LOG << "done." << std::endl;
      } else {
        LOG << "Nothing to do." << std::endl;
      }
      LOG << "done." << std::endl;
      Log::unindent();
    }
    return potential_matrix_;
  }
}

