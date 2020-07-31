// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"config.h"
#include"dvr.h"
#include"oscillator.h"
namespace yDVR{
  const Matrix& DVR::potentialMatrix(){
    grids(); // grids must available before potential energy matrix element are done
    if ( potential_matrix_.cols() == 0){
      int s = grids_.size();
      potential_matrix_=Matrix::Zero(s,s);
      for ( int i = 0; i < s; ++i){
        potential_matrix_(i,i) = oscillator_->potential(grids_(i));
      }
    }
    return potential_matrix_;
  }

  const Matrix DVR::coordinateMatrix(){
    return grids().asDiagonal();
  }
}
