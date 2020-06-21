// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"orthogonal_md_oscillator.h"
#include<utility>

namespace yDVR{
  void OrthogonalMDOscillator::split(){
    oscillators_.clear();
    for(std::vector<Scalar>::size_type i = 0; i < mass_.size(); ++i){
      oscillators_.push_back(
          new Oscillator(
            mass_[i],
            [=](Scalar q) -> Scalar{
            std::vector<Scalar> c(this->equilibrium_);
            c[i] = q;
            return this->potential(c);
            }
            )
          );
    }
    return;
  }

  const Oscillator& OrthogonalMDOscillator::oneDimension(int i){
    if(oscillators_.size() == 0) {
      split();
    }
    return *oscillators_[i];
  }

}
