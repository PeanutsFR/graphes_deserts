#include<stdio.h>
#include<stdlib.h>
#include "structure.h"



/*************************************************************************************/
/*                                                                                   */
/* fonction qui prend en argument un entier et une liste                             */
/* fait un malloc pour creer un chainon et l'ajoute a liste                          */
/*                                                                                   */
/*************************************************************************************/

void ajouter_arete_l(liste *l,int somet)
{
    liste tmp,memoire;
    liste element=(struct chainon *) malloc(sizeof(Couple) );
    memoire=NULL;

    if(!element) //on test si le malloc a reussi
    {
        printf("malloc echoué pour l'ajout d'un sommet \n");
        exit(EXIT_FAILURE);
    }
    else
    {
        element->st=somet;
        element->suivant=NULL;
    }

    if(!*l)// cas ou la liste est vide l'element créé devient la tete
    {
        *l=element;
    }
    else
    {
        tmp=*l;
        while(tmp->suivant && somet>=tmp->st) // on parcourt la liste jusqu'a l'avant dernier element
        {
            memoire=tmp;
            tmp=tmp->suivant;
        }
        if(somet<tmp->st)
        {
            if(tmp==*l)
            {
                element->suivant=tmp;
                *l=element;
            }
            else
            {
                element->suivant=tmp;
                memoire->suivant=element;
            }
        }
        else
        {
            if(!tmp->suivant)
                tmp->suivant=element; // on fait pointer le dernier element sur l'élement créé
        }
    }
}

/***************************************************************************************/
/*                                                                                     */
/* parcours une liste a la recherche d'un sommet pour le supprimer                     */
/*                                                                                     */
/***************************************************************************************/

void supprimer_arete_l(liste *l , int somet)
{

    liste tmp,memoire;

    if((*l)->st==somet) // si le sommet a supprimer est en tete de liste
    {
        tmp=*l;
        *l=(*l)->suivant;
    }
    else
    {
        tmp=*l;
        while(tmp && tmp->st!=somet) // sinon on parcours la liste a la recherche de l'élement
        {
            memoire=tmp;
            tmp=tmp->suivant;
        }
        if(tmp) //si on a trouvé un chainon qui correspond a sommet 
        {
            memoire->suivant=tmp->suivant; //on chaine le precedent de tmp avec le suivant de tmp
            free(tmp); // on libere tmp
        }
    }
}


void afficher_liste(liste *l)
{

    liste tmp;

    tmp=*l;

    while(tmp)
    {
        printf("->%d",tmp->st);
        tmp=tmp->suivant;
    }
    printf("->NULL\n");

}
