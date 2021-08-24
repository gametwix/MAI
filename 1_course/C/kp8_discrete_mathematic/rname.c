#include <stdio.h>
#include <stdlib.h>
#include "rname.h"
#include "replace.h"

struct gname* Create_gname(struct gname *top)
{
  if(top == NULL)
  {
    top=malloc(sizeof(struct gname));
    top->next = NULL;
    top->prev = NULL;
    return top;
  }
}

struct gname* Push_gname(struct gname *top, char data, int step, int pos)
{
  if(top == NULL)
  {
    top = Create_gname(top);
    top->obr = data;
    top->step = step;
    return top;
  }
  else
  {
    int size = Size_gname(top);
    if(pos > size)
    {
      struct gname *m = top;
      while(m->next != NULL) m=m->next;
      struct gname *q;
      q = malloc(sizeof(struct gname));
      q->prev = m;
      q->next  = NULL;
      q->obr = data;
      q->step = step;
      m->next = q;
      return top;
    }
    else if(pos == 1)
    {
      struct gname *q;
      q = malloc(sizeof(struct gname));
      q->prev = NULL;
      q->next = top;
      top->prev = q;
      q->obr = data;
      q->step = step;
      top = q;
      return top;
    }
    else
    {
      struct gname *m = top;
      for(int i = 2;i < pos;i++)
      {
        m=m->next;
      }
      struct gname *q;
      q = malloc(sizeof(struct gname));
      q->obr = data;
      q->step = step;
      q->prev = m;
      q->next = m->next;
      m->next->prev = q;
      m->next = q;
      return top;
    }
  }
}

int Size_gname(struct gname *top)
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

void Print_gname(struct gname *top)
{
  while(top != NULL)
  {
    printf("%c",top->obr);
    if(top->step != 1)
    {
      printf("^%d",top->step);
    }
    top = top->next;
  }
  printf("\n");
}

struct gname* Str_to_gname(char *sobr, struct gname *top)
{
  int i=0;
  int j=1;
  while(sobr[i] != '\0' && (int)sobr[i] != 10)
  {
    char obr = sobr[i];
    int step = 1;
    int m = 0;
    i++;
    if(sobr[i]=='^')
    {
      i++;
      if(sobr[i]=='-')
      {
        m = 1;
        i++;
      }
      if((int)sobr[i] >= 48 && (int)sobr[i] <= 57) step = 0;
      while((int)sobr[i] >= 48 && (int)sobr[i] <= 57)
      {
        step*=10;
        step+=(int)sobr[i] - 48;
        i++;
      }
    }
    if(m == 1) step*=-1;
    top = Push_gname(top,obr,step,j);
    j++;
  }
  return top;
}

struct gname* Norm_step_gname(struct gname *top)
{
  if(top != NULL)
  {
    struct gname *m = top;
    int pos = 1;
    while(m->next != NULL)
    {
      if(m->obr == m->next->obr)
      {
        m->step += m->next->step;
        top = Delete_gname_pos(top,pos+1);
        if(m->step == 0)
        {
          m = m->prev;
          top = Delete_gname_pos(top,pos);
          pos--;
          if(m == NULL) break;
        }
      }
      else
      {
        pos++;
        m = m->next;
      }
    }
    pos = 1;
    m = top;
    while(m != NULL)
    {
      if(m->step == 0)
      {
        m = m->next;
        top = Delete_gname_pos(top,pos);
        continue;
      }
      pos++;
      m = m->next;
    }
  }
  return top;
}


struct gname* Delete_gname_pos(struct gname *top, int pos)
{
  int size = Size_gname(top);
  if(pos > size) pos = size;

  if(pos == 1)
  {
    struct gname *m = top;
    top = m->next;
    free(m);
    return top;
  }
  else if(pos == size)
  {
    struct gname *m = top;
    while(m->next != NULL) m = m->next;
    m->prev->next = NULL;
    free(m);
    return top;
  }
  else
  {
    struct gname *m = top;
    for(int i = 1;i < pos;i++) m = m->next;
    m->prev->next = m->next;
    m->next->prev = m->prev;
    free(m);
    return top;
  }
}

struct gname* Gotopos_gname(struct gname *top,int pos)
{
  int size = Size_gname(top);
  if(size < pos) pos = size;
  for(int i = 1;i < pos;i++)
  {
    top = top->next;
  }
  return top;
}

int Include_str_legacy(struct gname *top1,struct gname *top2)
{
  if(top1 != NULL && top2 != NULL)
  {
    int pos = 1;
    struct gname *m1 = top1;
    struct gname *m2 = top2;
    int size1 = Size_gname(m1);
    int size2 = Size_gname(m2);
    while(m1->next != NULL)
    {
      m1 = Gotopos_gname(top1,pos);
      m2 = Gotopos_gname(top2,1);
      size1 = Size_gname(m1);
      size2 = Size_gname(m2);
      if(size1 < size2) break;
      if(size2 == 1 && m1->obr == m2->obr && m1->step != m2->step && ((m1->step > 0 && m2->step < 0) || (m1->step < 0 && m2->step > 0) || (m1->step > 0 && m2->step > 0 && m1->step < m2->step) || (m1->step < 0 && m2->step < 0 && m1->step > m2->step)) )
      {
        //printf("stop\n");
        pos++;
        continue;
      }
      if(m1->obr == m2->obr)
      {
        int flag = 1;
        if(size2 > 1)
        {
          m1 = m1->next;
          m2 = m2->next;
          for(int i = 2;i < size2;i++)
          {
            if((m1->obr != m2->obr) || (m1->step != m2->step)) flag = 0;
            m1 = m1->next;
            m2 = m2->next;
          }
          if(m1->obr != m2->obr) flag = 0;
        }
        if(flag == 1) return pos;
      }
      pos++;
    }
    if((size1 == 1 && size2 == 1 && m1->obr == m2->obr) && !((m1->step > 0 && m2->step > 0 && m1->step > m2->step) || (m1->step < 0 && m2->step < 0 && m1->step < m2->step)))
    {
      return 1;
    }
  }
  return 0;
}

struct gname* Replace_gname(struct gname *top,struct gname *rep, struct gname *to,int pos)
{
  int sizer = Size_gname(rep);
  struct gname *m = NULL;
  struct gname *c = NULL;
  for(int i = 0; i < sizer-1;i++)
  {
    m = Gotopos_gname(top,(pos+sizer-1-i));
    c = Gotopos_gname(rep,(sizer-i));
    m->step-=c->step;
    top = Norm_step_gname(top);
  }
  int flag = 0;
  m = Gotopos_gname(top,pos);
  c = rep;
  m->step-=c->step;
  if(m->step == 0) flag = 0;
  else flag = 1;
  top = Norm_step_gname(top);
  if(to->obr == 'e') return top;
  sizer = Size_gname(to);

  for(int i = 0; i < sizer; i++)
  {
    c = Gotopos_gname(to,i+1);
    top = Push_gname(top,c->obr,c->step,pos+i+flag);
    //Print_gname(top);
  }

  return top;
}


int Include_str(struct gname *top1,struct gname *top2)
{
  int posi = 0;
  int pos = 1;
  struct gname *m1 = top1;
  struct gname *m2 = top2;
  int size1 = Size_gname(top1);
  int size2 = Size_gname(top2);
  while(top1 != NULL && size1 >= size2)
  {
    if(top1->obr == top2->obr && top1->step == top2->step && size2 == 1)
    {
      posi = pos;
      break;
    }
    else if(size2 == 1 && top1->obr == top2->obr && top1->step > 0 && top2->step > 0 && top1->step > top2->step)
    {
      posi = pos;
      break;
    }
    else if(size2 == 1 && top1->obr == top2->obr && top1->step < 0 && top2->step < 0 && top1->step < top2->step)
    {
      posi = pos;
      break;
    }
    else if(size2 == 1 && top1->obr == top2->obr)
    {
      pos++;
      top1 = top1->next;
      size1 = Size_gname(top1);
      continue;
    }
    else
    {
      if(top1->obr == top2->obr)
      {
        m1 = top1;
        m2 = top2;
        int flag = 1;
        m1 = m1->next;
        m2 = m2->next;
        for(int i = 2;i < size2;i++)
        {
          if((m1->obr != m2->obr) || (m1->step != m2->step)) flag = 0;
          m1 = m1->next;
          m2 = m2->next;
        }
        if(m1->obr != m2->obr) flag = 0;
        if(size2 == 2 && RaznZnak(m1->step,m2->step) && RaznZnak(m1->prev->step,m2->prev->step))
        if(flag == 1)
        {
          posi = pos;
          break;
        }
      }
      pos++;
      top1 = top1->next;
      size1 = Size_gname(top1);
    }
  }
  return posi;
}

struct gname* Copy_gname(struct gname *top)
{
  struct gname *copy = NULL;
  int pos = 1;
  while(top != NULL)
  {
    copy = Push_gname(copy,top->obr,top->step,pos);
    pos++;
    top = top->next;
  }
  return copy;
}

int RaznZnak(int one,int two)
{
  if(one > 0 && two < 0) return 1;
  else if(one < 0 && two > 0) return 1;
  else return 0;
}
