// This file is part of yDVR.
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
#include<map>
#include<utility>

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
    LOG << "  J. E. Kilpatrick and R. L. Sass, J. Chem. Phys. 42, 2581 (1965) doi:10.1063/1.1696335" << std::endl; 
    beta_ = 0.5/oscillator.mass()/oscillator.omega();
    return;
  }

/* Hard code here, and I do not like it.
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
*/

  std::function<int(int)> harmonicFFunction(int p, int r){
    if (p%2 != r%2) return [](int N){(void)N; return 0; };
    const std::map<std::pair<int, int>, std::vector<int> > coeff = { 
      // generate using tools/harmonic_F.py
      // {{{
      {std::make_pair( 0,  0), std::vector<int>({1})},
      {std::make_pair( 1,  1), std::vector<int>({1})},
      {std::make_pair( 2,  2), std::vector<int>({1})},
      {std::make_pair( 2,  0), std::vector<int>({0, 1})},
      {std::make_pair( 3,  3), std::vector<int>({1})},
      {std::make_pair( 3,  1), std::vector<int>({0, 1})},
      {std::make_pair( 4,  4), std::vector<int>({1})},
      {std::make_pair( 4,  2), std::vector<int>({0, 1})},
      {std::make_pair( 4,  0), std::vector<int>({1, 0, 1})},
      {std::make_pair( 5,  5), std::vector<int>({1})},
      {std::make_pair( 5,  3), std::vector<int>({0, 1})},
      {std::make_pair( 5,  1), std::vector<int>({2, 0, 1})},
      {std::make_pair( 6,  6), std::vector<int>({1})},
      {std::make_pair( 6,  4), std::vector<int>({0, 1})},
      {std::make_pair( 6,  2), std::vector<int>({3, 0, 1})},
      {std::make_pair( 6,  0), std::vector<int>({0, 5, 0, 1})},
      {std::make_pair( 7,  7), std::vector<int>({1})},
      {std::make_pair( 7,  5), std::vector<int>({0, 1})},
      {std::make_pair( 7,  3), std::vector<int>({4, 0, 1})},
      {std::make_pair( 7,  1), std::vector<int>({0, 8, 0, 1})},
      {std::make_pair( 8,  8), std::vector<int>({1})},
      {std::make_pair( 8,  6), std::vector<int>({0, 1})},
      {std::make_pair( 8,  4), std::vector<int>({5, 0, 1})},
      {std::make_pair( 8,  2), std::vector<int>({0, 11, 0, 1})},
      {std::make_pair( 8,  0), std::vector<int>({9, 0, 14, 0, 1})},
      {std::make_pair( 9,  9), std::vector<int>({1})},
      {std::make_pair( 9,  7), std::vector<int>({0, 1})},
      {std::make_pair( 9,  5), std::vector<int>({6, 0, 1})},
      {std::make_pair( 9,  3), std::vector<int>({0, 14, 0, 1})},
      {std::make_pair( 9,  1), std::vector<int>({24, 0, 20, 0, 1})},
      {std::make_pair(10, 10), std::vector<int>({1})},
      {std::make_pair(10,  8), std::vector<int>({0, 1})},
      {std::make_pair(10,  6), std::vector<int>({7, 0, 1})},
      {std::make_pair(10,  4), std::vector<int>({0, 17, 0, 1})},
      {std::make_pair(10,  2), std::vector<int>({45, 0, 26, 0, 1})},
      {std::make_pair(10,  0), std::vector<int>({0, 89, 0, 30, 0, 1})},
      {std::make_pair(11, 11), std::vector<int>({1})},
      {std::make_pair(11,  9), std::vector<int>({0, 1})},
      {std::make_pair(11,  7), std::vector<int>({8, 0, 1})},
      {std::make_pair(11,  5), std::vector<int>({0, 20, 0, 1})},
      {std::make_pair(11,  3), std::vector<int>({72, 0, 32, 0, 1})},
      {std::make_pair(11,  1), std::vector<int>({0, 184, 0, 40, 0, 1})},
      {std::make_pair(12, 12), std::vector<int>({1})},
      {std::make_pair(12, 10), std::vector<int>({0, 1})},
      {std::make_pair(12,  8), std::vector<int>({9, 0, 1})},
      {std::make_pair(12,  6), std::vector<int>({0, 23, 0, 1})},
      {std::make_pair(12,  4), std::vector<int>({105, 0, 38, 0, 1})},
      {std::make_pair(12,  2), std::vector<int>({0, 309, 0, 50, 0, 1})},
      {std::make_pair(12,  0), std::vector<int>({225, 0, 439, 0, 55, 0, 1})},
      {std::make_pair(13, 13), std::vector<int>({1})},
      {std::make_pair(13, 11), std::vector<int>({0, 1})},
      {std::make_pair(13,  9), std::vector<int>({10, 0, 1})},
      {std::make_pair(13,  7), std::vector<int>({0, 26, 0, 1})},
      {std::make_pair(13,  5), std::vector<int>({144, 0, 44, 0, 1})},
      {std::make_pair(13,  3), std::vector<int>({0, 464, 0, 60, 0, 1})},
      {std::make_pair(13,  1), std::vector<int>({720, 0, 784, 0, 70, 0, 1})},
      {std::make_pair(14, 14), std::vector<int>({1})},
      {std::make_pair(14, 12), std::vector<int>({0, 1})},
      {std::make_pair(14, 10), std::vector<int>({11, 0, 1})},
      {std::make_pair(14,  8), std::vector<int>({0, 29, 0, 1})},
      {std::make_pair(14,  6), std::vector<int>({189, 0, 50, 0, 1})},
      {std::make_pair(14,  4), std::vector<int>({0, 649, 0, 70, 0, 1})},
      {std::make_pair(14,  2), std::vector<int>({1575, 0, 1219, 0, 85, 0, 1})},
      {std::make_pair(14,  0), std::vector<int>({0, 3429, 0, 1519, 0, 91, 0, 1})},
      {std::make_pair(15, 15), std::vector<int>({1})},
      {std::make_pair(15, 13), std::vector<int>({0, 1})},
      {std::make_pair(15, 11), std::vector<int>({12, 0, 1})},
      {std::make_pair(15,  9), std::vector<int>({0, 32, 0, 1})},
      {std::make_pair(15,  7), std::vector<int>({240, 0, 56, 0, 1})},
      {std::make_pair(15,  5), std::vector<int>({0, 864, 0, 80, 0, 1})},
      {std::make_pair(15,  3), std::vector<int>({2880, 0, 1744, 0, 100, 0, 1})},
      {std::make_pair(15,  1), std::vector<int>({0, 8448, 0, 2464, 0, 112, 0, 1})},
      {std::make_pair(16, 16), std::vector<int>({1})},
      {std::make_pair(16, 14), std::vector<int>({0, 1})},
      {std::make_pair(16, 12), std::vector<int>({13, 0, 1})},
      {std::make_pair(16, 10), std::vector<int>({0, 35, 0, 1})},
      {std::make_pair(16,  8), std::vector<int>({297, 0, 62, 0, 1})},
      {std::make_pair(16,  6), std::vector<int>({0, 1109, 0, 90, 0, 1})},
      {std::make_pair(16,  4), std::vector<int>({4725, 0, 2359, 0, 115, 0, 1})},
      {std::make_pair(16,  2), std::vector<int>({0, 16407, 0, 3619, 0, 133, 0, 1})},
      {std::make_pair(16,  0), std::vector<int>({11025, 0, 24940, 0, 4214, 0, 140, 0, 1})},
      {std::make_pair(17, 17), std::vector<int>({1})},
      {std::make_pair(17, 15), std::vector<int>({0, 1})},
      {std::make_pair(17, 13), std::vector<int>({14, 0, 1})},
      {std::make_pair(17, 11), std::vector<int>({0, 38, 0, 1})},
      {std::make_pair(17,  9), std::vector<int>({360, 0, 68, 0, 1})},
      {std::make_pair(17,  7), std::vector<int>({0, 1384, 0, 100, 0, 1})},
      {std::make_pair(17,  5), std::vector<int>({7200, 0, 3064, 0, 130, 0, 1})},
      {std::make_pair(17,  3), std::vector<int>({0, 27936, 0, 4984, 0, 154, 0, 1})},
      {std::make_pair(17,  1), std::vector<int>({40320, 0, 52352, 0, 6384, 0, 168, 0, 1})},
      {std::make_pair(18, 18), std::vector<int>({1})},
      {std::make_pair(18, 16), std::vector<int>({0, 1})},
      {std::make_pair(18, 14), std::vector<int>({15, 0, 1})},
      {std::make_pair(18, 12), std::vector<int>({0, 41, 0, 1})},
      {std::make_pair(18, 10), std::vector<int>({429, 0, 74, 0, 1})},
      {std::make_pair(18,  8), std::vector<int>({0, 1689, 0, 110, 0, 1})},
      {std::make_pair(18,  6), std::vector<int>({10395, 0, 3859, 0, 145, 0, 1})},
      {std::make_pair(18,  4), std::vector<int>({0, 43665, 0, 6559, 0, 175, 0, 1})},
      {std::make_pair(18,  2), std::vector<int>({99225, 0, 93204, 0, 8974, 0, 196, 0, 1})},
      {std::make_pair(18,  0), std::vector<int>({0, 230481, 0, 122156, 0, 10038, 0, 204, 0, 1})},
      {std::make_pair(19, 19), std::vector<int>({1})},
      {std::make_pair(19, 17), std::vector<int>({0, 1})},
      {std::make_pair(19, 15), std::vector<int>({16, 0, 1})},
      {std::make_pair(19, 13), std::vector<int>({0, 44, 0, 1})},
      {std::make_pair(19, 11), std::vector<int>({504, 0, 80, 0, 1})},
      {std::make_pair(19,  9), std::vector<int>({0, 2024, 0, 120, 0, 1})},
      {std::make_pair(19,  7), std::vector<int>({14400, 0, 4744, 0, 160, 0, 1})},
      {std::make_pair(19,  5), std::vector<int>({0, 64224, 0, 8344, 0, 196, 0, 1})},
      {std::make_pair(19,  3), std::vector<int>({201600, 0, 150016, 0, 11984, 0, 224, 0, 1})},
      {std::make_pair(19,  1), std::vector<int>({0, 648576, 0, 229760, 0, 14448, 0, 240, 0, 1})},
      {std::make_pair(20, 20), std::vector<int>({1})},
      {std::make_pair(20, 18), std::vector<int>({0, 1})},
      {std::make_pair(20, 16), std::vector<int>({17, 0, 1})},
      {std::make_pair(20, 14), std::vector<int>({0, 47, 0, 1})},
      {std::make_pair(20, 12), std::vector<int>({585, 0, 86, 0, 1})},
      {std::make_pair(20, 10), std::vector<int>({0, 2389, 0, 130, 0, 1})},
      {std::make_pair(20,  8), std::vector<int>({19305, 0, 5719, 0, 175, 0, 1})},
      {std::make_pair(20,  6), std::vector<int>({0, 90243, 0, 10339, 0, 217, 0, 1})},
      {std::make_pair(20,  4), std::vector<int>({363825, 0, 225308, 0, 15414, 0, 252, 0, 1})},
      {std::make_pair(20,  2), std::vector<int>({0, 1411785, 0, 382724, 0, 19614, 0, 276, 0, 1})},
      {std::make_pair(20,  0), std::vector<int>({893025, 0, 2250621, 0, 463490, 0, 21378, 0, 285, 0, 1})}
      // }}}
    };
    return [=](int N){
      int res = 0;
      auto cs = coeff.at(std::make_pair(p,r));

      for (int i = 0; i< (int)cs.size(); ++i){
        res += cs[i] * pow(N, i);
      }
      return res;
    };
  }
  Matrix HarmonicRepresentation::constructCoordinateMatrix(int p){
    // To implement the Eq. (19) need some symbolic calculation...
    // and we are saying C++ here so not a good idea.

    // if (p == 0) return Matrix::Identity(N_,N_);

    Matrix res = Matrix::Zero(N_,N_);
    for (int r = p; r >= 0; r -= 2){
      auto F = harmonicFFunction(p,r);
      for (int m = r; m < N_; ++m){
        int n = m-r;
        int N = m+n+1;
        int prod = 1;
        for (int i = N-r+1; i<= N+r-1; i += 2){
          prod *= i;
        }
        res(m,n) = sqrt(prod*1.)
          *std::tgamma(p+1) / std::tgamma((p-r)/2+1) / std::tgamma(p-(p-r)/2+1)
          *F(N);

        res(n,m) = res(m,n);
      }
    }

    return res *sqrt(pow(beta_,p)*pow(2,-p));
  }

  const Matrix& HarmonicRepresentation::coordinateMatrix(int i){
    if ((int)coordinate_matrices_.size() <= i){
      Log::indent();
      LOG << "Construct coordinate matrix of the " << i<< "th(st/nd/rd) order..." << std::endl;

      if (i > 0){
        // call this function to construct lower order coordinateMatrix
        coordinateMatrix(i-1); 
      }
      // Construct i'th order
      coordinate_matrices_.push_back(constructCoordinateMatrix(i));
      LOG << std::endl << coordinate_matrices_[i] << std::endl;
      LOG << "done." << std::endl;
      Log::unindent();
    }
    return coordinate_matrices_[i];
  }

  const Matrix& HarmonicRepresentation::potentialMatrix() {
    if (potential_matrix_.cols() == 0){
      Log::indent();
      LOG << "Calculate harmonic representation potential matrix..." << std::endl;
      potential_matrix_=Matrix::Zero(N_,N_);
      for (unsigned int i = 0; i<oscillator_taylor_->forceConstants().size(); ++i){
        potential_matrix_ += 
          oscillator_taylor_->forceConstants(i) / std::tgamma(i+1) * coordinateMatrix(i);
      }
      LOG << "done." << std::endl;
      Log::unindent();
    }
    return potential_matrix_;
  }

  const Matrix& HarmonicRepresentation::kineticMatrix() {
    if (kinetic_matrix_.cols() == 0){
      Log::indent();
      LOG << "Calculate harmonic representation kinetic matrix..." << std::endl;
      kinetic_matrix_=Matrix::Zero(N_,N_);
      for ( int i =0; i<N_; ++i){
        // The energy of the harmonic oscillator
        kinetic_matrix_(i,i) = (i+0.5) * oscillator_taylor_->omega();
      }
      // remove the potential energy
      kinetic_matrix_ -= 
        0.5 * oscillator_taylor_->forceConstants(2) * coordinateMatrix(2);
      LOG << "done." << std::endl;
      Log::unindent();
    }
    return kinetic_matrix_;
  }
}
