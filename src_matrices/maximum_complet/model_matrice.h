#ifndef MODEL_MATRICE_H
#define MODEL_MATRICE_H

void initialiser_matrice(graphe_m *);

void ajouter_arete_m(graphe_m *, int , int);

void afficher_matrice(graphe_m *);

int estSousGraphDesert (int tailleGraphe,
                        int graphe[tailleGraphe][tailleGraphe],
                        int tailleEns, int s[tailleEns]);

int estMaximal (int tailleGraphe,
                int graphe[tailleGraphe][tailleGraphe],
                int tailleEns,
                int s[tailleEns]);

int creeMaximal (int tailleGraphe,
                 int graphe[tailleGraphe][tailleGraphe],
                 int maximum);

int creeMaximumExact (int tailleGraphe,
                      int graphe[tailleGraphe][tailleGraphe],
                      int maximum);

int creeMaximumApproximatif (int tailleGraphe,
                             int graphe[tailleGraphe][tailleGraphe],
                             int maximum);

#endif


