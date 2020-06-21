// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"sincdvr.h"
#include"oscillator.h"
#include"log.h"
#include<chrono>

namespace yDVR{
  const Vector& SincDVR::grids(){
    if(grids_.size() == 0){
      Log::indent();
      LOG << "Calculate Sinc-DVR grids..." << std::endl;
      grids_.resize(N_plus_1_-1);
      Scalar deltax=(b_-a_)/N_plus_1_; 
      for(int i = 1; i < N_plus_1_; ++i){ 
        // I try to follow the way they write the paper, however, you know it is C++
        // here the x(i-1) thing is x(i) in their paper 
        // and the reason is that in C-like language the 
        // index start from 0
        // ... so here I only change the index
        grids_(i-1)=a_+deltax*i;
      }
      LOG << "done." << std::endl;
      Log::unindent();
    }
    return grids_;
  }

  const Matrix& SincDVR::kineticMatrix(){
    if(kinetic_matrix_.cols() == 0){
      Log::indent();
      LOG << "Calculate Sinc-DVR kinetic matrix..." << std::endl;
      Scalar deltax=(b_-a_)/N_plus_1_; 
      Scalar m=oscillator_->mass();
      kinetic_matrix_.resize(N_plus_1_-1, N_plus_1_-1); 
      // in the paper it is i' but I think using j is a better idea
      // For i!=j ... 
      for(int i=1; i<N_plus_1_; ++i){
        for(int j=1;j<i; ++j){
          kinetic_matrix_(i-1,j-1)
            =1.0/(2*m*pow(deltax,2))*pow(-1,(i-j))*2/pow((i-j),2);
          kinetic_matrix_(j-1,i-1)=kinetic_matrix_(i-1,j-1);
        }
      }
      // For i==j
      for(int i=1; i<N_plus_1_; ++i){
        kinetic_matrix_(i-1,i-1)
          =1.0/(2*m*pow(deltax,2))*pow(M_PI,2)/3.0;
      }
      LOG << "done." << std::endl;
      Log::unindent();
    }
    return kinetic_matrix_;
  }

  SincDVR::SincDVR(const Oscillator& oscillator, Scalar a, Scalar b, int N):
    DVR(oscillator), a_(a), b_(b), 
    N_plus_1_(N+1)  
    // some wrapper here to let the user feels good
    // and rename N_ to N_plus_1_ to let the author feels good
  {
    LOG << std::endl;
    LOG << "============================ class sincDVR ============================" << std::endl;
    LOG << std::endl;
    LOG << "Reference: "<< std::endl;
    LOG << "  D. T. Colbert and W. H. Miller, J. Chem. Phys. 96, 1982 (1992) doi:10.1063/1.462100" << std::endl;
    LOG << std::endl;
  }
}
