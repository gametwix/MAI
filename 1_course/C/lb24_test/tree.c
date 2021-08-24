#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "arvir.h"
void pushTree(struct tree **top,int data,int type)
{
  struct tree *q;
  q=malloc(sizeof(struct tree));
  q->data=data;
  q->type=type;
  q->right=NULL;
  q->left=NULL;
  (*top)=q;
}

void peekTree(struct tree **top,int *data,int *type)
{
  struct tree *q;
  q=(*top);
  *data=q->data;
  *type=q->type;
}

void posttotre(struct tree **tr,struct arvir **arv)
{
  int data;
  int type;
  pop_l(arv,&data,&type);
  pushTree(tr,data,type);

  peek_l(arv,&data,&type);
  if(type==0) posttotre(&((*tr)->right),arv);
  else
  {
    pop_l(arv,&data,&type);
    pushTree(&((*tr)->right),data,type);
  }

  peek_l(arv,&data,&type);
  if(type==0) posttotre(&((*tr)->right),arv);
  else
  {
    pop_l(arv,&data,&type);
    pushTree(&((*tr)->right),data,type);
  }
}

void tretopost(struct tree **tr,struct arvir **arv)
{
  if((*tr)!=NULL)
  {
    int data;
    int type;
    peekTree(tr,&data,&type);
    tretopost(&((*tr)->left),arv);
    tretopost(&((*tr)->right),arv);
    push_l(arv,data,type);
  }
}
