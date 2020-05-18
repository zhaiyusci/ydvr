// This file is part of ydvr.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_CONFIG_H_
#define YDVR_CONFIG_H_

#include<Eigen/Dense>
#include<Eigen/Eigenvalues>
#include<iostream>
#include<fstream>
#include<chrono>
#include<ctime>
#include<iomanip>

/** @brief All functions and class in %yDVR package.
 */
namespace yDVR{
  // Define precise used in yDVR
  typedef double Scalar; // ... can change here

  // Define Linear Algebra classes, user may want different linear algebra library
  typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> Matrix;
  typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> ColVector;
  typedef ColVector Vector;
  typedef Eigen::Matrix<Scalar, 1, Eigen::Dynamic> RowVector;
  typedef Eigen::SelfAdjointEigenSolver<Matrix> SelfAdjointEigenSolver;

  // Define log file
  class Log{
    private:
      static std::ostream* p_stream_;
      Log(){}
    public:
      inline static void set(std::ostream& stream){
        get() << "*** Change to other log stream." << std::endl;
        p_stream_ = &stream;
        auto&& t = std::chrono::system_clock::now();
        std::time_t t_c = std::chrono::system_clock::to_time_t(t);
        get() << "*** Open the log file, and the date is " << std::put_time(std::localtime(&t_c), "%F") << std::endl;
        return;
      }
      static void set(std::string filename){
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
      inline static std::ostream& get(){
        auto&& t = std::chrono::system_clock::now();
        std::time_t t_c = std::chrono::system_clock::to_time_t(t);
        return *p_stream_ << "[" << std::put_time(std::localtime(&t_c), "%T") << "]" << " yDVR > ";
      }
  };
}
#define LOG Log::get()

#endif // YDVR_CONFIG_H_
