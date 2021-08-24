#include <stdio.h>

int main()
{
  float a;
  float b;
  float c;
  float r;
  scanf("%f",&a);
  scanf("%f",&b);
  scanf("%f",&c);
  int flag=0;
  printf("%d\n",flag);
  for(float i=-20;i<20;i++)
  {
    printf("%d\n",flag);
    for(float j=-20;j<20;j++)
    {
      r=i*i*a+i*j*b+j*j*c;
      if(r>0){
        if(flag==0) flag=1;
        if(flag==-1)
        {
          printf("%d\n",flag);
          flag=2;
          printf("%d\n",flag);
        }
      }
      if(r<0){
        if(flag==0) flag=-1;
        if(flag==1)
        {
          printf("%d\n",flag);
          flag=2;
          printf("%d\n",flag);
        }
      }
      printf("%f\t%d\t%f\t%f\n",r,flag,i,j);
    }
  }
  if(flag==1) printf("Положительно\n");
  if(flag==-1) printf("Отрицательно\n");
  if(flag==2) printf("Переменно\n");
  return 0;
}
