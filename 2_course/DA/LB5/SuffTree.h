#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

class TSuffTree{
private:
    struct TNode;
    struct TEdge;

    TNode *Root;
    TNode *CurNode;
    int CurEdge;
    int Pos = 0;

    TNode *LastAdd = nullptr;

    std::string Text;

    int CountSuff = 0;
    int CountLists = 0;

    void Add(int inpos);
    void CreateList(int inpos,TNode *Node);
    void CreateSufflink(TNode *Node);
    bool EdgeFault();
    void BreakCreationNode(int inpos);
    void GoSuffLink();
public:
    TSuffTree(std::string &str);
    ~TSuffTree();
    void Find(std::string &pattern, std::vector<int> &ans);
    void Print();
};


struct TSuffTree::TNode{
    int NumList;
    int Left,Right;
    TNode *SuffLink = nullptr;
    std::unordered_map<char,TNode*> Edges;
    TNode(int left,int right,int list) : Left(left), Right(right), NumList(list){}
    ~TNode(); 
    void ListsNums(std::vector<int> &ans);
    void Print(int level,std::string &text);
};

