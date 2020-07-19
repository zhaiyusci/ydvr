#ifndef YDVR_SIMULTANEOUS_DIAGONALIZATION_H_
#define YDVR_SIMULTANEOUS_DIAGONALIZATION_H_
#include"config.h"
#include<initializer_list>
#include<vector>
namespace yDVR{
  class simultaneousDiagonalization{
    public:
      simultaneousDiagonalization(
          std::vector<Matrix> matrices,
          Scalar eps = 1.e-8);
      inline Vector eigenvalues(int i) const {
        return matrices_[i].diagonal(); 
      }
      inline Matrix remains(int i) const {
        return matrices_[i]; 
      }
      inline Matrix eigenvectors() const {
        return eigenvectors_; // all matrices share the same eigen vectors
      }
    private:
      std::vector<Matrix> matrices_;
      Matrix eigenvectors_;
      int r_;
      int c_;
      static Scalar off_(const Matrix & A);
      Scalar offsum_() const;
      Matrix2d G_(int i, int j) const;
      std::tuple<Scalar, Scalar> R_(int i, int j) const;
      void compute_(Scalar eps);
      std::vector<Scalar> scale_;
      void deal_fixed_point_();
      void remove_scaling_();
      void sweep_();
  };
}
#endif // YDVR_SIMULTANEOUS_DIAGONALIZATION_H_
