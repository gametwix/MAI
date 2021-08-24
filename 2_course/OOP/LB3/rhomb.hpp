#pragma once
#include "figure.hpp"

class Rhomb: public Figure
{
    public:

    double diag_1;
    double diag_2;

    Rhomb(double r_diag_1, double r_diag_2)
    {
        diag_1 = r_diag_1;
        diag_2 = r_diag_2;
    }
    Rhomb(){}
    double Area() override;
    void Print_cord() override;
    Dot Center() override;
    void Cords(Dot* cord);
};

