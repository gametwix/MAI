#ifndef _STACK_
#define _STACK_

struct stack_i{
  int data;
  struct stack_i *next;
} ;


void push_i(struct stack_i **top, int d);
int pop_i(struct stack_i **top);
int size_i(struct stack_i **top);
int peek_i(struct stack_i **top);

#endif
