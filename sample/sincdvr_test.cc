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
  Log::set("sincdvr_test.out");
  Oscillator harm(1., [](double r){return 0.5*r*r;});
  SincDVR sincdvr(harm,-10.,10.,200 );
  PODVR podvr(sincdvr, 5);
  for (int i=0; i!=5; ++i){
    cout << i << "\t"<< sincdvr.energyLevel(i) <<"   " << podvr.energyLevel(i)<< "   " << i*1.+0.5 << endl;
  }
  return 0;
}
