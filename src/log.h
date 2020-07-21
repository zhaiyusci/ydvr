// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef YDVR_LOG_H_
#define YDVR_LOG_H_

#include<iostream>
#include<fstream>
#include<chrono>
#include<ctime>
#include<iomanip>

/* @file
 */

namespace yDVR{
  /** @brief Log record mechanism of yDVR.
   *
   * yDVR log is different from your program output,
   * it will only write some information about its running progress,
   * with little scientific meaning.
   * By default, yDVR write its log to `std::cerr`.
   */
  class Log{
    private:
      static std::ostream* p_stream_;
      static int n_ind_;
      Log(){}
    public:
  /** @brief Set log destination to stream
   * @param stream output stream, e.g. `std::cerr`
   * Do not set it as the same you use to output the main result
   * e.g., `std::cout` if your main program write to screen,
   * or your outpur may be messed up.
   */
      static void set(std::ostream& stream);
  /** @brief Set log destination to a file
   * @param filename Log file name, e.g. `"ydvr.log"`
   */
      static void set(std::string filename);
  /** @brief Get the log stream
   */
      static std::ostream& get();
  /** @brief Get the log stream, but without the time information
   */
      static std::ostream& getPlain();
  /** @brief Increase indent
   */
      inline static void indent(){ n_ind_++; }
  /** @brief Decreas indent
   */
      inline static void unindent(){ if(n_ind_ > 0) n_ind_--; }
  };
}
#define LOG Log::get()
#define CONTINUE Log::getPlain()

#endif // YDVR_LOG_H_
