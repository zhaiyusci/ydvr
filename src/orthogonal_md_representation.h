// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"config.h"
#include"abstract_representation.h"
#include"orthogonal_md_oscillator.h"

namespace yDVR{
  class OrthogonalMDRepresentation : public AbstractRepresentation{
    protected:
      OrthogonalMDOscillator* oscillator_;
      std::vector<Representation*> representations_;
    public:
      Oscillator* OscillatorOfDimension(std::vector<Oscillator>::size_type i);


  };
}
