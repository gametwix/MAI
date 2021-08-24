#pragma once

#include <memory>
#include <unordered_map>
#include <string>

struct TNode{
    int Start;                                                  //Координата начала ноды в текста
    std::shared_ptr<int> End;                                   //Указатель на координату конца в тексте (общая для всех листьев)
    std::unordered_map<char,std::shared_ptr<TNode>> Children;   //Указатели на детей
    std::shared_ptr<TNode> SuffixLink;                          //Суффиксная ссылка
    int ListId;                                                 //Номер листа, если не листи, то -1
    std::shared_ptr<TNode> Parent;                              //Pодитель
    TNode(int InpStart,int InpEnd,int InpId) :  Start(InpStart), 
                                                End(new int(InpEnd)), 
                                                ListId(InpId),
                                                SuffixLink(nullptr){}
    TNode(int InpStart,std::shared_ptr<int> InpEnd,int InpId) :  Start(InpStart), 
                                                End(InpEnd), 
                                                ListId(InpId),
                                                SuffixLink(nullptr){}
    int Length(){return *End - Start + 1;}
    void Print(int level, std::string &text);
};

class TSuffTree{
private:
    std::string Text;                                           //Текст
    std::shared_ptr<TNode> Root;                                //Корень
    int ListNum;                                                //Количество листьев
    void GoTo(std::shared_ptr<TNode> &CurNode, int &Length, int Start, int Finish);
    bool CreateNode(std::shared_ptr<TNode> &Node, std::shared_ptr<TNode> &NewNode,int pos, int AddNum);
public:
    TSuffTree():Root(new TNode(-1,-2,-1)),End(new int(-1)),ListNum(0){Root->SuffixLink = Root;}
    void Init(std::string InpText);
    void AddAllSuffix(int InpEnd);
    void Print();
    std::shared_ptr<int> End;                                   //Общая координата конца для всех листьев
};



