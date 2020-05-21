// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"md_oscillator.h"

namespace yDVR{
  MDOscillator::MDOscillator(
      const std::vector<Scalar>& mass, 
      std::function<Scalar(const std::vector<Scalar>&)> potential):
    mass_(mass), potential_(potential)
  {
  }

  MDOscillator::MDOscillator(
      std::vector<Scalar>::size_type dimension, Scalar mass,
      std::function<Scalar(const std::vector<Scalar>&)> potential):
    mass_(dimension, mass), potential_(potential)
  {
  }

}
