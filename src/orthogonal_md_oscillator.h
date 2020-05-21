// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_ORTHOGONAL_MD_OSCILLATOR_H_
#define YDVR_ORTHOGONAL_MD_OSCILLATOR_H_

#include"config.h"
#include"oscillator.h"
#include<vector>
#include"md_oscillator.h"

namespace yDVR{
  /** @brief Multi-dimension oscillator.
   */
  class OrthogonalMDOscillator: public MDOscillator{
    protected:
      void Split();
      std::vector<Oscillator> oscillators_;
      std::vector<Scalar> equilibrium_;
    public:
      using MDOscillator::MDOscillator; // Use the constructor.
      /** @brief i'th one-dimension oscillator.
       */
      const Oscillator& OneDimension(std::vector<Oscillator>::size_type i);

      /** @brief Virtual destructor.
       */
      virtual ~OrthogonalMDOscillator(){};
  };

}

#endif //  YDVR_ORTHOGONAL_MD_OSCILLATOR_H_
