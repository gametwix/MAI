#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"



struct Matrix* End_Matrix(struct Matrix *mat)
{
  if(mat!=NULL)Push_Node(mat->Pos,-1);
  return mat;
}
struct Matrix* Mult_Matrix(struct Matrix *am,struct Matrix *bm)
{
  if(am->m==bm->n)
  {
    struct Matrix *cm = NULL;
    cm = Create_Matrix(cm,am->n,bm->m);
    for(int i=1;i<=am->n;i++)
    {
      for(int j=1;j<=bm->m;j++)
      {
        int ch=0;
        for(int k=1;k<=bm->n;k++)
        {
          int a=Peek_Matrix(am,i,k);
          int b=Peek_Matrix(bm,k,j);
          ch=ch+(a*b);
        }
        Push_Matrix(cm,i,j,ch);
      }
    }
    return cm;
  }
  else
  {
    printf("Невозможно умножить\n");
    return NULL;
  }
}

void Print_Matrix_Fis(struct Matrix *mat)
{
  if(mat!=NULL){
  int n=mat->n;
  int m=mat->m;
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
    {
      printf("%d\t",Peek_Matrix(mat,i,j));
    }
    printf("\n");
  }
}
}

int Peek_Matrix(struct Matrix *mat,int i,int j)
{
  int data;
  int pos=(i-1)*(mat->m)+j-1;
  int index=-1;
  struct Node *n=mat->Pos;
  while(n->data!=-1)
  {
    if(n->data==pos)
    {
      index=n->index;
      break;
    }
    n=n->next;
  }
  if(index==-1) return 0;
  else
  {
    Peek_Node(mat->Data,index,&data);
    return data;
  }
}

void Print_Matrix_WR(struct Matrix *mat)
{
  if(mat!=NULL)
  {
    int size = Size_Node(mat->Pos);
    int data;
    for(int i=0;i<size;i++) printf("%d\t",i);
    printf("\n");
    for(int i=0;i<size;i++)
    {
      Peek_Node(mat->Pos,i,&data);
      printf("%d\t",data);
    }
    printf("\n");
    for(int i=0;i<size-1;i++)
    {
      Peek_Node(mat->Data,i,&data);
      printf("%d\t",data);
    }
    printf("\n");
  }
}

struct Matrix* Create_Matrix(struct Matrix *mat,int n,int m)
{
  if(mat==NULL)
  {
    mat=malloc(sizeof(struct Matrix));
    mat->Data=NULL;
    mat->Pos=NULL;
    mat->m=m;
    mat->n=n;
  }
  return mat;
}

struct Matrix* Push_Matrix(struct Matrix *mat,int i,int j,int data)
{
  if((mat!=NULL)&&(data!=0))
  {
    mat->Data=Push_Node(mat->Data,data);
    int l=(i-1)*(mat->m)+j-1;
    mat->Pos=Push_Node(mat->Pos,l);
  }
  return mat;
}

//------------------------------------------------------------------------------

struct Node* Create_Node(struct Node *top)
{
  if(top==NULL)
  {
    top=malloc(sizeof(struct Node));
    top->index=-1;
    top->data=0;
    top->next=NULL;
    top->previous=NULL;
  }
  return top;
}

struct Node* Push_Node(struct Node *top,int data)
{
  if(top==NULL) top=Create_Node(top);
  if(top->index == -1)
  {
    top->data=data;
    top->index=0;
    return top;
  }
  else
  {
    int i=0;
    struct Node *q=top;
    while(q->next!=NULL)
    {
      q=q->next;
      i++;
    }
    q->next=Create_Node(q->next);
    q->next->data=data;
    q->next->index=i+1;
    q->next->previous=q;
  }
  return top;
}

void Peek_Node(struct Node *top,int ind,int *dat)
{
  while((top->index!=ind)&&(top->next!=NULL)) top=top->next;
  if(top->index==ind) *dat=top->data;
}

int Size_Node(struct Node *top)
{
  if(top!=NULL)
  {
    while(top->next!=NULL) top=top->next;
    return (top->index)+1;
  }
  else return 0;
}

void Print_Node(struct Node *top)
{
    while(top!=NULL)
    {
      printf("%d\t",top->data);
      top=top->next;
    }
    printf("\n");
}
