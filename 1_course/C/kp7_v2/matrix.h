#ifndef _MATRIX_
#define _MATRIX_

struct list{
  struct list *next;
  double data;
};

struct matrix{
  struct list *index;
  struct list *data;
  int m;
  int n;
};

struct list* create_list(struct list *root);
struct list* push_list(struct list* root, int pos, double data);
int size_list(struct list* root);
double peek_list(struct list* root, int pos);
struct list* delete_list(struct list* root, int pos);
double pop_list(struct list** root, int pos);
void print_list(struct list* root);

struct matrix* create_matrix(struct matrix* matr,int n,int m);
struct matrix* push_matrix(struct matrix* matr, int i,int j,double data);
void print_matr_mach(struct matrix* matr);
float znach_cord(struct matrix* matr,int i,int j);
void print_matr_standart(struct matrix* matr);
struct matrix* sum_matrix(struct matrix* am,struct matrix* bm,struct matrix* cm);
int simmetr_matr(struct matrix* cm);
#endif
