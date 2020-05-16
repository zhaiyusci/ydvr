// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"sincdvr.h"
#include<chrono>

namespace yDVR{
  Vector SincDVR::Grids(){
    if(grids_.size() == 0){
      std::cout << "Calculate DVR grids..." << std::flush;
      Scalar deltax=(b_-a_)/N_; 
      for(int i = 1; i < N_; ++i){ 
        // I try to follow the way they write the paper, however, you know it is C++
        // here the x(i-1) thing is x(i) in their paper 
        // and the reason is that in C-like language the 
        // index start from 0
        // ... so here I only change the index
        grids_(i-1)=a_+deltax*i;
      }
      std::cout << "done." << std::endl;
    }
    return grids_;
  }

  Matrix SincDVR::KineticMatrix(){
    if(kinetic_matrix_.cols() == 0){
      std::cout << "Calculate kinetic matrix..." << std::flush;
      Scalar deltax=(b_-a_)/N_; 
      Scalar m=oscillator_->mass();
      kinetic_matrix_.resize(N_-1, N_-1); 
      // in the paper it is i' but I think using j is a better idea
      // For i!=j ... 
      for(int i=1; i<N_; ++i){
        for(int j=1;j<i; ++j){
          kinetic_matrix_(i-1,j-1)
            =1.0/(2*m*pow(deltax,2))*pow(-1,(i-j))*2/pow((i-j),2);
          kinetic_matrix_(j-1,i-1)=kinetic_matrix_(i-1,j-1);
        }
      }
      // For i==j
      for(int i=1; i<N_; ++i){
        kinetic_matrix_(i-1,i-1)
          =1.0/(2*m*pow(deltax,2))*pow(M_PI,2)/3.0;
      }
      std::cout << "done." << std::endl;
    }
    return kinetic_matrix_;
  }

  SincDVR::SincDVR(Oscillator* oscillator, Scalar a, Scalar b, int N):
    DiscreteVariableRepresentation(oscillator), a_(a), b_(b), N_(N){}

  /*
  int sincDVR1d(yScalar m, int N, yScalar a, yScalar b, const DoubleFunction1d& potential, // in
      yVector &x, yVector &E, yMatrix &wf_sincDVR, yMatrix &H_sincDVR){ // out
    auto start=chrono::high_resolution_clock::now();
    cout << endl;
    cout << "============================ MODULE sincDVR ============================"<<endl;
    cout << endl;
    cout << "Reference: "<<endl
      <<"  D. T. Colbert and W. H. Miller, J. Chem. Phys. 96, 1982 (1992) doi:10.1063/1.462100"<<endl;
    cout << endl;
    //follow J. Chem. Phys. 96, 1982 (1992) Appendix A
    // (N-1) DVR points, and N intervals
    x.resize(N-1); // DVR point
    E.resize(N-1); // Final energy
    wf_sincDVR.resize(N-1,N-1); // Final wave function

    cout << "1. Calculate DVR grids..." << flush;
    yScalar deltax=(b-a)/N; 
    for(int i=1;i!=N;++i){ 
      // I try to follow the way they write the paper, however, you know it is C++
      // here the x(i-1) thing is x(i) in their paper 
      // and the reason is that in C-like language the 
      // index start from 0
      // ... so here I only change the index
      x(i-1)=a+deltax*i;
    }
    cout << "done." << endl;

    cout << "2. Calculate Hamiltonian matrix..." << flush;
    H_sincDVR.resize(N-1,N-1); // Hamiltonian
    // in the paper it is i' but I think using j is a better idea
    // For i!=j ... 
    for(int i=1; i!=N; ++i){
      for(int j=1;j!=i; ++j){
        H_sincDVR(i-1,j-1)=1.0/(2*m*pow(deltax,2))*pow(-1,(i-j))*2/pow((i-j),2);
        H_sincDVR(j-1,i-1)=H_sincDVR(i-1,j-1);
      }
    }
    // For i==j
    for(int i=1; i!=N; ++i){
      H_sincDVR(i-1,i-1)=1.0/(2*m*pow(deltax,2))*pow(M_PI,2)/3.0;
      H_sincDVR(i-1,i-1)=H_sincDVR(i-1,i-1)+potential(x(i-1));
    }
    cout << "done." << endl;
    // cout <<"Hamiltonian matrix on sincDVR " << endl;
    // cout << H_sincDVR << endl;

    cout << "3. Calculate eigenvalues and vectors of Hamiltonian..."<<flush;
    SelfAdjointEigenSolver<yMatrix> H_es(H_sincDVR);

    E=H_es.eigenvalues();
    wf_sincDVR=H_es.eigenvectors();
    cout << "done." << endl;
    // cout << "PODVR grids (in bohr):"<<endl;
    // cout << x<<endl;
    cout << "!!! sincDVR results..."<<endl;

    printResults(x, E, wf_sincDVR, E(0));


    auto stop=chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "TIME USED IN THIS MODULE: " << duration.count()/1.0e6 << " sec."<< endl;
    cout << "======================== END OF MODULE sincDVR ========================="<<endl;
    cout << endl;

    return 0;
  } 
  */
}
