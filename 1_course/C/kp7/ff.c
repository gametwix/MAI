#include <stdio.h>

int main()
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
    return 0;
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
    printf("%d,%d\n",sim,k);
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
  printf("\n\nn1=%d m1=%d n2=%d m2=%d\n",n1,m1,n2,m2);
  fclose(fl);

  return 0;
}
