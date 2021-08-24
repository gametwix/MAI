#ifndef _LIST_
#define _LIST_
typedef enum
{
  false,
  true
}bool;

struct list
{
  bool data;
  bool br;
  bool inl;
  int next;
};

void create(struct list *l,int *first);
int size(struct list *l,int *first);
void push(struct list *l,int *first, int pos, bool data);
int findmem(struct list *l);
void printlist(struct list *l,int *first);
void delpos(struct list *l,int *first,int pos);
int findel(struct list *l,int *first, bool data);
void delznach(struct list *l,int *first, bool data);
void kp(struct list *l,int *first, bool data);

#endif
