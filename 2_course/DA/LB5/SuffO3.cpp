#include "SuffO3.h"
#include <iostream>

void CompactTrie::Init(std::string _text){
    text = _text + "$";
    for(int i = 0;i < text.size();++i){
        for(int j = 0;j <= i;++j){
            std::cout << "debug: input: ";
            for(int k = j; k <= i; ++k){
                std::cout << text[k];
            }
            std::cout << std::endl;
            Add(j,i);
            Print();
        }
    }
}

void CompactTrie::Add(int Start, int End){
    Node *cur_node = &Root;
    int pos_in_node = 0;
    for(int i = Start; i <= End;++i){
        if(cur_node == &Root){                                                      //если это корень
            if(cur_node->childs.find(text[i]) != cur_node->childs.end()){               //если уже существует ветвь с симовлом
                cur_node = cur_node->childs.find(text[i])->second;
                pos_in_node = 1;
            }else{                                                                      //если такой нет, то создаем
                cur_node->childs.insert({text[i],new Node(i,i)});
                cur_node = cur_node->childs.find(text[i])->second;
                pos_in_node = 1;
            }
        } else {
            if(pos_in_node + cur_node->Start > cur_node->End){                     //если мы доли до конца ноды
                if(cur_node->childs.empty()){                                       //если нет детей, то просто продливаем
                    cur_node->End++;
                    pos_in_node++;
                }else {                                                             //если есть то
                    if(cur_node->childs.find(text[i]) != cur_node->childs.end()){       //либо переходим в нужную ветвь, если она есть
                        cur_node = cur_node->childs.find(text[i])->second;
                        pos_in_node = 1;
                    }else{                                                              //либо создаем ее и переходим в нее
                        cur_node->childs.insert({text[i],new Node(i,i)});
                        cur_node = cur_node->childs.find(text[i])->second;
                        pos_in_node = 1;
                    }
                }
            } else {                                                                //если мы в середине ноды
                if(text[i] == text[cur_node->Start+pos_in_node]){                   //если при этом совпал символ
                    pos_in_node++;                                                      //то просто продвигаемся по ноде
                } else {                                                            //если есть различие
                    Node *add_node = new Node(cur_node->Start + pos_in_node, cur_node->End);    //создаем новую ноду
                    add_node->childs = cur_node->childs;                                        //передаем ей всех детей
                    cur_node->childs.clear();                                                   //забываем о переданных детях
                    cur_node->childs.insert({text[cur_node->Start+pos_in_node],add_node});      //добавляем новую ноду как ребенка
                    cur_node->End = cur_node->Start + pos_in_node - 1;                          //переносим конец старой ноды
                    cur_node->childs.insert({text[i],new Node(i,i)});                           //создаем вторую ветвь
                    cur_node = cur_node->childs.find(text[i])->second;                          //переходим в нее
                    pos_in_node = 1;
                }
            }
        }
        
    }
    
}


void Node::Print(int level, std::string &text){
    for(int i = 0; i < level; ++i){
        std::cout << "\t";
    }
    for(int i = Start; i <= End; ++i){
        std::cout << text[i];
    }
    std::cout << std::endl;
    for(auto& i: childs){
        i.second->Print(level + 1, text);
    }
}

void CompactTrie::Print(){
    Root.Print(0,text);
}