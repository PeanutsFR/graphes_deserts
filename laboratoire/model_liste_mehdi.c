#include<stdio.h>
#include<stdlib.h>
#include "structure.h"

/*
 --- Structures ---

typedef struct chainon
{
    sommet st;
    struct chainon *suivant;
} Couple;

typedef Couple *liste;

typedef struct
{
    liste a[n_max];
    int n;
} graphe_l;

graphe_l gl;

*/


int presence_arrete_l(graphe_l *g,sommet x,sommet y)
{
    liste cour = g->a[x];
    while ((cour != NULL) && (cour->st != y))
    {
      cour = cour->suivant;
    }
    return (cour != NULL);
}


int verification_l(graphe_l *g,liste *l)
{

    liste curseur1,curseur2,memoire_curseur1;
    curseur1=*l;             //on pointe sur la tete de liste
    if(curseur1->suivant)    // si elle contient plus d'un élément
    {
        while(curseur1 && curseur1->suivant)      //on doit verifier que chaque sommet n'a pas d'arc entre eux
        {
            curseur2=curseur1->suivant;
            while(curseur2 && !presence_arrete_l(g,curseur1->st,curseur2->st) )
            {
                curseur2=curseur2->suivant;
            }
            memoire_curseur1=curseur1;  // memoire_curseur pointe sur position-2
            curseur1=curseur1->suivant; // en fin de boucle curseur1 pointera sur position-1
        }

        return presence_arrete_l(g,memoire_curseur1->st,memoire_curseur1->suivant->st);
    }
    else return 0;
}
