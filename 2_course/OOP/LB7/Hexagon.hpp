#pragma once

#include "Figure.hpp"
#include <iostream>
#include <utility>
#include <cmath>
#include <fstream>

#define PI 3.1415926

template <typename T>
class Hexagon: public Figure<T>{
protected:
 const size_t TYPE = 2;
 T Size;
public:
 Hexagon(std::pair<T,T> C,T S){
  Size = S;
  this->Center.first = C.first;
  this->Center.second = C.second;
 }
 void print()
 override{
  std::pair<double,double> cords[6];
  double R = Size;
  for(int i = 0;i < 6;++i){
   cords[i].first = this->Center.first;
   cords[i].second = this->Center.second;
   cords[i].first +=R*cos(2*PI*i/6); 
   cords[i].first +=R*sin(2*PI*i/6);
  }

  std::cout << "{";
  for(int i = 0;i < 6;++i)
   std::cout << "(" << cords[i].first << "," << cords[i].second << ")";  
  std::cout << "}" <<std::endl;
 }

 void write(std::ofstream& file)
 override{
  file.write((char*) &(this->TYPE), sizeof(size_t));
  file.write((char*) &(this->Center.first), sizeof (T));
  file.write((char*) &(this->Center.second), sizeof (T));
  file.write((char*) &(this->Size), sizeof (T));
 }
};