// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
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
  typedef Eigen::Matrix<_YDVR_SCALAR, Eigen::Dynamic, Eigen::Dynamic> yMatrix;
  typedef Eigen::Matrix<_YDVR_SCALAR, Eigen::Dynamic, 1> yVector;
  typedef _YDVR_SCALAR yScalar;


  extern yScalar mel(const int, const yVector& , const yVector& , const yVector& );

  /** @brief Pure virtual class defines the one-dimension function in math.
  */
  class DoubleFunction1d{
    public:
      /** @brief Perform the calculation.
      */
      virtual yScalar operator() (yScalar x) const =0;
      /** @brief Show the 'about' information.
      */
      virtual std::string what() const =0;
  };

  /** @brief One-dimension cubic Hermite spline interpolation function.
   *
   * One-dimension [cubic Hermite spline](https://en.wikipedia.org/wiki/Cubic_Hermite_spline).
   */
  class CubicSpline1d: public DoubleFunction1d {
    private:
      yVector x_;  
      yVector y_;
      yVector m_; // tangent value on each point
      int N_;    // grid number
    public:
      /** @brief Perform interpolation calculation
       *
       * There are some variant, maybe.  Here, we follow wikipedia.  [The formulae](https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Interpolation_on_an_arbitrary_interval).
       */
      yScalar operator()(yScalar x)const ;
      /** @brief Loading data.
       *
       * The tangents are calculated in this function using [finite difference method](https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Finite_difference).
       * @param N length of pointwise data.
       * @param x input variables. It is required that it is sorted.
       * @param y output variables.
       * @param mi tangent on the first point.
       * @param mf tangent on the final point.
       */
      CubicSpline1d(int N, const yVector& x, const yVector& y, yScalar mi, yScalar mf);
      /** @brief Show 'about' information
      */
      std::string what() const ;
  };

}
#endif 
