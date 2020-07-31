// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_OSCILLATOR_H_
#define YDVR_OSCILLATOR_H_
#include"config.hh"
// #include"orthogonal_md_oscillator.hh"

namespace yDVR{
  /** @brief Simple one-dimension oscillator.
   */
  class Oscillator{
    protected:
      Scalar mass_;
      std::function<Scalar(Scalar)> potential_;
    public:
      /** @brief Constructor.
       *
       * @param mass The mass of the oscillator.
       * @param potential The potential energy function of the oscillator.
       */
      inline Oscillator(Scalar mass, std::function<Scalar(Scalar)> potential)
        :   mass_(mass),
            potential_(potential)
        {
        }
      /** @brief Get the mass 
      */
      inline Scalar mass()const{ return mass_; }
      /** @brief Calculate the potential.
       *
       * @param q Coordinate at which the potential energy is calculated.
       */
      inline virtual Scalar potential(Scalar q)const{ 
        return potential_(q); 
      }
      virtual ~Oscillator(){}
  };
}
#endif // YDVR_OSCILLATOR_H_
