#ifndef AEF
#define AEF
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct AEF
{
    // definition des attributs
    char *alphabet;
    int *q;
    int q0;
    int taille;
    int *f;
    int **matriceTransition;
    int etat;
} t_AEF;

//fonction pour creer la matrice de transition
int **creerMatrice2D(int lignes, int colonnes);

//creer le tableau avec les differents etats
int *creerTableauQ(int taille);

//fonction pour initialiser un aef
t_AEF *initAEF(int *q, int q0, char *alphabet, int **matriceTransition, int *f, int taille);

//fonction pour supprimer un aef
void suppAEF(t_AEF *aef);

//fonction pour obtenir l'indice d'un caractere
int getIndex(char *alphabet, char entree);

//fonction pour faire des transitions 
int transition(t_AEF *aef, char entree);

t_AEF *lireFichier();

#endif