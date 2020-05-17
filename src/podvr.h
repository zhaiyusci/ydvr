// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_PODVR_H_
#define YDVR_PODVR_H_
// #include"mathtools.h"
#include"sincdvr.h"
// #include"iotools.h"

namespace yDVR{
  class PODVR : public DiscreteVariableRepresentation{
    protected:
      DiscreteVariableRepresentation* const primitive_representation_;
      int N_; // default value 10
      Matrix primitive_to_po_;
    public:
      PODVR(Oscillator* oscillator, 
          DiscreteVariableRepresentation* primitive_representation,
          int N);
      virtual Matrix KineticMatrix();
      virtual Matrix PotentialMatrix();
      virtual Vector Grids();
      void SetPrimitiveRepresentation(DiscreteVariableRepresentation* primitive_representation);
  };
}

#endif 
