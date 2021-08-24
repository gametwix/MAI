#include "ip.hpp"


//Конструкторы

NIP::IPAddress::IPAddress()
{
    for(int i = 0;i < 4;++i)
    {
        bytes[i]=0;
    }
}

NIP::IPAddress::IPAddress(unsigned char b1,unsigned char b2,unsigned char b3,unsigned char b4) 
{
    bytes[0] = b1;
    bytes[1] = b2;
    bytes[2] = b3;
    bytes[3] = b4;
}

NIP::IPAddress::IPAddress(const NIP::IPAddress& b)
{
    bytes[0] = b.bytes[0];
    bytes[1] = b.bytes[1];
    bytes[2] = b.bytes[2];
    bytes[3] = b.bytes[3];
}


//Оператор присваивания
void NIP::IPAddress::operator =(const NIP::IPAddress& b)
{
    bytes[0] = b.bytes[0];
    bytes[1] = b.bytes[1];
    bytes[2] = b.bytes[2];
    bytes[3] = b.bytes[3];
}

//Оператор возврата байтов
unsigned char& NIP::IPAddress::operator [](int i)
{
    return bytes[i];
}

//Оператовы арифметических действий 
NIP::IPAddress NIP::IPAddress::operator +(const NIP::IPAddress& b)
{
    IPAddress result;
    for(int i = 0;i < 4;++i)
    {
        result.bytes[i] = bytes[i] + b.bytes[i];
    }
    return result;
}

NIP::IPAddress NIP::IPAddress::operator -(const NIP::IPAddress& b)
{
    IPAddress result;
    for(int i = 0;i < 4;++i)
    {
        result.bytes[i] = bytes[i] - b.bytes[i];
    }
    return result;
}

//Операторы сравнения

bool NIP::IPAddress::operator ==(const NIP::IPAddress& b)
{
    for(int i = 0;i < 4;++i)
    {
        if(bytes[i]!=b.bytes[i])
            return false;
    }
    return true;
}

bool NIP::IPAddress::operator >(const NIP::IPAddress& b)
{
    for(int i = 0;i < 4;++i)
    {
        if(bytes[i] > b.bytes[i])
            return true;
        if(bytes[i] < b.bytes[i])
            break;
    }
    return false;
}

 bool NIP::IPAddress::operator <( const NIP::IPAddress& b)
{
    for(int i = 0;i < 4;++i)
    {
        if(bytes[i] < b.bytes[i])
            return true;
        if(bytes[i] > b.bytes[i])
            break;
    }
    return false;
}

bool NIP::IPAddress::operator >=(const NIP::IPAddress& b)
{
    for(int i = 0;i < 4;++i)
    {
        if(bytes[i] > b.bytes[i])
            return true;
        if(bytes[i] < b.bytes[i])
            return false;
    }
    return true;
}

bool NIP::IPAddress::operator <=(const NIP::IPAddress& b)
{
    for(int i = 0;i < 4;++i)
    {
        if(bytes[i] < b.bytes[i])
            return true;
        if(bytes[i] > b.bytes[i])
            return false;
    }
    return true;
}


//Коньюнкция по маске
NIP::IPAddress NIP::IPAddress::from_mask(const NIP::IPAddress& mask)
{
    IPAddress result;
    for(int i = 0;i < 4;++i)
    {
        result.bytes[i]=bytes[i] & mask.bytes[i];
    }
    return result;
}

//Является ли IP частью подсети
bool NIP::IPAddress::ip_in_net(const NIP::IPAddress& ip_net,const NIP::IPAddress& mask)
{
    if(from_mask(mask) == ip_net)
        return true;
    else
        return false;
}


//Пользовательский литерал преобразования строки в IPAdress
NIP::IPAddress operator "" _ip(const char* str, size_t size)
{
    int start = 0;
    int dot = 0;
    unsigned char res[4] = {};
    std::string s = std::string(str,size);
    for(int i = 0;i < 3;++i)
    {
        dot = s.find(".");
        res[i]= std::stoi(s.substr(start,dot));
        s = s.substr(dot+1,s.length());

    }
    res[3]=std::stoi(s.substr(start));

    NIP::IPAddress result(res[0],res[1],res[2],res[3]);

    return result;
}

NIP::IPAddress NIP::IPAddress::str_ip(std::string str)
{
    int start = 0;
    int dot = 0;
    unsigned char res[4] = {};
    std::string s = str;
    for(int i = 0;i < 3;++i)
    {
        dot = s.find(".");
        res[i]= std::stoi(s.substr(start,dot));
        s = s.substr(dot+1,s.length());

    }
    res[3]=std::stoi(s.substr(start));

    NIP::IPAddress result(res[0],res[1],res[2],res[3]);

    return result;
}

