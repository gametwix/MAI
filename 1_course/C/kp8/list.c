#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void Print_list(struct list *top)
{
  if(Size_list(top)==0) printf("~");
  while(top->br!=1)
  {
    printf("%d\t",top->data);
    top=top->next;
  }
  printf("\n");
}

struct list* Create_list(struct list *top)
{
  if(top==NULL)
  {
    top=malloc(sizeof(struct list));
    top->data=0;
    top->br=1;
    top->next=NULL;
  }
  return top;
}


int Size_list(struct list *top)
{
  int i=0;
  while(top->br!=1)
  {
    i++;
    top=top->next;
  }
  return i;
}

struct list* Push_list(struct list *top,int data,int pos)
{
  if(top==NULL) top=Create_list(top);
  if(pos>Size_list(top))
  {
    printf("Позиция больше длины списка, элимент записан последним.\n");

    struct list *q;
    q=malloc(sizeof(struct list));
    q->br=0;
    q->data=data;

    if(Size_list(top)==0)
    {
      q->next=top;
      top=q;
    }
    else
    {
      struct list *m=top;
      for(int i=1;i<Size_list(top);i++) m=m->next;
      q->next=m->next;
      m->next=q;
    }
  }
  else
  {
    struct list *q;
    q=malloc(sizeof(struct list));
    q->br=0;
    q->data=data;
    if(pos==1)
    {
      q->next=top;
      top=q;
    }
    else
    {
      struct list *m=top;
      for(int i=2;i<pos;i++) m=m->next;
      q->next=m->next;
      m->next=q;
    }
  }
  return top;
}

struct list* Delete_list_pos(struct list *top,int pos)
{
  if(top!=NULL)
  {
    struct list *q=top;
    if(pos>Size_list(top)) pos=Size_list(top);
    if(pos!=0)
    {
      if(pos==1)
      {
        top=top->next;
        free(q);
      }
      else
      {
        for(int i=2;i<pos;i++) q=q->next;
        struct list *m=q->next;
        q->next=m->next;
        free(m);
      }
    }
  }
  return top;
}

int Find_list_data(struct list *top,int data)
{
  int pos=0;
  if(top!=NULL)
  {
    while(top->br!=1)
    {
      pos++;
      if(top->data==data) break;
      top=top->next;
    }
    if(top->data!=data) pos=0;
  }
  return pos;
}

struct list* Delete_list_data(struct list *top,int data)
{
  if(top!=NULL)
  {
    int pos=Find_list_data(top,data);
    top=Delete_list_pos(top,pos);
  }
  return top;
}

struct list* Clear_list(struct list *top)
{
  if(top!=NULL)
  {
    while(Size_list(top)!=0)
    {
      top=Delete_list_pos(top,Size_list(top));
    }
  }
  return top;
}
