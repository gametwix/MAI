#pragma once

#include <cstring>
#include <cstddef>
#include <iostream>

namespace NVector
{
    int min(int a,int b)
    {
        if(a < b) return a;
        else return b;
    }
    
    template <typename T>
    class TVector
    {
        protected:
        T *Data;
        size_t Size_data;
        size_t Size_malloc;

        void Resize(size_t newsize)
        {
            T *new_data = new T[newsize];

            std::memcpy(new_data,Data,sizeof(T)*Size_data);
            delete[] Data;
            Data = nullptr;
            Data = new_data;
        }

        void Clear()
        {
            delete[] Data;
            Data = nullptr;
            Size_data = 0;
            Size_malloc = 0;
        }
        

        public:

        TVector()
        {
            Data = nullptr;
            Size_data = 0;
            Size_malloc = 0;
        }

        ~TVector()
        {
            Clear();
        }
        
        T* &Get_data()
        {
            return Data;
        }

        const int Size()
        const 
        {
            return Size_data;
        }


        int Size()
        {
            return Size_data;
        }

        void Renew(size_t new_size)
        {
            Resize(new_size);
            Size_data = new_size;
            Size_malloc = new_size;
        }

        T* Begin()
        {
            return Data;
        }

        T* End()
        {
            return &Data[Size()];
        }

        void Set(T* D,size_t size)
        {
            Data = D;
            Size_data = size;
            Size_malloc = size;
        }
        
        

        void Push_back(const T& item)
        {

            if(Size_data+1 > Size_malloc)
            {
                if(Size_malloc == 0)
                    Size_malloc = 2;
                else 
                    Size_malloc *= 2;

                Resize(Size_malloc);
            }
            
            Data[Size_data] = item;
            ++Size_data;
        }

        T& operator[](size_t itr)
        {
            return Data[itr];
        }

        const T &operator[](size_t itr) const {
            return Data[itr];
        }

        void operator=(const TVector<T> &second) 
        {
            Clear();

            for(int i=0;i < second.Size_data;++i)
            {
                Push_back(second.Data[i]);
            }
        }

    }; //class TVector

    
} //namespace NVector


