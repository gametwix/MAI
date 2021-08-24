#include <stdio.h>
#include "database.h"

int main()
{
  data base_node;
  FILE *file;
  char fname[50];
  printf("Enter filename: ");
  scanf("%s",fname);
  file=fopen(fname,"wb+");
  while(1)
  {
    int breaker;
    printf("Add in base - 1\n");
    printf("Stop adding - 0\n");
    scanf("%d",&breaker);
    if(breaker == 0)
    {
      break;
    }
    else
    {
      printf("Enter surname: ");
      scanf("%s",&base_node.surname);
      printf("Enter name: ");
      scanf("%s",&base_node.name);
      printf("Enter patronymic: ");
      scanf("%s",&base_node.patronymic);
      printf("Enter gender: ");
      scanf("%d",&base_node.gender);
      printf("Enter groupnum: ");
      scanf("%d",&base_node.groupnum);
      for(int i=0;i<5;i++)
      {
        printf("Enter assessment number %d: ",i+1);
        scanf("%d",&base_node.value[i]);
      }
      fwrite(&base_node,sizeof(data),1,file);
    }
  }
  fclose(file);
  return 0;
}
