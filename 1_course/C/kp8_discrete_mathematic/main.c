#include <stdio.h>
#include <stdlib.h>
#include "rname.h"
#include "replace.h"
#include "elgroup.h"

int main()
{



  struct reprule *rep = NULL;
  rep = Readfile_reprule(rep);
//  Print_reprule(rep);
  rep = Generate_reprule(rep);
  Print_reprule(rep);
  rep = Sort_rep(rep);
  Print_reprule(rep);

  struct elgroup *obr = NULL;
  obr = Readfile_obraz(obr);
//  Print_elgroup(obr);
  struct elgroup *elgr = NULL;
  elgr = Find_new_elem(elgr,obr,NULL,rep,1);

  Print_elgroup(elgr);


  int sizeg = Size_elgroup(elgr);
  int **mat = (int **)malloc(sizeg*sizeof(int *));
  for(int i = 0; i < sizeg; i++)
  {
    mat[i] = (int *)malloc(sizeg*sizeof(int));
  }

  for(int i = 1;i<=sizeg;i++)
  {
    struct elgroup *l1 = Gotopos_elgroup(elgr,i);
    struct gname *l1g = l1->data;
    for(int j =1;j<=sizeg;j++)
    {
      struct elgroup *l2 = Gotopos_elgroup(elgr,j);
      struct gname *l2g = Copy_gname(l2->data);
      l1g = Copy_gname(l1->data);
      int flag = 0;
      struct elgroup *ob = obr;
      while(ob != NULL)
      {
        l1g = Copy_gname(l1->data);
        if(l1g->obr == 'e') l1g = NULL;
        l1g = Push_gname(l1g,ob->data->obr,ob->data->step,Size_gname(l1g)+1);
        l1g = Norm_step_gname(l1g);
        if(Ravn_gname(l1g,l2g,rep)) flag =1;
        ob = ob->next;
        //printf("\n");
        //Print_gname(l1g);
      //  Print_gname(l2g);
    //    printf("%d\n",flag);
      }
      mat[i-1][j-1] = flag;
    }
  }
  FILE *fl;
  fl = fopen("result","w");
  for(int i=0;i<sizeg;i++)
  {
    for(int j=0;j<sizeg;j++)
    {
      fprintf(fl,"%d ",mat[i][j]);
    }
    fprintf(fl,"\n");
  }
  fclose(fl);
//  Print_elgroup(elgr);
//  printf("\n\n%d\n",Exist_ravn_elem(elgr,top1,rep));
for(int i=0;i<sizeg;i++)
{
  for(int j=0;j<sizeg;j++)
  {
    printf("%d ",mat[i][j]);
  }
  printf("\n");
}
  return 0;
}
