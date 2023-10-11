#include "aef.h"

// fonction pour creer la matrice de transition
int **creerMatrice2D(int lignes, int colonnes)
{
    // Allouer de la mémoire et copier les valeurs
    int **matrice = (int **)calloc(lignes, sizeof(int *));

    for (int i = 0; i < lignes; i++)
    {
        matrice[i] = (int *)calloc(colonnes, sizeof(int));
    }

    // mettre toute les valeurs de la matrice a -1
    for (int i = 0; i < lignes; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
            matrice[i][j] = -1;
        }
    }

    return matrice;
}

// creer le tableau avec les differents etats
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

// fonction pour initialiser un aef
t_AEF *initAEF(char *nom, int *q, int q0, char *alphabet, int **matriceTransition, int *f, int taille)
{
    t_AEF *aef = (t_AEF *)malloc(sizeof(t_AEF));

    aef->nom = (char *)malloc(strlen(nom) + 1);
    strcpy(aef->nom, nom);

    aef->alphabet = (char *)malloc(strlen(alphabet) + 1);
    strcpy(aef->alphabet, alphabet);

    aef->q = q;
    aef->q0 = q0;
    aef->etat = aef->q0;
    aef->f = f;
    aef->taille = taille;
    aef->matriceTransition = matriceTransition;

    return aef;
}

// fonction pour supprimer un aef
void suppAEF(t_AEF *aef)
{
    // Libération de la mémoire
    for (int i = 0; i < aef->taille; i++)
    {
        free(aef->matriceTransition[i]);
    }
    free(aef->matriceTransition);
    free(aef->nom);

    free(aef->q);
    free(aef->f);

    free(aef->alphabet);

    free(aef);
}

// fonction pour obtenir l'indice d'un caractere
int getIndex(char *alphabet, char entree)
{
    for (int i = 0; i < strlen(alphabet); i++)
    {
        if (entree == alphabet[i])
        {
            return i;
        }
    }
    return -1;
}

// fonction pour faire des transitions
int transition(t_AEF *aef, char entree)
{
    if (getIndex(aef->alphabet, entree) != -1)
    {
        if (aef->matriceTransition[aef->etat][getIndex(aef->alphabet, entree)] != -1)
        {
            aef->etat = aef->matriceTransition[aef->etat][getIndex(aef->alphabet, entree)];
            for (int i = 0; i < strlen(aef->alphabet); i++)
            {
                // printf("%d == %d\n", aef->etat, aef->f[i]);
                if (aef->etat == aef->f[i])
                {
                    printf("mot reconnu par l'automate\n");
                }
            }
        }
        else
        {
            printf("transition non definit %d, %c\n", aef->etat, entree);
        }
        return 1;
    }
    else
    {
        printf("mot non reconnu par l'automate\n");
        return 0;
    }
}

t_AEF *lireFichier()
{
    t_AEF *aef = NULL;
    int taille = 1;
    int *q = NULL;
    int q0 = 0;
    char entre[] = "BAAB"; // pas besoin
    char alphabet[] = "";
    int *f = NULL;
    char nom[100] = "";
    int **matrice2D = NULL;
    char chaine[100] = "";

    // chercher tout les fichiers
    FILE *fichier = fopen("matrice.txt", "r");

    if (fichier != NULL)
    {
        fgets(nom, 100, fichier);
        printf("nom : %s\n", nom); 

        fscanf(fichier, "%s", alphabet);
        printf("alphabet : %s\n", alphabet);
        
        fscanf(fichier, "%d", &taille);
        printf("taille : %d\n", taille);

        
        int *q = creerTableauQ(taille);
        printf("q : ");
        for (int i = 0; i < taille; i++)
        {
            printf("%d", q[i]);
        }
        printf("\n");


        fscanf(fichier, "%d", &q0);
        printf("q0 : %d\n", q0);

        // il y a un trou dans le fichier
        fgets(chaine, 100, fichier);
        printf("trou %s", chaine);

        
        fgets(chaine, 100, fichier);


        int *f = malloc(sizeof(int));

        matrice2D = (int **)creerMatrice2D(taille, strlen(alphabet));

        // compteur a 0
        int compteur = 0;
        for (int i = 0; i < strlen(chaine); i++)
        {
            // printf("%c", chaine[i]);
            if (chaine[i] != ' ')
            {
                f[compteur] = chaine[i] - '0';
                compteur += 1;
                realloc(f, compteur + 1);
            }
        }
        printf("f : ");
        for (int i = 0; i < 2; i++)
        {
            printf("%d ", f[i]);
        }
        printf("\n");

        printf("matrice2D: \n");
        int x0 = 0;
        int x1 = 0;
        char c = 'c';
        while (fgets(chaine, sizeof(chaine), fichier) != NULL)
        {
            sscanf(chaine, "%d %c %d", &x0, &c, &x1);
            printf("%d %c %d\n", x0, c, x1);
            matrice2D[x0][getIndex(alphabet, c)] = x1;
        }

        aef = initAEF(nom, q, q0, alphabet, matrice2D, f, taille);

        fclose(fichier);
    }

    return aef;
}

void afficherAEF(t_AEF *aef)
{
    printf("affichage AEF :\n");
    printf("nom : %s", aef->nom);
    printf("alphabet : %s\n", aef->alphabet);
    printf("taille : %d\n", aef->taille);
    printf("q : ");
    for (int i = 0; i < aef->taille; i++)
    {
        printf("%d", aef->q[i]);
    }
    printf("\n");
    printf("q0 : %d\n", aef->q0);
    printf("f : ");
    for (int i = 0; i < 2; i++)
    {
        printf("%d ", aef->f[i]);
    }
    printf("\n");
    printf("matrice2D: \n");
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            printf("%d ", aef->matriceTransition[i][j]);
        }
        printf("\n");
    }
}