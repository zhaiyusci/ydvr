// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"config.h"
/** @brief All functions and class in %yDVR package.
 */
namespace yDVR{
  // Define log file
  std::ostream* Log::p_stream_=&std::cerr;
}
