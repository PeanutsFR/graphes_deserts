#include <stdio.h>
#include <stdlib.h>
#include "couleur.h"
#include "parser.h"
#include "structure.h"
#include "model_liste.h"
#include "model_matrice.h"
#include "gestion_listes.h"


int main(int argc , char*argv[])
{



    clrscr();
    couleur("30;47");
    printf("+-----------------------------------------------------------------------------+\n");
    printf("|");couleur("0");
    couleur("42");printf("                                                                             ");couleur("0");
    couleur("30;47");
    printf("|\n");
    printf("+");couleur("0");
    couleur("30;42");printf("                 Bienvenue sur le projet de complexite                       ");couleur("0");
    couleur("30;47");
    printf("+\n");
    printf("|");couleur("0");
    couleur("42");printf("                                                                             ");couleur("0");
    couleur("30;47");
    printf("|\n");
    printf("+-----------------------------------------------------------------------------+\n\n\n\n");couleur("0");

    if(argc<2)
    {
        couleur("31");printf("usage : ./projet_complexite <chemin/fichier> \n");couleur("0");
    }
    else
    {
        couleur("32");printf("Ouverture fichier :''"),couleur("0");
        couleur("31");printf("%s",argv[1]),couleur("0");
        couleur("32");printf("''");couleur("0");
        couleur("32;5");printf("Appuyez sur entrée\n");couleur("0");
        getchar();

        FILE *fp;
        fp=NULL;

        if( (fp=fopen(argv[1],"r")) ) // on regarde si le fichier existe
        {
            //fp=fopen(argv[1],"r");

            parser(fp,&gl,&gm);                        //parser le fichier
            fclose(fp);



            // -------------------- /!\ ICI ON FAIT TOURNER LES ALGOS -------------------- //



            liste l = NULL;
            //ajouter_arete_l(&l,3);
            ajouter_arete_l(&l,5);
            ajouter_arete_l(&l,7);
            ajouter_arete_l(&l,9);
            printf("Ensemble de sommets à vérifier :\n");
            afficher_liste(&l);
            printf("\n");

            // VERIF LISTE
            int verif_l = 69;
            verif_l = verification_l(&gl,&l);
            printf("Verif_l : %d\n", verif_l);

            // VERIF MATRICE
            int verif_m = 69;
            verif_m = verification_m(&gm,&l);
            printf("Verif_m : %d\n", verif_m);

        }
        else
        {
            couleur("31");printf("le fichier demandé: ''");couleur("0");
            couleur("31;47;5");printf("%s",argv[1]);couleur("0");
            couleur("31");printf("'' n'existe pas \n");couleur("0");
        }

    }
    return 0;
}

