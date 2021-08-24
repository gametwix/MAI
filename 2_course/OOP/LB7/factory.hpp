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
 static std::shared_ptr<Figure<TDot>> CreatFig(){
  TDot D1,D2;
  std::pair<TDot,TDot> C;
  std::cout << "Введити размеры диагоналей: ";
  std::cin >> D1 >> D2;
  std::cout << "Введити координаты центра: ";
  std::cin >> C.first >> C.second;
  auto point = new Rhomb<TDot>(C, D1, D2);
  return std::shared_ptr<Figure<TDot>>(point);
 }
 static std::shared_ptr<Figure<TDot>> ReadFig(std::pair<TDot,TDot> C, TDot D1, TDot D2) {
  auto point = new Rhomb<TDot>(C, D1, D2);
  return std::shared_ptr<Figure<TDot>>(point);
 }
};

template <class TDot>
class Factory<TDot,Pentagon<TDot>>{
 public:
 static std::shared_ptr<Figure<TDot>> CreatFig(){
  TDot S;
  std::pair<TDot,TDot> C;
  std::cout << "Введити размеры стороны: ";
  std::cin >> S;
  std::cout << "Введити координаты центра: ";
  std::cin >> C.first >> C.second;
  auto point = new Pentagon<TDot>(C, S);
  return std::shared_ptr<Figure<TDot>>(point);
 }
 static std::shared_ptr<Figure<TDot>> ReadFig(std::pair<TDot,TDot> C, TDot S){
  auto point = new Pentagon<TDot>(C, S);
  return std::shared_ptr<Figure<TDot>>(point);
 }
};

template <class TDot>
class Factory<TDot,Hexagon<TDot>>{
 public:
 static std::shared_ptr<Figure<TDot>> CreatFig(){
  TDot S;
  std::pair<TDot,TDot> C;
  std::cout << "Введити размеры стороны: ";
  std::cin >> S;
  std::cout << "Введити координаты центра: ";
  std::cin >> C.first >> C.second;
  auto point = new Hexagon<TDot>(C, S);
  return std::shared_ptr<Figure<TDot>>(point);
 }
 static std::shared_ptr<Figure<TDot>> ReadFig(std::pair<TDot,TDot> C, TDot S){
  auto point = new Hexagon<TDot>(C, S);
  return std::shared_ptr<Figure<TDot>>(point);
 }
};