#include <stdio.h>
#include "table.h"
#include <time.h>
#include <stdlib.h>

void Create_table(struct table *t)
{
  t->size = 0;
  for(int i=0;i<SIZE;i++)
  {
    t->key[i] = 0;
  }
}

void Push_table(struct table *t,double key,char *data)
{
  if(t->size < SIZE)
  {
    t->key[t->size]=key;
    for(int i=0;i<256;i++)
    {
      t->data[t->size][i]=data[i];
    }
    t->size++;
  }
}

void Print_table(struct table *t)
{
  for(int i=0;i<t->size;i++)
  {
    printf("%f\t%s\n", t->key[i],t->data[i]);
  }
}


void Sort_table(struct table *t)
{
  int size = 0;
  while(size < t->size)
  {
    int pos = Find_paste(t,t->key[size],size);
    char d[256];
    for(int i=0;i<256;i++) d[i] = t->data[size][i];
    double key = t->key[size];
    for(int i=size;i>pos;i--)
    {
      for(int j=0;j<256;j++) t->data[i][j] = t->data[i-1][j];
      t->key[i] = t->key[i-1];
    }
    for(int i=0;i<256;i++) t->data[pos][i] = d[i];
    t->key[pos] = key;
    size++;
  }
}

int Find_paste(struct table *t,double key,int size)
{
  int min = 0;
  int max = size;
  int pos;
  while(1)
  {
    pos = min+max;
    pos = pos/2 + pos%2;
    if(pos == max && size==0 ) break;
    else if(pos == max && t->key[pos-1]<= key)break;
    else if(pos == min && size==0 ) break;
    else if(pos == min && t->key[pos]>= key)break;
    else if(pos == min+1 && t->key[min]>= key)
    {
      pos--;
      break;
    }
    else
    {
      if(t->key[pos-1]<= key && t->key[pos]>= key) break;
      else if(t->key[pos-1] > key) max = pos;
      else min = pos;
    }
  }
  return pos;
}

void Search_table(double key,double accur,struct table *m)
{
  int min_ind = 0;
  int max_ind = m->size-1;
  int ind;
  while(max_ind - min_ind > 1)
  {
    ind = (min_ind + max_ind)/2;
    if(key >= m->key[ind] - accur && key <= m->key[ind] + accur) break;
    else if(m->key[ind] < key) min_ind = ind;
    else max_ind = ind;
  }

  if(key >= m->key[ind] - accur && key <= m->key[ind] + accur) printf("%f\t%s\n",m->key[ind],m->data[ind]);
  else if(key >= m->key[max_ind] - accur && key <= m->key[max_ind] + accur) printf("%f\t%s\n",m->key[max_ind],m->data[max_ind]);
  else if(key >= m->key[min_ind] - accur && key <= m->key[min_ind] + accur) printf("%f\t%s\n",m->key[min_ind],m->data[min_ind]);
  else printf("Элимент не найден\n");
}


void Replace_mas(char *a, char *b)
{
  char c[256];
  for(int i=0;i<256;i++){
    c[i]=a[i];
    a[i]=b[i];
    b[i]=c[i];
  }
}

void Mix_table(struct table* t)
{
  int size = t->size;
  for(int i=0;i<2;i++)
  {
    srand(time(NULL));
    for(int j=0;j<size;j++)
    {
      int r = rand()%size;
      Replace_mas(t->data[j],t->data[r]);
      double key = t->key[j];
      t->key[j]=t->key[r];
      t->key[r]=key;
    //  printf("-----------------------\n");
      //Print_list(top);
    }
  }
}
