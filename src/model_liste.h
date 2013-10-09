#ifndef MODEL_LIST_H
#define MODEL_LIST_H

int presence_arrete_l(graphe_l *, sommet , sommet );

int verification_l(graphe_l *,liste *);
int maximalite(graphe_l *, liste *);

liste calcul_maximal(graphe_l *, int);

int maximum_rec(graphe_l *,int ,int *,sommet,liste *,int *);

int maximum(graphe_l *);


#endif
