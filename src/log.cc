// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include"log.h"
/** @brief All functions and class in %yDVR package.
 */
namespace yDVR{
  // Define log file
  std::ostream* Log::p_stream_=&std::cerr;
  int Log::n_ind_=0;
  void Log::set(std::ostream& stream){
    get() << "*** Change to other log stream." << std::endl;
    p_stream_ = &stream;
    auto&& t = std::chrono::system_clock::now();
    std::time_t t_c = std::chrono::system_clock::to_time_t(t);
    get() << "*** Open the log file, and the date is " << std::put_time(std::localtime(&t_c), "%F") << std::endl;
    return;
  }
  void Log::set(std::string filename){
    static std::ofstream* p_fs=nullptr;
    std::ofstream* p_newfs = new std::ofstream(filename, std::ios::app);
    set(*p_newfs);
    if(p_fs != nullptr){
      p_fs->close();
      delete p_fs;
    }
    p_fs = p_newfs;
    return;
  }
  std::ostream& Log::get(){
    auto&& t = std::chrono::system_clock::now();
    std::time_t t_c = std::chrono::system_clock::to_time_t(t);
    *p_stream_ << "[" << std::put_time(std::localtime(&t_c), "%T") << "]" << " yDVR > ";
    for(int i=0; i< n_ind_; ++i) *p_stream_ << "|   " ;
    return *p_stream_;
  }
  std::ostream& Log::getPlain(){
    return *p_stream_;
  }
  
}
