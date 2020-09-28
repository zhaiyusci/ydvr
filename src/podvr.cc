// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"podvr.hh"
// #include"stationary_state.hh"
#include"log.hh"
#include"oscillator.hh"

namespace yDVR{
  PODVR::PODVR(DVR& primitive, int N):
    DVR(primitive.oscillator()), 
    N_(N),
    primitive_(&primitive)
  {
    LOG << std::endl;
    LOG << "============================= class PODVR ============================="<<std::endl;
    LOG << std::endl;
    LOG << "Reference: "<<std::endl;
    LOG << "  J. Echave and D. C. Clary, Chem. Phys. Lett. 190, 225 (1992) doi:10.1016/0009-2614(92)85330-D"<<std::endl;
    LOG << std::endl;
  }

  const Vector& PODVR::grids(){
    if(grids_.size() == 0){
      Log::indent();
      LOG << "Calculate PO-DVR grids..." << std::endl;
      grids_=Vector::Zero(N_);
      Matrix coordinate_matrix; // (N_,N_);
      Matrix pri_coord = primitive_->coordinateMatrix();

      // Using the lowest N_ states to construct the coordinate matrix of PODVR
      coordinate_matrix = primitive_->energyStates().leftCols(N_).adjoint()
        * pri_coord
        * primitive_->energyStates().leftCols(N_);

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

  const Matrix& PODVR::kineticMatrix(){
    if(kinetic_matrix_.cols() == 0){
      Log::indent();
      LOG << "Calculate PO-DVR kinetic energy..." << std::endl;
      kinetic_matrix_=hamiltonianMatrix() - potentialMatrix();
      LOG << "done." << std::endl;
      Log::unindent();
    }
    return kinetic_matrix_;
  }

  const Matrix& PODVR::hamiltonianMatrix(){
    // Get the hamiltonian without know its potential and kinetic energy
    if(hamiltonian_matrix_.cols() == 0){
      Log::indent();
      LOG << "Calculate PO-DVR primitive hamiltonian direct from primitive energy levels..." << std::endl;
      hamiltonian_matrix_=Matrix::Zero(N_,N_);
      grids(); // make sure that primitive_to_po_ calculated
      for(int i = 0; i<N_; ++i){
        hamiltonian_matrix_(i,i) = primitive_->energyLevel(i);
      }
      hamiltonian_matrix_ = 
        primitive_to_po_.adjoint()
        *hamiltonian_matrix_
        *primitive_to_po_; 
      LOG << "done." << std::endl;
      Log::unindent();
    }
    return hamiltonian_matrix_;
  }
}

