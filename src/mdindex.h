// This file is part of yDVR.
//
// Copyright (C) 2017-2020 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MDINDEX_H
#define MDINDEX_H
#include<vector>
#include<iostream>
#include<initializer_list>
class mdindex{
  private:
    const std::vector <size_t> max_; 
    // max number of each dimension, staring from 0
    std::vector <size_t> val_; 
    int overflow_=0;
    // current indices
    size_t totalindex_;

  public:

    template<typename T>
      mdindex(const std::vector <T> &max): max_(max.begin(), max.end()), val_(max.size(),0), totalindex_(0){ }
    template<typename T>
      mdindex(const std::initializer_list <T> &max): max_(max.begin(), max.end()), val_(max.size(),0), totalindex_(0){ }

    mdindex(const mdindex& rhs):max_(rhs.max_), val_(rhs.val_), totalindex_(rhs.totalindex_){ }

    void reset(){
      for(size_t i=0; i!=val_.size(); ++i)val_[i]=0;
      totalindex_=0;
      overflow_ = 0;
    }

    const size_t & get() const{
      return totalindex_;
    }

    const size_t & get(const unsigned int & i) const{
      return val_[i];
    }

    size_t max() const {
      unsigned int tmp(1);
      for(size_t i=0; i!= max_.size(); ++i) tmp*=max_[i];
      return tmp;
    }

    const size_t & max(const size_t & i) const {
      return max_[i];
    }

    mdindex& operator=(const mdindex& rhs){
      try{
        if(rhs.max_!=this->max_) 
          throw std::runtime_error("RUNTIME ERROR: DIMENSION DOES NOT MATCH!");
        val_=rhs.val_;
      }catch(std::runtime_error& e){
        std::cerr << "Max size: " ;
        for(size_t i=0; i!=max_.size(); ++i) std::cerr << max_[i] <<"  " ;
        std::cerr << std::endl;
        throw;
      }
      return *this;
    }

    mdindex& operator=(const size_t& rhs){
      reset();
      (*this) += rhs;
      return *this;
    }

    mdindex& operator++(){ // ++index
      for(size_t i=0; i!=val_.size(); ++i){
        ++val_[i];
        if(val_[i]<max_[i]){
          ++totalindex_;
          return *this;
        }else{
          val_[i]=0;
        }
      }
      ++overflow_;
      return *this;
    }

    mdindex operator++(int){ // index++
      mdindex ret=*this;
      ++(*this);
      return ret;
    }

    mdindex& operator--(){ // --index
      for(size_t i=0; i!=val_.size(); ++i){
        if(val_[i]>0){
          --val_[i];
          --totalindex_;
          return *this;
        }else{
          val_[i]=max_[i]-1;
        }
      }
      --overflow_;
      return *this;
    }

    mdindex operator--(int){ // index--
      mdindex ret=*this;
      --(*this);
      return ret;
    }

    mdindex operator+(const int &inc) const{
      mdindex ret=*this;
      if(inc >=0){
        for(int i =0; i!= inc; ++i) ++ret;
        return ret;
      }else{
        for(int i =0; i!= -inc; ++i) --ret;
        return ret;
      }
    }

    mdindex operator-(const int &inc) const{
      return (*this)+(-inc);
    }

    mdindex& operator+=(const int &inc) {
      if(inc >=0){
        for(int i =0; i!= inc; ++i) ++(*this);
        return *this;
      }else{
        for(int i =0; i!= -inc; ++i) --(*this);
        return *this;
      }
    }

    mdindex& operator-=(const int &inc) {
      return (*this)+=(-inc);
    }

    operator bool() const{
      return overflow_ == 0;
    }

    operator size_t() const{
      return get();
    }

    operator int() const{
      return get();
    }

};
#endif // MDINDEX_H
