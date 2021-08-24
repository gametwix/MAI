#pragma once
#include "dot.hpp"

class Figure
{
    public:
    virtual double Area() = 0;
    virtual void Print_cord() = 0;
    virtual Dot Center() = 0;
};