#include <iostream>
#include <string>
#include <zmq.hpp>


#define ADDRESS_A "tcp://127.0.0.1:5556"
#define ADDRESS_C "tcp://127.0.0.1:5557"

int main(){
    zmq::context_t context(1);
    zmq::socket_t to_a(context,ZMQ_REP);
    zmq::socket_t to_c(context,ZMQ_REP);
    std::string my_ans = "OK";
    to_a.bind(ADDRESS_A);
    to_c.bind(ADDRESS_C);
    while(true){
        //work with A
        zmq::message_t message_a;
        to_a.recv(message_a);
        std::string ans_a = std::string(static_cast<char*>(message_a.data()), message_a.size());
        int size_str_a = std::stoi(ans_a);
        if(size_str_a == -1)
            break;
        message_a = zmq::message_t(my_ans.size());
        memcpy(message_a.data(), my_ans.c_str(), my_ans.size());
        to_a.send(message_a);

        //work with C
        zmq::message_t message_c;
        to_c.recv(message_a);
        std::string ans_c = std::string(static_cast<char*>(message_a.data()), message_a.size());
        int size_str_c = std::stoi(ans_c);
        message_c = zmq::message_t(my_ans.size());
        memcpy(message_c.data(), my_ans.c_str(), my_ans.size());
        to_c.send(message_c);

        //write
        std::cout << "Size str send A: " << size_str_a << "\tSize str send C: " << size_str_c << std::endl;

    }
    to_a.unbind(ADDRESS_A);
    to_c.unbind(ADDRESS_C);
    return 0;
}