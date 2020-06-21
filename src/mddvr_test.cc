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
#define DIM 2
  Log::set("mddvr_test.out");
  OrthogonalMDOscillator pib(DIM, 1., [](const std::vector<Scalar>& q ){Scalar res=0; for (size_t i =0; i!= DIM; ++i) res+=q[i]*q[i]; return 0.5*res;});
  // OrthogonalMDOscillator pib(3, 1., [](const std::vector<Scalar>& q ){return 0.;});
  std::vector<SincDVR*> pd;
  std::vector<PODVR*> d;
  for(size_t i =0; i!=DIM; ++i){
    pd.push_back(new SincDVR(pib.oneDimension(i), -2*M_PI, 2*M_PI, 20));
    cout << __LINE__ << "  " << pib.oneDimension(i).mass() << endl;
    std::cout<< i << "  "<< pd[i]->energyLevel(0) << std::endl;
    // d.push_back(new PODVR(*pd[i], 9));
  }
  OrthogonalMDDVR rep(pib);
  for(size_t i =0; i!=DIM; ++i){
    rep.setRepresentation(i, *pd[i]);
  }


  ofstream out("podvr27.list");
  for (int N_PO = 1; N_PO <= 50; ++N_PO){
    MDPODVR porep(rep, N_PO, 1e-16);
    // for (int i=0; i!=5; ++i){
      // cout << i << "\t"<< porep.energyLevel(i) 
        // << endl;
      // cout << podvr.EnergyState(i).bra() << endl;
    // }

    for(int i = 0; i!= N_PO; ++i){
      for(int j = 0; j!= DIM; ++j){
        out 
          << porep.grids(j)[i] << "\t";
      }
      out
        << endl;
    }
    out << endl;
  }
  return 0;
}
