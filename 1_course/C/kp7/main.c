#include <stdio.h>
#include "matrix.h"

void size_matr(int *i1,int *j1,int *i2,int *j2)
{
  int n1=0;
  int m1=0;
  int n2=0;
  int m2=0;
  FILE *fl;
  char name[]="martix";
  if ((fl = fopen(name, "r")) == NULL)
  {
    printf("Не удалось открыть файл");
  }
  int sim;
  sim=fgetc(fl);
  int flag=0;
  int k=0;
  while(sim!=EOF)
  {
    if((sim>=48)&&(sim<=57)) flag=1;
    else
    {
      if(flag==1)
      {
        m1++;
        flag=0;
      }
    }
    if(sim==10) break;
    sim=fgetc(fl);
  }
  flag=1;
  while(sim!=EOF)
  {
    if((sim>=48)&&(sim<=57))
    {
      flag=1;
      k=0;
    }
    else
    {
      if(sim==10)
      {
        if(flag==1)
        {
          n1++;
        }
        k++;
      }
      else k=0;
      flag=0;
      if(k==2) break;
    }
    //printf("%d,%d\n",sim,k);
    sim=fgetc(fl);
  }
  sim=fgetc(fl);
  flag=0;
  k=0;
  while(sim!=EOF)
  {
    if((sim>=48)&&(sim<=57)) flag=1;
    else
    {
      if(flag==1)
      {
        m2++;
        flag=0;
      }
    }
    if(sim==10) break;
    sim=fgetc(fl);
  }
  flag =1;
  while(sim!=EOF)
  {
    if((sim>=48)&&(sim<=57))
    {
      flag=1;
      k=0;
    }
    else
    {
      if(sim==10)
      {
        if(flag==1)
        {
          n2++;
        }
        k++;
      }
      else k=0;
      flag=0;
      if(k==2) break;
    }
    sim=fgetc(fl);
  }
  *i1=n1;
  *j1=m1;
  *i2=n2;
  *j2=m2;
  fclose(fl);
}


int main()
{
  FILE *fl;
  char name[]="martix";
  //------------------------
  struct Matrix *am=NULL;
  struct Matrix *bm=NULL;
  struct Matrix *cm=NULL;
  int n1,m1,n2,m2;
  size_matr(&n1,&m1,&n2,&m2);
  am=Create_Matrix(am,n1,m1);
  bm=Create_Matrix(bm,n2,m2);
  if ((fl = fopen(name, "r")) == NULL)
  {
    printf("Не удалось открыть файл");
    return 0;
  }
  for(int i=1;i<=n1;i++)
  {
    for(int j=1;j<=m1;j++)
    {
      int l;
      fscanf(fl,"%d",&l);
      Push_Matrix(am,i,j,l);
    }
  }
  for(int i=1;i<=n2;i++)
  {
    for(int j=1;j<=m2;j++)
    {
      int l;
      fscanf(fl,"%d",&l);
      Push_Matrix(bm,i,j,l);
    }
  }
  fclose(fl);
  End_Matrix(am);
  End_Matrix(bm);
  printf("Матрица А по схеме размещения:\n");
  Print_Matrix_WR(am);
  printf("Матрица А в еслественном виде:\n");
  Print_Matrix_Fis(am);

  printf("Матрица Б по схеме размещения:\n");
  Print_Matrix_WR(bm);
  printf("Матрица Б в еслественном виде:\n");
  Print_Matrix_Fis(bm);

  cm=Mult_Matrix(am,bm);
  if(cm!=NULL){
    End_Matrix(cm);
    printf("Матрица С (ответ) по схеме размещения:\n");
    Print_Matrix_WR(cm);
    printf("Матрица С (ответ) в еслественном виде:\n");
    Print_Matrix_Fis(cm);
    printf("В матрице С %d ненулевых элиментов",Size_Node(cm->Data));
  }



  return 0;
}
