#pragma once
#include <utility>
 
template <typename T>
class Figure{
public:
 std::pair<T,T> Center;
 virtual void print() = 0;
 virtual void write(std::ofstream& file) = 0;
};//class Figure