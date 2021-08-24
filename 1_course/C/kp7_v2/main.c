#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void size_matr(int *i1,int *j1,int *i2,int *j2)
{
  int n1=0;
  int m1=0;
  int n2=0;
  int m2=0;
  FILE *fl;
  char name[]="matrix";
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
    if((sim>=48)&&(sim<=57)||sim==46||sim==45) flag=1;
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
    if((sim>=48)&&(sim<=57)||sim==46||sim==45)
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
    if((sim>=48)&&(sim<=57)||sim==46||sim==45) flag=1;
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
    if((sim>=48)&&(sim<=57)||sim==46||sim==45)
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
  char name[]="matrix";
  //------------------------
  struct matrix *am=NULL;
  struct matrix *bm=NULL;
  struct matrix *cm=NULL;
  int n1,m1,n2,m2;
  size_matr(&n1,&m1,&n2,&m2);
  //printf("%d %d %d %d \n", n1,m1,n2,m2);
  am=create_matrix(am,n1,m1);
  bm=create_matrix(bm,n2,m2);
  if ((fl = fopen(name, "r")) == NULL)
  {
    printf("Не удалось открыть файл");
    return 0;
  }
  for(int i=1;i<=n1;i++)
  {
    for(int j=1;j<=m1;j++)
    {
      double l;
      fscanf(fl,"%lf ",&l);
    //  printf("%f q",l);
      am = push_matrix(am,i,j,l);
    }
    //printf("\n");
  }
  for(int i=1;i<=n2;i++)
  {
    for(int j=1;j<=m2;j++)
    {
      double l;
      fscanf(fl,"%lf ",&l);
      //printf("%f q",l);
      bm = push_matrix(bm,i,j,l);
    }
    //printf("\n");
  }
  fclose(fl);

  // тут добавить
  print_matr_mach(am);
  // тут добавить
  print_matr_mach(bm);

// тут добавить
  print_matr_standart(am);
  printf("\n");
  // тут добавить
  print_matr_standart(bm);
  printf("\n");

  if(am->n == bm->n && am->m == bm->m)
  {
    cm = create_matrix(cm,am->n,am->m);
    cm = sum_matrix(am,bm,cm);
    // тут добавить
    print_matr_standart(cm);
    printf("\n");
    // тут добавить
    if(simmetr_matr(cm)) printf("simetr\n");
    else printf("ne simetr\n");
  }
  else
  {
    // тут поменять
    printf("Raszn razmerov\n");
  }
  return 0;
}
