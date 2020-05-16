// This file is part of ydvr.
//
// Copyright (C) 2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_OSCILLATOR_H_
#define YDVR_OSCILLATOR_H_
#include"config.h"
// #include"representation.h"
#include<vector>
// #include"stationary_state.h"

namespace yDVR{
  class Representation;
  class StationaryState;

  class Oscillator{
    protected:
      const Scalar mass_;
      std::function<Scalar(Scalar)> potential_;
      Representation* representation_;
      std::vector<StationaryState*> stationary_states_;

      void ComputeEnergyLevels();
    public:
      inline Oscillator(Scalar mass, const std::function<Scalar(Scalar)>& potential)
        : mass_(mass), potential_(potential), representation_(nullptr) { }
      inline Scalar mass(){ return mass_; }
      inline Scalar Potential(Scalar q){ return potential_(q); }
      Scalar EnergyLevel(unsigned i);
      StationaryState EnergyState(unsigned i);
      void UseRepresentation(Representation* representation);
  };
}
#endif // YDVR_OSCILLATOR_H_
