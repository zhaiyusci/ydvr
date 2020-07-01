// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"ydvr.h"
#include"co_pes_2016/co_pes_2016.h"

using namespace std;
using namespace yDVR;
int main(){
  Log::set("harmonic_test.out");
  Oscillator codvr(6.856208638000723*1822.888486209, [](double r){return copes(r/1.8897261254578281)/219474.6313702;});
  /*
  for (double i=0.1; i<=5; i+=0.02){
    // cout << i << "\t"<<  co.potential(i)<< endl;
    printf("%5.2f  %20.8f\n", i, co.potential(i));
  }
  return 0;
  */


  std::vector<Scalar> force_c;
  double re = 1.128322531930*1.8897261254578281;
  double h = 1e-3;
  double f_2=codvr.potential(re-2*h);
  double f_1=codvr.potential(re-1*h);
  double f0=codvr.potential(re);
  double f1=codvr.potential(re+1*h);
  double f2=codvr.potential(re+2*h);
  force_c.push_back(f0);
  force_c.push_back(0.5/h*(f1-f_1));
  force_c.push_back(1./h/h*(f1+f_1-2*f0));
  force_c.push_back(0.5/h/h/h*(f2-2*f1-f_2+2*f_1));
  force_c.push_back(1./h/h/h/h*(f2+f_2-4*f1-4*f_1+6*f0));
  // OscillatorTaylor co(6.856208638000723*1822.888486209, 1.128322531930*1.8897261254578281,std::vector<Scalar>({ -5.85609722286001e-6, -0.00030408969010246, 1.2763754717476, -3.4325237870851, 3.5759687701914}));
  OscillatorTaylor co(6.856208638000723*1822.888486209, re, force_c);
  // for (double i=-0.5; i<=0.5; i+=0.02){
    // printf("%5.2f  %20.8f\n", i, co.potential(i));
  // }
  // return 0;
  // OscillatorTaylor co(6.856208638000723*1822.888486209, std::vector<Scalar>({ 
        // 0.,
        // 0.,
        // 1.2763754717476
        // }));
  HarmonicRepresentation hr(co,10 );
  SincDVR sincdvr(codvr,1.33, 4.33,100 );
    cout << "i       j       sincdvr          hr" << endl;
  for (int i=0; i!=5; ++i){
    cout << i << "\t" << i-1 << "\t"<< (sincdvr.energyLevel(i))*219474.6313702 << "\t" << (hr.energyLevel(i))*219474.6313702 << endl;
  }
  return 0;
}
