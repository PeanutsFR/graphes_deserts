#ifndef TRIANG_OUTILS__H
#define TRIANG_OUTILS__H

#include "graph.h"


void Gen_Alea_graph (graph * g, int n, int m, long *Seed);
/* permet de generer aleatoirement un graphe g avec n sommets et m aretes */

void Aff_graph (graph g);               /* affiche le graphe g                                             */

int nb_compo_connexe_graph (graph g);   /* calcule le nombre de composantes connexes de g                  */


void Free_graph (graph * g);            /* libere l'espace memoire alloue pour le graphe g                 */

void Sauve_graph (graph g, char nom[]); /* sauvegarde du graphe g */
#endif
