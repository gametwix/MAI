#pragma once
#include <iostream>

class Dot
{
    public:
    double x;
    double y;

    //Конструкторы
    Dot(double a, double b)
    {
        x = a;
        y = b;
    }

    Dot()
    {
        x = 0;
        y = 0;
    }

    //Операторы ввода вывода
    friend std::ostream& operator<< (std::ostream &out, const Dot &a)
    {
        out << "(" << a.x << "," << a.y << ")";
        return out;
    }
    
    friend std::istream& operator>>(std::istream &in, Dot &a)
    {
        in >> a.x >> a.y;
        return in;
    }

};