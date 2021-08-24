#include <stdio.h>
#include "deque.h"

void create(deque *deq)
{
  deq->size=0;
  deq->start=0;
  deq->end=0;
}

void push_s(deque *deq,int data)
{
  if(deq->size<100)
  {
    if(deq->size==0)
    {
      deq->node[0]=data;
      deq->size++;
    }
    else
    {
      int pos=deq->start-1;
      if(pos<0) pos=100+pos;
      deq->node[pos]=data;
      deq->start=pos;
      deq->size++;
    }
  }
}


void push_e(deque *deq,int data)
{
  if(deq->size<100)
  {
    if(deq->size==0)
    {
      deq->node[0]=data;
      deq->size++;
    }
    else
    {
      int pos=deq->end+1;
      if(pos>99) pos-=100;
      deq->node[pos]=data;
      deq->end=pos;
      deq->size++;
    }
  }
}

int peek_s(deque *deq)
{
  return deq->node[deq->start];
}

int peek_e(deque *deq)
{
  return deq->node[deq->end];
}

int pop_s(deque *deq)
{
  if(deq->size>0)
  {
    int data = deq->node[deq->start];
    deq->size--;
    if(deq->size != 0) deq->start=(deq->start+1)%100;
    return data;
  }
  return 0;
}

int pop_e(deque *deq)
{
  if(deq->size>0)
  {
    int data = deq->node[deq->end];
    deq->size--;
    if(deq->size != 0){ deq->end=(deq->end-1);
    if(deq->end < 0) deq->end+=100;}
    return data;
  }
  return 0;
}

int size_d(deque *deq)
{
  return deq->size;
}

int empty(deque *deq)
{
  if(deq->size==0) return 1;
  else return 0;
}

void printd(deque *deq)
{
  if(deq->size>0)
  {
    for(int i=0;i<deq->size;i++)
    {
      printf("%d ",deq->node[((deq->start)+i)%100]);
    }
    printf("\n");
  }
  else printf("~\n");
}


int find_max(deque *deq)
{
  int data_max=peek_s(deq);
  for(int i=0;i<deq->size;i++)
  {
    int tmp = pop_s(deq);
    if(tmp > data_max) data_max = tmp;
    push_e(deq,tmp);
  }
  return data_max;
}

void del_max(deque *deq)
{
  int data_max = find_max(deq);
  int f = 0;
  int size = deq->size;
  for(int i=0;i<size;i++)
  {
    int tmp = pop_s(deq);
    if(tmp == data_max && f==0) f=1;
    else push_e(deq,tmp);
  }
}


void sort(deque *deq)
{
  int size = deq->size;
  for(int i=0;i<size;i++)
  {
    int data = find_max_otr(deq,size-i);
    del_zn(deq,data);
    for(int j=0;j<i;j++)
    {
      push_s(deq,pop_e(deq));
    }
    push_e(deq,data);
    for(int j=0;j<i;j++)
    {
      push_e(deq,pop_s(deq));
    }
  }
}

int find_max_otr(deque *deq,int k)
{
  int data_max=peek_s(deq);
  int size = k;
  if(size > deq->size) size = deq->size;
  for(int i=0;i<size;i++)
  {
    int tmp = pop_s(deq);
    if(tmp > data_max) data_max = tmp;
    push_e(deq,tmp);
  }
  size = deq->size - size;
  for(int i=0;i<size;i++)
  {
    push_e(deq,pop_s(deq));
  }
  return data_max;
}

void del_zn(deque *deq,int data)
{
  int data_max = data;
  int f = 0;
  int size = deq->size;
  for(int i=0;i<size;i++)
  {
    int tmp = pop_s(deq);
    if(tmp == data_max && f==0) f=1;
    else push_e(deq,tmp);
  }
}
