#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"


struct list* Push_list(struct list* top,long double key,char *data, int pos)
{
  if(top==NULL)
  {
    top = Create_list(top);
    top->key = key;
    top->data = data;
  }
  else
  {
    if(pos > Size_list(top))
    {
      struct list *q;
      q=malloc(sizeof(struct list));
      q->key = key;
      q->data = data;
      q->next = NULL;
      struct list *m = top;
      while(m->next!=NULL)
      {
        m = m->next;
      }
      m->next = q;
      q->prev = m;
    }
    else
    {
      struct list *q;
      q = malloc(sizeof(struct list));
      q->key = key;
      q->data = data;
      if(pos == 1)
      {
        q->next = top;
        top->prev = q;
        q->prev = NULL;
        top = q;
      }
      else
      {
        struct list *m = top;
        for(int i = 2;i<pos;i++) m = m->next;
        q->next = m->next;
        m->next = q;
        q->prev = m;
        if(q->next!=NULL)
        {
          q->next->prev = q;
        }

      }
    }
  }

  return top;
}

struct list* Create_list(struct list* top)
{
  if(top == NULL)
  {
    top=malloc(sizeof(struct list));
    top->next=NULL;
    top->prev=NULL;
    top->key=0;
    top->data=NULL;
  }
  return top;
}

int Size_list(struct list* top)
{
  int size=0;
  while(top!=NULL)
  {
    top=top->next;
    size++;
  }
  return size;
}

void Print_list(struct list *top)
{
  while(top!=NULL)
  {
    printf("%Lf\t%s\n",top->key,top->data);
    top = top->next;
  }
}


struct list* Delete_list_pos(struct list *top,int pos)
{
  if(top != NULL)
  {
    struct list *q = top;
    if(pos > Size_list(top)) pos = Size_list(top);
    if(pos != 0)
    {
      if(pos == 1)
      {
        top = top->next;
        top->prev = NULL;
        free(q);
      }
      else
      {
        for(int i = 2;i < pos;i++) q = q->next;
        struct list *m = q->next;
        q->next = m->next;
        if(m->next!=NULL)
        {
          struct list *t = m->next;
          t = q->next;
          t->prev = q;
        }

        free(m);
      }
    }
  }
  return top;
}

void Pop_list(struct list *top,long double *key, char **data, int pos)
{
  int i;
  for(i = 1;i<pos;i++) top = top->next;
  *key=top->key;
  *data=top->data;
}

struct list* Change_pos(struct list *top,int pos1,int pos2)
{
  long double key;
  char *data;
  Pop_list(top,&key,&data,pos1);
  char *cdata;
  Copy_mass(data,&cdata);
  top = Delete_list_pos(top,pos1);
  top = Push_list(top,key,cdata,pos2);
  return top;
}

void Copy_mass(char *data,char **cdata)
{
  *cdata = NULL;
  *cdata = malloc((int)(256)*sizeof(char));
  for(int i=0;i<256;i++)
  {
    (*cdata)[i] = data[i];
  }
}

struct list* Sort_list(struct list *top)
{

  for(int i=1;i<=Size_list(top);i++)
  {
    struct list *m = top;
    for(int j = 1; j < i; j++) m = m->next;
    struct list *q = m;
    int j;
    for(j=i;j>=1;j--)
    {
      if(q->prev == NULL) break;
      if(q->prev->key < m->key) break;
      q = q->prev;
    }
    top = Change_pos(top,i,j);
  }
  return top;
}

struct list* Clear_list(struct list *top)
{
  while(top!=NULL)
  {
    if(Size_list(top) == 1)
    {
      free(top);
      top = NULL;
      break;
    }
    top = Delete_list_pos(top,1);
  }
  return top;
}

struct mas* List_mas(struct list* top, int *size)
{
  struct mas *m;
  *size = Size_list(top);
  m = malloc(sizeof(struct mas));
  for(int i=0;i<*size;i++)
  {
    m[i].key = top->key;
    m[i].data = top->data;
    top = top->next;
  }
  return m;
}

void Search_mas(long double key,long double accur,struct mas *m,int size)
{
  int min_ind = 0;
  int max_ind = size-1;
  int ind;
  while(max_ind - min_ind > 1)
  {
    ind = (min_ind + max_ind)/2;
    if(key >= m[ind].key - accur && key <= m[ind].key + accur) break;
    else if(m[ind].key < key) min_ind = ind;
    else max_ind = ind;
  }

  if(key >= m[ind].key - accur && key <= m[ind].key + accur) printf("%Lf\t%s\n",m[ind].key,m[ind].data);
  else if(key >= m[max_ind].key - accur && key <= m[max_ind].key + accur) printf("%Lf\t%s\n",m[max_ind].key,m[max_ind].data);
  else if(key >= m[min_ind].key - accur && key <= m[min_ind].key + accur) printf("%Lf\t%s\n",m[min_ind].key,m[min_ind].data);
  else printf("Элимент не найден\n");
}

struct list* Mix_list(struct list* top)
{
  int size = Size_list(top);
  for(int i=0;i<2;i++)
  {
    srand(time(NULL));
    for(int j=1;j<=size;j++)
    {
      int r = rand()%size;
      top = Change_pos(top,j,r);
    //  printf("-----------------------\n");
      //Print_list(top);
    }
  }
  return top;
}
