#pragma once
#include "figure.hpp"

class Trapezoid: public Figure
{
    public:

    double osn_1;
    double osn_2;
    double lateral;

    Trapezoid(double t_osn_1, double t_osn_2, double t_lat)
    {
        osn_1 = t_osn_1;
        osn_2 = t_osn_2;
        lateral = t_lat;
    }
    Trapezoid(){}
    double Area() override;
    void Print_cord() override;
    Dot Center() override;
    void Cords(Dot* cord);
};