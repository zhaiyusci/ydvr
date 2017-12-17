// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"sincdvr.h"

using namespace Eigen;
using namespace std;

int sinc_dvr_1d(double m, int N, double a, double b, VectorXd &x, VectorXd &E, MatrixXd &wf_DVR, MatrixXd &T_energy, const DoubleFunction1d& potential){ 
  //follow J. Chem. Phys. 96, 1982 (1992) Appendix A
  try{
    if (N<3){
      throw runtime_error("N is too small!!!");
    }
  }
  catch (runtime_error err){
    if(0==strcmp(err.what(),"N is too small!!!")){
      cerr<<"RUNTIME ERROR: "<<__FILE__ <<": l."<< __LINE__<<":"<<" "; 
      cerr<< err.what()<<endl; 
      return -1;
    }
  }
  // (N-1) DVR points, and N intervals
  x.resize(N-1); // DVR point
  E.resize(N-1); // Final energy
  wf_DVR.resize(N-1,N-1); // Final wave function
  MatrixXd T_DVR(N-1,N-1); // Kinetic matrix in DVR representation

  double deltax=(b-a)/N; 
  for(int i=1;i!=N;++i){ 
    // I try to follow the way they write the paper, however, you know it is C++
    // here the x(i-1) thing is x(i) in their paper and the reason is that in C-like language the 
    // index start from 0
    // ... so here I only change the index
    x(i-1)=a+deltax*i;
  }

  MatrixXd H_DVR(N-1,N-1); //Hamiltonian in DVR ...
  // in the paper it is i' but I think using j is a better idea
  // For i!=j ... 
  for(int i=1; i!=N; ++i){
    for(int j=1;j!=i; ++j){
      T_DVR(i-1,j-1)=1.0/(2*m)
        *pow(-1,i-j)/pow(b-a,2)
        *M_PI*M_PI/2.0
        *(
            1/pow(sin(M_PI*(i-j)/(2*N)),2)
            -1/pow(sin(M_PI*(i+j)/(2*N)),2)
         );
      T_DVR(j-1,i-1)=T_DVR(i-1,j-1);
      H_DVR(i-1,j-1)=T_DVR(i-1,j-1);
      H_DVR(j-1,i-1)=T_DVR(j-1,i-1);
    }
  }
  // For i==j
  for(int i=1; i!=N; ++i){
    T_DVR(i-1,i-1)=1.0/(2*m)
      *1.0/pow(b-a,2)
      *M_PI*M_PI/2.0
      *(
          (2.0*N*N+1.0)/3.0
          -1/pow(sin(M_PI*i/N),2)
       );
    H_DVR(i-1,i-1)=T_DVR(i-1,i-1)+potential.calc(x(i-1));
    // cerr << "sincdvr>> " << potential.calc(x(i-1)) << endl;
  }

  SelfAdjointEigenSolver<MatrixXd> H_es(H_DVR);

  E=H_es.eigenvalues();
  wf_DVR=H_es.eigenvectors();
  T_energy=wf_DVR.transpose()*T_DVR*wf_DVR;

  return 0;
} 
