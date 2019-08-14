#include<iostream>
#include"rotation.h"

using namespace Eigen;
using namespace std;

namespace yDVR{

  double RotationPotential1d::operator()(double r)const{
    return J_*(J_+1.0)/(2.0*m_*r*r);
  }

  RotationPotential1d::RotationPotential1d(double m, int J):m_(m), J_(J){ }

  int RotationPotential1d::setJ(int J){
    J_=J;
    return J_;
  }

  std::string RotationPotential1d::what() const{
    return std::string("Rotaional potential for J = ")
      + std::to_string(J_) + std::string(" and mu = ") + std::to_string(m_);
  }

  int rotationDVR(double m, const Eigen::VectorXd &x, const Eigen::MatrixXd &H, int maxJ, double E0){
    int N=x.size();
    RotationPotential1d V_rot(m, 0);
    for(int J=1; J<=maxJ; ++J){
      V_rot.setJ(J);
      auto H_rot=H;
      for(int i=0; i!=N; ++i){
        H_rot(i,i)+=V_rot(x(i));
      }
      SelfAdjointEigenSolver<MatrixXd> H_es(H_rot);
      auto E_rot=H_es.eigenvalues();
      auto wf_rot=H_es.eigenvectors();
      cout << V_rot.what() <<  endl;
      printResults(x,E_rot,wf_rot, E0);
    }
    return 0;
  }
}
