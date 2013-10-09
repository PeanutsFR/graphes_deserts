#include<stdio.h>
#include<stdlib.h>
#include "couleur.h"
#include "structure.h"
#include "gestion_listes.h"



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

int verification_l(graphe_l  *g , liste *l)
{
    liste curseur1,curseur2;
    curseur1=*l;             //on pointe sur la tete de liste 
  //  printf("on va verifier que la liste donne est bien un graphe desert \n");
    if(curseur1->suivant)    // si elle contient plus d'un élément
    {
    //    printf("la liste contient plus d'un élément \n");
         curseur2=NULL;
        while(curseur1 && !curseur2 )      //on doit verifier que chaque sommet n'a pas d'arc entre eux
        {
            curseur2=curseur1->suivant;
      //      printf(" on va verifier si %d as un d'arc avec:\n ",curseur1->st);
            while(curseur2 && !presence_arrete_l(g,curseur1->st,curseur2->st) )
            {
        //        printf("     %d ? ---> non\n",curseur2->st);
                curseur2=curseur2->suivant;
            }
          //  if(curseur2)
            //    printf("    %d ? ---> oui \n",curseur2->st);
           // memoire_curseur1=curseur1;  // memoire_curseur pointe sur position-2
            curseur1=curseur1->suivant; // en fin de boucle curseur1 pointera sur position-1
        }

        return curseur1==NULL; // si le curseur1 a parcouru toute la ligne sous graphe desert
    }
    else return 1;
}

int maximalite(graphe_l *g, liste *l)
{

    int i,test;
    liste curseur;
    curseur=*l;
    test=0;
    int tab[n_max]={0};
    for(i=0;i<g->n;i++) //tableau de marquage initialiser a 0
    {
        tab[i]=0;
    }
    while(curseur) //on rajoute les sommet present dans le tableau de marquage pour ne pas les revisiter
    {
        tab[curseur->st]=1;
        curseur=curseur->suivant;
    }
    for(i=0;i<g->n && !test;i++) // pour chaque sommet
    {
        if(!tab[i]) // si il ne fait pas partie de l'ensemble de depart
        {
            ajouter_arete_l(l,i); // ajoute le sommet a l'ensemble
            if( !(test=verification_l(g,l)) )//si le sommet rajouté ne forme pas un sous graphe desert
            {
                supprimer_arete_l(l,i); //on supprime le sommet et on essaye les sommet suivant
            }
        }
    }
    return test;
}



liste calcul_maximal(graphe_l *g, int x)
{


    liste tete_liste;

    tete_liste=NULL;

    ajouter_arete_l(&tete_liste,x);

    int i;
    for(i=0;i<g->n;i++)
    {
        if(i!=x)
        {
            ajouter_arete_l(&tete_liste,i); // ajoue le sommet a l'ensemble
            if( !verification_l(g,&tete_liste) )
            {
                supprimer_arete_l(&tete_liste,i);
            }
        }
    }

    return tete_liste;
}


void maximum_rec(graphe_l *g,int profondeur,int *profondeurmax,sommet x,liste *l, liste *final, int *pmarquage)
{


    int i;
    liste tmp;
   // printf("\n");

            (profondeur)++;

  //  printf("profondeur : %d sommet ajouté :%d \n",profondeur,x);

  //  afficher_liste(l);
    if( verification_l(g,l) ) //si l'ensemble fourni est un sous graphe
    {

      //  printf("cette ensemble est un sous graphe on descent \n");
        if( (profondeur)>(*profondeurmax) ) // si on trouve un sous graphe plus grand que ceux d'avant
        {
            for(i=0;i<g->n;i++)
                pmarquage[i]=0;
            (*final)=NULL;
            tmp=*l;
            while(tmp)
            {
                ajouter_arete_l(final,tmp->st);
                pmarquage[tmp->st]=1;
                tmp=tmp->suivant;
            }

            couleur("33");printf("nouvel ensensemble max : %d sommets \n",profondeur);couleur("0");

            printf("\n");
            afficher_liste(final);


            (*profondeurmax)=(profondeur);

        }
        for(i=x+1;i<g->n ;i++) // alors je lui ajoute un sommet et je "descend"
        {
            if(!pmarquage[i])
            {
            ajouter_arete_l(l,i);

         //   couleur("34");printf("on rappel la fonction pour i= : %d \n",i);couleur("0");
            maximum_rec(g,profondeur,profondeurmax,i,l,final,pmarquage);
            }
        }
    }
    else
    {

     //   printf("cette ensemble n'est pas un sous graphe on enleve %d \n",x);
        (profondeur)--;
        supprimer_arete_l(l,x);
    }
   profondeur--;
 supprimer_arete_l(l,x);

}


int maximum(graphe_l *g)
{

    int profondeurtmp,profondeurmax;
    int marquage[n_max];
    int *pmarquage;
    sommet x;
    liste l=NULL;
    liste final=NULL;
    profondeurmax=0;

    for(x=0;x<g->n;x++)
    {
        marquage[x]=0;
    }

    pmarquage=marquage;

    
    for(x=0;x<g->n;x++) //on part du sommet x
    {
       couleur("31");printf("on part de %d \n",x);couleur("0");
        ajouter_arete_l(&l,x);
        profondeurtmp=0;
        maximum_rec(g,profondeurtmp,&profondeurmax,x,&l,&final,pmarquage);
        l=NULL;
       // afficher_liste(&l);
    }

    couleur("31");printf("MAXIMUM TROUVE \n");couleur("0");
    afficher_liste(&final);

    return 1;//maximum_rec(g,pmarquage,profondeur);
}


