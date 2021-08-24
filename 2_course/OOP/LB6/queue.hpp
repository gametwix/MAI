#pragma once

#include <memory>
#include <iostream>
#include "allocator.hpp"

template <typename T, size_t size_alloc>
class Queue
{
    private:

        template <typename Q>
        struct Queue_elem
        {
            Q key;
            std::shared_ptr<Queue_elem<Q>> next;
            std::shared_ptr<Queue_elem<Q>> prev;

            static alloc::custom_allocator<Queue_elem<Q>,size_alloc> &get_allocator()
            {
                static alloc::custom_allocator<Queue_elem<Q>,size_alloc> al;
                return al;
            }


            void* operator new(size_t size)
            {
                void* point = get_allocator().allocate();
                if(point == nullptr)
                    throw -1;
                return point;
            }
            void operator delete(void* point)
            {
                get_allocator().deallocate((Queue_elem<Q>*)point);
            }
            Queue_elem()
            {
                next = nullptr;
                prev = nullptr;
            }


            Queue_elem(const Q data)
            {
                key = data;
                next = nullptr;
                prev = nullptr;
            }
        };

    size_t size = 0;
    std::shared_ptr<Queue_elem<T>> start;
    std::shared_ptr<Queue_elem<T>> finish;
    std::shared_ptr<Queue_elem<T>> Nil;


    Queue_elem<T>* Top()
    {
        return start;
    }

    public:
    bool be = false;

        Queue()
        {
            start = nullptr;
            finish = nullptr;
            Nil = nullptr;
            try
            {
                Nil = std::shared_ptr<Queue_elem<T>>(new Queue_elem<T>);
                Nil->prev = nullptr;
                Nil->next = start;
                be = true;
            }
            catch(int i)
            {
                std::cout << "Невозможно создать очередь такого размера" << std::endl;
                be = false;
            }
        }


        void Push(const T& data)
        {
            Queue_elem<T>* l = new Queue_elem<T>(data);
            std::shared_ptr<Queue_elem<T>> elem(l);
            if(start == nullptr)
            {
                finish = elem;
            }
            else
            {
                elem->next = start;
                start->prev = elem;
            }
            elem->prev = Nil;
            Nil->next = elem;
            start = elem;
            ++size;
        }


        T Pop()
        {
            if(finish == nullptr)
            {
                throw -1;
            }
            T data = finish->key;
            if(finish->prev == Nil)
            {
                finish = nullptr;
                start = nullptr;
            }
            else
            {
                finish = finish->prev;
            }
            --size;
            return data;
        }

        class iterator
        {
            
            Queue_elem<T>* data_iter;
            public:
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

                iterator()
                {
                    data_iter = nullptr;
                }
                
                iterator(Queue_elem<T>* second)
                {
                    data_iter = second;
                }

                T*& operator->()
                {
                    return &data_iter->key;
                }

                T& operator*()
                {
                    return data_iter->key;
                }

                bool operator==(const iterator &second)
                {
                    return (data_iter == second.data_iter);
                }

                bool operator==(const T* &second)
                {
                    return (data_iter == second);
                }

                bool operator!=(const iterator &second)
                {
                    return (data_iter != second.data_iter);
                }

                bool operator!=(const T* &second)
                {
                    return (data_iter != second);
                }

                void operator=(const iterator &second)
                {
                    data_iter = second.data_iter;
                }

                void operator=(const T* &second)
                {
                    data_iter = second;
                }

                iterator operator++()
                {
                    if(data_iter == nullptr)
                    {
                        throw -1;
                    }
                    data_iter = data_iter->prev.get();
                    return iterator(data_iter);
                }

                iterator operator--()
                {
                    if(data_iter == nullptr)
                    {
                        throw -1;
                    }
                    data_iter = data_iter->next.get();
                    return iterator(data_iter);
                }

                iterator operator+(const size_t &ind)
                {
                    iterator it(data_iter);
                    for(int i=0;i<ind;++i)
                    {
                        if(it.data_iter == nullptr)
                        {
                            throw -1;
                        }
                        it.data_iter = it.data_iter->prev.get();
                    }
                    return it;
                }

                iterator operator-(const size_t &ind)
                {
                    iterator it(data_iter);
                    for(int i=0;i<ind;++i)
                    {
                        if(it.data_iter == nullptr)
                        {
                            throw -1;
                        }
                        it.data_iter = it.data_iter->next.get();
                    }
                    return it;
                }
        };

        iterator Begin()
        {
            return iterator(finish.get());
            
        }

        iterator End()
        {
            iterator iter = start.get();
            ++iter;
            return (iter);
        }

        void Insert(iterator it,T data)
        {
            if((it == nullptr) || (it == Nil.get()))
                Push(data);
            else
            {
                Push(T());
                for(iterator iter = End() - 1;iter != it;--iter)
                {
                    *iter = *(iter-1);
                }
                *it = data;
            }
            
        }

        void Erase(iterator it)
        {
            if((it == nullptr) || (it == Nil.get()))
            {
                throw -1;
            }
            for(iterator iter = it;iter != Begin();--iter)
            {
                *iter = *(iter-1);
            }
            Pop();
        }

        int Size()
        {
            return size;
        }
};