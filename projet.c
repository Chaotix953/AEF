#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AEF
{
    // definition des attributs
    char *nom;
    char *alphabet;
    int *q;
    int *q0;
    int *taille;
    int *f;
    int **matriceTransition;
    int *etat;
} t_AEF;

//fonction pour creer la matrice de transition
void creerMatriceTransition(t_AEF *aef, int lignes, int colonnes)
{
    aef->matriceTransition = (int **)malloc(lignes * sizeof(int *));

    // Allouer de la mémoire et copier les valeurs
    for (int i = 0; i < lignes; i++)
    {
        aef->matriceTransition[i] = (int *)malloc(colonnes * sizeof(int));
    }

    //remplacer par une fonction qui remplit la matrice de transition
    aef->matriceTransition[0][0] = aef->q[3];
    aef->matriceTransition[0][1] = aef->q[1];
    aef->matriceTransition[1][0] = aef->q[1];
    aef->matriceTransition[1][1] = aef->q[2];
    aef->matriceTransition[2][0] = -1;
    aef->matriceTransition[2][1] = -1;
    aef->matriceTransition[3][0] = aef->q[3];
    aef->matriceTransition[3][1] = -1;
}

//creer le tableau avec les differents etats
int *creerTableauQ(int taille)
{
    int *q = (int *)malloc(taille * sizeof(int));

    if (q == NULL)
    {
        perror("Allocation de mémoire échouée");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < taille; i++)
    {
        q[i] = i;
    }
    return q;
}

//fonction pour initialiser un aef
t_AEF *initAEF(int *q, char *nom, char *alphabet, int *f, int *taille)
{
    t_AEF *aef = (t_AEF *)malloc(sizeof(t_AEF));

    // Allouer de la mémoire pour nom et alphabet
    aef->nom = (char *)malloc(strlen(nom) + 1);
    strcpy(aef->nom, nom);

    aef->alphabet = (char *)malloc(strlen(alphabet) + 1);
    strcpy(aef->alphabet, alphabet);

    aef->etat = (int *)calloc(1, sizeof(int));
    aef->q = q;
    aef->q0 = (int *)calloc(1, sizeof(int));
    aef->f = f;
    aef->taille = taille;

    aef->matriceTransition = NULL;

    return aef;
}

void suppAEF(t_AEF *aef, int taille)
{
    // Libération de la mémoire
    for (int i = 0; i < taille; i++)
    {
        free(aef->matriceTransition[i]);
    }
    free(aef->matriceTransition);

    free(aef->q);
    free(aef->q0);

    free(aef->nom);
    free(aef->alphabet);

    free(aef);
}

int getIndex(t_AEF *aef, char entree)
{
    for (int i = 0; i < 2; i++)
    {
        if (entree == aef->alphabet[i])
        {
            return i;
        }
    }
    return -1;
}

void transition(t_AEF *aef, char entree)
{
    if (aef->matriceTransition[*(aef->etat)][getIndex(aef, entree)] != -1)
    {
        *(aef->etat) = aef->matriceTransition[*(aef->etat)][getIndex(aef, entree)];
        for (int i = 0; i < 2; i++)
        {
            if (*(aef->etat) == aef->f[i])
            {
                printf("mot reconnu par l'automate\n");
            }
        }
    }
    else
    {
        printf("transition non definit %d, %c\n", *(aef->etat), entree);
    }
}

int main()
{
    // initialiser les variables avec un fichier texte
    int taille = 4;
    int *q = creerTableauQ(taille);
    char entre[] = "BAAB";
    char nom[] = "automate 1";
    char alphabet[] = "AB";
    int f[] = {2, 3};

    t_AEF *aef = initAEF(q, nom, alphabet, f, &taille);
    creerMatriceTransition(aef, taille, strlen(alphabet));

    // //matrice de transition
    // printf("matrice de transition : \n");
    // for (int i = 0; i < 4; i++)
    // {
    //     for (int j = 0; j < 2; j++)
    //     {
    //         printf("%d ", aef->matriceTransition[i][j]);
    //     }
    //     printf("\n");
    // }

    for (int i = 0; i < strlen(entre); i++)
    {
        transition(aef, entre[i]);
    }

    // Libération de la mémoire
    suppAEF(aef, 4);

    return 0;
}
