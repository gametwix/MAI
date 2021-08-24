#include <stdio.h>
#include "queue.h"

void creat(queue *q)
{
  q->count=0;
  q->start=0;
  q->end=-1;
}

int count(queue *q)
{
  return q->count;
}

int empty(queue *q)
{
  if(q->count == 0) return 1;
  else return 0;
}

void enqueue(queue *q,int key)
{
  if((q->count+1)>100)
  {
    printf("Queue if full\n");
  }
  else
  {
    q->count++;
    q->end=(q->end+1)%100;
    q->node[q->end]=key;
  }
}

int peek(queue *q)
{
  return q->node[q->start];
}

int dequeue(queue *q)
{
  int key = peek(q);
  q->count--;
  q->start=(q->start+1)%100;
  return key;
}

void printq(queue *q)
{
  for(int i=0;i<q->count;i++)
  {
    printf("%d ",peek(q));
    enqueue(q,dequeue(q));
  }
  printf("\n");
}
