#include <stdio.h>
#include <stdlib.h>
#include "rname.h"
#include "replace.h"


struct reprule* Create_reprule(struct reprule *top)
{
  if(top == NULL)
  {
    top=malloc(sizeof(struct reprule));
    top->next = NULL;
    top->prev = NULL;
    top->rep = NULL;
    top->to = NULL;
  }
  return top;
}

struct reprule* Push_reprule(struct reprule *top, struct gname *rep, struct gname *to, int pos)
{
  if(top == NULL)
  {
    top = Create_reprule(top);
    top->rep = rep;
    top->to = to;
    return top;
  }
  else
  {
    int size = Size_reprule(top);
    if(pos > size)
    {
      struct reprule *m = top;
      while(m->next != NULL) m=m->next;
      struct reprule *q;
      q = malloc(sizeof(struct reprule));
      q->prev = m;
      q->next  = NULL;
      q->rep = rep;
      q->to = to;
      m->next = q;
      return top;
    }
    else if(pos == 1)
    {
      struct reprule *q;
      q = malloc(sizeof(struct reprule));
      q->prev = NULL;
      q->next = top;
      q->rep = rep;
      q->to = to;
      top = q;
      return top;
    }
    else
    {
      struct reprule *m = top;
      for(int i = 2;i < size;i++) m=m->next;
      struct reprule *q;
      q = malloc(sizeof(struct reprule));
      q->rep = rep;
      q->to = to;
      q->prev = m;
      q->next = m->next;
      m->next->prev = q;
      m->next = q;
      return top;
    }
  }
}

int Size_reprule(struct reprule *top)
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

void Print_reprule(struct reprule *top)
{
  while(top != NULL)
  {
    printf("REP: ");
    Print_gname(top->rep);
    printf("TO: ");
    Print_gname(top->to);
    top = top->next;
  }
  printf("\n");
}

struct reprule* Readfile_reprule(struct reprule *top)
{
  FILE* fl;
  fl = fopen("reprule","r");
  int j = 1;
  while(!feof(fl))
  {
    int i = 0;
    char str1[256];
    char str2[256];
    char ch = fgetc(fl);
    if(feof(fl)) break;
    if((int)ch != 10 && (int)ch != 32 && ch != '\0'&& ch != '\n')
    {
      while((int)ch != 32)
      {
        str1[i]=ch;
        ch = fgetc(fl);
        i++;
      }
      str1[i] = '\0';
      ch = fgetc(fl);
      i=0;
      while((int)ch != 10)
      {
        str2[i]=ch;
        ch = fgetc(fl);
        i++;
      }
      //ch = fgetc(fl);
      str2[i] = '\0';
      struct gname *r = NULL;
      struct gname *t = NULL;
      r = Str_to_gname(str1,r);
      r = Norm_step_gname(r);
      t = Str_to_gname(str2,t);
      t = Norm_step_gname(t);
      top = Push_reprule(top,r,t,j);
      j++;
    }
  }
  return top;
  fclose(fl);
}


struct reprule* Delete_reprule_pos(struct reprule *top, int pos)
{
  int size = Size_reprule(top);
  if(pos > size) pos = size;

  if(pos == 1)
  {
    struct reprule *m = top;
    top = m->next;
    free(m);
    return top;
  }
  else if(pos == size)
  {
    struct reprule *m = top;
    while(m->next != NULL) m = m->next;
    m->prev->next = NULL;
    free(m);
    return top;
  }
  else
  {
    struct reprule *m = top;
    for(int i = 1;i < pos;i++) m = m->next;
    m->prev->next = m->next;
    m->next->prev = m->prev;
    free(m);
    return top;
  }
}

struct reprule* Find_include_rep(struct reprule *top, struct gname *obj)
{
  while(top!=NULL)
  {
    int t;
    t = Include_str(obj,top->rep);
    if(t != 0) return top;
    top = top->next;
  }
  return NULL;
}


int Ravn_gname(struct gname *top1, struct gname *top2, struct reprule *rule)
{
  struct gname *res = NULL;
  if(top1->obr == 'e') top1 = NULL;
  if(top2->obr == 'e') top2 = NULL;
  int size1 = Size_gname(top1);
  int size2 = Size_gname(top2);
  for(int i = 1;i<=size1;i++)
  {
    res = Push_gname(res,top1->obr,top1->step,i);
    top1 = top1->next;
  }
  top2 = Gotopos_gname(top2,size2);
  int i = 1;
  while(top2 != NULL)
  {
    int step = (top2->step);
    step *= -1;
    res = Push_gname(res,top2->obr,step,size1+i);
    top2 = top2->prev;
    i++;
  }
//  printf("\n");
//    Print_gname(res);
  res = Norm_step_gname(res);
//printf("\n");
//  Print_gname(res);

  struct reprule *incl = Find_include_rep(rule,res);
  struct reprule *last_incl = NULL;
  int last_pos = 0;
  int j = 0;
  while(res != NULL && incl != NULL && j < 100)
  {
    int p = Include_str(res,incl->rep);
    if(last_incl != NULL)
    {
      if(p == last_pos && Ravn_gname(last_incl->rep,incl->to,NULL)) break;
    }
    /*printf("REP: ");
    Print_gname(incl->rep);
    printf("TO: ");
    Print_gname(incl->to);
    printf("POS: %d\n",p);*/
    res = Replace_gname(res,incl->rep,incl->to,p);
  //  printf("1");
  //  Print_gname(res);
    res = Norm_step_gname(res);
//    printf("2");
//    Print_gname(res);
    if(last_incl != NULL) last_incl = Delete_reprule_pos(last_incl,1);
    last_incl = Push_reprule(last_incl,incl->rep,incl->to,1);
    last_pos = p;
    incl = Find_include_rep(rule,res);
    j++;
  }
  //Print_gname(res);
  if(res == NULL || res->obr == 'e') return 1;
  else return 0;
}

struct reprule *Generate_reprule(struct reprule *inp_rep)
{
  struct reprule *new_rep = NULL;
  int npos = 1;
  while(inp_rep != NULL)
  {
    struct gname *rep = inp_rep->rep;
    struct gname *to = inp_rep->to;
    struct gname *res1 = NULL;
    struct gname *res2 =  NULL;
    int pos = 1;
    while(rep != NULL)
    {
      res1 = Push_gname(res1,rep->obr,rep->step,pos);
      rep = rep->next;
      pos++;
    }
    to = Gotopos_gname(to,Size_gname(to));
    while(to != NULL && to->obr != 'e')
    {
      res1 = Push_gname(res1,to->obr,to->step*(-1),pos);
      to = to->prev;
      pos++;
    }
    res1 = Norm_step_gname(res1);
    res2 = NULL;
    pos = 1;
    if(res1 != NULL)
    {
      struct gname *c_res2 = Copy_gname(res2);
      if(c_res2 == NULL)
      {
        c_res2 = Push_gname(c_res2,'e',1,1);
      }
      int s1 = Size_gname(res1);
      int s2 = Size_gname(c_res2);
      if(!(s1 == 1 && s2 == 1 && res1->step > 0 && c_res2->step < 0))
      {
        new_rep = Push_reprule(new_rep,res1,c_res2,npos);
        npos++;
      }
    }
    if(res2 != NULL)
    {
      struct gname *c_res1 = Copy_gname(res1);
      if(c_res1 == NULL)
      {
        c_res1 = Push_gname(c_res1,'e',1,1);
      }
      int s1 = Size_gname(c_res1);
      int s2 = Size_gname(res2);
      if(!(s1 == 1 && s2 == 1 && res2->step > 0 && c_res1->step < 0))
      {
        new_rep = Push_reprule(new_rep,res2,c_res1,pos);
        npos++;
      }
    }
    while(res1 != NULL)
    {
      res1 = Copy_gname(res1);
      res2 = Copy_gname(res2);
      int size2 = Size_gname(res2);
      rep = Gotopos_gname(res1,Size_gname(res1));
      int zn = 1;
      if(rep->step < 0) zn = -1;
      rep->step -= zn;
      res2 = Push_gname(res2,rep->obr,zn*(-1),size2+1);
      res1 = Norm_step_gname(res1);
      res2 = Norm_step_gname(res2);
      if(res1 != NULL)
      {
        struct gname *c_res2 = Copy_gname(res2);
        if(c_res2 == NULL)
        {
          c_res2 = Push_gname(c_res2,'e',1,1);
        }
        int s1 = Size_gname(res1);
        int s2 = Size_gname(c_res2);
        if(!(s1 == 1 && s2 == 1 && res1->step > 0 && c_res2->step < 0))
        {
          new_rep = Push_reprule(new_rep,res1,c_res2,npos);
          npos++;
        }
      }
      if(res2 != NULL)
      {
       struct gname *c_res1 = Copy_gname(res1);
        if(c_res1 == NULL)
        {
          c_res1 = Push_gname(c_res1,'e',1,1);
        }
        int s1 = Size_gname(c_res1);
        int s2 = Size_gname(res2);
        if(!(s1 == 1 && s2 == 1 && res2->step > 0 && c_res1->step < 0))
        {
          new_rep = Push_reprule(new_rep,res2,c_res1,pos);
          npos++;
        }
      }
    }
    inp_rep = inp_rep->next;
  }
  return new_rep;
}


struct reprule* Sort_rep(struct reprule *top)
{
  if(top != NULL)
  {
    int size = Size_reprule(top);
    for(int i = 0;i<size;i++)
    {
      struct reprule *m = top;
      while(m->next != NULL)
      {
        if(Size_gname(m->to) > Size_gname(m->next->to))
        {
          struct gname *r1 = m->rep;
          struct gname *r2 = m->to;
          m->rep = m->next->rep;
          m->to = m->next->to;
          m->next->rep = r1;
          m->next->to = r2;
        }
        if(Size_gname(m->to) == Size_gname(m->next->to))
        {
          if(Size_gname(m->rep) < Size_gname(m->next->rep))
          {
            struct gname *r1 = m->rep;
            struct gname *r2 = m->to;
            m->rep = m->next->rep;
            m->to = m->next->to;
            m->next->rep = r1;
            m->next->to = r2;
          }
        }
        m = m->next;
      }
    }
  }
  return top;
}
