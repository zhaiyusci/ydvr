// This file is part of ydvr.
//
// Copyright (C) 2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MATHTOOLS_H
#define MATHTOOLS_H
#include<iostream>
#include<exception>
#include<stdexcept>
#include<Eigen/Dense>
#include<Eigen/Eigenvalues>
#include<cstring>
#include<cmath>
#include<vector>

/** @brief All functions and class in %yDVR package.
 */
namespace yDVR{
  typedef __YDVR_SCALAR__ Scalar;
  typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> Matrix;
  typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> ColVector;
  typedef ColVector Vector;
  typedef Eigen::Matrix<Scalar, 1, Eigen::Dynamic> RowVector;
  typedef Eigen::SelfAdjointEigenSolver<Matrix> SelfAdjointEigenSolver;


  extern Scalar mel(const int, const Vector& , const Vector& , const Vector& );

  /** @brief One-dimension cubic Hermite spline interpolation function.
   *
   * One-dimension [cubic Hermite spline](https://en.wikipedia.org/wiki/Cubic_Hermite_spline).
   */
  class CubicSpline1d {
    private:
      Vector x_;  
      Vector y_;
      Vector m_; // tangent value on each point
      int N_;    // grid number
    public:
      /** @brief Perform interpolation calculation
       *
       * There are some variant, maybe.  Here, we follow wikipedia.  [The formulae](https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Interpolation_on_an_arbitrary_interval).
       */
      Scalar operator()(Scalar x) const ;
      /** @brief Loading data.
       *
       * The tangents are calculated in this function using [finite difference method](https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Finite_difference).
       * @param N length of pointwise data.
       * @param x input variables. It is required that it is sorted.
       * @param y output variables.
       * @param mi tangent on the first point.
       * @param mf tangent on the final point.
       */
      CubicSpline1d(int N, const Vector& x, const Vector& y, Scalar mi, Scalar mf);
  };

}
#endif 
