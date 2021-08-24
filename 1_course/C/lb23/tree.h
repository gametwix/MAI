#ifndef _TREE_
#define _TREE_

struct tree{
  float data;
  struct tree *parent;
  struct tree *right;
  struct tree *left;
};


void add_t(struct tree **root,float data,struct tree *parent);
void pr_t(struct tree **root,int level);
void pad(int level);
void dl_t(struct tree **root,float data,struct tree *parent);
int laba(struct tree **root);
#endif
