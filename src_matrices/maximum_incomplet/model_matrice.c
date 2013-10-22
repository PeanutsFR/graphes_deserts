#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "gestion_listes.h"
#include "couleur.h"

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


void ajouter_arete_m(graphe_m *g, int somet1, int somet2)
{
    g->a[somet1][somet2]=1;
    g->a[somet2][somet1]=1;
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

//Verifie si un ensemble de sommets est un sous graphe desert
int estSousGraphDesert (int tailleGraphe, int graphe[tailleGraphe][tailleGraphe], int tailleEns, int s[tailleEns]){

    int i = 0, j = 0, ok = -1, nonOk = -1;
    int neutre = 0;

    for ( i = 0; i < tailleEns; i++){ //boucle sur la taille de l'ensemble de sommets

        for (j=0; j < tailleEns; j++){

            //printf("s de i = %d, s de j = %d\n", s[i], s[j]);
            if ( (graphe[s[i]][s[j]] == 0) && (s[i] != s[j])  && ( i !=j)) {
                // printf("dit ok \n");
                ok = 0; // Si il n'y a pas d'aretes entre les sommets et que  on met ok a 0
            }
            else if ( (s[i] == s[j]) && (i == j )) neutre = 0;
            else if ( ((graphe[s[i]][s[j]] == 1) && (s[i] != s[j])) || ( (graphe[s[i]][s[j]] == 0) && (s[i] == s[j]) && (i != j)) ) nonOk = 1; // sinon on met nonOk a 1
        }

    }

    if (nonOk == 1) return nonOk; // Si nonOk est a un on retourne nonOk
    else return ok; //Sinon on retourne ok
}



//Verifie si un ensemble de sommets est un sous graphe desert maximal.
int estMaximal (int tailleGraphe, int graphe[tailleGraphe][tailleGraphe], int tailleEns, int s[tailleEns]){

    int i = 0, ok = 0; // On defini la varaible ok a 0 pour maximal. Elle passera a 1 si l'ensemble n'es pas maximal

    int tailleTabTemp = tailleEns + 1;

    int tab_temp[tailleTabTemp]; // Creation d'un ensemble de sommets temporaire qui est plus grand de 1 par rapport a l'ensemble initial

    for (i = 0; i< tailleTabTemp; i++)tab_temp[i] = 0;

    if ( estSousGraphDesert( tailleGraphe, graphe, tailleEns, s) == 1 ) return 2; // Test si l'ensemble de points passer en paramétre est un sous graphe desert. Si c'est pas le cas renvoi 2

    for ( i=0; i<tailleEns; i++ ) {

        tab_temp[i] = s[i]; // copie les sommets de l'ensemble passer en parametre dans tab_temp
    }

    for (i = 0; i < tailleGraphe; i++){ // boucle sur la taille du graphe

        tab_temp[tailleTabTemp-1] = i; // a chaque tour de boucles ajoute un sommet du graphe a l'ensemble de sommets donner en parametres

        // for ( j = 0; j< tailleTabTemp; j++) printf("case %d valeure %d\n", j, tab_temp[j]);

        if ( estSousGraphDesert(tailleGraphe, graphe, tailleTabTemp, tab_temp) == 0 ){

            ok = 1; // test si le nouvel ensemble de sommet est un sous graphe desert. Si c'est le cas met la variable ok a 1 car l'ensemble n'es pas maximal

        }
    }


    return ok;
}


int creeMaximal (int tailleGraphe, int graphe[tailleGraphe][tailleGraphe], int maximum){

    int i,j,k,l,m, stock = 0, res = 0, cpt = 1, indice = 0, nbSommets, cardMaximum = 0;

    int ensemble[10000]; // ensemble dans lequel seront stocker les sommets du sous graphe maximal
    int cardGrapheMax[10000]; // tableau dans lequel seront stocker les cardinalites de tous les sous-graphe desert maximal

    for (int i = 0; i<10000; i++){
        ensemble[i] = 0; // initialise l'ensemble
        cardGrapheMax[i] = 0; // initialise le tableau des cardinalites
    }

    //boucle sur la matrice du graphe
    for (i = 0; i < tailleGraphe; i++){
        for (j = i+1; j < tailleGraphe; j++){

            ensemble[0] = i; // on met le premier sommet dans l'ensemble
            ensemble[cpt] = j; // et le second dans la deuxieme case du tableau de l'ensemble de sommets


            // sert a l'affichage des sommets inserer dans l'ensemble
            for (k = 0; k < cpt+1; k++) printf("element %d de l'ensemble : %d\n", k, ensemble[k]);

            nbSommets = cpt+1; // defini le nombre de sommets de l'ensemble

            if ( estSousGraphDesert(tailleGraphe, graphe, nbSommets, ensemble) == 0){
                printf("est desert \n");
                stock = j;
                cpt++;
                for (m = j+1; m<tailleGraphe; m++){
                    printf("\n");

                    ensemble[cpt] = m; // met le nouveaux sommet dans l'ensemble a tester

                    for (l = 0; l < cpt+1; l++) printf("element %d de l'ensemble : %d\n", l, ensemble[l]);

                    nbSommets = cpt+1; // defini le nombre de sommets de l'ensemble

                    res = estMaximal(tailleGraphe, graphe, nbSommets, ensemble); // test si l'ensemble de sommet est un sous graphe maximal


                    if (res == 1){ // Si c'est un graphe desert mais pas maximal

                        printf("Est desert mais pas maximal\n");
                        cpt++; // si 'estMaximal' renvoi 1 ça veux dire que l'ensemble est un sous graphe desert mais pas maximal. On increment donc cpt pour ajouter un autre sommet et tester a nouveau.

                    }
                    else if (res == 0){ //Si estMaximal renvoi 0 ça veux dire que le sous graphe desert est maximal
                        //Affiche la cardinalite du sous graphe desert maximal retourner
                        printf("on a un maximal de taille %d\n", cpt+1);
                        cardGrapheMax[indice] = cpt+1; // on stock la cardinalite du sous graphe desert maximal dans le tableau
                        cpt = 1; // on reinitialise le compteur
                        j = stock+1; // positionne la variable j au sommet suivant
                        indice++; // on increment l'indice pour pouvoir stocker la cardinalite du prochain sous graphe desert maximal
                        m = tailleGraphe; //stop la boucle pour ne pas tester la suite 2 fois (elle sera tester plus tard)
                    }
                }
                cpt = 1; // on reinitialise le compteur en sortant de la boucle
                j = stock; // on met la variable j à la valeur qu'elle avait après avoir trouver le premier sous graphe desert afin de continuer de tester avec le meme point de depart

                }
            else printf("n'est pas desert\n");

        }
    }

    if ( maximum == 1){ // sert a definir si on veux trouver le maximum exact en utilisant la fonction
        for (l = 0; l < indice; l++) // boucle sur l'ensemble des cardinal des sous graphe desert maximal pour trouver celui qui a la plus grande cardinalite
            if ( cardMaximum < cardGrapheMax[l]) cardMaximum = cardGrapheMax[l];
        return cardMaximum; // renvoi la cardinalite maximal
    }
    else return cardGrapheMax[0]; // on renvoi la cardinalite du premier sous graphe desert maximal trouver
}

int creeMaximumExact (int tailleGraphe, int graphe[tailleGraphe][tailleGraphe]){

    int indiceMaximum = 1, cardMaximum = 0; // choisi l'indice qu'il faut rentrer pour la fonction 'creeMaximal' et initialise cardMaximum

    cardMaximum = creeMaximal (tailleGraphe, graphe, indiceMaximum);

    return cardMaximum;

}

int creeMaximumApproximatif (int tailleGraphe, int graphe[tailleGraphe][tailleGraphe], int maximum){

    int i,j,k,l, res = 0, cpt = 1, indice = 0, nbSommets, cardMaximum = 0;

    int ensemble[10000]; // ensemble dans lequel seront stocker les sommets du sous graphe maximal
    int cardGrapheMax[10000]; // tableau dans lequel seront stocker les cardinalites de tous les sous-graphe desert maximal

    for (int i = 0; i<10000; i++){
        ensemble[i] = 0; // initialise l'ensemble
        cardGrapheMax[i] = 0; // initialise le tableau des cardinalites
    }

    //boucle sur la matrice du graphe
    for (i = 0; i < tailleGraphe; i++){
        for (j = 0; j < tailleGraphe; j++){

            ensemble[0] = i; // on met le premier sommet dans l'ensemble
            ensemble[cpt] = j; // et le second dans la deuxieme case du tableau de l'ensemble de sommets


            // sert a l'affichage des sommets inserer dans l'ensemble
            for (k = 0; k < cpt+1; k++) printf("element %d de l'ensemble : %d\n", k, ensemble[k]);

            nbSommets = cpt+1; // defini le nombre de sommets de l'ensemble

            res = estMaximal(tailleGraphe, graphe, nbSommets, ensemble); // test si l'ensemble de sommet est un sous graphe maximal

            if (res == 1){ // Si c'est un graphe desert mais pas maximal

                printf("Est desert mais pas maximal\n");
                cpt++; // si 'estMaximal' renvoi 1 ça veux dire que l'ensemble est un sous graphe desert mais pas maximal. On increment donc cpt pour ajouter un autre sommet et tester a nouveau.

            }
            else if (res == 0){ //Si estMaximal renvoi 0 ça veux dire que le sous graphe desert est maximal
                //Affiche la cardinalite du sous graphe desert maximal retourner
                printf("on a un maximal de taille %d\n", cpt+1);
                cardGrapheMax[indice] = cpt+1; // on stock la cardinalite du sous graphe desert maximal dans le tableau
                cpt = 1;
                indice++; // on increment l'indice pour pouvoir stocker la cardinalite du prochain sous graphe desert maximal
            }
        }
        cpt = 1; // on reinitialise le compteur en sortant de la boucle
    }
    if ( maximum == 1){ // sert a definir si on veux trouver le maximum exact en utilisant la fonction
        for (l = 0; l < indice; l++) // boucle sur l'ensemble des cardinal des sous graphe desert maximal pour trouver celui qui a la plus grande cardinalite
            if ( cardMaximum < cardGrapheMax[l]) cardMaximum = cardGrapheMax[l];
        return cardMaximum; // renvoi la cardinalite maximal
    }
    else return cardGrapheMax[0]; // on renvoi la cardinalite du premier sous graphe desert maximal trouver
}
