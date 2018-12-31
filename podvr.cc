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

int sinc_podvr_1d(double m, int N, int NPO, double a, double b, VectorXd& x, VectorXd& E, MatrixXd& wf, MatrixXd& H_PODVR, const DoubleFunction1d& potential){
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
  VectorXd pri_x; // "pri" here means primitive in 
  VectorXd pri_E;
  MatrixXd pri_wf;
  MatrixXd pri_T_energy;
  cout << "1. Call sincDVR module to get primitive states on reference potential..."<<endl;
  sinc_dvr_1d(m, N, a, b, pri_x, pri_E, pri_wf, potential);
  cout << "done."<<endl;

  cout << "2. Calculate coordinate matrix..."<<flush;
  MatrixXd X(NPO,NPO);
  for(int i=0; i!=NPO; ++i){
    for(int j=0; j!=i+1; ++j){
      X(i,j)=mel(1, pri_wf.col(i), pri_x, pri_wf.col(j)); // in 1D-sincDVR, we have (N-1) DVR points 
      X(j,i)=X(i,j);
    }
  }
  cout << "done." <<endl;
  cout <<"Coordinate matrix on energy representation" << endl;
  cout << X << endl;

  cout << "3. Calculate eigenvalues and vectors of coordinate matrix..."<<flush;
  SelfAdjointEigenSolver<MatrixXd> X_es(X);
  x=X_es.eigenvalues();
  MatrixXd podvrbasis=X_es.eigenvectors(); // we name it as "podvrbasis" and it is true, but the value here is the localized function on energy basis.
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

  MatrixXd H_energy=MatrixXd::Zero(NPO,NPO);
  for(int i=0; i!=NPO; ++i){
    H_energy(i,i)=pri_E(i); // on energy basis
    E(i)=pri_E(i);
  }
  H_PODVR= podvrbasis.transpose()*H_energy*podvrbasis; // on PODVR basis
  wf=podvrbasis.transpose();
  cout << "!!! PODVR results..."<<endl;
  cout << "Energy (in Eh)                  ";
  for(int i =0; i!=NPO; ++i) printf("  %14.8f",E(i)) ;
  cout <<endl;
  cout << "Gap (in 1/cm)                   ";
  for(int i =0; i!=NPO; ++i) printf("  %14.12g",(E(i)-E(0))*219474.6313702) ;
  cout <<endl;
  cout << "Grid (in bohr)       (in Angs)    Eigenvector...";
  cout << endl;
  // cout <<E.transpose()<<endl;
  for(int i =0; i!=NPO; ++i) {
    printf("%14.8f  %14.8f  ",x(i), x(i)*0.52917721067) ;
    for(int j =0; j!=NPO; ++j) printf("  %14.8f",wf(i,j)) ;
    cout << endl;
  }
  cout <<"Averaged power of coordinates (in bohr, lowest 5 states, up to 5th order)"<<endl;
  printf("         ");
  for(int j=0; j!=5&&j!=NPO; ++j){
    printf("        %1d       ", j);
  }
  printf("\n");

  for(int i=1; i!=6; ++i){
    printf("<x^%1d>  ",i);
    for(int j=0; j!=5&&j!=NPO; ++j){
      printf("  %14.8f", mel(i, wf.col(j), x, wf.col(j)));
    }
    printf("\n");
  }
  auto stop=chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << "TIME USED IN THIS MODULE: " << duration.count()/1.0e6 << " sec."<< endl;
  cout << "========================= END OF MODULE PODVR =========================="<<endl;
  cout << endl;

  return 0;
}

