#include <iostream>
#include <algorithm>
#include "queue.hpp"
#include "triangle.hpp"

int main()
{   
    Queue<Triangle<int>, 3> que;
    if(!que.be)
        return 0;


     while(true)
    {
        int sw=-1;
        Triangle<int> tr;
        int pos = 0;
        
        int minimal_suare = 0;
        auto print = [](Triangle<int> n) { std::cout << n << std::endl; };
        
        std::cout << std::endl;
        std::cout << "0 - Выход" << std::endl;
        std::cout << "1 - Добавить треугольник в конец очереди" << std::endl;
        std::cout << "2 - Добавить треугольник по индексу" << std::endl;
        std::cout << "3 - Удалить треугольник в начале очереди" << std::endl;
        std::cout << "4 - Удалить треугольник по индексу" << std::endl;
        std::cout << "5 - Вывести очередь" << std::endl;
        std::cout << "6 - Вывести количество треугольников площадь которых меньше указанной" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> sw;

        if(sw == 0)
        {
            std::cout << std::endl;
            break;
        } 
        else
        {
            switch (sw)
            {
            case 1:
                std::cout << "Введите длину стороны треугольника:";
                std::cin >> tr.Size;
                std::cout << "Введите координаты центра треугольника:";
                std::cin >> tr.Center.first >> tr.Center.second;
                try
                {
                    que.Push(tr);
                    std::cout << std::endl << "Добавление произведено успешно" << std::endl;
                }
                catch(int i)
                {
                    std::cout << "Выход за границу аллокатора" << std::endl;
                }
                break;
            case 2:
                std::cout << "Введите длину стороны треугольника:";
                std::cin >> tr.Size;
                std::cout << "Введите координаты центра треугольника:";
                std::cin >> tr.Center.first >> tr.Center.second;
                std::cout << "Введите индекс:" ;
                std::cin >> pos;
                try
                {
                    que.Insert(que.Begin()+(pos-1),tr);
                    std::cout << std::endl << "Добавление произведено успешно" << std::endl;
                }
                catch(int)
                {
                    std::cout << std::endl << "Выход за допустимую границу коллекции" << std::endl;
                }
                break;
            case 3:
                try
                {
                    que.Pop();
                    std::cout << std::endl << "Удаление произведено успешно" << std::endl;
                }
                catch(int)
                {
                    std::cout << std::endl << "Выход за допустимую границу коллекции" << std::endl;
                }
                break;
            case 4:
                std::cout << "Введите индекс:";
                std::cin >> pos;
                try
                {
                    que.Erase(que.Begin()+(pos-1));
                    std::cout << std::endl << "Удаление произведено успешно" << std::endl;
                }
                catch(int)
                {
                    std::cout << std::endl << "Выход за допустимую границу коллекции" << std::endl;
                }
                break;
            case 5:
                try
                {
                    if(que.Begin() == nullptr)
                        throw -1;
                    std::for_each(que.Begin(),que.End(),print);
                }
                catch(int)
                {
                    std::cout << std::endl << "Коллекция пуста" << std::endl;
                }
                break;
            case 6:
            
                try
                {
                    if(que.Begin() == nullptr)
                        throw -1;
                    std::cout << "Введите минимальную площадь:" ;
                    std::cin >> minimal_suare;
                    auto figures_less_squre = [minimal_suare](Triangle<int> n) { return (n.Square() < minimal_suare); };
                    std::cout << std::endl  << "Количество треугольников площадь которых меньше указанной: " << std::count_if(que.Begin(), que.End(), figures_less_squre) << std::endl;
                }
                catch(int)
                {
                    std::cout << std::endl << "Коллекция пуста" << std::endl;
                }
            }
        }
    }

    return 0;
}