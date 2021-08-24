#include "rhomb.hpp"
#include <iostream>
#include <cmath>


double Rhomb::Area()
{
    return diag_1*diag_2/2;
}

void Rhomb::Cords(Dot* cord)
{
    cord[1].x = diag_1/2;
    cord[1].y = (-1)*diag_2/2;
    cord[2].x = diag_1;
    cord[3].x = diag_1/2;
    cord[3].y = diag_2/2;
}

void Rhomb::Print_cord()
{
    Dot cord[4];
    Cords(cord);
    std::cout << cord[0] << " " << cord[1] << " " << cord[2] << " " << cord[3] << " " << std::endl;
}

Dot Rhomb::Center()
{
    return Dot(0,diag_2/2);
}



