// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "abinitio.h"

void Abinitio::printInfo() const {
  std::cout << "yDVR ab initio package interface :: " << std::flush;
}

void OrcaInterface::printInfo() const {
  Abinitio::printInfo();
  std::cout <<"ORCA"<<std::endl;
}

double OrcaInterface::calc(const std::vector< std::string > & atom, const Eigen::MatrixXd & r) const {
  // TODO
  return result;
}

OrcaInterface::OrcaInterface(const std::string & theory, const std::string & basis):theory_(theory), basis_(basis){
}


