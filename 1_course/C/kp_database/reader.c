#include <stdio.h>
#include "database.h"

int main()
{
  data *base_node;
  FILE *file;
  char fname[50];
  scanf("%s",fname);
  file=fopen(fname,"rb");
  while(1)
  {
    fread(base_node,sizeof(data),1,file);
    if(feof(file)) break;
    printf("%s\n",base_node -> surname);
    printf("%s\n",base_node -> name);
    printf("%s\n",base_node -> patronymic);
    printf("%d\n",base_node -> groupnum);
    for(int i=0;i<5;i++)
    {
      printf("%d\n",base_node -> value[i]);
    }
    printf("---------------------\n");
  }
  fclose(file);
  return 0;
}
