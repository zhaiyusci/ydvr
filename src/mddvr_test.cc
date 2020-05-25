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
  Log::set("mddvr_test.out");
  OrthogonalMDOscillator pib(2, 1., [](const std::vector<Scalar>& q ){return 0.5*(q[0]*q[0]+4.*q[1]*q[1]);});
  SincDVR pd0(pib.OneDimension(0), -7., 7., 200);
  SincDVR pd1(pib.OneDimension(1), -7., 7., 200);
  {
    PODVR d0(pib.OneDimension(0), pd0, 5);
    PODVR d1(pib.OneDimension(1), pd1, 5);
    ofstream out("mddvr5.list");
    for(int i = 0; i!= 5; ++i){
      for(int j = 0; j!= 5; ++j){
        out << "    " << d0.Grids()[i] << "    " << d1.Grids()[j] << endl;
      }
    }
  }
  PODVR d0(pib.OneDimension(0), pd0, 20);
  PODVR d1(pib.OneDimension(1), pd1, 20);
  OrthogonalMDDVR rep(pib);
  rep.SetRepresentation(0, d0);
  rep.SetRepresentation(1, d1);
  for (int i=0; i!=120; ++i){
    cout << i << "\t"<< rep.EnergyLevel(i) 
      <<"\t"<< d0.EnergyLevel(i) 
      <<"\t"<< d1.EnergyLevel(i) 
      << endl;
    // cout << podvr.EnergyState(i).bra() << endl;
  }


#define N_PO 25
  MDPODVR porep(rep, N_PO);
  for (int i=0; i!=5; ++i){
    cout << i << "\t"<< porep.EnergyLevel(i) 
      << endl;
    // cout << podvr.EnergyState(i).bra() << endl;
  }

  {
    ofstream out("podvr25.list");
    for(int i = 0; i!= N_PO; ++i){
      out 
        << porep.Grids(0)[i] << "\t"
        << porep.Grids(1)[i] << "\t"
        << endl;
    }
  }
  return 0;
}
