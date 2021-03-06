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
	int i;
        fp=NULL;

        if( (fp=fopen(argv[1],"r")) ) // on regarde si le fichier existe
        {
            //fp=fopen(argv[1],"r");

            parser(fp,&gl,&gm);                        //parser le fichier
            fclose(fp);

      printf("calcul maximal \n");
            Ensemble maximal;

          
            for(i=0;i<gl.n;i++)
            {
                maximal=calcul_maximal(&gl,i);
                printf("Ensemble maximal trouve en partant de  %d \n",i);
                couleur("31");afficher_ensemble(&maximal);couleur("0");
                supprimer_ensemble(&maximal);
                maximal=NULL;
		printf("\n");
            }            
            printf("\n");




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

