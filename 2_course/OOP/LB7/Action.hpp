#include <iostream>
#include <vector>
#include <stack>

template <typename Type>
class Document
{
 private:
  class BackAction{
  public:
   virtual void Action(Document* doc) = 0;
   ~BackAction(){};
  };

  class B_Add_Action: public BackAction{
   private:
    size_t pos;
    std::shared_ptr<Type> elem;
   public:
    B_Add_Action(size_t p, std::shared_ptr<Type> el):pos(p),elem(el) {}
    void Action(Document* doc)
    override{
     doc->Add_elem(pos,elem);
    };
    ~B_Add_Action(){};
  };

  class B_Del_Action: public BackAction{
   private:
    size_t pos;
   public:
    B_Del_Action(size_t p):pos(p){}
    void Action(Document* doc)
    override{
     doc->Del_elem(pos);
    };
    ~B_Del_Action(){}
  };
  std::stack<std::shared_ptr<BackAction>> actions;
  void Add_elem(size_t pos,std::shared_ptr<Type> elem){
   elems.insert(elems.begin()+pos,elem);
  }
  void Del_elem(size_t pos){
   elems.erase(elems.begin()+pos);
  }
  
 public:
  std::vector<std::shared_ptr<Type>> elems;
  void Create(){
   elems.clear();
   while (!actions.empty())
    actions.pop();
  }
  void Add(size_t pos,std::shared_ptr<Type> elem){
   if(pos > elems.size())
    throw -1;
   Add_elem(pos,elem);
   auto act = new B_Del_Action(pos);
   actions.push(std::shared_ptr<BackAction>(act));
  }
  void Del(size_t pos){
   if(pos > elems.size()-1 )
    throw -1;
   auto act = new B_Add_Action(pos,elems.at(pos));
   actions.push(std::shared_ptr<BackAction>(act));
   Del_elem(pos);
  }
  void Undo(){
   if(actions.empty())
    throw -1;
   
   actions.top()->Action(this);
   actions.pop();
  }
};//class Document




