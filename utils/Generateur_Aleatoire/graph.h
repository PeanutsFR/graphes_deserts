#ifndef GRAPH__H
#define GRAPH__H

/******************************************/
/* structures de donnees pour les graphes */
/******************************************/

struct Maillon
{
  int info;
  struct Maillon * suiv;
};

typedef struct Maillon maillon, * chain_list;

struct Graph
{
  int nb_sommets;            /* nombre de sommets du graphe                                          */
  chain_list * list_voisins; /* ensembles des sommets voisins de chaque sommet (liste d'adjacence)   */
  int ** mat_voisins;        /* ensembles des sommets voisins de chaque sommet (matrice d'adjacence) */
};

typedef struct Graph graph;

#endif
