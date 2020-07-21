// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_PODVR_H_
#define YDVR_PODVR_H_
#include"dvr.h"

namespace yDVR{
  /** @brief Potential Optimized Discrete Variable Representation
   *
   * Ref: 
   * J. Echave and D. C. Clary, Chem. Phys. Lett. 190, 225 (1992) 
   * doi:10.1016/0009-2614(92)85330-D
   */
  class PODVR : public DVR{
    protected:
      int N_; // default value 10
      DVR* primitive_;
      Matrix primitive_to_po_;
    public:
  /** @brief Constructor.
   *
   * @param primitive Pointer to the DVR which is the base of PODVR.  E.g., you can perform a sinc-DVR as the primitive calculation.
   * @param N Number of PODVR grids.
   */
      PODVR( DVR& primitive,
          int N);
  /** @brief Kinetic energy matrix on PO-DVR.
   */
      virtual const Matrix& kineticMatrix() override;
  /** @brief Hamiltonian matrix on PO-DVR.
   *
   * Overwrite definition of representation.
   */
      virtual const Matrix& hamiltonianMatrix() override;
  /** @brief PODVR grids.
   */
      virtual const Vector& grids() override;
  };
}

#endif 
