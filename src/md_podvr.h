#include"orthogonal_md_dvr.h"

namespace yDVR{
  class MDPODVR : public AbstractRepresentation{
    protected:
      OrthogonalMDDVR* primitive_;
      int N_;
      std::vector<Vector> grids_;
      Matrix primitive_to_po_;
      void ComputeGrids();
      Scalar eps_;
    public:
      MDPODVR(OrthogonalMDDVR& primitive, int N, Scalar eps=1.e-6)
        : primitive_(&primitive), N_(N), 
        grids_(primitive_->dimension(),Vector(0)), eps_(eps)
      {}
      const Vector& Grids(std::vector<Vector>::size_type i);
      virtual const Matrix& KineticMatrix(){return kinetic_matrix_;}
      virtual const Matrix& PotentialMatrix(){return potential_matrix_;}
      virtual const Matrix& HamiltonianMatrix();
      
  };
}
