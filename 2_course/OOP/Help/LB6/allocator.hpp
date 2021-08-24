#include <list>

template <typename T,size_t size_mem>
class alloc
{
    private:
        T* memory;
        std::list<T*> list;
        size_t size = size_mem;
        public:

        alloc()
        {
            memory = new T[size];
            for(size_t i = 0;i < size;++i)
                list.push_back(memory+i);
        }
        
        ~alloc()
        {
            delete[] memory;
        }

        T* allocate()
        {
            if(!list.empty())
            {
                T* point = list.back();
                list.pop_back();
                return point;
            }
            else
                return nullptr;
        }

        void deallocate(T* point)
        {
            list.push_back(point);
        }
};