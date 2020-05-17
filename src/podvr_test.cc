#include"sincdvr.h"
#include"podvr.h"
#include"stationary_state.h"
#include"co_pes_2016/co_pes_2016.h"

using namespace std;
using namespace yDVR;
int main(){
  Oscillator co(6.856208638000723*1822.888486209, [](double r){return copes(r/1.8897261254578281)/219474.6313702;});
  SincDVR sincdvr(&co,1.33,4.3,100 );
  PODVR podvr(&co, &sincdvr, 10);
  for (int i=0; i!=5; ++i){
    cout << i << "\t"<< podvr.EnergyLevel(i)*219474.6313702 << endl;
    cout << podvr.EnergyState(i).bra() << endl;
  }
  return 0;
}
