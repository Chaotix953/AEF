#ifndef AEF
#define AEF
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
int ***creerMatrice3D(int lignes, int colonnes, int x);

int **creerMatrice2D(int lignes, int colonnes, int x);

// creer le tableau avec les differents etats
int *creerTableauQ(int taille);

//fonction pour detecter des doublons dans une liste
int detecterOccurence(int *tab, int tailleTab, int val);

// fonction pour initialiser un aef
t_AEF *initAEF(char *nom, int *q, int q0, char *alphabet, int ***matriceTransition, int *f, int taille, int **nbElementsMatriceTransition, int nbF);

// fonction pour supprimer un aef
void suppAEF(t_AEF *aef);

// fonction pour obtenir l'indice d'un caractere
int getIndex(char *alphabet, char entree);

// fonction pour faire des transitions
void transition(t_AEF *aef, char entree);

void afficherAEF(t_AEF *aef);

t_AEF *lireFichier(char *dir);

t_AEF *saisirAEF();

void enregistrerAEF(t_AEF *aef);

void supprimerAEF(t_AEF **liste_aef, t_AEF *aef, int *nbAEF);

int reconnaitreMot(t_AEF *aef, char *mot);

int verifAutomateDeterministe(t_AEF *aef);

int verifAutomateComplet(t_AEF *aef);

void transformerAutomateComplet(t_AEF *aef);

t_AEF *transformerAutomateDeterministe(t_AEF *aef, int *nbAEF);

int factoriel(int n);

int** combinaisons_v2(int p, int* e, int n, int comb_count);

int ***creerTabComb(int* tab, int lignes, int colonnes);

int contient(int *tab, int taille, int valeur);

int* supprimerDoublons(int *tab, int *taille);

int *supprimerValeur(int *tab, int *taille, int valeur);

void trierOrdreCroissant(int *tab, int *taille);

#endif