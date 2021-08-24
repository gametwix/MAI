#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void create(struct list *l,int *first)
{
  for(int i=0;i<100;i++)
  {
    l[i].br = false;
    l[i].inl = false;
  }
  l[0].br = true;
  l[0].inl = true;
  *first = 0;
}

int size(struct list *l,int *first)
{
  int size = 0;
  int i = *first;
  while(l[i].br != true)
  {
    size++;
    i = l[i].next;
  }
  return size;
}

void push(struct list *l,int *first, int pos, bool data)
{
  if(size(l,first)==0)
  {
    l[1].data = data;
    l[1].inl = true;
    l[1].br = false;
    l[1].next = 0;
    *first = 1;
  }
  else
  {
    if(size(l,first)<100)
    {
      if(pos>size(l,first)+1) pos = size(l,first)+1;
      int mem = findmem(l);

      if(pos == 1)
      {
        l[mem].data = data;
        l[mem].inl = true;
        l[mem].br = false;
        l[mem].next = *first;
        *first = mem;
      }
      else
      {
        int step = *first;
        for(int i = 2;i<pos;i++)
        {
          step = l[step].next;
        }
        l[mem].data = data;
        l[mem].inl = true;
        l[mem].br = false;
        l[mem].next = l[step].next;
        l[step].next = mem;
      }
    }
  }
}

int findmem(struct list *l)
{
  int i=0;
  while(l[i].inl != false)
  {
    i++;
  }
  return i;
}

void printlist(struct list *l,int *first)
{
  int i=*first;
  if(l[i].br == true) printf("~\n");
  while(l[i].br != true)
  {
    printf("%d\n",l[i].data);
    i = l[i].next;
  }
}


void delpos(struct list *l,int *first,int pos)
{
  if(size(l,first)>0)
  {
    if(pos > size(l,first)) pos = size(l,first);
    if(pos == 1)
    {
      l[*first].inl = false;
      *first = l[*first].next;
    }
    else
    {
      int step = *first;
      for(int i = 2;i<pos;i++)
      {
        step = l[step].next;
      }
      l[l[step].next].inl = false;
      l[step].next = l[l[step].next].next;
    }
  }
}


int findel(struct list *l,int *first, bool data)
{
  int pos = 1;
  int step = *first;
  while(l[step].data != data && l[step].br != true)
  {
    step = l[step].next;
    pos++;
  }
  if(l[step].data != data || l[step].br == true) pos = 0;
  return pos;
}

void delznach(struct list *l,int *first, bool data)
{
  int pos = findel(l,first,data);
  printf("%d\n",pos);
  if(pos != 0) delpos(l,first,pos);
}

void kp(struct list *l,int *first, bool data)
{
  int pos = findel(l,first,data);
  if(pos != 0)
  {
    while(size(l,first)>pos) delpos(l,first,size(l,first));
    while(size(l,first) > 1) delpos(l,first,1);

  }
}
