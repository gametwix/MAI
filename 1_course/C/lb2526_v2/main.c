#include <stdio.h>
#include "deque.h"

int main()
{
  deque a;
  create(&a);
  while(1)
  {
    int sw;
    printf("Добавить элемент в начало дека - 1\n");
    printf("Добавить элемент в конец дека - 2\n");
    printf("Вытащить первый элемент из дека - 3\n");
    printf("Вытащить последний элемент из дека - 4\n");
    printf("Вывести дек - 5\n");
    printf("Вывести максимальный элемент - 6\n");
    printf("Удалить максимальный элемент - 7\n");
    printf("Сортировка - 8\n");
    printf("Выход - 0\n");

    printf("Введите число:");
    scanf("%d",&sw);

    if(sw==0) break;
    else
    {
      printf("\n");
      int data;
      switch (sw)
      {
        case 1:
          printf("Введите число:");
          scanf("%d",&data);
          push_s(&a,data);
          break;
        case 2:
          //int data;
          printf("Введите число:");
          scanf("%d",&data);
          push_e(&a,data);
          break;
        case 3:
        //  int data;
          data = pop_s(&a);
          printf("Первое число: %d\n",data);
          break;
        case 4:
        //  int data;
          data = pop_e(&a);
          printf("Последнее число: %d\n",data);
          break;
        case 5:
          printd(&a);
          break;
        case 6:
          //  int data;
          data = find_max(&a);
          printf("Максимальное число: %d\n",data);
          break;
        case 7:
          del_max(&a);
          break;
        case 8:
          sort(&a);
          break;
      }
    }
    printf("\n");

  }
  return 0;
}
