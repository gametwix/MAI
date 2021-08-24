#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

struct list* create_list(struct list *root)
{
  if(root == NULL)
  {
    root = malloc(sizeof(struct list));
    root->next = NULL;
  }
}

struct list* push_list(struct list *root, int pos, double data)
{
  if(root == NULL)
  {
    root = create_list(root);
    root->data = data;
  }
  else
  {
    if(pos > size_list(root)) pos = size_list(root);
    if(pos == 0)
    {
      struct list*q = NULL;
      q = create_list(q);
      q->data = data;
      q->next = root;
      root = q;
    }
    else
    {
      struct list*m = root;
      for(int i=1;i < pos;i++)
      {
        m = m->next;
      }
      struct list*q = NULL;
      q = create_list(q);
      q->data = data;
      q->next = m->next;
      m->next = q;
    }
  }
  return root;
}

int size_list(struct list* root)
{
  int size = 0;
  while(root != NULL)
  {
    size++;
    root = root->next;
  }
  return size;
}

double peek_list(struct list* root, int pos)
{
  if(pos > size_list(root)) pos = size_list(root) - 1;
  for(int i = 0; i<pos; i++)
  {
    root = root->next;
  }
  return root->data;
}

struct list* delete_list(struct list* root, int pos)
{
  if(pos > size_list(root)) pos = size_list(root) - 1;
  if(pos == 0)
  {
    struct list* q = root;
    root = root->next;
    free(q);
  }
  else
  {
    struct list* m = root;
    for(int i = 0;i < pos-1; i++)
    {
      m = m->next;
    }
    struct list* q = m->next;
    m->next = q->next;
    free(q);
  }
  return root;
}

double pop_list(struct list** root, int pos)
{
  double data = peek_list(*root,pos);
  *root = delete_list(*root,pos);
  return data;
}

void print_list(struct list *root)
{
  if(root == NULL) printf("~\n");
  else
  {
    while(root != NULL)
    {
      printf("%f ",root->data);
      root = root->next;
    }
    printf("\n");
  }
}

//------------------------matrix------------------------------------------


struct matrix* create_matrix(struct matrix* matr,int n,int m)
{
  if(matr == NULL)
  {
    matr = malloc(sizeof(struct matrix*));
    matr->index = NULL;
    for(int i=0;i<n;i++)
    {
      matr->index = push_list(matr->index,i,0);
    }
    matr->data = NULL;
    matr->n = n;
    matr->m = m;
  }
  return matr;
}

struct matrix* push_matrix(struct matrix* matr, int i,int j,double data)
{
  if(data != 0)
  {
    if(peek_list(matr->index,i-1) == 0)
    {
      matr->index = delete_list(matr->index,i-1);
      matr->index = push_list(matr->index,i-1,size_list(matr->data)+1);
      matr->data = push_list(matr->data,size_list(matr->data),j);
      matr->data = push_list(matr->data,size_list(matr->data),data);
      matr->data = push_list(matr->data,size_list(matr->data),0);
    }
    else
    {
      int pos = peek_list(matr->index,i-1)-1;
      while(peek_list(matr->data,pos+2)!=0)
      {
        pos = peek_list(matr->data,pos+2);
      }
      matr->data = delete_list(matr->data,pos+2);
      matr->data = push_list(matr->data,pos+2,size_list(matr->data)+1);
      matr->data = push_list(matr->data,size_list(matr->data),j);
      matr->data = push_list(matr->data,size_list(matr->data),data);
      matr->data = push_list(matr->data,size_list(matr->data),0);
    }
  }
  return matr;
}


void print_matr_mach(struct matrix* matr)
{
  print_list(matr->index);
  printf("\n");
  print_list(matr->data);
  printf("\n");
}

float znach_cord(struct matrix* matr,int i,int j)
{
  if(peek_list(matr->index,i-1)==0) return 0;
  else
  {
    int pos = peek_list(matr->index,i-1)-1;
    while((peek_list(matr->data,pos+2)!=0) && (peek_list(matr->data,pos)!=j))
    {
      pos = peek_list(matr->data,pos+2);
    }
    if(peek_list(matr->data,pos)==j) return peek_list(matr->data,pos+1);
    else return 0;
  }
}

void print_matr_standart(struct matrix* matr)
{
  for(int i=1;i<=matr->n;i++)
  {
    for(int j=1;j<=matr->m;j++)
    {
      printf("%f\t",znach_cord(matr,i,j));
    }
    printf("\n");
  }
}

struct matrix* sum_matrix(struct matrix* am,struct matrix* bm,struct matrix* cm)
{
  for(int i=1;i<=am->n;i++)
  {
    for(int j=1;j<=bm->m;j++)
    {
      cm = push_matrix(cm,i,j,znach_cord(am,i,j)+znach_cord(bm,i,j));
    }
  }
  return cm;
}

int simmetr_matr(struct matrix* cm)
{
  int flag = 1;
  for(int i=1;i<=cm->n;i++)
  {
    for(int j=1;j<=cm->m;j++)
    {
      if(znach_cord(cm,i,j) != znach_cord(cm,j,i)) flag =0;
    }
  }
  return flag;
}
