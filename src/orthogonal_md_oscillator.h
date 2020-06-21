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
      void split();
      std::vector<Oscillator*> oscillators_;
      std::vector<Scalar> equilibrium_;
    public:
      /** @brief Constructor.
       *
       * @param mass Vector of mass 
       * @param potential The potential function, whose parameter is vector formed by the coordinates
       *
       * The user should make sure the dimension of the two part are identical.
       */
      OrthogonalMDOscillator(const std::vector<Scalar>& mass, std::function<Scalar(const std::vector<Scalar>&)> potential):
        MDOscillator(mass, potential), equilibrium_(mass.size(), 0.)
    { }
      /** @brief Constructor for uniform mass case.
       *
       * @param dimension
       * @param mass 
       * @param potential The potential function, whose parameter is vector formed by the coordinates
       *
       * The user should make sure the dimension of the two part are identical.
       */
      OrthogonalMDOscillator(int dimension, Scalar mass, std::function<Scalar(const std::vector<Scalar>&)> potential):
        MDOscillator(dimension, mass, potential), equilibrium_(dimension, 0.)
    {}
      /** @brief i'th one-dimension oscillator.
       */
      const Oscillator& oneDimension(int i);

      /** @brief Virtual destructor.
       */
      virtual ~OrthogonalMDOscillator(){
        for(auto && i : oscillators_){
          delete i;
        }
      };
  };

}

#endif //  YDVR_ORTHOGONAL_MD_OSCILLATOR_H_
