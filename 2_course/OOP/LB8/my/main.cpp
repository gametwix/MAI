#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include "Figure.hpp"
#include "Hexagon.hpp"
#include "Pentagon.hpp"
#include "Rhomb.hpp"
#include "functions.hpp"
#include "factory.hpp"

/*
Автор: Мохляков Павел
Лабораторная работа на тему многопоточность
Обработка фигор происходит в отдельном потоке
*/
int main(int argc, char **argv){
    size_t buf_size = 10;
    if(argc == 2){
        std::stringstream arg;
        arg << argv[1];
        arg >> buf_size;
    }

    Functions<Figure<int>> func(buf_size);
    
    func.AddFunction([](const std::vector<Figure<int>*>& figures){
        for(const auto& figure: figures) {
            figure->print();
        }
    });

    func.AddFunction([](const std::vector<Figure<int>*>& figures){
        static int i = 0;
        std::string str  = std::to_string(i)+".txt";
        std::ofstream file(str);
        for(auto figure: figures) {
            figure->write(file);
        }
        ++i;
        file.close();
    });

    func.Start();
    int sw;
    while(true)
    {
        std::cout << "0 - Выход" << std::endl;
        std::cout << "1 - Создать ромб" << std::endl;
        std::cout << "2 - Создать пятиугольник" << std::endl;
        std::cout << "3 - Создать шестиугольник" << std::endl;
        std::cout << "Ввод: "; 
        std::cin >> sw;
        
        if(sw == 0)
            break;
        switch (sw)
        {
        case 1:
            func.Push(Factory<int,Rhomb<int>>::CreatFig());
            break;
        case 2:
            func.Push(Factory<int,Pentagon<int>>::CreatFig());
            break;
        case 3:
            func.Push(Factory<int,Hexagon<int>>::CreatFig());
            break;
        
        default:
            break;
        }
    }
    return 0;
}
