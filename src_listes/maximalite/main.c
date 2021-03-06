#include <stdio.h>
#include <stdlib.h>
#include "couleur.h"
#include "parser.h"
#include "structure.h"
#include "gestion_listes.h"
#include "model_liste.h"


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
        couleur("31");printf("pas d'option spe \n");couleur("0");
    }
    else
    {
        couleur("32");printf("Ouverture fichier :''");couleur("0");
        couleur("31");printf("%s",argv[1]);couleur("0");
        couleur("32");printf("''");couleur("0");
        couleur("32;5");printf("Appuyez sur entrée\n");couleur("0");
        getchar();

        FILE *fp;
	int i,test;
        fp=NULL;

        if( (fp=fopen(argv[1],"r")) ) // on regarde si le fichier existe
        {
            //fp=fopen(argv[1],"r");

            parser(fp,&gl,&gm);                        //parser le fichier
            fclose(fp);

        Ensemble tmp=NULL;
            saisie_ensemble_sommet(&tmp);
            printf("la chaine saisie est :\n");
            afficher_ensemble(&tmp);
            printf("\n");
	test=verification_l(&gl,&tmp);
            if (test==1)
{
                printf("c'est un sous graphe desert\n");
	test=maximalite(&gl,&tmp);
            if(!test)
            {
                afficher_ensemble(&tmp);
                couleur("31");printf("l'ensemble est maximal\n");couleur("0");
            }
            else
            {
                couleur("31");printf("on a trouve un ensemble plus grand \n");couleur("0");
                afficher_ensemble(&tmp);
            }
            supprimer_ensemble(&tmp);
}
            else 
                printf(" c'est ensemble n'est pas un sous graphe desert a la base\n");


    	   
            





            for(i=0;i<gl.n;i++) // efface le graph
            {
                supprimer_liste(&gl.a[i]);
            }


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

