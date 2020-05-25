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
  class OrthogonalMDDVR : public AbstractRepresentation{
    protected:
      OrthogonalMDOscillator* oscillator_;
      std::vector<DVR*> representations_;
      std::vector<int> number_of_grids_;
      const std::vector<int> NumberOfGrids();
      Scalar PrimitiveHamiltonianMatrixElement(const mdindex& i, const mdindex& j);
      Scalar PotentialCorrection(const mdindex& i);
      std::vector<Vector> grids_;
    public:
      OrthogonalMDDVR(OrthogonalMDOscillator& oscillator)
        : oscillator_(&oscillator), representations_(oscillator.dimension(), nullptr),
        number_of_grids_(), grids_(oscillator.dimension(), Vector(0))
      {
      }
      const Oscillator& OscillatorOfDimension(std::vector<Oscillator>::size_type i);
      void SetRepresentation(std::vector<DVR*>::size_type i, DVR& representation);
      virtual const Matrix& KineticMatrix(){return kinetic_matrix_;}
      virtual const Matrix& PotentialMatrix(){return potential_matrix_;}
      virtual const Matrix& HamiltonianMatrix();
      virtual const Matrix CoordinateMatrix(std::vector<Vector>::size_type i);
      virtual ~OrthogonalMDDVR(){};
      size_t dimension(){ return oscillator_->dimension(); }
  };
}
#endif //YDVR_ORTHOGONAL_MD_DVR_H_
