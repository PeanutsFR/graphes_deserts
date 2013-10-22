#include<stdio.h>
#include<stdlib.h>
#include "couleur.h"
#include "structure.h"
#include "gestion_listes.h"


/***************************************************************************************************/
/*                                                                                                 */
/* fonction qui prend en entrée un graphe avec liste d'adjacence , un sommet x et un sommet y      */
/* se place sur la liste de voisins de x                                                           */
/* et test si chaque sommet de la liste est y                                                      */
/* retourne 1 si y est present dans la liste 0 sinon                                               */
/* complexite  en O( d+(x) )                                                                       */
/*                                                                                                 */
/***************************************************************************************************/

int presence_arrete_l(graphe_l *g, sommet x , sommet y)
{

    liste tmp;
    tmp=g->a[x];
    while(tmp && tmp->st!=y)
    {
        tmp=tmp->suivant;
    }
    if(tmp)
        return 1;
    else
        return 0;
}

/***************************************************************************************************/
/*                                                                                                 */
/* fonction qui prend en entrée un graphe avec liste d'adjacence et un ensemble de sommet          */
/* et qui va test si chaque sommet de l'ensemble n'est pas voisins des autres sommet de l'ensemble */
/* retourne 1 si un sommet est voisin d'un autre , 0 sinon                                         */
/* complexite  :                                                                                   */
/*                                                                                                 */
/***************************************************************************************************/

int verification_l(graphe_l  *g , Ensemble *l)
{
    Ensemble curseur1,curseur2;
    curseur1=*l;             //on pointe sur la tete de liste 
    if(curseur1->suivant)    // si elle contient plus d'un élément
    {
        curseur2=NULL;
        while(curseur1 && !curseur2 )      //on doit verifier que chaque sommet n'a pas d'arc entre eux
        {
            curseur2=curseur1->suivant;   // on pointe l'element aprés curseur1
            while(curseur2 && !presence_arrete_l(g,curseur1->st,curseur2->st) ) // on verifie que cet element n'est pas voisin de curseur1
            {
                curseur2=curseur2->suivant; // on pointe sur l'element qui suit
            }
            curseur1=curseur1->suivant; // en fin de boucle curseur1 pointera sur position-1
        }

        return curseur1==NULL; // si le curseur1 a parcouru toute tout l'ensemble le sous graphe est desert
    }
    else return 1;
}


Ensemble calcul_maximal(graphe_l *g, int x)
{


    Ensemble tete_liste;

    tete_liste=NULL;

    ajouter_element_ensemble(&tete_liste,x);

    int i;
    int tab[n_max]={0};
    for(i=0;i<g->n;i++) //tableau de marquage initialiser a 0
    {
        tab[i]=0;
    }
    tab[x]=1;

    for(i=0;i<g->n;i++)
    {
        if(i!=x && !tab[i])
        {
            ajouter_element_queue(&tete_liste,i); // ajoue le sommet a l'ensemble
            tab[i]=1;
            if( !verification_l(g,&tete_liste) )
            {
                tab[i]=0;
                supprimer_queue_ensemble(&tete_liste);
            }
        }
    }

    return tete_liste;
}


