#pragma once

#include <iostream>
#include <zmq.hpp>
#include <sstream>
#include <string>

namespace my_net{

    #define MY_PORT 4040
    #define MY_IP "tcp://127.0.0.1:"

    int bind(zmq::socket_t *socket, int id){
        int port  = MY_PORT + id;
        while(true){
            std::string adress = MY_IP  + std::to_string(port);
            try{
                socket->bind(adress);
                break;
            } catch(...){
                port++;
            }    
        }
        return port;
    }

    void connect(zmq::socket_t *socket, int port){
        std::string adress = MY_IP + std::to_string(port);
        socket->connect(adress);
    }

    void unbind(zmq::socket_t *socket, int port) {
        std::string adress = MY_IP + std::to_string(port);
        socket->unbind(adress);
    }

    void disconnect(zmq::socket_t *socket, int port) {
        std::string adress = MY_IP + std::to_string(port);
        socket->disconnect(adress);
    }

    void send_message(zmq::socket_t *socket, const std::string msg) {
        zmq::message_t message(msg.size());
        memcpy(message.data(), msg.c_str(), msg.size());
        try{
            socket->send(message);
        }catch(...){}
    }

    std::string reseave(zmq::socket_t *socket){
        zmq::message_t message;
        bool success = true;
        try{
            socket->recv(&message,0);
        }catch(...){
            success = false;
        }
        if(!success || message.size() == 0){;
            throw -1;
        }
        std::string str(static_cast<char*>(message.data()), message.size());
        return str;
    }

}