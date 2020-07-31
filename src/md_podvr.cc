// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"md_podvr.h"
#include"simultaneous_diagonalization.h"
#include"log.h"

namespace yDVR{
  const Vector& MDPODVR::grids(std::vector<Vector>::size_type i){
    if (grids_[i].size() == 0) computeGrids();
    return grids_[i];
  }

  void MDPODVR::computeGrids(){
    Log::indent();
    LOG << "Calculate MD-PODVR grids..." << std::endl;
    std::vector<Matrix> coordinate_matrices;
    Log::indent();
    LOG << "Construct coordinate matrices under primitive energy representation..." << std::endl;
    for( size_t ii =0; ii< primitive_->dimension(); ++ii){
      Matrix tmp(N_,N_);
      Matrix pri_coord = primitive_->coordinateMatrix(ii);
      for(int i=0; i<N_; ++i){
        for(int j=i; j<N_; ++j){
          tmp(i,j)=
            Matrix(primitive_->energyState(i).adjoint()
                *pri_coord
                *primitive_->energyState(j))(0,0);
          tmp(j,i)=tmp(i,j);
        }
      }
      LOG << "CoordinateMatrix "<<  ii << std::endl << tmp << std::endl;
      coordinate_matrices.push_back(tmp);
    }
    // !!! Add from here to test what happened ----v
    LOG << "Commute???" << std::endl << coordinate_matrices[0]*coordinate_matrices[1] - coordinate_matrices[1]*coordinate_matrices[0] << std::endl;
    // !!! Add to here to test what happened ----^
    LOG << "done." << std::endl;
    LOG << "Call simultaneous Diagonalization code..." << std::endl;
    simultaneousDiagonalization tmp(coordinate_matrices, eps_);
    for( size_t ii =0; ii< primitive_->dimension(); ++ii){
      grids_[ii]=tmp.eigenvalues(ii);
      LOG << "CoordinateMatrix cooked "<<  ii << std::endl << tmp.remains(ii) << std::endl;
    }
    LOG << "done." << std::endl;
    Log::unindent();

    // eigenfunction of coordinate on energy representation
    primitive_to_po_=tmp.eigenvectors(); 

    // Some sign adjustment just like 1D PODVR
    // Ket of ground state should have no node.
    for(int i=0; i < N_; ++i){
      primitive_to_po_.col(i)*=primitive_to_po_(0,i)>0?1:-1;
    }
    LOG << "done." << std::endl;
    Log::unindent();

    return;
  }

  const Matrix& MDPODVR::hamiltonianMatrix(){
    // Get the hamiltonian without know its potential and kinetic energy
    if(hamiltonian_matrix_.cols() == 0){
      Log::indent();
      LOG << "Calculate MD-PODVR primitive hamiltonian direct from primitive energy levels..." << std::endl;
      hamiltonian_matrix_=Matrix::Zero(N_,N_);
      computeGrids(); // make sure that primitive_to_po_ calculated
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
