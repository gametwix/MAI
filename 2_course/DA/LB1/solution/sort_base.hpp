#ifndef SORTBASE
#define SORTBASE

#include "vector.hpp"
#include "base.hpp"

namespace NSort_base
{
    const void Sort_ch( NVector::TVector<NBase::TBase_elem>  &base,NVector::TVector<NBase::TBase_elem> &newbase, int num)
    {
        int k[26] = {};
        //newbase.Renew(base.Size());
        int size = base.Size();
        for(int i = 0;i < size;++i)
        {
            int l = (int)base[i].Carnum.Sym[num]-65;
            ++k[l];
        }
        for(int i=1;i<26;++i)
        {
            k[i]+=k[i-1];
        }
        for(int i = size - 1;i >= 0;--i)
        {
            int l = (int)base[i].Carnum.Sym[num]-65;
            newbase[k[l]-1] = base[i];
            --k[l];
        }

    }


    void Sort_int(const NVector::TVector<NBase::TBase_elem> &base,NVector::TVector<NBase::TBase_elem> &newbase)
    {
        int k[1000] = {};
        //newbase.Renew(base.Size());
        int size = base.Size();
        for(int i = 0;i < size;++i)
        {
            int l = base[i].Carnum.Num;
            ++k[l];
        }
        for(int i=1;i<1000;++i)
        {
            k[i]+=k[i-1];
        }
        for(int i = size - 1;i >= 0;--i)
        {
            int l = base[i].Carnum.Num;
            newbase[k[l]-1] = base[i];
            --k[l];
        }
    }

    void Sort(NVector::TVector<NBase::TBase_elem> &base1)
    {
        NVector::TVector<NBase::TBase_elem> base2;
        base2.Renew(base1.Size());
        Sort_ch(base1,base2,2);
        Sort_ch(base2,base1,1);
        Sort_int(base1,base2);
        Sort_ch(base2,base1,0);
    }

} // namespace NSort_base

#endif