#include<stdio.h>
#include<stdlib.h>
#include "couleur.h"
#include "structure.h"
#include "gestion_listes.h"

void maximum_incomplete(graphe_d *g)
{
    int i,degre_max,indice,nb_sommet,nb_supprime;
    int marque[n_max];
    liste tmp=NULL;
    Ensemble l=NULL;
    degre_max=indice=nb_sommet=nb_supprime=0;

    for(i=0;i<g->n;i++) // initialise le tableau des sommet enleve a 0
        marque[i]=0;

    while((nb_sommet+nb_supprime)<g->n)
    {


        for(i=0;i<g->n;i++) //parcours les degree
        {
            if(!marque[i] )
            {
                if(g->degre[i] > degre_max) //cherche le degre le plus grand et le memorise
                {
                    indice=i;
                    degre_max=g->degre[i];
                }
                if(!g->degre[i] && !marque[i]) // si le degre est 0 et que le sommet n'a pas encore etait ajouté
                {
                    ajouter_element_ensemble(&l,i); //on ajoute le sommet isolé
                    nb_sommet++;
                    marque[i]=1;
                }
            }
        }
      
        //suppression du sommet ayant le plus grand degre

        marque[indice]=1; // marque le sommet comme supprime
        tmp=g->a[indice];
        while(tmp) //parcours la liste du sommet a supprimer
        {
            supprimer_arete_l(&g->a[tmp->st],indice); //supprime le sommet de la liste de chacun de ses voisins
            g->degre[tmp->st]--;
            tmp=tmp->suivant;
        }
        supprimer_liste(&g->a[indice]);
        nb_supprime++;
        g->degre[indice]=0;
        degre_max=0;
     
    }
    couleur("31");printf("ON A TROUVE UN SOUS GRAPHE MAXIMUM DE %d SOMMETS\n",nb_sommet);couleur("0");
    afficher_ensemble(&l);

}

void copie_graphe_l(graphe_l *gl ,graphe_d *gd)
{

    int i;
    liste tmp;

    gd->n=gl->n;
    for(i=0;i<gl->n;i++)
        gd->degre[i]=0;

    for(i=0;i<gl->n;i++)
    {
        tmp=gl->a[i];
        while(tmp)
        {
            ajouter_arete_l(&gd->a[i],tmp->st);
            gd->degre[i]++;
            ajouter_arete_l(&gd->a[tmp->st],i);
            tmp=tmp->suivant;
        }
    }
}

