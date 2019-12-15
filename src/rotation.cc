#include<iostream>
#include"rotation.h"

using namespace Eigen;
using namespace std;

namespace yDVR{

  yScalar RotationPotential1d::operator()(yScalar r)const{
    return J_*(J_+1.0)/(2.0*m_*r*r);
  }

  RotationPotential1d::RotationPotential1d(yScalar m, int J):m_(m), J_(J){ }

  int RotationPotential1d::setJ(int J){
    J_=J;
    return J_;
  }

  std::string RotationPotential1d::what() const{
    return std::string("Rotaional potential for J = ")
      + std::to_string(J_) + std::string(" and mu = ") + std::to_string(m_);
  }

  int rotationDVR(yScalar m, const yVector &x, const yMatrix &H, int maxJ, yScalar E0){
    int N=x.size();
    RotationPotential1d V_rot(m, 0);
    for(int J=1; J<=maxJ; ++J){
      V_rot.setJ(J);
      auto H_rot=H;
      for(int i=0; i!=N; ++i){
        H_rot(i,i)+=V_rot(x(i));
      }
      SelfAdjointEigenSolver<yMatrix> H_es(H_rot);
      auto E_rot=H_es.eigenvalues();
      auto wf_rot=H_es.eigenvectors();
      cout << V_rot.what() <<  endl;
      printResults(x,E_rot,wf_rot, E0);
    }
    return 0;
  }
}
