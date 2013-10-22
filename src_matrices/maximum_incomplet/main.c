//MAIN POUR LA FONCTION creeMaximumApproximatif

#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "model_matrice.h"

//fonction main
int main(int argc, const char * argv[])
{

    if (argc < 0) return 0;
    if (sizeof(argv[0]) == 0) return 0;

    int tailleG = 0, maximumAppr = 0;

    FILE *fp;
    fp=NULL;

    //ouverture du fichier en lecture ( modifier l'adresse de l'emplacement du fichier )
    fp=fopen("../../utils/Benchs/myciel4.txt","r");

    int s1,s2;
    int i, j;

    if( fscanf(fp,"%d %d",&s1,&s2) ) //saisie la premiere ligne nb sommet et nb arrete
        printf("nb sommet %d , nb arrete %d \n",s1,s2);
    tailleG=s1; //stock le nombre de sommets dans la variable tailleG

    int graphe[tailleG][tailleG]; // declaration de la matrice du graphe

    //initialisation de la matrice du graphe a 0
    for ( i=0; i<tailleG; i++){
        for (j=0; j<tailleG; j++){
            graphe[i][j] = 0;
        }
    }


    while( fscanf(fp,"%d %d",&s1,&s2)==2 ) //lit tout le fichier, fscanf retourne le nombre de variables saisies si on en a plus ou moins que deux on sort
    {
        //Ajout des aretes dans la matrice du graphe
        graphe[s1][s2] = 1;
        graphe[s2][s1] = 1;
    }

    fclose(fp);

    maximumAppr = creeMaximumApproximatif(tailleG, graphe, 0);
    printf(" cardinalitee du sous graphe desert maximum approximatif: %d\n", maximumAppr);

    return 0;
}


