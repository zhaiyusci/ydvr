// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"molecule.h"
#include<stdexcept>

using namespace std;
using namespace Eigen;

Molecule::Molecule(vector< string >& atom, const MatrixXd& re, const vector< MatrixXd >& xi){
  atom_=atom;
  re_=re;
  xi_=xi;
  n_atom_=atom_.size();
  n_mode_=xi_.size();
  if (n_atom_!=re_.cols()) throw runtime_error("Number of atoms and coordinates do not match!");
}

int Molecule::reset(){
  r_=re_;
  return 0;
}

int Molecule::moveByMode(int k, double Q_k){
  r_+=xi_[k]*Q_k;
  return 0;
}

