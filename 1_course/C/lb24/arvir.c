#include <stdio.h>
#include <stdlib.h>
#include "arvir.h"

void push_f(struct arvir **top,int d,int type)
{
  struct arvir *q;
  q=malloc(sizeof(struct arvir));
  q->data=d;
  q->type=type;
  if((*top)==NULL)
  {
    q->next=NULL;
    q->previous=NULL;
    q->last=q;
    (*top)=q;
  }
  else
  {
    q->next=(*top);
    q->previous=NULL;
    q->last=(*top)->last;
    (*top)=q;
  }
}


void push_l(struct arvir **top,int d,int type)
{
  struct arvir *q;
  q=malloc(sizeof(struct arvir));
  q->data=d;
  q->type=type;
  if((*top)==NULL)
  {
    q->next=NULL;
    q->previous=NULL;
    q->last=q;
    (*top)=q;
  }
  else
  {
    q->previous=(*top)->last;
    q->next=NULL;
    q->last=q;
    (*top)->last->next=q;
    (*top)->last=q;
  }
}

void pop_f(struct arvir **top,int *d,int *type)
{
  *d=(*top)->data;
  *type=(*top)->type;
  if((*top)->next==NULL)
  {
    free((*top));
    (*top)=NULL;
  }
  else
  {
    struct arvir *q;
    q=(*top);
    (*top)=(*top)->next;
    (*top)->previous=NULL;
    (*top)->last=q->last;
    free(q);
  }
}

void pop_l(struct arvir **top,int *d,int *type)
{
  struct arvir *l;
  l=(*top)->last;
  *d=l->data;
  *type=l->type;
  if(l->previous==NULL)
  {
    free((*top));
    (*top)=NULL;
  }
  else
  {
    struct arvir *q;
    q=l;
    l=q->previous;
    l->next=NULL;
    l->last=l;
    (*top)->last=l;
    free(q);
  }
}

int size_ar(struct arvir **top)
{
  int size=0;
  struct arvir *q=(*top);
  while(q!=NULL)
  {
    q=q->next;
    size++;
  }
  return size;
}

void peek_f(struct arvir **top,int *d,int *type)
{
  *d=(*top)->data;
  *type=(*top)->type;
}

void peek_l(struct arvir **top,int *d,int *type)
{
  struct arvir *l;
  l=(*top)->last;
  *d=l->data;
  *type=l->type;
}

void strtoarvir(char *array,int maxsize,struct arvir **top)
{
  int i=0;
  int a=0;
  int flag=0;
  while(1)
  {
    if((array[i]>=48)&&(array[i]<=57))
    {
      if(flag==0)
      {
        flag=1;
        a+=array[i]-48;
      }
      else
      {
        a*=10;
        a+=array[i]-48;
      }
    }
    else
    {
      if(flag==1)
      {
        flag=0;
        push_l(top,a,1);
        a=0;
        if(array[i]=='\0') break;
        push_l(top,(int)array[i],0);
      }
      else
      {
        if(array[i]=='\0') break;
        push_l(top,(int)array[i],0);
      }
    }
    if(array[i]=='\0') break;
    i++;
  }
}


void prarvir(struct arvir **top)
{
  struct arvir *q=(*top);
  int data;
  int type;
  for(int i=0;i<size_ar(top);i++)
  {
    peek_f(&q,&data,&type);
    if(type==0) printf("%c",(char)data);
    if(type==1) printf("%d", data);
    q=q->next;
  }
  printf("\n");
}
