#include"co_pes_2016.h"
#include<iostream>

int main(){

  for(double r=0.70; r<=3.0; r+=0.001){
    printf("%20.6f      %20.6f\n", r , copes(r) );
    // std::cout << r<<"      "<<copes(r) <<std::endl;
  }
  return 0;
}

