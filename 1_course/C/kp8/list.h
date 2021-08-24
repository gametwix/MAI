#ifndef _LIST_
#define _LIST_

struct list{
  int data;
  int br;
  struct list *next;
};

void Print_list(struct list *top);
struct list* Create_list(struct list *top);
int Size_list(struct list *top);
struct list* Push_list(struct list *top,int data,int pos);
struct list* Delete_list_pos(struct list *top,int pos);
int Find_list_data(struct list *top,int data);
struct list* Delete_list_data(struct list *top,int data);
struct list* Clear_list(struct list *top);

#endif
