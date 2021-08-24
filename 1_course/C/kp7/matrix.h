#ifndef _MATRIX_
#define _MATRIX_

struct Matrix{
  int m;
  int n;
  struct Node *Data;
  struct Node *Pos;
};

struct Node{
  int index;
  int data;
  struct Node *next;
  struct Node *previous;
};


struct Matrix* End_Matrix(struct Matrix *mat);
struct Matrix* Mult_Matrix(struct Matrix *am,struct Matrix *bm);
void Print_Matrix_WR(struct Matrix *mat);
struct Matrix* Create_Matrix(struct Matrix *mat,int n,int m);
struct Matrix* Push_Matrix(struct Matrix *mat,int i,int j,int data);
int Peek_Matrix(struct Matrix *mat,int i,int j);
void Print_Matrix_Fis(struct Matrix *mat);
//--------------------------------------------------------------------------
struct Node* Create_Node(struct Node *top);
struct Node* Push_Node(struct Node *top,int data);
void Peek_Node(struct Node *top,int ind,int *dat);
int Size_Node(struct Node *top);
void Print_Node(struct Node *top);

#endif
