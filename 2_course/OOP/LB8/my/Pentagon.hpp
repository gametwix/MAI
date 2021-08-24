#pragma once

#include "Figure.hpp"
#include <iostream>
#include <utility>
#include <cmath>
#include <fstream>
#include <string>
#include <fstream>

#define PI 3.1415926

template <typename T>
class Pentagon: public Figure<T>
{
protected:
 const size_t TYPE = 0;
 T Size;
public:
 Pentagon(std::pair<T,T> C,T S){
  Size = S;
  this->Center.first = C.first;
  this->Center.second = C.second;
 }
 void print()
 override{
  std::pair<double,double> cords[5];
  double R = sqrt(10)*sqrt(5+sqrt(5))*Size/10;
  for(int i = 0;i < 5;++i){
   cords[i].first = this->Center.first;
   cords[i].second = this->Center.second;
   cords[i].first +=R*cos(2*PI*i/5); 
   cords[i].first +=R*sin(2*PI*i/5);
  }

  std::cout << "{";
  for(int i = 0;i < 5;++i)
   std::cout << "(" << cords[i].first << "," << cords[i].second << ")";  
  std::cout << "}" <<std::endl;
 }

 void write(std::ofstream &file)
 override{
  std::pair<double,double> cords[5];
  double R = sqrt(10)*sqrt(5+sqrt(5))*Size/10;
  for(int i = 0;i < 5;++i){
   cords[i].first = this->Center.first;
   cords[i].second = this->Center.second;
   cords[i].first +=R*cos(2*PI*i/5); 
   cords[i].first +=R*sin(2*PI*i/5);
  }

  file << "{";
  for(int i = 0;i < 5;++i)
   file << "(" << cords[i].first << "," << cords[i].second << ")";  
  file << "}" <<std::endl;
 }

};