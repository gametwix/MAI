#ifndef _QUEUE_
#define _QUEUE_

typedef struct
{
  int node[100];
  int start;
  int end;
  int count;
} queue;

int count(queue *q);
void creat(queue *q);
int empty(queue *q);
void enqueue(queue *q,int key);
int peek(queue *q);
int dequeue(queue *q);
void printq(queue *q);
#endif
