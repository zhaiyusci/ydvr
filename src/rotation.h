// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ROTATION_H
#define ROTATION_H
#include"mathtools.h"
#include"iotools.h"

/* @file
 */

namespace yDVR{
  /** @brief Rotational "potential" for diatomic systems
   */
  class RotationPotential1d:public DoubleFunction1d {
    private:
      double m_;
      int J_;
    public:
      /** @brief Compute the value
       *
       */
      double operator()(double x)const ;

      /** @brief Tell the user what it is
       */
      std::string what() const ;

      /** @brief Load the basic info
       */
      RotationPotential1d(double m, int J);

      /** @brief set the rotational quantum number J
       */
      int setJ(int J);

  };

  extern int rotationDVR(double m, const Eigen::VectorXd &x, const Eigen::MatrixXd &H, int maxJ, double E0);
}

#endif // ROTATION_H
