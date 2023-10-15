#ifndef AEF
#define AEF
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct AEF
{
    // definition des attributs
    char *nom;
    char *alphabet;
    int *q;
    int q0;
    int taille;
    int *f;
    int ***matriceTransition;
    int **nbElementsMatriceTransition;
    int etat;
    int nbF;
} t_AEF;

// fonction pour creer la matrice de transition
int ***creerMatrice3D(int lignes, int colonnes);

int **creerMatrice2D(int lignes, int colonnes);

// creer le tableau avec les differents etats
int *creerTableauQ(int taille);

// fonction pour initialiser un aef
t_AEF *initAEF(char *nom, int *q, int q0, char *alphabet, int ***matriceTransition, int *f, int taille, int **nbElementsMatriceTransition, int nbF);

// fonction pour supprimer un aef
void suppAEF(t_AEF *aef);

// fonction pour obtenir l'indice d'un caractere
int getIndex(char *alphabet, char entree);

// fonction pour faire des transitions
int transition(t_AEF *aef, char entree);

void afficherAEF(t_AEF *aef);

t_AEF *lireFichier(char *dir);

t_AEF *saisirAEF();

void enregistrerAEF(t_AEF *aef);

void supprimerAEF(t_AEF **liste_aef, t_AEF *aef, int *nbAEF);

#endif