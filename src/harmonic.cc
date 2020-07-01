// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"harmonic.h"
#include"oscillator_taylor.h"
#include"log.h"
#include<chrono>

namespace yDVR{

  HarmonicRepresentation::HarmonicRepresentation(const OscillatorTaylor& oscillator, int N):
    Representation(oscillator), 
    N_(N),
    oscillator_taylor_(&oscillator)
  {
    LOG << std::endl;
    LOG << "============================ class HarmonicRepresentation ============================" << std::endl;
    LOG << std::endl;
    LOG << "Reference: "<< std::endl;
    LOG << "  TODO" << std::endl; // TODO
    beta_ = 0.5/oscillator.mass()/oscillator.omega();
    // coordinate_matrices_(oscillator.forceConstants().size(), Matrix::Zero(N_, N_))

    LOG << std::endl;
  }

  Matrix HarmonicRepresentation::constructCoordinateMatrix(int i){
    if (i == 0){
      return Matrix::Identity(N_, N_);
    }else if ( i == 1){
      Matrix res = Matrix::Zero(N_,N_);
      for ( int  n = 1; n < N_; ++n){
        res(n,n-1) = sqrt(n*1.);
        res(n-1,n) = res(n,n-1);
      }
      res = sqrt(beta_) * res;
      return res;
    }else if ( i == 2){
      Matrix res = Matrix::Zero(N_,N_);
      for ( int  n = 0; n < N_; ++n){
        res(n,n) = 2*n+1;
      }
      for ( int  n = 2; n < N_; ++n){
        res(n,n-2) = sqrt(n*(n-1.));
        res(n-2,n) = res(n,n-2);
      }
      res = beta_ * res;
      return res;
    }else if ( i == 3){
      Matrix res = Matrix::Zero(N_,N_);
      for ( int  n = 1; n < N_; ++n){
        res(n,n-1) = 3.*sqrt(n*1.)*n;
        res(n-1,n) = res(n,n-1);
      }
      for ( int  n = 3; n < N_; ++n){
        res(n,n-3) = sqrt(n*(n-1.)*(n-2.));
        res(n-3,n) = res(n,n-3);
      }
      res = pow(sqrt(beta_),3) * res;
      return res;
    }else if ( i == 4){
      Matrix res = Matrix::Zero(N_,N_);
      for ( int  n = 0; n < N_; ++n){
        res(n,n) = 6*n*n + 6*n +3;
      }
      for ( int  n = 2; n < N_; ++n){
        res(n,n-2) = sqrt(n*(n-1.))*(4*n-2);
        res(n-2,n) = res(n,n-2);
      }
      for ( int  n = 4; n < N_; ++n){
        res(n,n-4) = sqrt(n*(n-1.)*(n-2.)*(n-3.));
        res(n-4,n) = res(n,n-4);
      }
      res = pow(beta_,2) * res;
      return res;
    }else{
      Matrix res = Matrix::Zero(N_,N_);
      throw("In this version matrix of coodinate to the i'th power (i > 4) is not ready.");
      return res;
    }
  }

  const Matrix& HarmonicRepresentation::coordinateMatrix(int i){
    if ((int)coordinate_matrices_.size() <= i){
      if (i > 0){
        // call this function to construct lower order coordinateMatrix
        coordinateMatrix(i-1); 
      }
      // Construct i'th order
      coordinate_matrices_.push_back(constructCoordinateMatrix(i));
    }
    return coordinate_matrices_[i];
  }

  const Matrix& HarmonicRepresentation::potentialMatrix() {
    if (potential_matrix_.cols() == 0){
      potential_matrix_=Matrix::Zero(N_,N_);
      for (unsigned int i = 0; i<oscillator_taylor_->forceConstants().size(); ++i){
        potential_matrix_ += 
          oscillator_taylor_->forceConstants(i) / std::tgamma(i+1) * coordinateMatrix(i);
      }
    }
    return potential_matrix_;
  }

  const Matrix& HarmonicRepresentation::kineticMatrix() {
    if (kinetic_matrix_.cols() == 0){
      kinetic_matrix_=Matrix::Zero(N_,N_);
      for ( int i =0; i<N_; ++i){
        // The energy of the harmonic oscillator
        kinetic_matrix_(i,i) = (i+0.5) * oscillator_taylor_->omega();
      }
      // remove the potential energy
      kinetic_matrix_ -= 
        0.5 * oscillator_taylor_->forceConstants(2) * coordinateMatrix(2);
    }
    return kinetic_matrix_;
  }
}
