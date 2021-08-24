#ifndef _EGR_
#define _EGR_

struct elgroup{
  struct elgroup *next;
  struct elgroup *prev;
  struct gname *data;
};

struct elgroup* Create_obr(struct elgroup* top);
struct elgroup* Create_ver(struct elgroup* top);
struct elgroup* Push_obr(struct elgroup *top, struct gname *obr, int pos);
int Size_elgroup(struct elgroup *top);
struct elgroup* Readfile_obraz(struct elgroup *top);
void Print_elgroup(struct elgroup *top);
struct elgroup* Push_elgr(struct elgroup *top, struct gname *data, int pos);
int Exist_ravn_elem(struct elgroup *top,struct gname *gn,struct reprule *rule);
struct elgroup *Find_new_elem(struct elgroup *top,struct elgroup *obr,struct gname *gn,struct reprule *rule, int n);
struct elgroup* Gotopos_elgroup(struct elgroup *top,int pos);
#endif
