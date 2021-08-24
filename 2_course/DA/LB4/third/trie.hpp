#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>


class TTrie{
    class TNode{
    public:
        bool Last;
        long long Sym;
        std::vector<int> Jockers;
        TNode* Parent;
        TNode* Suffix;
        TNode* SubLast;
        std::unordered_map<long long,TNode*> Childs;

        TNode(long long inSym = -1,bool inLast = false):Sym(inSym),Last(inLast){
        Parent = nullptr;
        Suffix = nullptr;
        SubLast = nullptr;
        }

        ~TNode(){
            for(auto child: Childs){
                delete(child.second);
            }
        }

        TNode* ChildPrt(long long &inSym){
            try{
                return Childs.at(inSym);
            }
            catch(std::out_of_range){
                return nullptr;
            }
        }
    };


public:

    TNode* Root;
    TNode* Cur;

    TTrie(){
        Root = new TNode;
        Cur = Root;
    }

    ~TTrie(){
        delete(Root);
    }

    void Push(long long inSym,bool inLast = false,int pos = 0){
        if(Cur->ChildPrt(inSym) == nullptr){
            TNode* child = new TNode(inSym);
            child->Parent = Cur;
            Cur->Childs.insert({inSym,child});
            Cur = child;
        } else{
            Cur = Cur->ChildPrt(inSym);
        }

        if(inLast){
            Cur->Last = inLast;
            Cur->Jockers.push_back(pos);
        }
    }


    void BorSuf(){
        //BFS
        std::queue<TNode*> queue;
        queue.push(Root);
        while(!queue.empty()){
            TNode* elem = queue.front();
            queue.pop();
            for(auto child: elem->Childs)
            {
                queue.push(child.second);
            }
            //~BFS
            //Suf
            if(elem == Root) //not for Root
                continue;
            
            TNode* parent = elem->Parent;
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

};