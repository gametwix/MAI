#include <iostream>
#include "string.hpp"
#include "dict.hpp"


int main()
{
    
    NString::TString cmd;
    NDict::TDict dict;

    while(std::cin >> cmd)
    {
        dict.parse_comand(cmd);
        
    }
   
    
    return 0;
}