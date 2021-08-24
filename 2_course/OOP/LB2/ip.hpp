#include <string>
#include <iostream>

namespace NIP
{
    class IPAddress
    {
        protected:
        unsigned char bytes[4];

        public:
        //Конструкторы
        IPAddress();
        IPAddress(unsigned char b1,unsigned char b2,unsigned char b3,unsigned char b4);
        IPAddress(const IPAddress& b);

        //Оператор присваивания
        void operator =(const IPAddress& b);
        //Оператор возврата байтов
        unsigned char& operator [](int i); 
        //Оператовы арифметических действий 
        IPAddress operator +(const IPAddress& b);
        IPAddress operator -(const IPAddress& b);
        //Операторы сравнения 
        bool operator ==(const IPAddress& b);
        bool operator >(const IPAddress& b);
        bool operator <(const IPAddress& b);
        bool operator >=(const IPAddress& b);
        bool operator <=(const IPAddress& b);


        //Коньюнкция по маске
        IPAddress from_mask(const IPAddress& mask);

        //Является ли IP частью подсети
        bool ip_in_net(const IPAddress& ip_net,const IPAddress& mask);

        //Операторы ввода вывода
        friend std::ostream& operator<< (std::ostream &out, const IPAddress &a)
        {
            for(int i = 0;i < 3;++i)
            {
                out << (int)a.bytes[i] << ".";
            }
            out << (int)a.bytes[3];
            return out;
        }
        
        friend std::istream& operator>>(std::istream &in, IPAddress &a)
        {
            char str[30];
            in >> str;
            a = a.str_ip(str);
            return in;
        }

        IPAddress str_ip(std::string str);
    }; //class TIP
} //namespace NIP


//Пользовательский литерал преобразования строки в IPAdress
NIP::IPAddress operator "" _ip(const char* str, size_t size);
