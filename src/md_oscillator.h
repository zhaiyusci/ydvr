// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_MD_OSCILLATOR_H_
#define YDVR_MD_OSCILLATOR_H_

#include"config.h"
#include"oscillator.h"
#include<vector>

namespace yDVR{
  /** @brief Multi-dimension oscillator.
   */
  class MDOscillator{
    protected:
      std::vector<Scalar> mass_;
      std::function<Scalar(const std::vector<Scalar>&)> potential_;
    public:
      /** @brief Constructor.
       *
       * @param mass Vector of mass 
       * @param potential The potential function, whose parameter is vector formed by the coordinates
       *
       * The user should make sure the dimension of the two part are identical.
       */
      MDOscillator(const std::vector<Scalar>& mass, std::function<Scalar(const std::vector<Scalar>&)> potential);
      /** @brief Constructor for uniform mass case.
       *
       * @param dimension
       * @param mass 
       * @param potential The potential function, whose parameter is vector formed by the coordinates
       *
       * The user should make sure the dimension of the two part are identical.
       */
      MDOscillator(std::vector<Scalar>::size_type dimension, Scalar mass, std::function<Scalar(const std::vector<Scalar>&)> potential);
      /** @brief Return effective mass of i'th dimension.
       *
       * @param i i'th dimension
       */
      inline Scalar mass(std::vector<Scalar>::size_type i) const { return mass_[i];}
      /** @brief Virtual destructor.
       */
      virtual ~MDOscillator(){}
  };

}

#endif // YDVR_MD_OSCILLATOR_H_
