#include <iostream>
#include "string.hpp"
#include "dict.hpp"


int main()
{
    
    NString::TString cmd;
    NDict::TDict dict;
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    while(std::cin >> cmd)
    {
        dict.parse_comand(cmd);   
    }
   
    
    return 0;
}