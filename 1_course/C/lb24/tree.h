#ifndef _TREE_
#define _TREE_

struct tree{
  int data;
  int type;
  struct tree *right;
  struct tree *left;
};

void peek_Tree(struct tree **root,int *data,int *type);
void print_Tree(struct tree **root,int level);
void push_tree(struct tree **top,int data,int type);
void pr_padding(char ch,int level);
void pop_Tree(struct tree **root,int *data,int *type);

#endif
