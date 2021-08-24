#include <stdio.h>
#include "list.h"

int main()
{
  struct list *l=NULL;
  while(true)
  {
    int k;
    printf("Выберете действие:\n1-Добавить элимент в список\n");
    printf("2-Вывести список\n3-Удалить элимент из списка по позиции\n");
    printf("4-Удалить элимент из списка по значению\n");
    printf("5-Вывести длину списка\n");
    printf("6-Очистить список если в нем присудствует введенный элимент\n");
    printf("7-Выход\n");
    printf("Выбор: ");
    scanf("%d",&k);
    if(k==7)break;
    else
    {
      bool d;
      int p;
      switch (k) {
        case 1:
          printf("Введите значение элимента: ");
          scanf("%d",&d);
          printf("Введите позицию элимента: ");
          scanf("%d",&p);
          l=Push_list(l,d,p);
          break;
        case 2:
          Print_list(l);
          break;
        case 3:
          printf("Введите позицию элимента: ");
          scanf("%d",&p);
          l=Delete_list_pos(l,p);
          break;
        case 4:
          printf("Введите значение элимента: ");
          scanf("%d",&d);
          l=Delete_list_data(l,d);
          break;
        case 5:
          printf("Длина списка: %d\n",Size_list(l));
          break;
        case 6:
          printf("Введите значение элимента: ");
          scanf("%d",&d);
          p=Find_list_data(l,d);
          if(p!=0) l=Clear_list(l);
          break;
        default:
          break;
      }
    }
    printf("\n");
  }
  return 0;
}
