// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MOLECULE_H
#define MOLECULE_H
#include<iostream>
#include<exception>
#include<stdexcept>
#include<Eigen/Dense>
#include<Eigen/Eigenvalues>
#include<cstring>
#include<cmath>
#include<vector>
#include<string>

class Molecule{
  private:
    int n_atom_; // number of atoms
    int n_mode_; // number of vibrational modes
    std::vector< std::string > atom_; // name of atoms
    Eigen::MatrixXd re_; // stationary point geometry
    std::vector< Eigen::MatrixXd > xi_; // vibrational modes
    Eigen::MatrixXd r_; // current geometry
    // double (*abInitio) (const std::string&, const std::string&, const Eigen::MatrixXd&); 
    // point to an ab initio package?
    Abinitio * ab_initio_; // point to an ab initio package interface

  public:
    // Constructors:
    Molecule(std::vector< std::string >& , const Eigen::MatrixXd& , const std::vector< Eigen::MatrixXd >& );
    int readOptimization() ;
    // Change geometry:
    int moveByMode(int, double);
    int reset();
    // Get potential energy:
    double setPotentialMethod(const std::string &, const std::string &, const std::string &);
    double potential();
};




#endif 
