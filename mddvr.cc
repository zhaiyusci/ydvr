// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"mddvr.h"

using namespace Eigen;
using namespace std;

int sinc_podvr_md(const vector<double>& m, const vector<int>& N, const vector<int>& NPO, const vector<double>& a, const vecotr<double>& b, vector<VectorXd>& x, VectorXd& E, MatrixXd& wf, MatrixXd& H_PODVR, const DoubleFunction1d& potential){
  // Here m is the vector that stores effective masses of each orthogonal 
  // vibrational modes, N the primitive basis set size, NPO PODVR grids number
  // a, b the starting and ending point...
  //
  // Below three xxi's are for 1d problems.
  vector<VectorXd> Ei(m.size());
  vector<MatrixXd> wfi(m.size());
  vector<MatrixXd> Hi_PODVR(m.size());
  //
  // 1. Perform (size of m) 1d podvr.  
  for(int i=0; i!=m.size(); ++i){
    sinc_podvr_1d(m[i], N[i], NPO[i], a[i], b[i], x[i], Ei[i], 
        wfi[i], MatrixXd& Hi_PODVR, potential);
    cout << "========================================================================"<<endl;
    cout << "Dimension " << i << ":"<<endl;
    cout << "PODVR grids (in bohr):"<<endl;
    cout << x[i]<<endl;
    cout <<"Energy levels (in Hartree):"<<endl;
    cout << Ei[i]<<endl;
    cout << "Eigenstate on PODVR:"<<endl;
    cout <<wfi[i]<<endl;
    cout << "========================================================================"<<endl;

  }

  // Construct the md hamiltonian on PODVR grids
  // 1. Calcu



  return 0;
}

