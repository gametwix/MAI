#include <iostream>
#include "bignum.hpp"



int main(){
    NBigNum::TBigNum num[2];
    char sym;
    while(std::cin >> num[0] >> num[1] >> sym){
        switch(sym){
            case '+':
                std::cout << num[0] + num[1] << std::endl;
                break;
            case '-':
                try{
                std::cout << num[0] - num[1] << std::endl;
                } catch( int i){
                    std::cout << "Error" <<std::endl;
                }
                break;
            case '*':
                std::cout << num[0] * num[1] << std::endl;
                break;
            case '/':
                try{
                std::cout << num[0] / num[1] << std::endl;
                } catch( int i){
                    std::cout << "Error" <<std::endl;
                }
                break;
            case '^':
                try{
                std::cout << (num[0] ^ num[1]) << std::endl;
                } catch( int i){
                    std::cout << "Error" <<std::endl;
                }
                break;
            case '>':
                std::cout << ((num[0] > num[1]) ? "true" : "false") << std::endl;
                break;
            case '=':
                std::cout << ((num[0] == num[1]) ? "true" : "false") << std::endl;
                break;
            case '<':
                std::cout << ((num[0] < num[1]) ? "true" : "false") << std::endl;
                break;
        }
    }

    return 0;
}