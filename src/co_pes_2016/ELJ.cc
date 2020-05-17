#include"ELJ.h"
#include<iostream>
#include<stdexcept>
#include<cmath>

// Ref:
// Photos G. Hajigeorgiou, J. Mol. Spectr. 330, 4-13 (2016)
// doi: 10.1016/j.jms.2016.06.014
// See the notes in the git repo


using namespace std;

ELJ::ELJ( double D_e_, double r_e_, int M_, const int *n_, const double *C_n_,
    double delta_LR_, double R_LR_, double R_c_, int N_, const double *rho_,
    double delta_n_, double R_n_, double a_, double b_, int type_): D_e(D_e_),
  r_e(r_e_), M(M_), n(n_), C_n(C_n_), delta_LR(delta_LR_), R_LR(R_LR_),
  R_c(R_c_), N(N_), rho(rho_), delta_n(delta_n_), R_n(R_n_),
  a(a_), b(b_), type(type_), fLRre(f_LR(r_e_)), Cnre(getCnre(M_,C_n_,n_,r_e_)),
  over2De(0.5/D_e_) {
    // Here I ignore the safety checking...
  }

double* ELJ::getCnre(int M, const double* Cn, const int* n, double re){
  double* result;
  result=new double[M];
  for (int i=0; i!=M; ++i){
    *(result+i)=*(Cn+i)/pow(re,*(n+i));
  }
  return result;
}

double ELJ::C(double r) const{
  double result(0.0);
  double ffLR(f_LR(r)/fLRre);
  double rr(r_e/r);
  result=(1.0-ffLR)*over2De;
  double sc(0.0);
  for(int i=0; i!=M; ++i){
    sc+=Cnre[i]*pow(rr,n[i]-n[0]);
  }
  result*=sc;
  result+=ffLR;
  return result;
}

double ELJ::nn(double r) const{
  double result(0.0);
  if(r>R_c){
    double sr(0.0);
    for(int i=0; i!=N; ++i){
      sr+=rho[i]*pow(zeta(r),i);
    }
    result=sr*f_n(r)+n[0]*(1.0-f_n(r));

  }else{
    result=a*exp(b*r);
  }
  return result;
}

double ELJ::f_LR(double r)const {
  double result(0.0);
  result=1.0+exp(delta_LR*(r-R_LR));
  result=1.0/result;
  return result;
}

double ELJ::f_n(double r)const {
  double result(0.0);
  result=1.0+exp(delta_n*(r-R_n));
  result=1.0/result;
  return result;
}

double ELJ::zeta(double r) const{
  switch(type){
    case 0:
      return xi(r);
      break;
    case 1:
      return z(r);
      break;
    default:
      throw runtime_error( "ERROR: Unknown zeta function type.");
  }
  return 0;
}

double ELJ::xi(double r) const {
  return (r-r_e)/r_e;
}

double ELJ::z(double r) const {
  return 2.0*(r-r_e)/(r+r_e);
}

double ELJ::operator()(double r)const {
  double rr=r_e/r;
  double result(D_e);
  result*=pow(1-C(r)*pow(rr,nn(r)),2);
  return result;
}
