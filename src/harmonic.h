// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_HARMONIC_H_
#define YDVR_HARMONIC_H_
#include"representation.h"
#include"oscillator_taylor.h"

/* @file
 */

namespace yDVR{
  /** @brief Sinc Discrete Variable Representation
   *
   * Ref:
   * D. T. Colbert and W. H. Miller, J. Chem. Phys. 96, 1982 (1992) 
   * doi:10.1063/1.462100
   */
  class HarmonicRepresentation : public Representation{
    protected:
      const int N_;
      Scalar beta_;
      std::vector<Matrix> coordinate_matrices_;
      Matrix constructCoordinateMatrix(int i);
      const OscillatorTaylor* oscillator_taylor_;
    public:
      /** @brief Constructor.
       *
       * @param oscillator The oscillator.
       * @param N Number of basis functions.
       */
      HarmonicRepresentation(const OscillatorTaylor& oscillator, int N);
      /** @brief Kinetic energy matrix.
       */
      virtual const Matrix& kineticMatrix() override;
      /** @brief Potential energy matrix.
       */
      virtual const Matrix& potentialMatrix() override;
      /** @brief Coordinate matrix.
       */
      const Matrix& coordinateMatrix();
      /** @brief Matrix of coordinate to i'th power.
       */
      const Matrix& coordinateMatrix(int i);
      /** Destructor
       */
      ~HarmonicRepresentation(){}
  };
}

#endif // YDVR_HARMONIC_H_
