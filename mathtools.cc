// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"mathtools.h"
using namespace Eigen;
using namespace std;
double mel(int N, const VectorXd& bra, const VectorXd& op, const VectorXd& ket){
  double res=0.0;
  res=0.0;
  for (int i =0; i!=N ;++i){
    res+=bra(i)*op(i)*ket(i);
  }
  return res;
}


CubicSpline1d::CubicSpline1d(int N, const VectorXd& x, const VectorXd& y, double mi, double mf){
  N_=N;
  x_=x; y_=y; m_=VectorXd::Zero(N);
  for (int i =1; i!= N-1; ++i){
    // Finite difference method are used to get the tangents...
    m_(i)=0.5*( (y(i+1)-y(i))/(x(i+1)-x(i))+(y(i-1)-y(i))/(x(i-1)-x(i)));
  }
  m_(0)=mi; // tangent of the init point
  m_(N-1)=mf; // tangent of the final point

  // deal with the absolutely abnormal situation with finite difference method
  if(fabs(mi)>1.0e30) m_(0)=(y(0)-y(1))/(x(0)-x(1));
  if(fabs(mf)>1.0e30) m_(N-1)=(y(N-2)-y(N-1))/(x(N-2)-x(N-1));
  return;

}


// double DoubleFunction1d::calc(const double& x) const{
  // return 0;
// }

double CubicSpline1d::calc(double x) const{

  // find the right interval using bisec method...
  int posi, posf, posm;
  posi=1;
  posf=N_-2; // here we want the extropolate value be reasonable, as if they stay in the first or last section
  if(x>x_(posi) && x<=x_(posf)){
    posm=(posi+posf)/2; // mid point.  because they are all ints here, it is ok to do so
    for(int i=0; i!=log2(N_)+1 && posf-posi!=1; ++i){
      (x>x_(posi) && x<=x_(posm) )?  posf=posm : posi=posm;
      posm=(posi+posf)/2; 
    }
  }else{
    // if x is out of range...  warning... but do not stop
    (x<=x_(0) || x>x_(N_-1))? (cerr<< "Warning: Cubic spline: x out of range, x="<< x << ", min(x)=" << x_(0) <<", max(x)="<<x_(N_-1) << endl, 1==1) : (1==1);
    (x<=x_(1))? (posi=0, posf=1 ):(posi=N_-2, posf=N_-1);
  }
  // cerr<< posi <<"  "<< posf <<endl;

  double t=(x-x_(posi))/(x_(posf)-x_(posi));
  double t2=t*t;
  double t3=t2*t;
  double h00=2*t3-3*t2+1;
  double h10=t3-2*t2+t;
  double h01=-2*t3+3*t2;
  double h11=t3-t2;
  // cerr << "t   " << t<< endl;
  return h00*y_(posi)
    +h10*(x_(posf)-x_(posi))*m_(posi)
    +h01*y_(posf)
    +h11*(x_(posf)-x_(posi))*m_(posf);
}

CuttedPotential1d DoubleFunctionmd::linearcut(const VectorXd& xe, const VectorXd& deltax){
  CuttedPotential1d func1d(xe, deltax, this);
  return func1d;
}

CuttedPotential1d::CuttedPotential1d(const Eigen::VectorXd& xe, const Eigen::VectorXd& deltax, DoubleFunctionmd* funcmd){
  xe_=xe;
  deltax_=deltax;
  funcmd_=funcmd;
}

double CuttedPotential1d::calc(double x)const{
  VectorXd xx=xe_+x*deltax_;
  return funcmd_->calc(xx);
}









