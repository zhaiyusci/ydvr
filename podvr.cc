// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"podvr.h"

using namespace Eigen;
using namespace std;

int sinc_podvr_1d(double m, int N, int NPO, double a, double b, VectorXd& x, VectorXd& E, MatrixXd& wf, MatrixXd& H_PODVR, const DoubleFunction1d& potential){
  // Pontential optimization part follow Chem. Phys. Lett. 190, 225 (1992)
  x.resize(NPO);
  E.resize(NPO);
  wf.resize(NPO,NPO);
  H_PODVR.resize(NPO,NPO);
  VectorXd pri_x; // "pri" here means primitive in 
  VectorXd pri_E;
  MatrixXd pri_wf;
  MatrixXd pri_T_energy;
  sinc_dvr_1d(m, N, a, b, pri_x, pri_E, pri_wf, pri_T_energy, potential);

  MatrixXd X(NPO,NPO);
  for(int i=0; i!=NPO; ++i){
    for(int j=0; j!=i+1; ++j){
      X(i,j)=mel(N-1, pri_wf.col(i), pri_x, pri_wf.col(j)); // in 1D-sincDVR, we have (N-1) DVR points 
      X(j,i)=X(i,j);
    }
  }

  SelfAdjointEigenSolver<MatrixXd> X_es(X);
  x=X_es.eigenvalues();
  MatrixXd podvrbasis=X_es.eigenvectors(); // we name it as "podvrbasis" and it is true, but the value here is the localized function on energy basis.

  // Well... at this state you may find this just OK because the way we transform energy 
  // representation to PODVR representation is straight forward...
  // It is not true because you see that both Psi and -Psi are quasi-eigenvector of X
  // That is a severe problem when you represent the final wavefunction in PODVR representation
  // Here I prefer to let all the parameters for ground state to be positive
  //

  for(int i=0; i!=NPO; ++i){
    podvrbasis.col(i)*=podvrbasis(0,i)>0?1:-1;
  }

  MatrixXd H_energy=MatrixXd::Zero(NPO,NPO);
  for(int i=0; i!=NPO; ++i){
    H_energy(i,i)=pri_E(i); // on energy basis
    E(i)=pri_E(i);
  }
  H_PODVR= podvrbasis.transpose()*H_energy*podvrbasis; // on PODVR basis
  wf=podvrbasis.transpose();

  return 0;
}

