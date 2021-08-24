#ifndef _LIST_
#define _LIST_

struct list{
  struct list* next;
  struct list* prev;
  long double key;
  char *data;
};

struct mas
{
  long double key;
  char *data;
};

void Print_list(struct list *top);
int Size_list(struct list* top);
struct list* Create_list(struct list* top);
struct list* Push_list(struct list* top,long double key,char *data, int pos);
struct list* Delete_list_pos(struct list *top,int pos);
void Pop_list(struct list *top,long double *key, char **data, int pos);
struct list* Change_pos(struct list *top,int pos1,int pos2);
void Copy_mass(char *data,char **cdata);
struct list* Sort_list(struct list *top);
struct list* Clear_list(struct list *top);
struct mas* List_mas(struct list* top, int *size);
void Search_mas(long double key,long double accur,struct mas *m,int size);
struct list* Mix_list(struct list* top);
#endif
