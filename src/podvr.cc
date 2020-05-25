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
#include"oscillator.h"

namespace yDVR{
  PODVR::PODVR(const Oscillator& oscillator, 
      DVR& primitive,
      int N):
    DVR(oscillator), 
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

  const Vector& PODVR::Grids(){
    if(grids_.size() == 0){
      Log::indent();
      LOG << "Calculate PO-DVR grids..." << std::endl;
      grids_=Vector::Zero(N_);
      Matrix coordinate_matrix(N_,N_);
      Matrix pri_coord = primitive_->CoordinateMatrix();
      for(int i=0; i<N_; ++i){
        for(int j=i; j<N_; ++j){
          coordinate_matrix(i,j)=
            Matrix(primitive_->EnergyState(i).bra()
                *pri_coord
                *primitive_->EnergyState(j).ket())(0,0);
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

  const Matrix& PODVR::KineticMatrix(){
    if(kinetic_matrix_.cols() == 0){
      Log::indent();
      LOG << "Calculate PO-DVR kinetic energy..." << std::endl;
      Log::indent();
      LOG << "Calculate PO-DVR primitive hamiltonian..." << std::endl;
      kinetic_matrix_=Matrix::Zero(N_,N_);
      Grids(); // make sure that primitive_to_po_ calculated
      for(int i = 0; i<N_; ++i){
        kinetic_matrix_(i,i) = primitive_->EnergyLevel(i);
      }
      kinetic_matrix_ = 
        primitive_to_po_.adjoint()
        *kinetic_matrix_
        *primitive_to_po_; 
      LOG << "done." << std::endl;
      LOG << "Remove the potential part..." << std::endl;
      for(int i = 0; i<N_; ++i){
        kinetic_matrix_(i,i) -= 
          primitive_
          ->oscillator()
          .Potential(Grids()(i));
      }
      LOG << "done." << std::endl;
      Log::unindent();
      Log::unindent();
    }
    return kinetic_matrix_;
  }

  const Matrix& PODVR::PotentialMatrix(){
    if(potential_matrix_.cols() == 0){
      Log::indent();
      LOG << "Calculate PO-DVR potential..." << std::endl;
      potential_matrix_ = Matrix::Zero(N_,N_);
      for(int i = 0; i < N_; ++i){
        potential_matrix_(i,i) = 
          this->oscillator_->Potential(Grids()(i));
      }
      LOG << "done." << std::endl;
      Log::unindent();
    }
    return potential_matrix_;
  }

  const Matrix& PODVR::HamiltonianMatrix(){

    if(oscillator_ == &(primitive_->oscillator())){
      // Get the hamiltonian without know its potential and kinetic energy
      if(hamiltonian_matrix_.cols() == 0){
        Log::indent();
        LOG << "Calculate PO-DVR primitive hamiltonian direct from primitive energy levels..." << std::endl;
        hamiltonian_matrix_=Matrix::Zero(N_,N_);
        Grids(); // make sure that primitive_to_po_ calculated
        for(int i = 0; i<N_; ++i){
          hamiltonian_matrix_(i,i) = primitive_->EnergyLevel(i);
        }
        hamiltonian_matrix_ = 
          primitive_to_po_.adjoint()
          *hamiltonian_matrix_
          *primitive_to_po_; 
        LOG << "done." << std::endl;
        Log::unindent();
      }
      return hamiltonian_matrix_;
    }else{
      return DVR::HamiltonianMatrix();
    }
  }
}

