#include<iostream>
#include<vector>

void toNext(std::vector<int> & v, const std::vector<int> & max){
  int dim=v.size();
  if(dim != max.size()) {
    std::cout << "Wrong in dim" << std::endl;
  }

  for(int i=0; i!=dim ; ++i){
    v[i]++;
    if(v[i]<max[i]){
      return ;
    }else{
      v[i]-=max[i];
    }
  }

  return;
}

int main(){
  int dim=3; // number of dimension
  std::vector<int> max(dim); // max number of point in each dim
  std::vector<int> v(dim); // max number of point in each dim
  max[0]=3;
  max[1]=4;
  max[2]=5;
  for (int i=0; i!=3*4*5; ++i){
    std::cout <<v[2] << "   " << v[1] << "   " << v[0] <<std::endl;
    toNext(v, max);
  }
  return 0;
}

