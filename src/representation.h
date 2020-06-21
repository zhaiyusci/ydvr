// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_REPRESENTATION_H_
#define YDVR_REPRESENTATION_H_

#include<iostream>
#include<vector>
#include"config.h"
#include"stationary_state.h"
#include"abstract_representation.h"
#include"oscillator.h"

/* @file
 */

namespace yDVR{
  /** @brief Pure virtual class define the interface of a representation.
  */
  class Representation : public AbstractRepresentation{
    protected:
      const Oscillator* oscillator_;
    public:
      /** @brief Constructor
      */
      Representation(const Oscillator& oscillator): 
        AbstractRepresentation(),
        oscillator_(&oscillator){}
      /** @brief Distructor.
      */
      virtual ~Representation(){}
      /** @brief Return pointer to its oscillator.
      */
      inline const Oscillator& oscillator(){return *oscillator_;}
  };
}
#endif //  YDVR_REPRESENTATION_H_
