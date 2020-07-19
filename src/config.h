// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_CONFIG_H_
#define YDVR_CONFIG_H_

#include<Eigen/Dense>
#include<Eigen/Sparse>
#include<Eigen/Eigenvalues>

/** @brief All functions and class in %yDVR package.
 */
namespace yDVR{
  // Define precise used in yDVR
  typedef double Scalar; // ... can change here

  /* @brief Define Linear Algebra classes, user may want different linear algebra library
   */
  typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> Matrix;
  typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> ColVector;
  typedef ColVector Vector;
  typedef Eigen::Matrix<Scalar, 1, Eigen::Dynamic> RowVector;
  typedef Eigen::SelfAdjointEigenSolver<Matrix> SelfAdjointEigenSolver;
  typedef Eigen::Matrix<Scalar, 2, 2> Matrix2d;
  typedef Eigen::Matrix<Scalar, 2, 1> Vector2d;
  typedef Eigen::SelfAdjointEigenSolver<Matrix2d> SelfAdjointEigenSolver2d;
  typedef Eigen::SparseMatrix<Scalar> SparseMatrix;

}
#define LOG Log::get()

#endif // YDVR_CONFIG_H_
