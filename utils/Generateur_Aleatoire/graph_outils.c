#include "graph_outils.h"
#include <stdio.h>
#include <stdlib.h>
#include "generation.h"


void Gen_Alea_graph (graph * g, int N, int C, long *Seed)
{
  int PossibleCTs;       /* CT means "constraint" */
  unsigned long *CTarray;
  long selectedCT;
  int i,j, c,r,x,y;
  int var1, var2;
  static int instance;
  chain_list p;


  /* Check for valid values of N, D, C, and T. */
  if (N < 2)
    {
      printf("Gen_Alea_graph: ***Illegal value for N: %d\n", N);
      return;
    }
  if (C < 0 || C > N * (N - 1) / 2)
    {
      printf("MakeURBCSP: ***Illegal value for C: %d\n", C);
      return;
    }

  if (*Seed < 0)      /* starting a new sequence of random numbers */
    instance = 0;
  else
    ++instance;       /* increment static variable */

  /* initialise le graph */
  g->nb_sommets = N;
  
  /* creation de la liste et de la matrice d'adjacence */
  
  g->list_voisins = (chain_list *) malloc (sizeof(chain_list) * N);
  g->mat_voisins = (int **) malloc (sizeof(int *) * N);
  
  for (i = 0; i < N; i++)
  {
    g->list_voisins[i] = NULL;
    g->mat_voisins[i] = (int *) malloc (sizeof(int) * N);
    for (j = 0; j < N; j++)
      g->mat_voisins[i][j] = 0;
  }



  /* The program has to choose randomly and uniformly m values from
     n possibilities.  It uses the following logic for both constraints
     and nogood value pairs:
           1. Let t[] be an array of the n possibilities
	   2. for i = 0 to m-1
	   3.    r = random(i, n-1)    ; random() returns an int in [i,n-1]
	   4.    swap t[i] and t[r]
	   5. end-for
     At the end of the for loop, the elements from t[0] to t[m-1] are
     the m randomly selected elements.
   */

  /* Create an array for each possible binary constraint. */
  PossibleCTs = N * (N - 1) / 2;
  CTarray = (unsigned long*) malloc(PossibleCTs * sizeof(unsigned long));


  /* Initialize the CTarray.  Each entry has one var in the high two
     bytes, and the other in the low two bytes. */
  i=0;
  for (var1=0; var1<(N-1); ++var1)
    for (var2=var1+1; var2<N; ++var2)
      CTarray[i++] = (var1 << 16) | var2;

  /* Select C constraints. */
  for (c=0; c<C; ++c)
  {
    /* Choose a random number between c and PossibleCTs - 1, inclusive. */
    r =  c + (int) (ran2(Seed) * (PossibleCTs - c)); 

    /* Swap elements [c] and [r]. */
    selectedCT = CTarray[r];
    CTarray[r] = CTarray[c];
    CTarray[c] = selectedCT;

    /* Broadcast the constraint. */
    x = (int)(CTarray[c] >> 16); 
    y = (int)(CTarray[c] & 0x0000FFFF);
      
    p = (chain_list) malloc (sizeof(maillon));
    p->info = x;
    p->suiv = g->list_voisins[y];
    g->list_voisins[y] = p;
    g->mat_voisins[y][x]=1;

    p = (chain_list) malloc (sizeof(maillon));
    p->info = y;
    p->suiv = g->list_voisins[x];
    g->list_voisins[x] = p;
    g->mat_voisins[x][y]=1;
  }
   
  free(CTarray);
}



void Aff_graph (graph g)
/* affiche le graphe g */
{  
  int i,j;
  chain_list p;
  
  /* affichage du nombre de sommets */
  
  printf ("Nombre de sommets : %d\n",g.nb_sommets);
  
  
  /* affichage de la liste d'adjacence */
  
  for (i = 0; i < g.nb_sommets; i++)
  {
    printf ("voisin de %4d : ",i+1);

    p = g.list_voisins[i];
    while (p != NULL)
    {
      printf ("%4d ",p->info+1);
      p = p->suiv;
    }
    printf ("\n");
  }
  
  
  /* affichage de la matrice d'adjacence */
  
  printf ("\nMatrice :\n   ");
  for (i = 0; i < g.nb_sommets; i++)
    printf ("  x%d ",i+1);
  printf ("\n");
    
  for (i = 0; i < g.nb_sommets; i++)
  {
    printf ("\nx%d ",i+1);
    for (j = 0; j < g.nb_sommets; j++)
      printf("%4d ",g.mat_voisins[i][j]);
  }
  
  printf ("\n");
}


void Sauve_graph (graph g, char nom[]) /* sauvegarde du graphe g */
{  
  int i,j,m;
  FILE * f;
  
  f = fopen (nom,"w");
  
  /* sauvegarde du nombre de sommets */ 
  m = 0;
  for (i = 0; i < g.nb_sommets; i++)
    for (j = i+1; j < g.nb_sommets; j++)
      m += g.mat_voisins[i][j];
  
  fprintf (f,"%d %d\n",g.nb_sommets,m);
  
  
  /* sauvergarde des paires d'aretes */
  
  for (i = 0; i < g.nb_sommets; i++)
    for (j = i+1; j < g.nb_sommets; j++)
      if (g.mat_voisins[i][j])
        fprintf (f,"%d %d\n",i,j);
  fclose (f);
}


void Free_graph (graph * g)
/* libere l'espace memoire alloue pour le graphe g */
{
  int i;
  chain_list p,q;
  
  for (i = 0; i < g->nb_sommets; i++)
  {
    p = g->list_voisins[i];
    while (p != NULL)
    {
      q = p;
      p = p->suiv;
      free (q);
    }
    free (g->mat_voisins[i]);
  }
  free (g->mat_voisins);
  free (g->list_voisins);
}
