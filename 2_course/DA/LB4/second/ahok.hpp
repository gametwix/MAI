#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

struct SText
{
    long long Sym;
    int str;
    int word;
};


class TAhoKorasik{
protected:
class TNode{
    public:
    using node_ptr = TNode*;
    long long Sym;                 //Data
    bool Last;
    std::vector<int> Jockers;
    node_ptr Parent;               //Ptrs
    node_ptr Suffix;
    node_ptr SubLast;
    std::unordered_map<long long,node_ptr> Childs;

    TNode(long long inSym = -1,bool inLast = false):Sym(inSym),Last(inLast){
        Parent = nullptr;
        Suffix = nullptr;
        SubLast = nullptr;
    }

    ~TNode(){
        for(auto Child: Childs){
            delete(Child.second);
        }
    }

    node_ptr ChildPrt(long long &inSym){
        std::unordered_map<long long,node_ptr>::iterator child = Childs.find(inSym);
        if(child == Childs.end())
            return nullptr;
        else
            return child->second;    
    }
};//TNode
using node_ptr = TNode::node_ptr;

node_ptr Root;

public:

TAhoKorasik(){
    Root = new TNode();
}
~TAhoKorasik(){
    delete(Root);
}

void Push(const std::vector<long long> &pattern, int pos){
    node_ptr cur = Root;
    for(auto elem_pattern: pattern){
        node_ptr child = cur->ChildPrt(elem_pattern);
        if(child == nullptr){
            child = new TNode(elem_pattern);
            child->Parent = cur;
            cur->Childs.insert({elem_pattern,child});
        }
        cur = child;
    }
    cur->Last = true;
    cur->Jockers.push_back(pos);
}

void BorSuf(){
    //BFS
    std::queue<node_ptr> queue;
    queue.push(Root);
    while(!queue.empty()){
        node_ptr elem = queue.front();
        queue.pop();
        for(auto child: elem->Childs)
        {
            queue.push(child.second);
        }
        //~BFS
        //Suf
        if(elem == Root) //not for Root
		    continue;
        
        node_ptr parent = elem->Parent;
        parent = parent->Suffix;
        while(parent != nullptr && parent->ChildPrt(elem->Sym) == nullptr)
            parent = parent->Suffix;
        
        if(parent == nullptr)
            elem->Suffix = Root;
        else
            elem->Suffix = parent->ChildPrt(elem->Sym);
        //~Suf
        //SubLast
        if(elem->Suffix->Last)
            elem->SubLast = elem->Suffix;
        else if(elem->Suffix->SubLast != nullptr)
            elem->SubLast = elem->Suffix->SubLast;
        //~SubLast
    }//while
}

void ThisLast(node_ptr Cur,std::vector<int> &vect_incl,int pos){
    if(Cur->SubLast != nullptr)
        ThisLast(Cur->SubLast,vect_incl,pos);
    for(auto jocker: Cur->Jockers){ 
        if(pos-jocker >= 0)
            ++vect_incl[pos-jocker];
    }
}

void Find(std::vector<SText> &text,std::vector<int> &pos_incl){
    node_ptr cur = Root;
    int i=0;
    for(auto elem: text){
        while(cur->ChildPrt(elem.Sym)==nullptr && cur->Suffix!=nullptr)
            cur = cur->Suffix;
        if(cur->ChildPrt(elem.Sym)!=nullptr)
            cur = cur->Childs.at(elem.Sym);
        if(cur->Last)
            ThisLast(cur,pos_incl,i);
        else if(cur->SubLast != nullptr)
            ThisLast(cur->SubLast,pos_incl,i);
        
        ++i;
    }
}

};//TAhoKorasik