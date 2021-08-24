#include <iostream>
#include <vector>
#include "squere.hpp"
#include "rhomb.hpp"
#include "trapezoid.hpp"

int main()
{
    std::cout << "Программа для работы с фигурами (квадрат, ромб, равнобедренная трапеция). Для квадрата вводится размер его стороны, для ромба размеры диаганалей, а для трапеции два основания и боковая грань. При вводе боковой стороны трапеции меньше необходимной для его замыкания координаты по y и центр по y выводятся как -nan" << std::endl;
    std::vector<Figure*> vect;
    while(true)
    {
        int sw=-1;
        double a = 0;
        double b = 0;
        double c = 0;
        unsigned int pos = 0;
        std::cout << "0 - Выход" << std::endl;
        std::cout << "1 - Добавить квадрат по индексу" << std::endl;
        std::cout << "2 - Добавить ромб по индексу" << std::endl;
        std::cout << "3 - Добавить бавнобедреннуб трапецию по индексу по индексу" << std::endl;
        std::cout << "4 - Вывести центр элимента по индексу" << std::endl;
        std::cout << "5 - Вывести координаты элимента по индексу" << std::endl;
        std::cout << "6 - Вывести площадь элимента по индексу" << std::endl;
        std::cout << "7 - Удалить элимент по индексу" << std::endl;
        std::cout << "8 - Общая площадь элиментов" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> sw;

        if(sw == 0) break;
        else
        {
            switch (sw)
            {
            case 1:
                std::cout << "Введите длину стороны квадрата:" << std::endl;
                std::cin >> a;
                std::cout << "Введите позицию:" << std::endl;
                std::cin >> pos;
                if (pos > vect.size()) pos = vect.size();
                vect.insert(vect.begin()+pos,new Squere(a));
                break;
            case 2:
                std::cout << "Введите длину первой диагонали ромба:" << std::endl;
                std::cin >> a;
                std::cout << "Введите длину второй диагонали ромба:" << std::endl;
                std::cin >> b;
                std::cout << "Введите позицию:" << std::endl;
                std::cin >> pos;
                if (pos > vect.size()) pos = vect.size();
                vect.insert(vect.begin()+pos,new Rhomb(a,b));
                break;
            case 3:
                std::cout << "Введите длину первого основания трапеции:" << std::endl;
                std::cin >> a;
                std::cout << "Введите длину второго основания трапеции:" << std::endl;
                std::cin >> b;
                std::cout << "Введите длину боковой сторон трапеции:" << std::endl;
                std::cin >> c;
                std::cout << "Введите позицию:" << std::endl;
                std::cin >> pos;
                if (pos > vect.size()) pos = vect.size();
                vect.insert(vect.begin()+pos,new Trapezoid(a,b,c));
                break;
            case 4:
                std::cout << "Введите индекс:" << std::endl;
                std::cin >> pos;
                if (vect.size() == 0)
                {
                    std::cout << "Вектор пуст" << std::endl;
                    break;
                }
                if (pos > vect.size() - 1) pos = vect.size() - 1;
                std::cout << vect[pos]->Center() << std::endl;
                break;
            case 5:
                std::cout << "Введите индекс:" << std::endl;
                std::cin >> pos;
                if (vect.size() == 0)
                {
                    std::cout << "Вектор пуст" << std::endl;
                    break;
                }
                if (pos > vect.size() - 1) pos = vect.size() - 1;
                vect[pos]->Print_cord();
                std::cout << std::endl;
                break;
            case 6:
                std::cout << "Введите индекс:" << std::endl;
                std::cin >> pos;
                if (vect.size() == 0)
                {
                    std::cout << "Вектор пуст" << std::endl;
                    break;
                }
                if (pos > vect.size() - 1) pos = vect.size() - 1;
                std::cout << vect[pos]->Area() << std::endl;
                break;
            case 7:
                std::cout << "Введите индекс:" << std::endl;
                std::cin >> pos;
                if (vect.size() == 0)
                {
                    std::cout << "Вектор пуст" << std::endl;
                    break;
                }
                if (pos > vect.size() - 1) pos = vect.size() - 1;
                vect.erase(vect.begin() + pos);
                break;
            case 8:
                double sum = 0;
                for(int i = 0;i < vect.size();++i)
                {
                    sum += vect[i]->Area();
                }
                std::cout << "Общая площадь: " << sum << std::endl;
                break;
            }
        }
    }

    return 0;
}