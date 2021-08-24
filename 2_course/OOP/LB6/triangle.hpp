#pragma once 

#include <iostream>
#include <utility>
#include <cmath>

template <typename T>
class Triangle
{
    using vertex_t = std::pair<T,T>;
    
    public:
        
        vertex_t Center;
        T Size;

        Triangle() : Size(0)
        {
            Center.first = 0;
            Center.second = 0;
        }

        friend std::ostream& operator<< (std::ostream &out, const Triangle &triangle)
        {
            
            double height = triangle.Size * sqrt(3) / 2.0;
            out << "{";
            out << "(" << triangle.Center.first + triangle.Size / 2.0 << ", " << triangle.Center.second - height / 3.0 << "), ";
            out << "(" << triangle.Center.first << ", " << triangle.Center.second + 2 * height / 3.0 << "), ";
            out << "(" << triangle.Center.first - triangle.Size / 2.0 << ", " << triangle.Center.second - height / 3.0 << ")";
            out << "}";

            return out;
        }

        double Square()
        {
            return (sqrt(3)/2)*Size*Size;
        }
};