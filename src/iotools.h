// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"mathtools.h"
#include<cstdio>

namespace yDVR{

  /** @brief Print result of DVR calculation
   * @param[in] x ...
   */
  extern int printResults(const Eigen::VectorXd &x, const Eigen::VectorXd &E, const Eigen::MatrixXd &wf, double E0);
}
