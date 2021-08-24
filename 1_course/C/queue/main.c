#include <stdio.h>
#include "queue.h"
void sdvig(queue *q,int d)
{
  for(int i=0;i<d;i++)
  {
    enqueue(q,dequeue(q));
  }
}
void paste(queue *q,int k,int i,int f)
{
  sdvig(q,k-i-2);
  int pr;
  pr=dequeue(q);
  enqueue(q,pr);
  int s=0;
  while(!((f>=pr)&&(f<peek(q))))
  {
    enqueue(q,dequeue(q));
    s++;
  }
  enqueue(q,f);
  enqueue(q,dequeue(q));
  sdvig(q,i-s-1);
}
int main()
{
  queue a;
  creat(&a);
  printf("Введите количество элементов(не больше 100)\n");
  int k;
  scanf("%d",&k);
  printf("Вводите элементы\n");
  for(int i=0;i<k;i++)
  {
    int j;
    scanf("%d",&j);
    enqueue(&a,j);
  }
  printq(&a);
  int f=dequeue(&a);
  enqueue(&a,f);
  for(int i=0;i<k-1;i++)
  {
    if(peek(&a)<f)
    {
      paste(&a,k,i,dequeue(&a));
    }
    else {
      f=dequeue(&a);
      enqueue(&a,f);
    }
  }
  printq(&a);
  return 0;
}
