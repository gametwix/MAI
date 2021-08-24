#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "arvir.h"
#include "tree.h"

void laba(struct tree **root)
{
  if((*root)!=NULL)
  {
    int data;
    int type;
    peek_Tree(root,&data,&type);
    if((type==0)&&((data==47)||(data==42)))
    {
      if(((*root)->right->type==1)&&((*root)->right->data==1))
      {
        struct tree *q=(*root);
        free((*root)->right);
        (*root)=(*root)->left;
        free(q);
      }
      else if(((*root)->left->type==1)&&((*root)->left->data==1)&&(data==42))
      {
        struct tree *q=(*root);
        free((*root)->left);
        (*root)=(*root)->right;
        free(q);
      }
    }
    laba(&((*root)->right));
    laba(&((*root)->left));
  }
}

void tree_to_inf(struct tree **root,struct arvir **top,int last)
{
  if((*root)!= NULL)
  {
    int data;
    int type;
    int pres=-1;
    int sw=0;
    peek_Tree(root,&data,&type);
    if(type == 1) pres=0;
    else if((type==0)&&((data==42)||(data==47))) pres=2;
    else if((type==0)&&((data==43)||(data==45))) pres=1;
    if((pres<last)&&(pres!=0)) sw=1;
    if(sw==1) push_l(top,40,0);
    tree_to_inf(&((*root)->left),top,pres);
    struct tree *r=(*root)->right;
    pop_Tree(root,&data,&type);
    push_l(top,data,type);
    tree_to_inf(&r,top,pres);
    if(sw==1) push_l(top,41,0);
  }
}


void post_to_tree(struct arvir **first,struct tree **top)
{
  int data;
  int type;
  pop_l(first,&data,&type);
  push_tree(top,data,type);
  if(type == 0)
  {
    post_to_tree(first,&((*top)->right));
    post_to_tree(first,&((*top)->left));
  }
}

void inf_to_post(struct arvir *pre,struct arvir **pos)
{
  int ur=0;
  int s=size_ar(&pre);
  struct stack_i *ch=NULL;
  for(int i=0;i<s;i++)
  {
    int data;
    int type;
    pop_f(&pre,&data,&type);
    //------------------------1-------------------------------------------
    if(type==1)
    {
      push_l(pos,data,1);
    }
    else
    {
      //----------------------2a------------------------------------------
      if((peek_i(&ch)==40)||(ch==NULL))
      {
        if((data==42)||(data==47)) ur=1;
        if((data==43)||(data==45)) ur=0;
        push_i(&ch,data);
      }
      //----------------------2b------------------------------------------
      else if((ur==0)&&((data==42)||(data==47)||(data==43)||(data==45)))
      {
        if((data==42)||(data==47)) ur=1;
        if((data==43)||(data==45)) ur=0;
        push_i(&ch,data);
      }
      else if((ur==1)&&((data==42)||(data==47))) push_i(&ch,data);
      //----------------------2c------------------------------------------
      else if((ur==1)&&((data==43)||(data==45)))
      {
        while((peek_i(&ch)!=40)&&(size_i(&ch)!=0))
        {
          push_l(pos,pop_i(&ch),0);
        }
        ur=0;
        push_i(&ch,data);
      }
      //----------------------3------------------------------------------
      else if(data==40) push_i(&ch,data);
      //----------------------4------------------------------------------
      else if(data==41)
      {
        while(peek_i(&ch)!=40)
        {
          push_l(pos,pop_i(&ch),0);
        }
        pop_i(&ch);
        if((peek_i(&ch)==42)||(peek_i(&ch)==47)) ur=1;
        if((peek_i(&ch)==43)||(peek_i(&ch)==45)) ur=0;
      }
    }
  }
  s=size_i(&ch);
  for(int i=0;i<s;i++)
  {
    push_l(pos,pop_i(&ch),0);
  }
}

int main()
{
  char ch[100];
  struct arvir *arinf=NULL;
  struct arvir *arpost=NULL;
  struct tree *tr=NULL;
  scanf("%s",ch);
  strtoarvir(ch,100,&arinf);
  inf_to_post(arinf,&arpost);
  prarvir(&arpost);
  post_to_tree(&arpost,&tr);

  laba(&tr);
  print_Tree(&tr,0);
  tree_to_inf(&tr,&arpost,0);
  prarvir(&arpost);
  return 0;
}
