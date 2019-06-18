// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ABINITIO_H
#define ABINITIO_H
#include<iostream>
#include<exception>
#include<stdexcept>
#include<Eigen/Dense>
#include<Eigen/Eigenvalues>
#include<cstring>
#include<cmath>
#include<vector>
#include<string>

class Abinitio{
  public:
    virtual double calc( const std::vector< std::string > &, const Eigen::MatrixXd &) const =0;
    virtual void printInfo()const;
};

class OrcaInterface:public Abinitio{
  private:
    std::string theory_;
    std::string basis_;
  public:
    void printInfo() const;
    double calc( const std::vector< std::string > &, const Eigen::MatrixXd &) const ;
    OrcaInterface(const std::string &, const std::string &);
};



#endif 
