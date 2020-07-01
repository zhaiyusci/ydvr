// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_OSCILLATOR_TAYLOR_H_
#define YDVR_OSCILLATOR_TAYLOR_H_
#include"config.h"
#include"oscillator.h"
#include<vector>

namespace yDVR{
  /** @brief Simple one-dimension oscillator with potential energy using 
   * Taylor expension polynomial.
   */
  class OscillatorTaylor: public Oscillator{
    protected:
      std::vector<Scalar> force_constants_;
      const Scalar re_;

    public:
      /** @brief Constructor.
       *
       * @param mass The mass of the oscillator.
       * @param potential The potential energy function of the oscillator.
       */
      inline OscillatorTaylor(Scalar mass, Scalar re, std::vector<Scalar> force_constants)
        :  Oscillator(mass, nullptr),
        force_constants_(force_constants),
        re_(re)
        {
        }
      /** @brief Get the mass 
      */
      inline Scalar mass()const{ return mass_; }
      /** @brief Calculate the potential.
       *
       * @param q Coordinate at which the potential energy is calculated.
       */
      inline Scalar potential(Scalar q)const override{ 
        Scalar res = 0.;
        Scalar qe=q-re_;
        for (unsigned int i = 0; i < force_constants_.size(); ++i){
          // Note that Gamma(i+i) == i!
          // See https://en.cppreference.com/w/cpp/numeric/math/tgamma
          res += force_constants_[i] * pow(qe,i) / std::tgamma(i+1);
        }
        return res;
      }
      /** @brief Get the force constants
       */
      inline const std::vector<Scalar>& forceConstants() const {
        return force_constants_;
      }
      /** @brief Get the force constants
       */
      inline Scalar forceConstants(int i) const {
        return force_constants_[i];
      }
      /** @brief Get the omega, which is directly related to the second-order 
       * force constant, or, force constant, say, in the most condition.
       */
      inline Scalar omega() const{
        assert(force_constants_.size() >= 3); // 0, 1, 2
        return sqrt(force_constants_[2]/mass_); 
      }
      /** @brief Get the equlibrium bond length.
       */
      inline Scalar re() const{
        return re_;
      }
  };
}
#endif // YDVR_OSCILLATOR_TAYLOR_H_
