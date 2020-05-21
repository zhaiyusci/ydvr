// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_STATIONARY_STATE_H_
#define YDVR_STATIONARY_STATE_H_

#include"config.h"

namespace yDVR{
  class AbstractRepresentation;
  /** @brief Stationary state.
   */
  class StationaryState{
    protected:
      Scalar energy_;
      Vector ket_;
      AbstractRepresentation* representation_;
    public:
      /** @brief Stationary state.
       *
       * @param energy Energy of the state.
       * @param ket The normalized eigenvector of the state.
       * @param representation The coresponding representation.
      */
      inline StationaryState(Scalar energy, Vector ket, AbstractRepresentation* representation)
        : energy_(energy), ket_(ket), representation_(representation){}
      /** @brief Energy.
       */
      inline Scalar energy() const { return energy_; }
      /** @brief ket vector.
       */
      inline Vector ket() const { return ket_; }
      /** @brief bra vector.
       */
      inline RowVector bra() const { return ket_.adjoint(); }
      /** @brief i'th element of the ket vector.
       */
      inline Scalar ket(int i) const { return ket_(i); }
      // TODO: good for real number but ...
      /** @brief i'th element of the bra vector.
       */
      inline Scalar bra(int i) const { return ket_(i); } 
  };
}

#endif
