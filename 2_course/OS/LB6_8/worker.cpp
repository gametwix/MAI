#include "node.hpp"
#include "net_func.hpp"
#include <fstream>
#include <vector>
#include <signal.h>

int my_id = 0;

void Log(std::string str){
    std::string f = std::to_string(my_id) + ".txt";
    std::ofstream fout(f,std::ios_base::app);
    fout << str;
    fout.close();
}

int main(int argc, char **argv){
    if(argc != 3){
        return -1;
    }
    
    Node me(atoi(argv[1]),atoi(argv[2]));
    std::string prog_path = "./worker";
    while(1){
        std::string message;
        std::string command = " ";
        message = my_net::reseave(&(me.parent));
        std::istringstream  request(message);
        request >> command;

        
        if(command == "create"){
            int id_child, id_parent;
            request >> id_child;
            std::string ans = me.Create_child(id_child, prog_path);
            my_net::send_message(&me.parent,ans);
        } else if(command == "pid"){
            std::string ans = me.Pid();
            my_net::send_message(&me.parent,ans);
        } else if(command == "ping"){
            int id_child;
            request >> id_child;
            std::string ans = me.Ping_child(id_child);
            my_net::send_message(&me.parent,ans);
        } else if(command == "send"){
            int id;
            request >> id;
            std::string str;
            getline(request, str);
            str.erase(0,1);
            std::string ans;
            ans = me.Send(str,id);
            my_net::send_message(&me.parent,ans);
        } else if(command == "exec"){
            std::string str;
            std::string pattern;
            request >> str >> pattern;
            std::vector<int> answers;
            int start = 0;
            while(str.find(pattern,start) != -1){
                start = str.find(pattern,start);
                answers.push_back(start);
                start++;
            }
            std::string to_send;
            if(answers.size() == 0){
                to_send = "-1";
            }else{
                to_send = std::to_string(answers[0]);
                for(int i = 1; i < answers.size();++i){
                    to_send = to_send + ";" + std::to_string(answers[i]);
                }
            }
            to_send = "Ok:" + std::to_string(me.id) + ":" + to_send;
            my_net::send_message(&me.parent,to_send);
        } else if(command == "remove"){
            std::string ans = me.Remove();
            ans = std::to_string(me.id) + " " + ans;
            my_net::send_message(&me.parent, ans);
            my_net::disconnect(&me.parent, me.parent_port);
            me.parent.close();
            break;
        }
    }
    sleep(1);
    return 0;
}



