#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "arvir.h"

void peek_Tree(struct tree **root,int *data,int *type)
{
  if((*root)!=NULL)
  {
    *data=(*root)->data;
    *type=(*root)->type;
  }
}

void pop_Tree(struct tree **root,int *data,int *type)
{
  if((*root)!=NULL)
  {
    *data=(*root)->data;
    *type=(*root)->type;
    free(*root);
  }
}

void push_tree(struct tree **top,int data,int type)
{
  if((*top)==NULL)
  {
    (*top)=malloc(sizeof(struct tree));
    (*top)->right=NULL;
    (*top)->left=NULL;
    (*top)->data=data;
    (*top)->type=type;
  }
  else (*top)->data=data;
}

void print_Tree(struct tree **root,int level)
{
    if((*root)!=NULL)
    {
      int data;
      int type;
      print_Tree(&((*root)->right),level+1);
      pr_padding('\t',level);
      peek_Tree(root,&data,&type);
      if(type==1) printf("%d\n",data);
      if(type==0) printf("%c\n",(char)data);
      print_Tree(&((*root)->left),level+1);
    }
}

void pr_padding(char ch,int level)
{
  for(int i=0;i<(level);i++)
  {
    printf("%c",ch);
  }
}
