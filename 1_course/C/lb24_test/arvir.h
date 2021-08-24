#ifndef _QUEUE_
#define _QUEUE_

struct arvir{
  int type;
  int data;
  struct arvir *next;
  struct arvir *previous;
  struct arvir *last;
};
void prarvir(struct arvir **top);

void push_f(struct arvir **top,int d,int type);
void push_l(struct arvir **top,int d,int type);

void pop_f(struct arvir **top,int *d,int *type);
void pop_l(struct arvir **top,int *d,int *type);

void peek_f(struct arvir **top,int *d,int *type);
void peek_l(struct arvir **top,int *d,int *type);

int size_ar(struct arvir **top);

void strtoarvir(char *array,int maxsize,struct arvir **top);



#endif
