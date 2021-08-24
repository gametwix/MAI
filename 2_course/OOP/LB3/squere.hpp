#pragma once
#include "figure.hpp"
class Squere: public Figure
{
    public:
    
    double size;

    Squere(double s_size)
    {
        size = s_size;
    }
    Squere(){}
    double Area() override;
    void Print_cord() override;
    Dot Center() override;
    void Cords(Dot* cord);
};