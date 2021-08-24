#include <iostream>
#include <string>
#include <zmq.hpp>


#define ADDRESS_A "tcp://127.0.0.1:5555"
#define ADDRESS_B "tcp://127.0.0.1:5557"

int main(){
    zmq::context_t context(1);
    zmq::socket_t to_a(context,ZMQ_REQ);
    zmq::socket_t to_b(context,ZMQ_REQ);

    to_a.connect(ADDRESS_A);
    to_b.connect(ADDRESS_B);

    std::string msg = "Connect";
    zmq::message_t message(msg.size());
    memcpy(message.data(), msg.c_str(), msg.size());
    to_a.send(message);

    while(true){
        to_a.recv(message);
        std::string ans(static_cast<char*>(message.data()), message.size());
        if(ans == "$$$"){
            break;
        }else{
            std::string msg = "Success";
            message = zmq::message_t(msg);
            memcpy(message.data(), msg.c_str(), msg.size());
            to_a.send(message);
            std::cout << ans << std::endl;
            //Отправляем длину строке программе B
            std::string size = std::to_string(ans.size());
            message = zmq::message_t(size.size());
            memcpy(message.data(), size.c_str(), size.size());
            to_b.send(message);
            to_b.recv(message);
        }
    }
    

    to_a.disconnect(ADDRESS_A);
    to_b.disconnect(ADDRESS_B);

    return 0;
}