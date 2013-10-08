#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "gestion_listes.h"


void initialiser_matrice(graphe_m *g)
{
    int i,j;
    for(i=0;i<g->n;i++)
    {
        for(j=0;j<g->n;j++)
        {
            g->a[i][j]=0;
        }
    }
}


void ajouter_arete_m(graphe_m *g, sommet x, sommet y)
{
    g->a[x][y]=1;
    g->a[y][x]=1;
}

void afficher_matrice(graphe_m *g)
{

    int i,j;
    printf("   ");
    for(i=0;i<g->n;i++)
    {
        printf(" %d ",i);
    }
    printf("\n");
    for(i=0;i<g->n;i++)
    {
        printf(" %d ",i);
        for(j=0;j<g->n;j++)
        {
            printf(" %d ",g->a[i][j]);
        }
        printf("\n");
    }
}

/**********************************************************************************/
/*                                                                                */
/* fonction qui retourne la valeur presente dans la matrice carré                 */
/* retourne 1 si presence arrete  0 sinon                                         */
/*                                                                                */
/**********************************************************************************/

int presence_arrete_m(graphe_m *g,sommet x,sommet y)
{
    return g->a[x][y];
}


int verification_m(graphe_m *g,liste *l)
{

    liste curseur1,curseur2,memoire_curseur1;
    curseur1=*l;             //on pointe sur la tete de liste
    if(curseur1->suivant)    // si elle contient plus d'un élément
    {
        while(curseur1 && curseur1->suivant)      //on doit verifier que chaque sommet n'a pas d'arc entre eux
        {
            curseur2=curseur1->suivant;
            while(curseur2 && !presence_arrete_m(g,curseur1->st,curseur2->st) )
            {
                curseur2=curseur2->suivant;
            }
            memoire_curseur1=curseur1;  // memoire_curseur pointe sur position-2
            curseur1=curseur1->suivant; // en fin de boucle curseur1 pointera sur position-1
        }

        return presence_arrete_m(g,memoire_curseur1->st,memoire_curseur1->suivant->st);
    }
    else return 0;
}
