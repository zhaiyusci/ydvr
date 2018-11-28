// This file is part of ydvr.
//
// Copyright (C) 2017 Yu Zhai <me@zhaiyusci.net>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include<iomanip>
#include<sstream>
#include"mathtools.h"
#include"podvr.h"
#include"tinyxml2.h"
using namespace Eigen;
using namespace std;
using namespace tinyxml2;

int main(int argc, char *argv[]){
  cout.setf(ios::fixed, ios::floatfield);
  cout << std::setprecision(8);
  extern int load_input_file(const char*, int&, int&, int&, double& ,double&, double&, VectorXd& , VectorXd&) ;

  int pri_n, po_n,pot_n;
  double m,a,b;
  VectorXd x;
  VectorXd y;
  load_input_file(argv[1], pri_n, po_n, pot_n, m,a,b, x, y);
  CubicSpline1d spl(pot_n, x, y, 1.0e31, 1.0e31);
  // cout << "Grids"<<endl;
  // for(int i=0; i!=pot_n; ++i){
    // cout <<setw(20) <<x(i)<<"  "<< y(i) << "  " << spl.calc(x(i))<< endl;
  // }
  // cout << "Curve"<<endl;
  // for(double xx=0.6; xx<=2.5; xx=xx+0.001){
    // cout <<setw(20) <<xx<<"  "<< spl.calc(xx)<< endl;
  // }

  VectorXd grid;
  VectorXd E;
  MatrixXd wf;
  MatrixXd T;


  sinc_podvr_1d(m,pri_n,po_n, a, b, grid, E, wf, T, spl);

  cout <<"grid in angstrom"<<endl;
  cout <<grid*0.529177249<<endl;

  cout <<"E in cm-1"<<endl;
  cout <<E*219474.6313702<<endl;
  cout <<"wf"<<endl;
  cout <<wf<<endl;
  return 0;
}

int load_input_file(const char* fn, int& pri_DVR_N, int& PODVR_N, int& pot_N, double& m,double& a, double& b, VectorXd& x, VectorXd& y ){
  stringstream ss;
  XMLDocument input;
  input.LoadFile(fn);
  XMLNode* xmlroot=input.FirstChildElement("dvrinput");
  const char* title=xmlroot->FirstChildElement("title")->GetText();
  cout << title << endl;
  const char* potential=xmlroot->FirstChildElement("potential")->GetText();
  // cout << potential << endl;
  const char* potential_length_unit=xmlroot->FirstChildElement("potential")->Attribute("lengthunit");
  const char* potential_energy_unit=xmlroot->FirstChildElement("potential")->Attribute("energyunit");
  const char* potential_number=xmlroot->FirstChildElement("potential")->Attribute("number");
  // cout << potential_number << endl;
  ss.str(potential_number);
  ss>> pot_N;
  // cout <<pot_N <<endl;
  x.resize(pot_N);
  y.resize(pot_N);
  ss.clear();
  ss.str(potential);
  for(int i=0; i!=pot_N; ++i){
    ss>>x(i)>>y(i);
  }

  if(0==strcmp(potential_length_unit,"angstrom")) x/=0.529177249;
  
  if(0==strcmp(potential_energy_unit,"cm-1")) y/=219474.6313702;
  // cout <<"uuuuu"<<y <<endl;
  const char* mass_unit=xmlroot->FirstChildElement("mass")->Attribute("massunit");
  // cout << mass_unit << endl;
  const char* mass=xmlroot->FirstChildElement("mass")->GetText();
  ss.clear();
  ss.str(mass);
  ss>>m;
  if(0==strcmp(mass_unit,"dalton")) m*=1822.888486192;
  // cout <<"m="<<m<<endl;
  const char* primitive=xmlroot->FirstChildElement("primitive")->GetText();
  ss.clear();
  ss.str(primitive);
  ss>>pri_DVR_N;
  const char* po=xmlroot->FirstChildElement("podvr")->GetText();
  ss.clear();
  ss.str(po);
  ss>>PODVR_N;
  const char* at=xmlroot->FirstChildElement("a")->GetText();
  ss.clear();
  ss.str(at);
  ss>>a;
  const char* bt=xmlroot->FirstChildElement("b")->GetText();
  ss.clear();
  ss.str(bt);
  ss>>b;
  const char* a_length_unit=xmlroot->FirstChildElement("a")->Attribute("lengthunit");
  const char* b_length_unit=xmlroot->FirstChildElement("b")->Attribute("lengthunit");
  if(0==strcmp(a_length_unit,"angstrom")) a/=0.529177249;
  if(0==strcmp(b_length_unit,"angstrom")) b/=0.529177249;
  return 0;
}
