#include <stdio.h>
#include <stdlib.h>

#include "couleur.h"
#include "structure.h"
#include "gestion_listes.h"
#include "model_matrice.h"

/****************************************************************************************/
/*                                                                                      */
/* parser ()  parcourt un fichier en lisant chaque ligne                                */
/*                                                                                      */
/****************************************************************************************/

void parser(FILE *fp, graphe_l *gl, graphe_m *gm)
{
    int s1,s2;
    int i;

    if( fscanf(fp,"%d %d",&s1,&s2) ) //saisie la premiere ligne nb sommet et nb arrete
        printf("nb sommet %d , nb arrete %d \n",s1,s2);
    gm->n=s1;
    gl->n=s1;


    initialiser_matrice(gm);

    while( fscanf(fp,"%d %d",&s1,&s2)==2 ) //lit tout le fichier, fscanf retourne le nombre de variables saisies si on en a plus ou moins que deux on sort
    {
        printf("sommet %d<->%d \n",s1,s2);
        ajouter_arete_l(&gl->a[s1],s2);   //graphe non oriente donc si 1->2 on a 2->1
        ajouter_arete_l(&gl->a[s2],s1);
        ajouter_arete_m(gm,s1,s2);
    }

    for(i=0;i<gl->n;i++)
    {
        printf("[%d]",i);
        afficher_liste(&gl->a[i]);

    }
    printf("\n");
    afficher_matrice(gm);

}

// void saisie_ensemble_sommet(liste *l)
// {

// }
