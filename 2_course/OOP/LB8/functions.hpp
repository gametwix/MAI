#pragma once

#include <condition_variable>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <queue>
#include <functional>
#include <atomic>
#include <vector>

#include <iostream>

template<typename T>
class TFunctions
{
private:
bool started = false, running = true;
    std::mutex mutex_queue;
    std::thread thread;
    std::condition_variable cv;
    std::queue<T> queue;
    std::vector<std::function<void(const std::vector<T>&)>> functions;
    std::size_t queue_max_size = 0;

    static void execution_in_thread(TFunctions *this_){
        while(this_->running) {
            std::unique_lock<std::mutex> lk(this_->mutex_queue);
            this_->cv.wait(lk, [this_]() {return this_->queue_full() || !this_->running;});
            std::vector<T> vec;
            while(!this_->queue.empty()) {
                vec.push_back(this_->queue.front());
                this_->queue.pop();
            }
            std::reverse(vec.begin(), vec.end());
            if(!vec.empty()) {
                for (auto item: this_->handlers) {
                    item(vec);
                }
            }
            lk.unlock();
            this_->cv.notify_one();
        }
    }
    
public:
    explicit TFunctions(size_t queue_ms):queue_max_size(queue_ms){}

    ~TFunctions(){
        if(running && started){
            stop();
        }
    }

    void start(){
        started = true;
        thread = std::thread(execution_in_thread, this);
    }

    void stop(){
        running = false;
        cv.notify_one();
        thread.join();
    }

    bool queue_full(){
        return queue.size() == queue_max_size;
    }

    void push(T el){
        std::unique_lock<std::mutex> lk(mutex_queue);
        queue.push(el);
        if(queue_full()) {
            cv.notify_one();
            cv.wait(lk, [this](){return queue.empty();});
        }
    }

    void register_handler(std::function<void(const std::vector<T>&)>&& func){
        if(!started) {
            handlers.push_back(func);
        } else{
            throw -1;
        }
    }

};