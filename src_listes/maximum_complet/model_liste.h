#ifndef MODEL_LIST_H
#define MODEL_LIST_H

void afficher_tab(int *, int);

int verif(liste *,int *);

int maximum_rec(graphe_l *,int ,int *,sommet,Ensemble *,int *,int *,int );

int maximum_rec_sans_coupure(graphe_l *);

int maximum(graphe_l *);




#endif
