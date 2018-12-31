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
        wfi[i], MatrixXd& Hi_PODVR[i], potential[i]);
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
  // 1. Calculate the size of hamiltonian, indices, etc.
  mdindex mdindexi(NPO);
  mdindex mdindexj(mdindexi);
  MatrixXd H_energy=MatrixXd::Zero(mdindexi.max(),mdindexj.max());

  // 2. Calculate the 'raw' hamiltonian without high-order cross term
  // The value should be 
  // <i1|<i2|<i3|H1+H2+H3|j1>|j2>|j3>
  //=<i1|H1|j1><i2|j2><i3|j3>+<i2|H2|j2><i1|j1><i3|j3>+<i3|H3|j3><i1|j1><i2|j2>
  for(mdindexi.reset(); mdindexi.overflow()==0; ++mdindexi){
    for(mdindexj.reset(); mdindexj.overflow()==0; ++mdindexj){
      for(int i =0; i!=m.size(); ++i){
        int delta=1;
        for(int j =0; j!=m.size(); ++j){
          if(j!=i){
            if(mdindexi.current(j)!=mdindexj.current(j)){
              delta=0;
              break;
            }
          }
        }
        H_PODVR(mdindexi.current(),mdindexj.current())
          +=Hi_PODVR[i](mdindexi.current(i), mdindexj.current(i))*delta;
      }
    }
  }

  // 3. Add cross term potential to hamiltonian
  // Only diagonal elements has value
  for(mdindexi.reset(); mdindexi.overflow()==0; ++mdindexi){
    H_PODVR(mdindexi.current(),mdindexi.current())
      +=potential();
    for(int i=0; i!=m.size(); ++i){
    H_PODVR(mdindexi.current(),mdindexi.current())
      -=potential();
    }
  }

  // 4. Diagonalization
  SelfAdjointEigenSolver<MatrixXd> H_es(H_PODVR);
  E=H_es.eigenvalues();
  wf=H_es.eigenvectors();


  return 0;
}

