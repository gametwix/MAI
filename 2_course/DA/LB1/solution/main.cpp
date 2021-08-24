#include "vector.hpp"
#include "base.hpp"
#include "sort_base.hpp"
#include <iostream>
#include <iomanip>
#include <stdio.h>




int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    NBase::TBase_elem elem;
    NVector::TVector<NBase::TBase_elem> base;
    
    while(std::cin >> elem.Carnum.Sym[0] >> elem.Carnum.Num >> elem.Carnum.Sym[1]>> elem.Carnum.Sym[2] >> elem.Str)
    {
        base.Push_back(elem);
    }

    NSort_base::Sort(base);

    for(int i = 0; i < base.Size(); ++i)
    {
        std::cout << base[i].Carnum.Sym[0] << " " <<  std::setfill('0') << std::setw(3);
        std::cout  << base[i].Carnum.Num << " " << base[i].Carnum.Sym[1];
        std::cout << base[i].Carnum.Sym[2]<< "\t" <<  base[i].Str << std::endl;
    }
 }