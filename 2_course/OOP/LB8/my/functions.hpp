#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <vector>
#include <memory>
#include <condition_variable>

template <typename T>
class Functions{
protected:
size_t size_queue;
std::thread thread;
std::queue<T*> queue;
std::vector<T*> vector;
std::condition_variable waiter;
std::vector<std::function<void(const std::vector<T*>&)>> funcs;
bool run = false;

static void Processing(Functions *who)
{
    int i = 0;
    std::unique_lock<std::mutex> lock(who->mutex);
    while(who->run)
    {
        who->waiter.wait(lock);
        
            if(!who->queue.empty()){
                int size_l;
                if(who->size_queue == who->queue.size())
                    size_l = who->size_queue;
                else
                    size_l = who->queue.size();

                for(int i = 0; i < size_l;++i){
                    T* elem = who->queue.front();
                    who->vector.push_back(elem);
                    who->queue.pop();
                }

                for(auto i: who->funcs)
                    i(who->vector);
                who->vector.clear();
            }
        
        ++i;
        
        who->waiter.notify_one();
    }
}

public:
std::mutex mutex;

explicit Functions(size_t queue_in):size_queue(queue_in){};

~Functions(){Stop();}
void AddFunction(std::function<void(const std::vector<T*>&)>&& func){
    if(!run) {
            funcs.push_back(func);
    } else{
            throw -1;
    }
}

void Push(T* elem){
    std::unique_lock<std::mutex> lock(mutex);
    queue.push(elem);
    if(queue.size() == size_queue){
        waiter.notify_one();
        waiter.wait(lock);
    }
}



void Start(){
    run = true;
    thread = std::thread(Processing,this);
}

void Stop(){
    run = false;
    waiter.notify_one();
    thread.join();
}

};