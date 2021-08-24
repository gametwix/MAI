#include <stdio.h>
#include <stdlib.h>
#include "rname.h"
#include "replace.h"
#include "elgroup.h"

struct elgroup* Create_ver(struct elgroup* top)
{
  if(top == NULL)
  {
    top=malloc(sizeof(struct elgroup));
    top->next = NULL;
    top->prev = NULL;
    top->data = NULL;
  }
  return top;
}

struct elgroup* Create_obr(struct elgroup* top)
{
  if(top == NULL)
  {
    top=malloc(sizeof(struct elgroup));
    top->next = NULL;
    top->prev = NULL;
    top->data = Push_gname(top->data,'e',1,1);
  }
  return top;
}

struct elgroup* Push_elgr(struct elgroup *top, struct gname *obr, int pos)
{
  if(top == NULL)
  {
    top = Create_obr(top);
  }
    int size = Size_elgroup(top);
    if(pos > size)
    {
      struct elgroup *m = top;
      while(m->next != NULL) m = m->next;
      struct elgroup *q;
      q = malloc(sizeof(struct elgroup));
      q->prev = m;
      q->next  = NULL;
      q->data = obr;
      m->next = q;
      return top;
    }
    else if(pos == 1)
    {
      struct elgroup *q;
      q = malloc(sizeof(struct elgroup));
      q->prev = NULL;
      q->next = top;
      q->data = obr;
      top = q;
      return top;
    }
    else
    {
      struct elgroup *m = top;
      for(int i = 2;i < size;i++) m=m->next;
      struct elgroup *q;
      q = malloc(sizeof(struct elgroup));
      q->data = obr;
      q->prev = m;
      q->next = m->next;
      m->next->prev = q;
      m->next = q;
      return top;
    }
}


int Size_elgroup(struct elgroup *top)
{
  int size = 0;
  if(top != NULL)
  {
    size = 1;
    while(top->next != NULL)
    {
      size++;
      top = top->next;
    }
  }
  return size;
}

void Print_elgroup(struct elgroup *top)
{
  while(top != NULL)
  {
    printf("ELGROUP: ");
    Print_gname(top->data);
    top = top->next;
  }
  printf("\n");
}

struct elgroup* Readfile_obraz(struct elgroup *top)
{
  FILE* fl;
  fl = fopen("obraz","r");
  int j = 1;
  while(!feof(fl))
  {
    int i = 0;
    char str1[256];
    char ch = fgetc(fl);
    if(feof(fl)) break;
    if((int)ch != 10 && (int)ch != 32 && ch != '\0'&& ch != '\n')
    {
      while((int)ch != 10)
      {
        str1[i]=ch;
        ch = fgetc(fl);
        i++;
      }
      str1[i] = '\0';
      struct gname *r = NULL;
      r = Str_to_gname(str1,r);
      r = Norm_step_gname(r);
      top = Push_obr(top,r,j);
      j++;
    }
  }
  return top;
  fclose(fl);
}


struct elgroup* Push_obr(struct elgroup *top, struct gname *data, int pos)
{
  if(top == NULL)
  {
    top = Create_ver(top);
    top->data = data;
    return top;
  }
  else
  {
    int size = Size_elgroup(top);
    if(pos > size)
    {
      struct elgroup *m = top;
      while(m->next != NULL) m=m->next;
      struct elgroup *q;
      q = malloc(sizeof(struct elgroup));
      q->prev = m;
      q->next  = NULL;
      q->data = data;
      m->next = q;
      return top;
    }
    else if(pos == 1)
    {
      struct elgroup *q;
      q = malloc(sizeof(struct elgroup));
      q->prev = NULL;
      q->next = top;
      q->data = data;
      top = q;
      return top;
    }
    else
    {
      struct elgroup *m = top;
      for(int i = 2;i < size;i++) m=m->next;
      struct elgroup *q;
      q = malloc(sizeof(struct elgroup));
      q->data = data;
      q->prev = m;
      q->next = m->next;
      m->next->prev = q;
      m->next = q;
      return top;
    }
  }
}

int Exist_ravn_elem(struct elgroup *top,struct gname *gn,struct reprule *rule)
{
  int ex = 0;
  while(top != NULL)
  {
    if(Ravn_gname(top->data,gn,rule)) ex = 1;
    top = top->next;
  }
  return ex;
}


struct elgroup *Find_new_elem(struct elgroup *top,struct elgroup *obr,struct gname *gn,struct reprule *rule, int n)
{
  while(obr != NULL)
  {
    gn = Copy_gname(gn);
    gn = Push_gname(gn,obr->data->obr,obr->data->step,Size_gname(gn)+1);
    gn = Norm_step_gname(gn);
    if(!Exist_ravn_elem(top,gn,rule))
    {
      top = Push_elgr(top,gn,Size_elgroup(top)+1);
      if(n < 5)
      {
        top = Find_new_elem(top,obr,gn,rule,(n+1));
      }
    }
    obr = obr->next;
  }
  return top;
}

struct elgroup* Gotopos_elgroup(struct elgroup *top,int pos)
{
  int size = Size_elgroup(top);
  if(size < pos) pos = size;
  for(int i = 1;i < pos;i++)
  {
    top = top->next;
  }
  return top;
}
