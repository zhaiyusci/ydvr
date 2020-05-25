// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"orthogonal_md_representation.h"
namespace yDVR{
  const Oscillator& OrthogonalMDRepresentation::OscillatorOfDimension(
      std::vector<Oscillator>::size_type i){
    return oscillator_->OneDimension(i);
  }
}
