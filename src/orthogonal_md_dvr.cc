// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"orthogonal_md_dvr.h"
#include"log.h"
#include"../contrib/mdindex/mdindex.h"
namespace yDVR{
  const Oscillator& OrthogonalMDDVR::OscillatorOfDimension(
      std::vector<Oscillator>::size_type i){
    return oscillator_->OneDimension(i);
  }
  void OrthogonalMDDVR::SetRepresentation(
      std::vector<DVR*>::size_type i, 
      DVR& representation
      ){
    representations_[i] = &representation;
  }

  const std::vector<int> OrthogonalMDDVR::NumberOfGrids(){
    if(number_of_grids_.size() == 0){
      for(auto&& i : representations_){
        number_of_grids_.push_back(i->Grids().size());
      }
    }
    return number_of_grids_;
  }

  Scalar OrthogonalMDDVR::PrimitiveHamiltonianMatrixElement(const mdindex& i, const mdindex& j){
    Scalar res = 0;
    for (std::vector<DVR*>::size_type ii = 0; ii < representations_.size(); ++ii){
      // On dimension ii, calculate the hamiltonian element
      Scalar h=representations_[ii]->HamiltonianMatrix()(i.get(ii),j.get(ii));
      // Other dimensions, calculate the delta
      for (std::vector<DVR*>::size_type jj = 0; jj < representations_.size(); ++jj){
        if (jj != ii) {
          if (i.get(jj) != j.get(jj)) {
            h = 0.;
            break;
          }
        }
      }
      res += h;
    }
    return res;
  }

  Scalar OrthogonalMDDVR::PotentialCorrection(const mdindex& i){
    Scalar res = 0;
    std::vector<Scalar> q;
    // Primitive 
    for (std::vector<DVR*>::size_type ii = 0; ii < representations_.size(); ++ii){
      res += representations_[ii]->PotentialMatrix()(i.get(ii),i.get(ii));
      q.push_back(representations_[ii]->Grids()(i.get(ii)));
    }
    // true
    res -= oscillator_->Potential(q);
    res *= -1;

    return res;
  }
  const Matrix& OrthogonalMDDVR::HamiltonianMatrix(){ // TODO: Maybe sparse matrix instead.
    if(hamiltonian_matrix_.cols() == 0){
      Log::indent();
      LOG << "Calculate MDDVR hamiltonian..." << std::endl;
      Log::indent();
      LOG << "Get the grids..." << std::endl;
      mdindex i(NumberOfGrids());
      LOG << "done." << std::endl;
      hamiltonian_matrix_=Matrix::Zero(i.max(),i.max());
      LOG << "Calculate MDDVR primitive hamiltonian..." << std::endl;
      for(i = 0; i; ++i){ // mdindex library does all the trick here
        for(auto j = i; j; ++j){ 
          hamiltonian_matrix_(i.get(),j.get()) = PrimitiveHamiltonianMatrixElement(i,j);
          hamiltonian_matrix_(j.get(),i.get()) = hamiltonian_matrix_(i.get(),j.get());
        }
      }
      LOG << "done." << std::endl;
      LOG << "Calculate MDDVR potential correction..." << std::endl;
      for(i = 0; i; ++i){ // mdindex library does all the trick here
        hamiltonian_matrix_(i.get(),i.get()) += PotentialCorrection(i);
      }
      LOG << "done." << std::endl;
      Log::unindent();
      LOG << "done." << std::endl;
      Log::unindent();
    }
    return hamiltonian_matrix_;
  }

  const Matrix OrthogonalMDDVR::CoordinateMatrix(std::vector<Vector>::size_type i){
    if(grids_[i].size() == 0){
      mdindex ii(NumberOfGrids());
      grids_[i] = Vector::Zero(ii.max());
      for( ii = 0; ii; ++ii){
        grids_[i][ii.get()] = representations_[i]->Grids()[ii.get(i)];
      }
    }
    return grids_[i].asDiagonal();
  }

}
