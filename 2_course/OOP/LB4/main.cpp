#include <iostream>
#include <tuple>
#include <utility>
#include <cmath>

#define PI 3.14159265

template <typename T>
class hexagon
{
    public:
    using cord = std::pair<T,T>;
    cord dot[6];
    int dots = 6;
};

template <typename T>
class octagon
{
    public:
    using cord = std::pair<T,T>;
    cord dot[8];
    int dots = 8;
};

template <typename T>
class triangle
{
    public:
    using cord = std::pair<T,T>;
    cord dot[3];
    int dots = 3;
};

template <typename T>
void print(T& a)
{
    for(int i = 0;i<a.dots;++i)
    {
        std::cout << "(" << std::get<0>(a.dot[i]) << ";" << std::get<1>(a.dot[i]) << ") "; 
    }
    std::cout << std::endl;
}

template <typename T>
double sqtriangle(T& tr)
{
    double osn = tr.dot[2].first;
    double h = tr.dot[1].second;
    return (osn*h)/2;
}

template <typename T>
double sqhexagon(T& hx)
{
    double st = hx.dot[0].first;
    return (st*st*3*sqrt(3))/2;
}

template <typename T>
double sqoctagon(T& hx)
{
    double st = hx.dot[0].second*2;
    return 2*st*st*(1+sqrt(2));
}


int main()
{
    std::tuple<hexagon<double>,hexagon<int>,octagon<double>,octagon<int>,triangle<double>,triangle<int>> tup;
    while(true)
    {
        int sw=-1;
        std::cout << "0 - Выход" << std::endl;
        std::cout << "1 - Добавить треугольник с вещественными координатами" << std::endl;
        std::cout << "2 - Добавить шестиугольник с вещественными координатами" << std::endl;
        std::cout << "3 - Добавить восьмиугольник с вещественными координатами" << std::endl;
        std::cout << "4 - Добавить треугольник с целыми координатами" << std::endl;
        std::cout << "5 - Добавить шестиугольник с целыми координатами" << std::endl;
        std::cout << "6 - Добавить восьмиугольник с целыми координатами" << std::endl;
        std::cout << "7 - Вывести" << std::endl;
        std::cout << "8 - Найти площадь" << std::endl;
        std::cin >> sw;
        double osn;
        double st;
        double p;
        if(sw == 0) break;
        else
        {
            switch (sw)
            {
            case 1:
                std::cout << "Введите длину основания треугольника:" << std::endl;
                std::cin >> osn;
                std::cout << "Введите длину боковой стороны треугольника:" << std::endl;
                std::cin >> st;
                std::get<4>(tup).dot[1].first = osn/2;
                std::get<4>(tup).dot[1].second = std::sqrt(st*st-(osn/2)*(osn/2));
                std::get<4>(tup).dot[2].first = osn;
                print(std::get<4>(tup));
                break;
            case 2:
                std::cout << "Введите длину стороны шестиугольника:" << std::endl;
                std::cin >> st;
                p = 60 * PI / 180;
                std::get<0>(tup).dot[0].first = st;
                std::get<0>(tup).dot[3].first = -st;
                std::get<0>(tup).dot[1].first = std::cos(p)*st;
                std::get<0>(tup).dot[1].second = std::sin(p)*st;
                std::get<0>(tup).dot[2].first = (-1)*std::cos(p)*st;
                std::get<0>(tup).dot[2].second = std::sin(p)*st;
                std::get<0>(tup).dot[4].first = (-1)*std::cos(p)*st;
                std::get<0>(tup).dot[4].second = (-1)*std::sin(p)*st;
                std::get<0>(tup).dot[5].first = std::cos(p)*st;
                std::get<0>(tup).dot[5].second = (-1)*std::sin(p)*st;
                print(std::get<0>(tup));
                break;
            case 3:
                std::cout << "Введите длину стороны восьмиугольника:" << std::endl;
                std::cin >> st;
                p = st/std::sqrt(2);
                std::get<2>(tup).dot[0].first = st/2 + p;
                std::get<2>(tup).dot[0].second = st/2;
                std::get<2>(tup).dot[1].first = st/2;
                std::get<2>(tup).dot[1].second = st/2 + p;
                std::get<2>(tup).dot[2].first = (-1)*st/2;
                std::get<2>(tup).dot[2].second = st/2 + p;
                std::get<2>(tup).dot[3].first = (-1)*(st/2 + p);
                std::get<2>(tup).dot[3].second = st/2;
                std::get<2>(tup).dot[4].first = (-1)*(st/2 + p);
                std::get<2>(tup).dot[4].second = (-1)*st/2;
                std::get<2>(tup).dot[5].first = (-1)*st/2;
                std::get<2>(tup).dot[5].second = (-1)*(st/2 + p);
                std::get<2>(tup).dot[6].first = st/2;
                std::get<2>(tup).dot[6].second = (-1)*(st/2 + p);
                std::get<2>(tup).dot[7].first = st/2 + p;
                std::get<2>(tup).dot[7].second = (-1)*st/2;
                print(std::get<2>(tup));
                break;
            case 4:
                std::cout << "Введите длину основания треугольника:" << std::endl;
                std::cin >> osn;
                std::cout << "Введите длину боковой стороны треугольника:" << std::endl;
                std::cin >> st;
                std::get<5>(tup).dot[1].first = osn/2;
                std::get<5>(tup).dot[1].second = std::sqrt(st*st-(osn/2)*(osn/2));
                std::get<5>(tup).dot[2].first = osn;
                print(std::get<5>(tup));
                break;
            case 5:
                std::cout << "Введите длину стороны шестиугольника:" << std::endl;
                std::cin >> st;
                p = 60 * PI / 180;
                std::get<1>(tup).dot[0].first = st;
                std::get<1>(tup).dot[3].first = -st;
                std::get<1>(tup).dot[1].first = std::cos(p)*st;
                std::get<1>(tup).dot[1].second = std::sin(p)*st;
                std::get<1>(tup).dot[2].first = (-1)*std::cos(p)*st;
                std::get<1>(tup).dot[2].second = std::sin(p)*st;
                std::get<1>(tup).dot[4].first = (-1)*std::cos(p)*st;
                std::get<1>(tup).dot[4].second = (-1)*std::sin(p)*st;
                std::get<1>(tup).dot[5].first = std::cos(p)*st;
                std::get<1>(tup).dot[5].second = (-1)*std::sin(p)*st;
                print(std::get<1>(tup));
                break;
            case 6:
                std::cout << "Введите длину стороны восьмиугольника:" << std::endl;
                std::cin >> st;
                p = st/std::sqrt(2);
                std::get<3>(tup).dot[0].first = st/2 + p;
                std::get<3>(tup).dot[0].second = st/2;
                std::get<3>(tup).dot[1].first = st/2;
                std::get<3>(tup).dot[1].second = st/2 + p;
                std::get<3>(tup).dot[2].first = (-1)*st/2;
                std::get<3>(tup).dot[2].second = st/2 + p;
                std::get<3>(tup).dot[3].first = (-1)*(st/2 + p);
                std::get<3>(tup).dot[3].second = st/2;
                std::get<3>(tup).dot[4].first = (-1)*(st/2 + p);
                std::get<3>(tup).dot[4].second = (-1)*st/2;
                std::get<3>(tup).dot[5].first = (-1)*st/2;
                std::get<3>(tup).dot[5].second = (-1)*(st/2 + p);
                std::get<3>(tup).dot[6].first = st/2;
                std::get<3>(tup).dot[6].second = (-1)*(st/2 + p);
                std::get<3>(tup).dot[7].first = st/2 + p;
                std::get<3>(tup).dot[7].second = (-1)*st/2;
                print(std::get<3>(tup));
                break;
            case 7:
                std::cout << "1 - Вывести треугольник с вещественными координатами" << std::endl;
                std::cout << "2 - Вывести шестиугольник с вещественными координатами" << std::endl;
                std::cout << "3 - Вывести восьмиугольник с вещественными координатами" << std::endl;
                std::cout << "4 - Вывести треугольник с целыми координатами" << std::endl;
                std::cout << "5 - Вывести шестиугольник с целыми координатами" << std::endl;
                std::cout << "6 - Вывести восьмиугольник с целыми координатами" << std::endl;
                std::cout << "7 - Вывести все" << std::endl;
                std::cin >> sw;
                switch (sw)
                {
                    case 1:
                        print(std::get<4>(tup));
                        break;
                    case 2:
                        print(std::get<0>(tup));
                        break;
                    case 3:
                        print(std::get<2>(tup));
                        break;
                    case 4:
                        print(std::get<5>(tup));
                        break;
                    case 5:
                        print(std::get<1>(tup));
                        break;
                    case 6:
                        print(std::get<3>(tup));
                        break;
                    case 7:
                        print(std::get<4>(tup));
                        print(std::get<0>(tup));
                        print(std::get<2>(tup));
                        print(std::get<5>(tup));
                        print(std::get<1>(tup));
                        print(std::get<3>(tup));
                        break;  
                }
                break;
            case 8:
                std::cout << "1 - Площадь треугольника с вещественными координатами" << std::endl;
                std::cout << "2 - Площадь шестиугольника с вещественными координатами" << std::endl;
                std::cout << "3 - Площадь восьмиугольника с вещественными координатами" << std::endl;
                std::cout << "4 - Площадь треугольника с целыми координатами" << std::endl;
                std::cout << "5 - Площадь шестиугольника с целыми координатами" << std::endl;
                std::cout << "6 - Площадь восьмиугольника с целыми координатами" << std::endl;
                std::cout << "7 - Сумма площадей" << std::endl;
                std::cin >> sw;
                switch(sw)
                {
                    case 1:
                        std::cout << sqtriangle(std::get<4>(tup)) << std::endl;
                        break;
                    case 2:
                        std::cout << sqhexagon(std::get<0>(tup)) << std::endl;
                        break;
                    case 3:
                        std::cout << sqoctagon(std::get<2>(tup)) << std::endl;
                        break;
                    case 4:
                        std::cout << sqtriangle(std::get<5>(tup)) << std::endl;
                        break;
                    case 5:
                        std::cout << sqhexagon(std::get<1>(tup)) << std::endl;
                        break;
                    case 6:
                        std::cout << sqoctagon(std::get<3>(tup)) << std::endl;
                        break;
                    case 7:
                        double sum = 0;
                        sum+=sqtriangle(std::get<4>(tup));
                        sum+=sqhexagon(std::get<0>(tup));
                        sum+=sqoctagon(std::get<2>(tup));
                        sum+=sqtriangle(std::get<5>(tup));
                        sum+=sqhexagon(std::get<1>(tup));
                        sum+=sqoctagon(std::get<3>(tup));
                        std::cout << sum << std::endl;
                }
                break;
            }
        }
    }
    return 0;
}