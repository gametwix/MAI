#include "SuffTree.h"
#include <iostream>

TSuffTree::~TSuffTree(){
    delete Root;
}

TSuffTree::TNode::~TNode(){
    for(auto &i: Edges){
        delete i.second;
    }    
}

TSuffTree::TSuffTree(std::string &str){
    Text = str + "$";

    int size = Text.size();
    Root = new TNode(-1,-1,-1);
    CurNode = Root;
    for(int i = 0; i < size; ++i){
        Add(i);
    }
}


void TSuffTree::Add(int inpos){
    LastAdd = nullptr;
    ++CountSuff;
    while(CountSuff){
        //Если в узле, то выбираем ребро
        if(Pos == 0){
            CurEdge = inpos;
        }
        //Проверяем существование ребра
        if(CurNode->Edges.find(Text[CurEdge])==CurNode->Edges.end()){
            //Если такового нет, то создаем новый лист и пробуем создать суфф ссылку
            CreateList(inpos,CurNode);
            CreateSufflink(CurNode);
        } else { 
            //Если посицие длиннее ребра, переходим дальше и все перепроверяем
            if(EdgeFault()){
                continue;
            }
            //Если символ существует, то переходим в него, создаем суфф ссылку и ничего больше не делаем
            TNode *Edge = CurNode->Edges[Text[CurEdge]];
            if(Text[Edge->Left+Pos] == Text[inpos]){
                CreateSufflink(CurNode);
                Pos++;
                break;
            } else {
                //Разрываем вершину, создаем новый лист, привязываем суфф сылку
                BreakCreationNode(inpos);
            }
        }
        --CountSuff;
        GoSuffLink();
    }
}

void TSuffTree::CreateList(int inpos,TNode *Node){
    CountLists++;
    TNode *List = new TNode(inpos,Text.size() - 1,CountLists);
    Node->Edges[Text[inpos]] = List;
}

void TSuffTree::CreateSufflink(TNode *Node){
    if(LastAdd != nullptr){
        LastAdd->SuffLink = Node;
        LastAdd = nullptr;
    }
}

bool TSuffTree::EdgeFault(){
    TNode *Edge = CurNode->Edges[Text[CurEdge]];
    int lenedge = Edge->Right - Edge->Left + 1;
    if(Pos >= lenedge){
        CurEdge += lenedge;
        Pos -= lenedge;
        CurNode = Edge;
        return true;
    }
    return false;
}

void TSuffTree::BreakCreationNode(int inpos){
    TNode *Edge = CurNode->Edges[Text[CurEdge]];
    TNode *SplitNode = new TNode(Edge->Left,Edge->Left + Pos - 1,-1);
    CurNode->Edges[Text[CurEdge]] = SplitNode;
    Edge->Left += Pos;
    SplitNode->Edges[Text[Edge->Left]] = Edge;
    CreateList(inpos,SplitNode);
    CreateSufflink(SplitNode);
    LastAdd = SplitNode;
}

void TSuffTree::GoSuffLink(){
    if(CurNode == Root){
        if(Pos > 0){
            --Pos;
            ++CurEdge;
        }
    } else {
        //По идее суфф линк должен быть всегда, но мало ли))
        if(CurNode->SuffLink != nullptr){
            CurNode = CurNode->SuffLink;
        } else {
            CurNode = Root;
        }
    }
}



void TSuffTree::Find(std::string &pattern, std::vector<int> &ans){
    ans.clear();
    int size = pattern.size();
    TNode *Cur = Root;
    for(int i = 0;i < size;){
        //Если есть ребро начинающиеся с нужного символаж
        if(Cur->Edges.find(pattern[i]) != Cur->Edges.end()){
            //Переходим в нее и сверяем
            Cur = Cur->Edges[pattern[i]];
            for(int j = Cur->Left; j <= Cur->Right && i < size; ++i,++j){
                if(Text[j] != pattern[i]){
                    return;
                }
            }
        } else { 
            return;
        }
    }
    Cur->ListsNums(ans);
    std::sort(ans.begin(),ans.end());
}


void TSuffTree::TNode::ListsNums(std::vector<int> &ans){
    if(NumList == -1){
        for(auto &i:Edges){
            i.second->ListsNums(ans);
        }
    } else {
        ans.push_back(NumList);
    }
}

void TSuffTree::TNode::Print(int level,std::string &text){
    for(int i = 0; i < level; ++i){
        std::cout << "\t";
    }
    for(int i = Left; i<=Right;++i){
        std::cout << text[i];
    }
    std::cout << std::endl;
    for(auto &i:Edges){
        i.second->Print(level + 1,text);
    }
}

void TSuffTree::Print(){
    Root->Print(0,Text);
}