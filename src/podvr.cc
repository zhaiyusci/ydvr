// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"podvr.h"
#include<chrono>

using namespace Eigen;
using namespace std;

namespace yDVR{
  int sincPODVR1d(yScalar m, int N, int NPO, yScalar a, yScalar b, const DoubleFunction1d& potential, 
      yVector& x, yVector& E, yMatrix& wf, yMatrix& H_PODVR){
    auto start=chrono::high_resolution_clock::now();
    cout << endl;
    cout << "============================= MODULE PODVR ============================="<<endl;
    cout << endl;
    cout << "Reference: "<<endl
      <<"  J. Echave and D. C. Clary, Chem. Phys. Lett. 190, 225 (1992) doi:10.1016/0009-2614(92)85330-D"<<endl;
    cout << endl;
    x.resize(NPO);
    E.resize(NPO);
    wf.resize(NPO,NPO);
    H_PODVR.resize(NPO,NPO);
    yVector pri_x; // "pri" here means primitive in 
    yVector pri_E;
    yMatrix pri_wf;
    yMatrix pri_H;
    cout << "1. Call sincDVR module to get primitive states on reference potential..."<<endl;
    sincDVR1d(m, N, a, b, potential, pri_x, pri_E, pri_wf, pri_H);
    cout << "done."<<endl;

    cout << "2. Calculate coordinate matrix..."<<flush;
    yMatrix X(NPO,NPO);
    for(int i=0; i!=NPO; ++i){
      for(int j=0; j!=i+1; ++j){
        X(i,j)=mel(1, pri_wf.col(i), pri_x, pri_wf.col(j)); // in 1D-sincDVR, we have (N-1) DVR points 
        X(j,i)=X(i,j);
      }
    }
    cout << "done." <<endl;
    // cout <<"Coordinate matrix on energy representation" << endl;
    // cout << X << endl;

    cout << "3. Calculate eigenvalues and vectors of coordinate matrix..."<<flush;
    SelfAdjointEigenSolver<yMatrix> X_es(X);
    x=X_es.eigenvalues();
    yMatrix podvrbasis=X_es.eigenvectors(); // we name it as "podvrbasis" and it is true, but the value here is the localized function on energy basis.
    cout << "done." << endl;

    cout << "4. Adjust signs..."<<flush;
    // Well... at this state you may find this just OK because the way we transform energy 
    // representation to PODVR representation is straight forward...
    // It is not true because you see that both Psi and -Psi are quasi-eigenvector of X
    // That is a severe problem when you represent the final wavefunction in PODVR representation
    // Here I prefer to let all the parameters for ground state to be positive
    //

    for(int i=0; i!=NPO; ++i){
      podvrbasis.col(i)*=podvrbasis(0,i)>0?1:-1;
    }
    cout << "done." << endl;

    yMatrix H_energy=yMatrix::Zero(NPO,NPO);
    for(int i=0; i!=NPO; ++i){
      H_energy(i,i)=pri_E(i); // on energy basis
      E(i)=pri_E(i);
    }
    H_PODVR= podvrbasis.transpose()*H_energy*podvrbasis; // on PODVR basis
    wf=podvrbasis.transpose();
    cout << "!!! PODVR results..."<<endl;

    printResults(x,E,wf,E(0));

    auto stop=chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "TIME USED IN THIS MODULE: " << duration.count()/1.0e6 << " sec."<< endl;
    cout << "========================= END OF MODULE PODVR =========================="<<endl;
    cout << endl;

    return 0;
  }
}

