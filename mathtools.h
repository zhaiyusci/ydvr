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

extern double mel(int , const Eigen::VectorXd& , const Eigen::VectorXd& , const Eigen::VectorXd& );

class DoubleFunction1d{
  public:
    virtual double calc(double) const =0;
};

class DoubleFunctionmd;

class CuttedPotential1d: public DoubleFunction1d{
  private:
    Eigen::VectorXd xe_;
    Eigen::VectorXd deltax_;
    DoubleFunctionmd* funcmd_;
  public:
    double calc(double) const;
    CuttedPotential1d(const Eigen::VectorXd&, const Eigen::VectorXd&, DoubleFunctionmd* funcmd_);
};

class DoubleFunctionmd{
  public:
    virtual double calc(const Eigen::VectorXd&) const =0;
    CuttedPotential1d linearcut(const Eigen::VectorXd&, const Eigen::VectorXd&);
};

class CubicSpline1d: public DoubleFunction1d {
  private:
    Eigen::VectorXd x_;  
    Eigen::VectorXd y_;
    Eigen::VectorXd m_; // tangent value on each point
    int N_;    // grid number
  public:
    double calc(double)const ;
    CubicSpline1d(int, const Eigen::VectorXd&, const Eigen::VectorXd&, double, double);
};


#endif 
