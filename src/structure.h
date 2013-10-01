#ifndef STRUCTURE_H
#define STRUCTURE_H

#define n_max 20000 // nombre maximum de sommets 

typedef int sommet ; // sommet est de type entier


/*representation par matrice d'adjacence */

typedef struct 
{
    int a[n_max][n_max]; //matrice carré 1 pour presence arc entre x et y 0 pour absence 
    int n;               // compris entre 0 et n_max (nombre de sommet)
}graphe_m;

graphe_m gm;



/*representation par liste d'adjacence */

typedef struct chainon
{
    sommet st;
    struct chainon *suivant;
} Couple;

typedef Couple *liste;

typedef struct
{
    liste a[n_max];
    int n;
} graphe_l;

graphe_l gl;

#endif
