#ifndef _ARVIR_
#define _ARVIR_

struct arvir{
  int type;
  int data;
  struct arvir *next;
  struct arvir *previous;
  struct arvir *last;
};


void push_f(struct arvir **top,int d,int type);
void push_l(struct arvir **top,int d,int type);

void pop_f(struct arvir **top,int *d,int *type);
void pop_l(struct arvir **top,int *d,int *type);

int size_ar(struct arvir **top);

void peek_f(struct arvir **top,int *d,int *type);
void peek_l(struct arvir **top,int *d,int *type);

void strtoarvir(char *array,int maxsize,struct arvir **top);

void prarvir(struct arvir **top);

#endif
