// This file is part of ydvr.
//
// Copyright (C) 2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"config.h"
#include"representation.h"
namespace yDVR{
  Matrix Representation::HamiltonianMatrix() {
    if (hamiltonian_matrix_.cols() == 0){
      hamiltonian_matrix_ = KineticMatrix() + PotentialMatrix();
    }
    return hamiltonian_matrix_;
  }

}
