#include"config.h"
#include"simultaneous_diagonalization.h"
#include<iostream>
#include<fstream>

namespace yDVR{

  simultaneousDiagonalization::simultaneousDiagonalization(
      std::vector<Matrix> matrices, Scalar eps ): 
    matrices_(matrices), 
    r_ ( matrices_[0].rows() ), c_ ( matrices_[0].cols() ) ,
    scale_( matrices.size(), 1.)
  {
    if(r_ != c_){
      throw std::runtime_error("Sizes inconsist.");
    }
    for(auto && i : matrices_){
      if(i.rows() != r_ || i.cols() != c_){
        throw std::runtime_error("Sizes inconsist.");
      }
    }
    eigenvectors_.setIdentity(r_,c_);
    compute_(eps); // solve the problem on construction...
  }

  Scalar simultaneousDiagonalization::off_(const Matrix & A){
    Scalar res=0.0;
    for(int i=0; i!=A.rows(); ++i){
      for(int j=i; j!=A.rows(); ++j){
        if(i != j) res += pow(A(i,j),2);
      }
    }
    return res;
  }

  Scalar simultaneousDiagonalization::offsum_()const{
    static int iter(0);
    Scalar res=0.0;
    std::cout << iter;
    for(auto && i : this -> matrices_){
      auto off = off_(i) ;
      std::cout <<"   "<< off;
      res += off;
    }
    std::cout <<"   "<<  res << std::endl;
    iter++;
    return res;
  }

  Matrix2d simultaneousDiagonalization::G_(int i, int j) const {
    Matrix2d res=Matrix2d::Zero();
    for (auto && A: this -> matrices_){
      Vector2d h;
      h << A(i,i)-A(j,j), A(i,j)+A(j,i);
      res += h*h.adjoint();
    }
    return res;
  }

  // Eigen::SparseMatrix<Scalar> simultaneousDiagonalization::R_(int i, int j) const{
  std::tuple<Scalar, Scalar> simultaneousDiagonalization::R_(int i, int j) const{
    SparseMatrix res (r_, c_);
    Vector2d xy = 
      SelfAdjointEigenSolver2d(G_(i,j))
      .eigenvectors().col(1);
    Scalar x = xy[0];
    Scalar y = xy[1];
    Scalar c = sqrt((x+1.)/2.);
    Scalar s = y/sqrt(2.*(x+1.));
    /*
       for (int i = 0; i< r_; ++i){
       res.insert(i,i) = 1.;
       }
       res.insert(i,i) = c;
       res.insert(j,j) = c;
       res.insert(i,j) = -s; 
       res.insert(j,i) =  s;
       */
    return std::make_tuple(c,s);
    // return res;
  }

  void simultaneousDiagonalization::compute_(Scalar eps){
    Scalar oldoffsum(1.e308); // big enough
    for(int iter = 0; iter < 10000; ++iter){
      Scalar offsum = offsum_();
      if(fabs(oldoffsum - offsum) > eps) {
        sweep_();
        // remove_scaling_();
        oldoffsum = offsum;
      }else{
        // remove_scaling_();
        sweep_();
        std:: cout << "CONVERGED. offsum = " << offsum_() <<std::endl;
        return;
      }
    }
    // remove_scaling_();
    // sweep_();
    for(int i = 0; i != 3; ++i) std::cout 
      << "-!- ### NOT CONVERGED WITHIN 10000 STEPS ### -!-" <<std::endl;
    return;
  }

  void simultaneousDiagonalization::sweep_(){
    for(int i=0; i<r_; ++i){
      for(int j=i+1; j<r_; ++j){
        // Eigen::SparseMatrix<Scalar> Rmat = R_(i,j);
        Scalar c, s;
        std::tie(c,s) = R_(i,j);
        for(auto && A : matrices_){
          // A= Rmat.adjoint() * A * Rmat;
          // The right hand side
          Vector coli = A.col(i);
          Vector colj = A.col(j);
          A.col(i) = c*coli + s*colj;
          A.col(j) = -s*coli + c*colj;
          // The left hand side
          RowVector rowi = A.row(i);
          RowVector rowj = A.row(j);
          A.row(i) = c*rowi + s*rowj;
          A.row(j) = -s*rowi + c*rowj;
        }

        // eigenvectors_ *= Rmat;
        Vector coli = eigenvectors_.col(i);
        Vector colj = eigenvectors_.col(j);
        eigenvectors_.col(i) = c*coli + s*colj;
        eigenvectors_.col(j) = -s*coli + c*colj;
      }
    }
    return;
  }

  void simultaneousDiagonalization::deal_fixed_point_(){
    for (size_t i = 1; i< matrices_.size(); ++i){
      matrices_[i] *= pow(1.2, i);
      scale_[i] *= pow(1.2, i);
    }
    return; 
  }
  void simultaneousDiagonalization::remove_scaling_(){
    for (size_t i = 1; i< matrices_.size(); ++i){
      matrices_[i] /= scale_[i];
      scale_[i] =1.;
    }
    return; 
  }
}
