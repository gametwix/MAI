#pragma once

#include <iostream>
#include <memory>
#include "Pentagon.hpp"
#include "Rhomb.hpp"
#include "Hexagon.hpp"
#include <utility>

template <class TDot,class Fig>
class Factory;

template <class TDot>
class Factory<TDot,Rhomb<TDot>>{
 public:
 static Figure<TDot>* CreatFig(){
  TDot D1,D2;
  std::pair<TDot,TDot> C;
  std::cout << "Введити размеры диагоналей: ";
  std::cin >> D1 >> D2;
  std::cout << "Введити координаты центра: ";
  std::cin >> C.first >> C.second;
  auto point = new Rhomb<TDot>(C, D1, D2);
  return point;
 }
};

template <class TDot>
class Factory<TDot,Pentagon<TDot>>{
 public:
 static Figure<TDot>* CreatFig(){
  TDot S;
  std::pair<TDot,TDot> C;
  std::cout << "Введити размеры стороны: ";
  std::cin >> S;
  std::cout << "Введити координаты центра: ";
  std::cin >> C.first >> C.second;
  auto point = new Pentagon<TDot>(C, S);
  return point;
 }
};

template <class TDot>
class Factory<TDot,Hexagon<TDot>>{
 public:
 static Figure<TDot>* CreatFig(){
  TDot S;
  std::pair<TDot,TDot> C;
  std::cout << "Введити размеры стороны: ";
  std::cin >> S;
  std::cout << "Введити координаты центра: ";
  std::cin >> C.first >> C.second;
  auto point = new Hexagon<TDot>(C, S);
  return point;
 }
};