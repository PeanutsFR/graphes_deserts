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
        while(tmp->suivant && somet>tmp->st) // on parcourt la liste jusqu'a l'avant dernier element
        {
            memoire=tmp;
            tmp=tmp->suivant;
        }
        if(somet!=tmp->st)
        {
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
            tmp=NULL;
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


void supprimer_liste(liste *l)
{
    liste tmp,tmp2;

    tmp=*l;
    tmp2=tmp;
    while(tmp)
    {
        tmp2=tmp->suivant;
        free(tmp);
        tmp=tmp2;
    }
    *l=NULL;
}

void afficher_ensemble(Ensemble  *l)
{

    Ensemble tmp;

    tmp=*l;

    while(tmp)
    {
        //   printf("->(%p,%d:<-%p,%p->)",tmp,tmp->st,tmp->precedent,tmp->suivant);
        printf("->%d",tmp->st);
        tmp=tmp->suivant;
    }
    printf("->NULL\n");

}


void ajouter_element_ensemble(Ensemble *chaine , int somet)
{
    Ensemble tmp;
    Ensemble maillon=(struct Element *) malloc(sizeof(Maillon) );

    // printf("on va creer %d \n",somet);

    if(!maillon) //on test si le malloc a reussi
    {
        printf("malloc echoué pour l'ajout d'un sommeta l'ensemble \n");
        exit(EXIT_FAILURE);
    }
    else
    {
        maillon->st=somet;
        maillon->suivant=NULL;
        maillon->precedent=NULL;
    }

    if(!*chaine)// cas ou la liste est vide l'element créé devient la tete
    {
        //  printf("la chaine est vide \n");
        *chaine=maillon;
        maillon->precedent=maillon; //la tete pointera toujours sur la fin de l'ensemble
        //   printf("tete %d queue %d",(*chaine)->st,(*chaine)->precedent->st);
    }
    else
    {

        //    printf(" la chaine n'est pas vide \n");

        if(somet<(*chaine)->st) // si le sommet est plus petit que la tete alors il devient la tete 
        {

            //      printf("mais %d est < a %d \n",somet,(*chaine)->st);
            tmp=(*chaine)->precedent; // on sauvegarde la tete
            (*chaine)->precedent=maillon; // l'ancienne tete devient le seconde element donc il pointe sur maillon qui devient la nouvel tete 
            maillon->suivant=(*chaine); // maillon devient la tete 
            maillon->precedent=tmp; // la tete repointe sur la fin
            (*chaine)=maillon; //le pointeur de la chaine pointe sur la nouvelle tete
            //     printf("nouvelle tete %d queue %d \n",(*chaine)->st,(*chaine)->precedent->st);

        }
        else if(somet>(*chaine)->precedent->st) // si le sommet est plus grand que la fin il devient la fin
        {
            //     printf("mais %d > a la tete %d \n",somet,(*chaine)->precedent->st);
            maillon->precedent=(*chaine)->precedent; // le precedent de  nouvelle fin pointe sur l'ancienne
            (*chaine)->precedent->suivant=maillon; // le suivant de l'ancienne tete pointe sur la nouvel
            (*chaine)->precedent=maillon; //le precedentde  tete pointe sur la nouvel fin


        }
        else // sinon on est obligé de rechercher l'endroit ou inserer notre somet
        {
            //     printf("le sommet %d n'est ni < a tete ni > a la queue on recherche l'endroit ou le placer \n",somet);
            tmp=*chaine;

            while(tmp->suivant && somet>=tmp->st) // on parcourt la liste jusqu'a l'avant dernier element
            {
                //printf("->%d",tmp->st);
                tmp=tmp->suivant;
            }
            //     printf("on va place %d aprés %d \n",somet,tmp->st);

            tmp->precedent->suivant=maillon;
            maillon->precedent=tmp->precedent;
            tmp->precedent=maillon;
            maillon->suivant=tmp;


        }
    }
    //   printf("la chaine est devenu : ");
    //    afficher_ensemble(chaine);
}


void supprimer_queue_ensemble(Ensemble *l)
{
    Ensemble queue,tete;

    queue=(*l)->precedent;
    tete=*l;
    if(queue!=tete)
    {
        //   printf("la tete precedent dif de tete suivant\n");
        //   printf("on va donc supprimer %d \n",tmp->st);

        tete->precedent=queue->precedent;
        (tete->precedent)->suivant=NULL;
        free(queue);
        queue=NULL;
    }
    else
    {
        free(*l);
        *l=NULL;
    }

}



void supprimer_ensemble(Ensemble *l)
{
    Ensemble tmp;


    tmp=(*l)->precedent;
    while(tmp && tmp!=tmp->precedent)
    {
        (*l)->precedent=tmp->precedent;
        free(tmp);
        tmp=(*l)->precedent;
    }
    if(tmp==tmp->precedent)
        free(tmp);
    *l=NULL;
}




void ajouter_element_queue(Ensemble *chaine , int somet)
{
    Ensemble maillon=(struct Element *) malloc(sizeof(Maillon) );

    //   printf("on va creer %d \n",somet);

    if(!maillon) //on test si le malloc a reussi
    {
        printf("malloc echoué pour l'ajout d'un sommeta l'ensemble \n");
        exit(EXIT_FAILURE);
    }
    else
    {
        maillon->st=somet;
        maillon->suivant=NULL;
        maillon->precedent=NULL;
    }

    if(!*chaine)// cas ou la liste est vide l'element créé devient la tete
    {
        *chaine=maillon;
        maillon->precedent=maillon; //la tete pointera toujours sur la fin de l'ensemble
    }
    else
    {

        Ensemble tete,queue;
        tete=(*chaine);
        queue=(*chaine)->precedent;

        tete->precedent=maillon;

        maillon->precedent=queue;
        queue->suivant=maillon;


        //         maillon->precedent=(*chaine)->precedent; // le precedent de  nouvelle fin pointe sur l'ancienne
        //       (*chaine)->precedent->suivant=maillon; // le suivant de l'ancienne tete pointe sur la nouvel
        //     (*chaine)->precedent=maillon; //le precedentde  tete pointe sur la nouvel fin


    }
    //   printf("la chaine est devenu : ");
    //   afficher_ensemble(chaine);
}

