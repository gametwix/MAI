#ifndef _TABLE_
#define _TABLE_

#define SIZE 60

struct table
{
  double key[SIZE];
  char data[SIZE][256];
  int size;
};

void Create_table(struct table *t);
void Push_table(struct table *t,double key,char *data);
void Print_table(struct table *t);
int Find_paste(struct table *t,double key,int size);
void Sort_table(struct table *t);
void Search_table(double key,double accur,struct table *m);
void Replace_mas(char *a, char *b);
void Mix_table(struct table* t);


#endif
