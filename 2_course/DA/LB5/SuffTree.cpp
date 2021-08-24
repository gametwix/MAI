#include "SuffTree.hpp"
#include <iostream>

void TSuffTree::Init(std::string InpText){
    Text = InpText + "$";
    int SizeText = Text.size();
    for(int i = 0;i < SizeText; ++i){
        AddAllSuffix(i);
    }
}

void TSuffTree::AddAllSuffix(int InpEnd){
    std::shared_ptr<TNode> CurNode = Root;
    std::shared_ptr<TNode> Next = nullptr;
    std::shared_ptr<TNode> LastAdd = nullptr;
    (*End)++;
    int Length;
    GoTo(CurNode, Length, ListNum,InpEnd - 1);
    int CountSuf = ListNum;
    for(int i = CountSuf; i <= InpEnd; ++i){
        if(CreateNode(CurNode,LastAdd,Length,InpEnd)){
            if(CurNode == Root){
                Length--;
            } else {
                CurNode = CurNode->SuffixLink;
            }
        } else {
            break;
        }
    }
}

void TSuffTree::GoTo(std::shared_ptr<TNode> &CurNode, int &Length, int Start, int Finish){
    Length = Finish - Start + 1;
    std::shared_ptr<TNode> Next = nullptr;
    while(Length > 0){
        if(Next != nullptr){
            std::cout << Next->Length() << std::endl;
            for(int i = Next->Start; i <= *(Next->End); ++i){
                std::cout << Text[i];
            }
            std::cout << std::endl;
            if(Next->Length() >= Length)
                break;
            CurNode = Next;
        }
        Next = CurNode->Children[Text[Start + CurNode->Length()]];
        Start += CurNode->Length();
    }
}

bool TSuffTree::CreateNode(std::shared_ptr<TNode> &Node, std::shared_ptr<TNode> &LastAdd,int Length, int AddNum){
    std::shared_ptr<TNode> Next = nullptr;
    if(Node->Children.find(Text[AddNum - Length]) != Node->Children.end()){
        Next = Node->Children[Text[AddNum - Length]];
    }
    if(Next == nullptr){
        std::shared_ptr<TNode> NewNode(new TNode(AddNum,End,ListNum + 1));
        Node->Children.insert({Text[AddNum],NewNode});
        ++ListNum;
        if(LastAdd != nullptr){
            LastAdd->SuffixLink = NewNode;
        }
        return true;
    } else {
        if(Length == Next->Length()){
            if(Next->Children.find(Text[AddNum]) == Next->Children.end()){
                std::shared_ptr<TNode> NewNode(new TNode(AddNum,End,ListNum + 1));
                Next->Children.insert({Text[AddNum],NewNode});
                ++ListNum;
                if(LastAdd != nullptr){
                    LastAdd->SuffixLink = NewNode;
                }
                LastAdd = NewNode;
                return true;
            } else {
                if(LastAdd != nullptr){
                    LastAdd->SuffixLink = Next->Children[Text[AddNum]];
                }
                return false;
            }
        } else {
            if(Text[Next->Start + Length] == Text[AddNum]){
                if(LastAdd != nullptr){
                    LastAdd->SuffixLink = Next->Children[Text[AddNum]];
                }
                return false;
            } else {
                std::shared_ptr<TNode> NewNode(new TNode(Next->Start,Next->Start + Length - 1,-1));
                Node->Children[Text[Next->Start]] = NewNode;
                Next->Start += Next->Start + Length;
                NewNode->Children.insert({Text[Next->Start],Next});
                std::shared_ptr<TNode> List(new TNode(AddNum,End,ListNum + 1));
                ListNum++;
                NewNode->Children.insert({Text[AddNum],List});
                if(LastAdd != nullptr){
                    LastAdd->SuffixLink = NewNode;
                }
                LastAdd = NewNode;
                return true;
            }
        }
    }
}

void TNode::Print(int level,std::string &text){
    for(int i = 0;i < level;++i){
        std::cout << "\t";
    }
    for(int i = Start; i <= *End; ++i){
        std::cout << text[i];
    }
    std::cout << std::endl;
    for(auto& child: Children){
        child.second->Print(level + 1, text);
    }
}

void TSuffTree::Print(){
    Root->Print(0,Text);
}