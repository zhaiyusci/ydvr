// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_MD_PODVR_H_
#define YDVR_MD_PODVR_H_
#include"orthogonal_md_dvr.h"

namespace yDVR{
  /** @brief Simultaneous-Diagonalization DVR or Multi-Dimension PODVR.
   *
   * These class is following 
   * Richard Dawes, and Tucker Carrington
   * J. Chem. Phys. 121, 726 (2004). 
   *
   * It seems that SDDVR is the prefered name, however I still use MDPODVR here,
   * Because the idea behind consists with PODVR.
   * However, if you want, you can use SDDVR.
   */

  class MDPODVR : public AbstractRepresentation{
    protected:
      OrthogonalMDDVR* primitive_;
      int N_;
      std::vector<Vector> grids_;
      Matrix primitive_to_po_;
      void computeGrids();
      Scalar eps_;
    public:
      /** @brief Constructor.
       *
       * @param primitive Primitive representation.
       * @param N Total number of integration grids.
       * @param eps Convergence threshold of simultaneous diagonalization.
       */
      MDPODVR(OrthogonalMDDVR& primitive, int N, Scalar eps=1.e-6)
        : primitive_(&primitive), N_(N), 
        grids_(primitive_->dimension(),Vector(0)), eps_(eps)
      {}
      /** @brief Grids of the i'th dimension.
       *
       * @param i i'th dimesnion.
       */
      const Vector& grids(std::vector<Vector>::size_type i);
      /** @brief Kinetic Energy matrix.
       */
      virtual const Matrix& kineticMatrix(){return kinetic_matrix_;}
      /** @brief Potential Energy matrix.
       */
      virtual const Matrix& potentialMatrix(){return potential_matrix_;}
      /** @brief Hamiltonian matrix.
       */
      virtual const Matrix& hamiltonianMatrix();
      
  };

  /** @brief Alias of MDPODVR.
   */
  typedef MDPODVR SDDVR;
}

#endif
