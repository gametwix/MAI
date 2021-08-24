#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <math.h>

struct list* rfile(struct list *top,FILE *fl)
{
  top = Clear_list(top);
  int i=1;
  long double key;
  char *data;
  char ch;
  ch = fgetc(fl);
  while(ch!=EOF)
  {
    int j=0;
    int flagm=0;
    data = malloc(256*sizeof(char));
    key=0;

    long double mn=0.1;
    while((int)ch!=46 && (int)ch!=32)
    {
      if((int)ch == 45)
      {
        flagm=1;
        ch = fgetc(fl);
        continue;
      }
      key*=10;
      key+=(int)ch-48;
      ch = fgetc(fl);
    }
    if((int)ch!=32)
    {
    ch = fgetc(fl);
    while((int)ch!=32)
    {
      key+=(((int)ch-48)*mn);
      mn*=0.1;
      ch = fgetc(fl);
    }
  }
    if(flagm == 1) key*=-1;
    ch = fgetc(fl);
    while((int)ch!=10)
    {
      data[j]=ch;
      j++;
      ch = fgetc(fl);
    }
    top=Push_list(top,key,data,i);
    i++;
    //ch = fgetc(fl);
    ch = fgetc(fl);
  }
  return top;
}

void menu(struct list *top, struct mas* m)
{
  int size = 0;
  int sort = 0;
  int read = 0;
  while(1)
  {
    int sw;
    printf("Список действий:\n");
    printf("0 - Выход\n");
    printf("1 - Прочитать файл\n");
    if(read == 1) printf("2 - Сортировка таблицы\n");
    else printf("2 - Сортировка таблицы(доступно после считывания файла)\n");
    if(sort == 1) printf("3 - Поиск в таблице\n");
    else printf("3 - Поиск в таблице (не доступно на не отсортированной таблице)\n");
    if(read == 1) printf("4 - Перемешать таблицу\n");
    else printf("4 - Перемешать таблицу(доступно после считывания файла)\n");
    printf("Введите вариант: ");
    scanf("%d",&sw);
    if(sw==0)
    {
        break;
    }
    else if(sw ==1)
    {
        FILE *fl;

        char fname[80];
        printf("Введите имя файла:");
        scanf("%s",fname);
        if ((fl = fopen(fname, "r")) == NULL)
        {
          printf("Не удалось открыть файл\n");
          continue;
        }
        top = rfile(top,fl);
        fclose(fl);
        Print_list(top);
        sort = 0;
        read = 1;
    }
    else if(sw == 2 && read == 1)
    {
        top = Sort_list(top);
        Print_list(top);
        m = List_mas(top,&size);
        sort = 1;
    }
    else if(sw == 3 && sort == 1)
    {
      printf("Введите ключ для поиска:");
      long double key;
      scanf("%Lf",&key);
      long double accur;
      printf("Введите точность:");
      scanf("%Lf",&accur);
      Search_mas(key,accur,m,size);
    }
    else if(sw == 4 && read == 1)
    {
      top = Mix_list(top);
      sort = 0;
      Print_list(top);
    }
  }
}


int main()
{
  struct list *l_tab = NULL;
  struct mas *m = NULL;
  menu(l_tab,m);
  return 0;
}
