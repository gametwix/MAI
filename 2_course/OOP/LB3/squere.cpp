#include "squere.hpp"
#include <iostream>



double Squere::Area()
{
    return size*size;
}

void Squere::Cords(Dot* cord)
{
    cord[1].x = size;
    cord[2].x = size;
    cord[2].y = size;
    cord[3].y = size;
}

void Squere::Print_cord()
{
    Dot cord[4];
    Cords(cord);
    std::cout << cord[0] << " " << cord[1] << " " << cord[2] << " " << cord[3] << " " << std::endl;
}

Dot Squere::Center()
{
    return Dot(size/2,size/2);
}