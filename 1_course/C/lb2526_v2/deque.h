#ifndef _DEQUE_
#define _DEQUE_

typedef struct {
  int node[100];
  int size;
  int start;
  int end;
} deque;

void create(deque *deq);
void push_s(deque *deq,int data);
void push_e(deque *deq,int data);
int peek_s(deque *deq);
int pop_s(deque *deq);
int pop_e(deque *deq);
int size_d(deque *deq);
int empty(deque *deq);
void printd(deque *deq);
int find_max(deque *deq);
void del_max(deque *deq);
void sort(deque *deq);
int find_max_otr(deque *deq,int k);
void del_zn(deque *deq,int data);
#endif
