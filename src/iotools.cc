// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"iotools.h"

using namespace Eigen;
using namespace std;

namespace yDVR{
  int printResults(const yVector &x, const yVector &E, const yMatrix &wf, yScalar E0){
    int N=x.size();
    cout << "Energy (in Eh)                  ";
    for(int i =0; i!=N; ++i) printf("  %14.8f",E(i)) ;
    cout <<endl;
    cout << "Gap (in 1/cm)                   ";
    for(int i =0; i!=N; ++i) printf("  %14.8f",(E(i)-E0)*219474.6313702) ;
    cout <<endl;
    cout << "Grid (in bohr)       (in Angs)    Eigenvector...";
    cout << endl;
    // cout <<E.transpose()<<endl;
    for(int i =0; i!=N; ++i) {
      printf("%14.8f  %14.8f  ",x(i), x(i)*0.52917721067) ;
      for(int j =0; j!=N; ++j) printf("  %14.8f",wf(i,j)) ;
      cout << endl;
    }
    cout <<"Averaged power of coordinates (in bohr, lowest 5 states, up to 5th order)"<<endl;
    printf("         ");
    for(int j=0; j!=5&&j!=N; ++j){
      printf("        %1d       ", j);
    }
    printf("\n");

    for(int i=1; i!=6; ++i){
      printf("<x^%1d>  ",i);
      for(int j=0; j!=5&&j!=N; ++j){
        printf("  %14.8f", mel(i, wf.col(j), x, wf.col(j)));
      }
      printf("\n");
    }

    return 0;
  } 
}
