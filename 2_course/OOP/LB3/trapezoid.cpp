#include "trapezoid.hpp"
#include <iostream>
#include <cmath>



double Trapezoid::Area()
{
    double osn = abs((osn_1-osn_2)/2);
    double high = sqrt(lateral*lateral - osn*osn);
    return high*(osn_1+osn_2)/2;
}

void Trapezoid::Cords(Dot* cord)
{
    double osn = abs((osn_1-osn_2)/2);
    double high = sqrt(lateral*lateral - osn*osn);
    cord[1].x = osn_1;
    if(osn_1 > osn_2)
    {
        cord[2].x = osn+osn_2;
        cord[3].x = osn;
    }
    else
    {
        cord[2].x = osn_2 - osn;
        cord[3].x = -osn;
    }
    cord[2].y = high;
    cord[3].y = high;
    
}

void Trapezoid::Print_cord()
{
    Dot cord[4];
    Cords(cord);
    std::cout << cord[0] << " " << cord[1] << " " << cord[2] << " " << cord[3] << " " << std::endl;
}

Dot Trapezoid::Center()
{
    double osn = abs((osn_1-osn_2)/2);
    double high = sqrt(lateral*lateral - osn*osn);
    Dot cords[4];
    Cords(cords);
    double bolsh;
    double mensh;

    if(osn_1 > osn_2)
    {
        bolsh = osn_1;
        mensh = osn_2;
    }
    else 
    {
        bolsh = osn_2;
        mensh = osn_1;
    }
    
    double y = (high*(2*bolsh+mensh))/(3*(bolsh+mensh));
    return Dot(cords[1].x/2,y);
}