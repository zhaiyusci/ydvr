#include"config.h"
#include"representation.h"

namespace yDVR{
  class StationaryState{
    protected:
      Scalar energy_;
      Vector ket_;
      Representation* representation_;
    public:
      StationaryState(Scalar energy, Vector ket, Representation* representation)
        : energy_(energy), ket_(ket), representation_(representation){}
      Scalar energy() const { return energy_; }
      Vector ket() const { return ket_; }
      RowVector bra() const { return ket_.adjoint(); }
      Scalar ket(unsigned i) const { return ket_(i); }
      // TODO: good for real number but ...
      Scalar bra(unsigned i) const { return ket_(i); } 
  };
}
