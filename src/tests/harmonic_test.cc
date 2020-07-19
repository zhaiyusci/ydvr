// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"ydvr.h"

using namespace std;
using namespace yDVR;
int main(){
  Log::set("harmonic_test.out");
  Oscillator codvr(1.0, [](double r){return 0.5*r*r;});
  /*
  for (double i=0.1; i<=5; i+=0.02){
    // cout << i << "\t"<<  co.potential(i)<< endl;
    printf("%5.2f  %20.8f\n", i, co.potential(i));
  }
  return 0;
  */


  std::vector<Scalar> force_c;
  double re = 0.;
  double h = 1e-3;
  double f_2=codvr.potential(re-2*h);
  double f_1=codvr.potential(re-1*h);
  double f0=codvr.potential(re);
  double f1=codvr.potential(re+1*h);
  double f2=codvr.potential(re+2*h);
  force_c.push_back(f0);                                  // 0th
  force_c.push_back(0.5/h*(f1-f_1));                      // 1st
  force_c.push_back(1./h/h*(f1+f_1-2*f0));                // 2nd
  force_c.push_back(0.5/h/h/h*(f2-2*f1-f_2+2*f_1));       // 3rd
  force_c.push_back(1./h/h/h/h*(f2+f_2-4*f1-4*f_1+6*f0)); // 4th
  OscillatorTaylor co(1., re, force_c);
  // OscillatorTaylor co(1., 0, {0, 0, 1});
  HarmonicRepresentation hr(co,10 );
  // SincDVR sincdvr(co,1.33, 4.33,100 );
  SincDVR sincdvr(codvr,-10.,10.,200 );
    cout << "i     sincdvr          hr" << endl;
  for (int i=0; i!=5; ++i){
    // cout << i << "\t" << sincdvr.energyLevel(i) << "\t" << hr.energyLevel(i) << endl;
    cout << i << "\t" << (sincdvr.energyLevel(i))<< "\t" << hr.energyLevel(i)<< endl;
  }
  PODVR po(sincdvr,5);
  cout << po.grids() << endl;
  return 0;
}
