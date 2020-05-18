// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"config.h"
#include"representation.h"

namespace yDVR{
  class StationaryState{
    protected:
      Scalar energy_;
      Vector ket_;
      Representation* representation_;
    public:
      inline StationaryState(Scalar energy, Vector ket, Representation* representation)
        : energy_(energy), ket_(ket), representation_(representation){}
      inline Scalar energy() const { return energy_; }
      inline Vector ket() const { return ket_; }
      inline RowVector bra() const { return ket_.adjoint(); }
      inline Scalar ket(unsigned i) const { return ket_(i); }
      // TODO: good for real number but ...
      inline Scalar bra(unsigned i) const { return ket_(i); } 
  };
}
