#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void push_i(struct stack_i **top, int d)
{
  struct stack_i *q;
  q=malloc(sizeof(struct stack_i));
  q->data=d;
  if((*top)==NULL)
  {
    q->next=NULL;
    (*top)=q;
  }
  else
  {
    q->next=(*top);
    (*top)=q;
  }
}

int pop_i(struct stack_i **top)
{
  int d=(*top)->data;
  struct stack_i *q=(*top);
  (*top)=(*top)->next;
  free(q);
  return d;
}

int size_i(struct stack_i **top)
{
  struct stack_i *q;
  q=(*top);
  int size=0;
  while(q!=NULL)
  {
    size++;
    q=(q->next);
  }
  return size;
}

int peek_i(struct stack_i **top)
{
  if (*top!=NULL) return (*top)->data;
  else return -1;
}
