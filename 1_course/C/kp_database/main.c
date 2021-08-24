#include <stdio.h>
#include "database.h"
void theme()
{
  for(int i=0;i<99;i++) printf("-");
  printf("\n");
  printf("| № |    Surename    |    Name    | Patronymic | Gender | Gr_num | assessment > 1 | 2 | 3 | 4 | 5 |\n" );
  for(int i=0;i<99;i++) printf("-");
  printf("\n");
}
void output(data base, int *n)
{
  printf("|%3d|%16s|",*n,base.surname);
  printf("%12s|%12s|",base.name,base.patronymic);
  printf("%8d|%8d|",base.gender,base.groupnum);
  printf("%16d|%3d|",base.value[0],base.value[1]);
  printf("%3d|%3d|%3d|\n",base.value[2],base.value[3],base.value[4]);

  for(int i=0;i<99;i++) printf("-");
  printf("\n");
  (*n)++;
}

int sumval(data *base)
{
  int a=0;
  for(int i=0;i<5;i++)
  {
    a += base->value[i];
  }
  return a;
}

int morfour(data *base)
{
  int a=1;
  for(int i=0;i<5;i++)
  {
    if(base->value[i]<4) a=0;
  }
  return a;
}

int main(int argc, char * argv[])
{
  int n=1;
  data base;
  FILE *file;
  char fname[50];
  double grmax[20]={0};
  int grst[20]={0};
  printf("Enter filename: ");
  scanf("%s",fname);
  if((file=fopen(fname,"rb"))==NULL)
  {
    printf("Error input file name\n");
    return 1;
  }
  if((argc==2) && (argv[1][0]=='-')&&(argv[1][1]=='f')) theme();
  while(!feof(file))
  {
    fread(&base,sizeof(data),1,file);
    if(feof(file)) break;
    if((argc==2) && (argv[1][0]=='-')&&(argv[1][1]=='f')) output(base,&n);
    if(base.gender == 0){
      grmax[base.groupnum]+=(double)sumval(&base);
      grst[base.groupnum]++;
    }
  }
  for(int i=0;i<20;i++)
  {
    if(grst[i]!=0) grmax[i] = grmax[i] / (grst[i]*5);
  }
  int num = 0;
  double maximum=0;
  for(int i=0;i<20;i++)
  {
    if(grmax[i] >= maximum){
      maximum = grmax[i];
      num = i;
    }
  }
  fclose(file);
  /*grmax[base.groupnum];
  file=fopen(fname,"rb");
  printf("Surname of the best students of the course\n");
  for(int i=0;i<35;i++)printf("-");
  printf("\n");
  while(!feof(file))
  {
    fread(&base,sizeof(data),1,file);
    if(feof(file)) break;
    if(base.gender == 0)
    {
      if(morfour(&base))
      {
        if(sumval(&base)>= grmax[base.groupnum])
        {
          printf("|  Surename  |%20s|\n",base.surname);
          for(int i=0;i<35;i++)printf("-");
          printf("\n");
        }
      }
    }
  }

  fclose(file);*/

  printf("%d  %f\n",num,maximum );
  return 0;
}
