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
  Log::set("sincdvr_test.out");
  Oscillator co(6.856208638000723*1822.888486209, [](double r){return copes(r/1.8897261254578281)/219474.6313702;});
  SincDVR sincdvr(co,1.33,4.3,100 );
  for (int i=0; i!=5; ++i){
    cout << i << "\t"<< sincdvr.EnergyLevel(i)*219474.6313702 << endl;
  }
  return 0;
}
