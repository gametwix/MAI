#ifndef _REPRULE_
#define _REPRLE_

struct reprule{
  struct reprule *next;
  struct reprule *prev;
  struct gname *rep;
  struct gname *to;
};

struct reprule* Create_reprule(struct reprule *top);
struct reprule* Push_reprule(struct reprule *top, struct gname *rep, struct gname *to, int pos);
int Size_reprule(struct reprule *top);
void Print_reprule(struct reprule *top);
struct reprule* Readfile_reprule(struct reprule *top);
struct reprule* Delete_reprule_pos(struct reprule *top, int pos);
struct reprule* Find_include_rep(struct reprule *top, struct gname *obj);
int Ravn_gname(struct gname *top1, struct gname *top2, struct reprule *rule);
struct reprule *Generate_reprule(struct reprule *inp_rep);
struct reprule* Sort_rep(struct reprule *top);
#endif
