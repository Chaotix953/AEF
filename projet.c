#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AEF
{
    // definition des attributs
    char *nom;
    char *q;
    char **matriceTransition;
    int etat;
    char *mdp;
    char *mot;

    // definition des methodes
    int (*transition)(struct AEF *);
} t_AEF;

void afficherMatrice(char **mat)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c(%d) ", mat[i][j], &mat[i][j]);
        }
        printf("\n");
    }
}

// Fonction pour déterminer l'état suivant en fonction de la transition
int transition(struct AEF *aef)
{
    afficherMatrice(aef->matriceTransition);

    for (int i = 0; i < 3; i++)
    {
        //printf("%c \n", aef->mot[i]);

        if (aef->matriceTransition[aef->etat][aef->etat] == aef->mot[i])
        {
            aef->etat += 1;
        }
        else
        {
            aef->etat = 0;
        }
    }
    return (aef->etat == 3) ? 1 : 0;
}

t_AEF *initAEF(char *nom, char *q, char **matriceTransition, char *mdp, char *mot, int (*transition)(t_AEF *))
{
    t_AEF *aef = (t_AEF *)malloc(sizeof(t_AEF));

    aef->nom = nom;
    aef->q = q;
    aef->etat = 0;
    aef->matriceTransition = matriceTransition;
    aef->mdp = mdp;
    aef->mot = mot;
    aef->transition = transition;

    return aef;
}

int main()
{
    int etat = 0;
    char *mdp = (char *)"ABC";
    char *mot = (char *)"ABC";
    char q[4] = {'0', 'A', 'B', 'C'};

    char **matriceTransition = (char**) calloc(3, sizeof(char*));
    for (int i = 0; i < 3; i++)
    {
        *(matriceTransition+i) = (char*) calloc(3, sizeof(char));
    }

    matriceTransition[0][0] = q[1];
    matriceTransition[0][1] = q[0];
    matriceTransition[0][2] = q[0];
    matriceTransition[1][0] = q[0];
    matriceTransition[1][1] = q[2];
    matriceTransition[1][2] = q[0];
    matriceTransition[2][0] = q[0];
    matriceTransition[2][1] = q[0];
    matriceTransition[2][2] = q[3];

    t_AEF *aef = initAEF(strdup("automate1"), strdup(q), (char **)matriceTransition, strdup(mdp), strdup(mot), transition);

    printf("%d", aef->transition(aef));

    for (int i = 0; i < 3; i++)
    {
        free(matriceTransition[i]);
    }
    free(matriceTransition);

    free(aef);

    return 0;
}