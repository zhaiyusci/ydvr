// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PODVR_H
#define PODVR_H
#include"mathtools.h"
#include"sincdvr.h"

using namespace Eigen;

extern int sinc_podvr_1d(double , int ,int , double , double , VectorXd&, VectorXd&, MatrixXd&, MatrixXd&, const DoubleFunction1d&, bool);

#endif 
