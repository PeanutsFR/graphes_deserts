#include<stdio.h>
#include<stdlib.h>
#include "couleur.h"
#include "structure.h"
#include "gestion_listes.h"


void afficher_tab( int *tab, int fin)
{
    int i;
    for(i=0;i<fin;i++)
    {
        printf("%d:%d ",i,tab[i]);
    }
    printf("\n");
}


int verif(liste *l , int *tab)
{
    liste tmp;
    tmp=*l;
    while(tmp && !tab[tmp->st])
    {
        tmp=tmp->suivant;
    }
    
    if(!tmp)
        return 1;
    else
        return 0;


}


void maximum_rec(graphe_l *g,int profondeur,int *profondeurmax,sommet x,Ensemble *l, Ensemble *final, int *pinterdit,int * ppresent,int nbpossible)
{


    Ensemble tmp;
    liste voisins_sommet;

    // afficher_ensemble(l);
    for(x=x+1;x<g->n ;x++) // alors je lui ajoute un sommet et je "descend"
    {

      //    printf("on tente d'ajouter %d et t[%d]=%d \n",x,x,pinterdit[x]);
        // printf("profondeur %d %d> %d\n",profondeur,((profondeur+nbpossible)+1),*profondeurmax);
       //  afficher_tab(ppresent,g->n);
        if(!pinterdit[x] && ( (profondeur+nbpossible)> (*profondeurmax ) ) ) //si le sommet n'est pas marque
        {

         //   printf("on a %d sommet ,il reste %d sommetpossible ,pf max = %d \n",profondeur,nbpossible,*profondeurmax);
            if( verif(&g->a[x],ppresent) ) //verification_m(gm,l) ) // si c'est un desert on "descend" BESOIN TABLEAU DES SOMMETS PRESENTS indicer les sommets de marquage a ++ au lieu de 1
            {
                //      printf("ajout %d \n",x);
                ajouter_element_queue(l,x);

                //  afficher_ensemble(l);

                (profondeur)++;
                pinterdit[x]++;
                if(pinterdit[x]==1 )
                    nbpossible--;
                ppresent[x]=1;

                voisins_sommet=g->a[x];
                while(voisins_sommet)
                {
                    pinterdit[voisins_sommet->st]++;
                    if( pinterdit[voisins_sommet->st]==1 )
                        nbpossible--;
                    voisins_sommet=voisins_sommet->suivant;
                }

                //   printf("l'ensemble est un sous graphe desert \n");
                if( (profondeur)>(*profondeurmax) ) // si on trouve un sous graphe plus grand que ceux d'avant
                {
                    if(!final)
                        supprimer_ensemble(final);
                    (*final)=NULL;
                    tmp=*l;
                    while(tmp)
                    {
                        ajouter_element_queue(final,tmp->st);
                        //pmarquage[tmp->st]=1;
                        tmp=tmp->suivant;
                    }

                 //   couleur("33");printf("nouvel ensensemble max : %d sommets \n",profondeur);couleur("0");

                  //  printf("\n");
                  //  afficher_ensemble(final);


                    (*profondeurmax)=(profondeur);

                }

                maximum_rec(g,profondeur,profondeurmax,x,l,final,pinterdit,ppresent,nbpossible);
                if(ppresent[x])
                {
                    profondeur--;
                    supprimer_queue_ensemble(l);
                    ppresent[x]=0;
                    pinterdit[x]--;
                    nbpossible++;
                    voisins_sommet=g->a[x];
                    while(voisins_sommet)
                    {
                        pinterdit[voisins_sommet->st]--;
                        if( !pinterdit[voisins_sommet->st] &&  (voisins_sommet->st)>x )
                            nbpossible++;
                        voisins_sommet=voisins_sommet->suivant;
                    }

                }

              //  afficher_ensemble(l);
            }
            else
            {
                pinterdit[x]++;
                if(pinterdit[x]==1)
                    nbpossible--;

            }
            /*  else// on "remonte"
                {

            //  printf("l'ensemble n'est pas un sous graphe desert \n");

            (profondeur)--;

            // supprimer_queue_ensemble(l);
            // pmarquage[x]=0;

            //    afficher_ensemble(l);
            // printf("-%d",x);
            }*/

        }


    }
    // couleur("31");printf("sorite for \n");couleur("0");
    // afficher_ensemble(l);
}


int maximum(graphe_l *g)
{

    int profondeurtmp,profondeurmax;
    int sommet_interdit[n_max],sommet_present[n_max];
    int *pinterdit,*ppresent;
    sommet x;
    int i,nbpossible;
    Ensemble l=NULL;
    Ensemble final=NULL;
    profondeurmax=0;

    liste tmp;

    for(x=0;x<g->n;x++)
    {
        sommet_interdit[x]=0;
        sommet_present[x]=0;
    }

    pinterdit=sommet_interdit;
    ppresent=sommet_present;


    for(x=0;x<g->n;x++) //on part du sommet x
    {
        //couleur("31");printf("on part de %d",x);couleur("0");
       // printf("\n");
        ajouter_element_ensemble(&l,x);
        pinterdit[x]=1;
        ppresent[x]=1;
        tmp=g->a[x];
        nbpossible=g->n-1;
        while(tmp)
        {
            pinterdit[tmp->st]=1;
            nbpossible--;
            tmp=tmp->suivant;
        }
        profondeurtmp=1;
        maximum_rec(g,profondeurtmp,&profondeurmax,x,&l,&final,pinterdit,ppresent,nbpossible);
        for(i=0;i<g->n;i++)
        {
            pinterdit[i]=0;
            ppresent[i]=0;
        }

        supprimer_ensemble(&l);
        l=NULL;
    }
     printf("\n");
    couleur("31");printf("MAXIMUM TROUVE \n");couleur("0");
    couleur("33"),printf(" %d sommets \n",profondeurmax);
    afficher_ensemble(&final);couleur("0");
    printf("\n");

    supprimer_ensemble(&final);

    return 1;//maximum_rec(g,pmarquage,profondeur);
}


