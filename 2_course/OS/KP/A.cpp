#include <iostream>
#include <string>
#include <vector>
#include <zmq.hpp>

#define ADDRESS_C "tcp://127.0.0.1:5555"
#define ADDRESS_B "tcp://127.0.0.1:5556"

int main(){
    zmq::context_t context(1);
    zmq::socket_t to_c(context,ZMQ_REP);
    zmq::socket_t to_b(context,ZMQ_REQ);

    to_c.bind(ADDRESS_C);
    to_b.connect(ADDRESS_B);

    std::string str;
    std::vector<std::string> all_strings;
    while(std::getline(std::cin,str)){
        all_strings.push_back(str);
    }

    std::string ans;
    zmq::message_t message;
    to_c.recv(message);
    ans = std::string(static_cast<char*>(message.data()), message.size());
    if(ans != "Connect")
        return 1;

    for(auto& string: all_strings){
        //Отправляем строку
        message = zmq::message_t(string.size());
        memcpy(message.data(), string.c_str(), string.size());
        to_c.send(message);
        //Принимаем ответ
        to_c.recv(message);
        ans = std::string(static_cast<char*>(message.data()), message.size());
        if(ans != "Success")
            break;
        //Отправляем длину строке программе B
        std::string size = std::to_string(string.size());
        message = zmq::message_t(size.size());
        memcpy(message.data(), size.c_str(), size.size());
        to_b.send(message);
        to_b.recv(message);
        ans = std::string(static_cast<char*>(message.data()), message.size());
        if(ans != "OK")
            break;
    }
    ans = "$$$";
    message = zmq::message_t(ans.size());
    memcpy(message.data(), ans.c_str(), ans.size());
    to_c.send(message);


    ans = "-1";
    message = zmq::message_t(ans.size());
    memcpy(message.data(), ans.c_str(), ans.size());
    to_b.send(message);


    to_c.unbind(ADDRESS_C);
    to_b.disconnect(ADDRESS_B);

    return 0;
}