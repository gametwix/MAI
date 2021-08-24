//Test algorihm O^3
#pragma once

#include <memory>
#include <unordered_map>
#include <string>

struct Node{
    std::unordered_map<char,Node*> childs;       //Список детей
    int Start;
    int End;
    Node(int _start,int _end): Start(_start),End(_end){}
    void Print(int level, std::string &text);
};


class CompactTrie{
    std::string text;
    Node Root;
    void Add(int Start, int End);
    public:
    void Init(std::string _text);
    CompactTrie(): Root(-1,-1){};
    void Print();
};