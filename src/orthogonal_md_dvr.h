// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_ORTHOGONAL_MD_DVR_H_
#define YDVR_ORTHOGONAL_MD_DVR_H_

#include"config.h"
#include"abstract_representation.h"
#include"dvr.h"
#include"orthogonal_md_oscillator.h"

class mdindex;
namespace yDVR{
  /** @brief Multi-dimension DVR where coordinates are orthogonal, like normal modes.
   *
   * Or, you can say that this class is a direct-product DVR.
   * It can take any-dimension DVR as if your RAM is big enough (and time is adequate.).
   */
  class OrthogonalMDDVR : public AbstractRepresentation{
    protected:
      OrthogonalMDOscillator* oscillator_;
      std::vector<DVR*> representations_;
      std::vector<int> number_of_grids_;
      const std::vector<int> numberOfGrids();
      Scalar primitiveHamiltonianMatrixElement(const mdindex& i, const mdindex& j);
      Scalar potentialCorrection(const mdindex& i);
      std::vector<Vector> grids_;
    public:
      /** @brief Constructor.
       *
       * @param oscillator OrthogonalMDOscillator
       */
      OrthogonalMDDVR(OrthogonalMDOscillator& oscillator)
        : oscillator_(&oscillator), representations_(oscillator.dimension(), nullptr),
        number_of_grids_(), grids_(oscillator.dimension(), Vector(0))
      {
      }
      /** @brief 1D oscillator of the dimesnion i
       *
       * @param i i'th dimension
       */
      const Oscillator& oscillatorOfDimension(std::vector<Oscillator>::size_type i);
      /** @brief Set the 1D representation of the dimesnion i
       *
       * @param i i'th dimension
       */
      void setRepresentation(std::vector<DVR*>::size_type i, DVR& representation);
      /** @brief Kinetic energy
       *
       * It is not written actually.  Bad design here. TODO: Refactor.
       */
      virtual const Matrix& kineticMatrix(){return kinetic_matrix_;}
      /** @brief Potential energy
       *
       * It is not written actually.  Bad design here. TODO: Refactor.
       */
      virtual const Matrix& potentialMatrix(){return potential_matrix_;}
      /** @brief Hamiltonian matrix
       *
       * Calculate directly from containing 1D representations. 
       * It will not call potential and kinetic energy.
       */
      virtual const Matrix& hamiltonianMatrix();
      /** @brief Coordinate matrix of dimesnion i
       *
       * @param i i'th dimension
       */
      virtual const Matrix coordinateMatrix(std::vector<Vector>::size_type i);
      /** @brief Destructor.
       */
      virtual ~OrthogonalMDDVR(){};
      /** @brief Number of dimesnion
       */
      size_t dimension(){ return oscillator_->dimension(); }
  };
}
#endif //YDVR_ORTHOGONAL_MD_DVR_H_
