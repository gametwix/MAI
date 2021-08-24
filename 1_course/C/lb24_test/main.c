#include <stdio.h>
#include "stack.h"
#include "arvir.h"
#include "tree.h"

void pretopost(struct arvir *pre,struct arvir **pos)
{
  int ur=0;
  int s=size_ar(&pre);
  struct stack_i *ch=NULL;
  for(int i=0;i<s;i++)
  {
    int data;
    int type;
    pop_f(&pre,&data,&type);
    //-----------------------1--------------------------------------------------
    if(type==1)
    {
      push_l(pos,data,1);
    }
    else
    {
      //----------------------2a-------------------------------------------------
      if((peek_i(&ch)==40)||(ch==NULL))
      {
        if((data==42)||(data==47)) ur=1;
        if((data==43)||(data==45)) ur=0;
        push_i(&ch,data);
      }
      //----------------------2b---------------------------
      else if((ur==0)&&((data==42)||(data==47)||(data==43)||(data==45)))
      {
        if((data==42)||(data==47)) ur=1;
        if((data==43)||(data==45)) ur=0;
        push_i(&ch,data);
      }
      else if((ur==1)&&((data==42)||(data==47))) push_i(&ch,data);
      //-------------------------2c---------------------------
      else if((ur==1)&&((data==43)||(data==45)))
      {
        while((peek_i(&ch)!=40)&&(size_i(&ch)!=0))
        {
          push_l(pos,pop_i(&ch),0);
        }
        ur=0;
        push_i(&ch,data);
      }
      //------------------------3------
      else if(data==40) push_i(&ch,data);
      //------------------------4-------
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
  for(int i=0;i<size_i(&ch);i++)
  {
    push_l(pos,pop_i(&ch),0);
  }
}

int main()
{
  struct tree *t=NULL;
  struct arvir *k=NULL;
  struct arvir *p=NULL;
  char vir[50];
  scanf("%s",vir);
  strtoarvir(vir,50,&k);
  pretopost(k,&p);
  prarvir(&p);
  posttotre(&t,&p);
  tretopost(&t,&p);
  prarvir(&p);

  return 0;
}
