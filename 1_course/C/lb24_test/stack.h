#ifndef _QUEUE_
#define _QUEUE_

struct stack_i{
  int data;
  struct stack_i *next;
} ;

struct stack_c{
  char data;
  struct stack_c *next;
};

void push_i(struct stack_i **top, int d);
int pop_i(struct stack_i **top);
int size_i(struct stack_i **top);
int peek_i(struct stack_i **top);

void push_c(struct stack_c **top, char d);
int pop_c(struct stack_c **top);
int size_c(struct stack_c **top);
char peek_c(struct stack_c **top);
#endif
