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

using namespace Eigen;
using namespace std;

extern double mel(const int& , const VectorXd& , const VectorXd& , const VectorXd& );

class DoubleFunction1d{
  public:
    virtual double calc(const double&) const =0;

};
class CubicSpline: public DoubleFunction1d {
  private:
    VectorXd x_;  
    VectorXd y_;
    VectorXd m_; // tangent value on each point
    int N_;    // grid number
  public:
    double calc(const double& )const ;
    CubicSpline(const int&, const VectorXd&, const VectorXd&, const double&, const double&);
};


#endif 
