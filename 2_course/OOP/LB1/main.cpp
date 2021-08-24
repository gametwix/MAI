/*
Программа для работы со счетами в старой британской системе
Создатель Мохляков Павел Александрович
*/
#include <iostream>
#include "britishmoney.hpp"

int main()
{
    

    while(true)
    {
        BritishMoney a;
        BritishMoney b;
        int sw=-1;
        double c;
        
        std::cout << "0 - Выход" << std::endl;
        std::cout << "1 - Сложить 2 счета" << std::endl;
        std::cout << "2 - Вычесть один счет из другого" << std::endl;
        std::cout << "3 - Умножить счет на число" << std::endl;
        std::cout << "4 - Разделить счет на число" << std::endl;
        std::cout << "5 - Разделить счет на счет" << std::endl;
        std::cout << "6 - Подменю сравнения двух счетов" << std::endl;
        std::cout << "Выбирите действие: ";
        std::cin >> sw;

        if(sw == 0) break;
        else
        {
            switch (sw)
            {
            case 1:
                std::cout << "Введите количество денег на первом счету (ponds shilling penny):" << std::endl;
                std::cin >> a;
                std::cout << "Введите количество денег на втором счету (ponds shilling penny):" << std::endl;
                std::cin >> b;
                std::cout << "Сумма равна " << a+b << std::endl;
                break;
            case 2:
                std::cout << "Введите количество денег на первом счету (ponds shilling penny):" << std::endl;
                std::cin >> a;
                std::cout << "Введите количество денег на втором счету (ponds shilling penny):" << std::endl;
                std::cin >> b;
                std::cout << "Разность равна " << a-b << std::endl;
                break;
            case 3:
                std::cout << "Введите количество денег на первом счету (ponds shilling penny):" << std::endl;
                std::cin >> a;
                std::cout << "Введите число:" << std::endl;
                std::cin >> c;
                std::cout << "Произведение равно " << a*c << std::endl;
                break;
            case 4:
                std::cout << "Введите количество денег на первом счету (ponds shilling penny):" << std::endl;
                std::cin >> a;
                std::cout << "Введите число:" << std::endl;
                std::cin >> c;
                std::cout << "Частное равно " << a/c << std::endl;
                break;
            case 5:
                std::cout << "Введите количество денег на первом счету (ponds shilling penny):" << std::endl;
                std::cin >> a;
                std::cout << "Введите количество денег на втором счету (ponds shilling penny):" << std::endl;
                std::cin >> b;
                std::cout << "Частное равна " << a/c << std::endl;
                break;
            case 6:
                while(true)
                {
                    int sw2 = -1;
                    std::cout << "0 - Выйти из подменю" << std::endl;
                    std::cout << "1 - Равны ли 2 счета" << std::endl;
                    std::cout << "2 - Больше ли первый счет" << std::endl;
                    std::cout << "3 - Меньше ли первый счет" << std::endl;
                    std::cout << "4 - Больше или равен первый счет" << std::endl;
                    std::cout << "5 - Меньше или равен первый счет" << std::endl;
                    std::cout << "Выбирите действие: ";
                    std::cin >> sw2;
                    
                    if(sw2 == 0) break;
                    else
                    {
                        switch (sw2)
                        {
                        case 1:
                            std::cout << "Введите количество денег на первом счету (ponds shilling penny):" << std::endl;
                            std::cin >> a;
                            std::cout << "Введите количество денег на втором счету (ponds shilling penny):" << std::endl;
                            std::cin >> b;
                            if(a == b) 
                                std::cout << "true" << std::endl;
                            else
                                std::cout << "false" << std::endl;
                            break;
                        case 2:
                            std::cout << "Введите количество денег на первом счету (ponds shilling penny):" << std::endl;
                            std::cin >> a;
                            std::cout << "Введите количество денег на втором счету (ponds shilling penny):" << std::endl;
                            std::cin >> b;
                            if(a > b) 
                                std::cout << "true" << std::endl;
                            else
                                std::cout << "false" << std::endl;
                            break;
                        case 3:
                            std::cout << "Введите количество денег на первом счету (ponds shilling penny):" << std::endl;
                            std::cin >> a;
                            std::cout << "Введите количество денег на втором счету (ponds shilling penny):" << std::endl;
                            std::cin >> b;
                            if(a < b) 
                                std::cout << "true" << std::endl;
                            else
                                std::cout << "false" << std::endl;
                            break;
                        case 4:
                            std::cout << "Введите количество денег на первом счету (ponds shilling penny):" << std::endl;
                            std::cin >> a;
                            std::cout << "Введите количество денег на втором счету (ponds shilling penny):" << std::endl;
                            std::cin >> b;
                            if(a >= b) 
                                std::cout << "true" << std::endl;
                            else
                                std::cout << "false" << std::endl;
                            break;
                        case 5:
                            std::cout << "Введите количество денег на первом счету (ponds shilling penny):" << std::endl;
                            std::cin >> a;
                            std::cout << "Введите количество денег на втором счету (ponds shilling penny):" << std::endl;
                            std::cin >> b;
                            if(a <= b) 
                                std::cout << "true" << std::endl;
                            else
                                std::cout << "false" << std::endl;
                            break;
                        
                        default:
                            break;
                        }
                    }
                    

                }

                break;

            default:
                break;
            }
        }
    }
    
    return 0;
}