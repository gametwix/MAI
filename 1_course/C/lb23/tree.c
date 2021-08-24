#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

void add_t(struct tree **root,float data,struct tree *parent)
{
  if((*root)==NULL)
  {
    (*root)=malloc(sizeof(struct tree));
    (*root)->right=NULL;
    (*root)->left=NULL;
    (*root)->data=data;
    (*root)->parent=parent;
    if(parent!=NULL)
    {
      if(data<parent->data) parent->left=(*root);
      else parent->right=(*root);
    }
  }
  else
  {
    if(data<(*root)->data) add_t(&((*root)->left),data,(*root));
    else add_t(&((*root)->right),data,(*root));
  }
}

void pr_t(struct tree **root,int level)
{
  if((*root)!=NULL)
  {
    pr_t(&((*root)->right),level+1);
    pad(level);
    printf("%g\n",(*root)->data);
    pr_t(&((*root)->left),level+1);

  }
  else
  {
    pad(level);
    printf("-\n");
  }
}

void pad(int level)
{
  for(int i=0;i<level;i++)
  {
    printf("\t");
  }
}

void dl_t(struct tree **root,float data,struct tree *parent)
{
  if((*root)!=NULL)
  {
    if(data<(*root)->data) dl_t(&((*root)->left),data,(*root));
    if(data>(*root)->data) dl_t(&((*root)->right),data,(*root));
    if(data==(*root)->data)
    {
      if(((*root)->right==NULL)&&((*root)->left==NULL))
      {
        if(parent->right->data==data)
        {
          struct tree *q=(*root)->parent;
          free((*root));
          q->right=NULL;
        }
        else
        {
          struct tree *q=(*root)->parent;
          free((*root));
          q->left=NULL;
        }
      }
      else if(((*root)->right!=NULL)&&((*root)->left!=NULL))
      {
        struct tree *last=(*root);
        last=last->right;
        if(last->left!=NULL)
        {
          while(last->left!=NULL)
          {
            last=last->left;
          }
          (*root)->data=last->data;
          if(last->right==NULL)
          {
            last->parent->left=NULL;
            free(last);
          }
          else
          {
            last->parent->left=last->right;
            free(last);
          }
        }
        else
        {
          if(last->right==NULL)
          {
            last->parent->right=NULL;
            free(last);
          }
          else
          {
            last->parent->right=last->right;
            free(last);
          }
        }
      }
      else if(((*root)->right!=NULL)&&((*root)->left==NULL))
      {
        struct tree *last=(*root);
        struct tree *pr=last->parent;
        if(last==pr->right) pr->right=last->right;
        else pr->left=last->right;
        free(last);
      }
      else if(((*root)->right==NULL)&&((*root)->left!=NULL))
      {
        struct tree *last=(*root);
        struct tree *pr=last->parent;
        if(last==pr->right) pr->right=last->left;
        else pr->left=last->left;
        free(last);
      }
    }
  }
}

int laba(struct tree **root)
{
  if((*root)==NULL || ((*root)->right==NULL && (*root)->left==NULL)) return 1;
  return 0;
}
