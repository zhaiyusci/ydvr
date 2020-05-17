#ifndef _ELJ_H
#define _ELJ_H

class ELJ{
  public:
    double operator() (double)const ;
  private:
    // 1. Parameters
    const double D_e;
    const double r_e;
    const int M;
    const int * const n;
    const double * const C_n;
    const double delta_LR;
    const double R_LR;
    const double R_c;
    const int N;
    const double * const rho;
    const double delta_n;
    const double R_n;
    const double a;
    const double b;
    const int type;

    // 2. Terms
    const double fLRre;
    const double * const Cnre;
    const double over2De;

    // 3. Functions
    double C(double) const;
    double nn(double) const;
    double f_LR(double) const;
    double f_n(double) const;
    double xi(double) const;
    double z(double) const;
    double zeta(double) const;

    static double* getCnre(int, const double*, const int*, double) ;

    // initialization
  public:
    ELJ(
        double D_e_,
        double r_e_,
        int M_,
        const int *n_,
        const double *C_n_,
        double delta_LR_,
        double R_LR_,
        double R_c_,
        int N_,
        const double *rho_,
        double delta_n_,
        double R_n_,
        double a_,
        double b_,
        int type_
       );

};


#endif // _ELJ_H
