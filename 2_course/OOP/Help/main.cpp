#include <iostream>


int main()
{
    int* n[10];
    int **nl = new int*[20];
    std::cout << n << " " << &n[0] << std::endl;
    for(int i = 0;i<10;++i)
        n[i] = i;
    for(int i = 9;i>=0;--i)
    {
       std::cout << n[i] << " " << *(n+i) <<std::endl;
    }
    return 0;
}