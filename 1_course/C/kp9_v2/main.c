#include <stdio.h>
#include <stdlib.h>
#include "table.h"


void rfile(struct table *t,FILE *fl);



int main()
{

  struct table t;

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
        Create_table(&t);
        char fname[80];
        printf("Введите имя файла:");
        scanf("%s",fname);
        if ((fl = fopen(fname, "r")) == NULL)
        {
          printf("Не удалось открыть файл\n");
          return 1;
        }
        rfile(&t,fl);
        fclose(fl);

        Print_table(&t);

        sort = 0;
        read = 1;
    }
    else if(sw == 2 && read == 1)
    {
        Sort_table(&t);
        Print_table(&t);
        sort = 1;
    }
    else if(sw == 3 && sort == 1)
    {
      printf("Введите ключ для поиска:");
      double key;
      scanf("%lf",&key);
      double accur;
      printf("Введите точность:");
      scanf("%lf",&accur);
      Search_table(key,accur,&t);
    }
    else if(sw == 4 && read == 1)
    {
      Mix_table(&t);
      sort = 0;
      Print_table(&t);
    }
  }
/*
  Sort_table(&t);
  printf("\n");
  Print_table(&t);

  double d;
  double s;
  scanf("%lf",&d);
  scanf("%f",&s);

*/


}

void rfile(struct table *t,FILE *fl)
{
  int i=1;
  double key;
  char *data;
  char ch;
  ch = fgetc(fl);
  while(ch!=EOF)
  {
    int j=0;
    int flagm=0;
    data = malloc(256*sizeof(char));
    key=0;

    double mn=0.1;
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
    Push_table(t,key,data);
    i++;
    //ch = fgetc(fl);
    ch = fgetc(fl);
  }
}
