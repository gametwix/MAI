#include <iostream>
#include "ip.hpp"

int main()
{
    std::cout << "IP адреса и маски вводятся как 4 положительных чистла от 0 до 255, разделенных точками." << std::endl;
    std::cout << "Пример: 192.168.1.1" << std::endl;
    std::cout << "Сложение и вычитание поразрядное и цикличное (0-1=255)." << std::endl;

    while(true)
    {
        NIP::IPAddress ip_1;
        NIP::IPAddress ip_2;
        NIP::IPAddress net;
        NIP::IPAddress mask;
        int sw=-1;
        std::cout << "0 - Выход" << std::endl;
        std::cout << "1 - Сложить 2 IP" << std::endl;
        std::cout << "2 - Вычесть один IP из другого" << std::endl;
        std::cout << "3 - Равны ли 2 IP" << std::endl;
        std::cout << "4 - Больше ли первый IP" << std::endl;
        std::cout << "5 - Меньше ли первый IP" << std::endl;
        std::cout << "6 - Больше или равен первый IP" << std::endl;
        std::cout << "7 - Меньше или равен первый IP" << std::endl;
        std::cout << "8 - Находится ли IP в подсети" << std::endl;
        std::cout << "Выбирите действие: ";
        std::cin >> sw;

        if(sw == 0) break;
        else
        {
            switch (sw)
            {
            case 1:
                std::cout << "Введите первый IP:" << std::endl;
                std::cin >> ip_1;
                std::cout << "Введите второй IP:" << std::endl;
                std::cin >> ip_2;
                std::cout << "Сумма равна " << ip_1 + ip_2 << std::endl;
                break;
            case 2:
                std::cout << "Введите первый IP:" << std::endl;
                std::cin >> ip_1;
                std::cout << "Введите второй IP:" << std::endl;
                std::cin >> ip_2;
                std::cout << "Разность равна " << ip_1 - ip_2 << std::endl;
                break;
            case 3:
                std::cout << "Введите первый IP:" << std::endl;
                std::cin >> ip_1;
                std::cout << "Введите второй IP:" << std::endl;
                std::cin >> ip_2;
                if(ip_1 == ip_2) 
                    std::cout << "true" << std::endl;
                else
                    std::cout << "false" << std::endl;
                break;
            case 4:
                std::cout << "Введите первый IP:" << std::endl;
                std::cin >> ip_1;
                std::cout << "Введите второй IP:" << std::endl;
                std::cin >> ip_2;
                if(ip_1 > ip_2) 
                    std::cout << "true" << std::endl;
                else
                    std::cout << "false" << std::endl;
                break;
            case 5:
                std::cout << "Введите первый IP:" << std::endl;
                std::cin >> ip_1;
                std::cout << "Введите второй IP:" << std::endl;
                std::cin >> ip_2;
                if(ip_1 < ip_2) 
                    std::cout << "true" << std::endl;
                else
                    std::cout << "false" << std::endl;
                break;
            case 6:
                std::cout << "Введите первый IP:" << std::endl;
                std::cin >> ip_1;
                std::cout << "Введите второй IP:" << std::endl;
                std::cin >> ip_2;
                if(ip_1 >= ip_2) 
                    std::cout << "true" << std::endl;
                else
                    std::cout << "false" << std::endl;
                break;
            case 7:
                std::cout << "Введите первый IP:" << std::endl;
                std::cin >> ip_1;
                std::cout << "Введите второй IP:" << std::endl;
                std::cin >> ip_2;
                if(ip_1 <= ip_2) 
                    std::cout << "true" << std::endl;
                else
                    std::cout << "false" << std::endl;
                break;
            case 8:
                std::cout << "Введите IP:" << std::endl;
                std::cin >> ip_1;
                std::cout << "Введите IP сети:" << std::endl;
                std::cin >> net;
                std::cout << "Введите маску сети:" << std::endl;
                std::cin >> mask;
                if(ip_1.ip_in_net(net,mask)) 
                    std::cout << "true" << std::endl;
                else
                    std::cout << "false" << std::endl;
                break;
            }
        }
    }
    return 0;
}