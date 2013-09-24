#include <stdlib.h>
#include <stdio.h>
#include "generation.h" 
#include "graph_outils.h"

int main(int argc, char ** argv)
{
  char nom_fic [100];
  int i;
  int N,M,I;
  long S;
  graph g;

  if (argc != 4) {printf ("%s N M I\n",argv[0]); exit (1);}
  
  N = atoi (argv[1]); 
  M = atoi (argv[2]);
  I = atoi (argv[3]);
  
  S = -10;

  for (i = 0 ; i < I; i++)
  {
    sprintf (nom_fic,"graph_%d_%d_%d",N,M,i);

    Gen_Alea_graph (&g,N,M,&S);

    Sauve_graph (g,nom_fic);
    
    Free_graph (&g);
  }
  
  return (1);
}
