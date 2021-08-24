#include <stdio.h>
#include "tree.h"

int main()
{
  struct tree *t=NULL;
  printf("Заполнение дерева:\n");
  while(1)
  {
    int v;
    printf("Добавить новый элимент (да-1,нет-0):");
    scanf("%d",&v);
    if(v==0) break;
    else
    {
      float j;
      printf("Введите новый элимент:");
      scanf("%f",&j);
      add_t(&t,j,NULL);
      pr_t(&t,0);
    }
  }
  pr_t(&t,0);
  if(laba(&t)) printf("Дерево симметричное\n");
  else printf("Дерево не симметричное\n");

  return 0;
}
