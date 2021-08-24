#ifndef _GNAME_
#define _GNAME_

struct gname{
  struct gname *next;
  struct gname *prev;
  char obr;
  int step;
};

struct gname* Create_gname(struct gname *top);
struct gname* Push_gname(struct gname *top, char data, int step, int pos);
int Size_gname(struct gname *top);
void Print_gname(struct gname *top);
struct gname* Str_to_gname(char *sobr, struct gname *top);
struct gname* Norm_step_gname(struct gname *top);
struct gname* Delete_gname_pos(struct gname *top, int pos);
struct gname* Gotopos_gname(struct gname *top,int pos);
int Include_str(struct gname *top1,struct gname *top2);
struct gname* Replace_gname(struct gname *top,struct gname *rep, struct gname *to,int pos);
int Include_str_legacy(struct gname *top1,struct gname *top2);
struct gname* Copy_gname(struct gname *top);
int RaznZnak(int one,int two);
#endif
