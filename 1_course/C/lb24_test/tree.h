#ifndef _QUEUE_
#define _QUEUE_

struct tree{
  int data;
  int type;
  struct tree *right;
  struct tree *left;
};

void pushTree(struct tree **top,int data,int type);
void peekTree(struct tree **top,int *data,int *type);
void posttotre(struct tree **tr,struct arvir **arv);
void tretopost(struct tree **tr,struct arvir **arv);
#endif
