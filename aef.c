#include "aef.h"

// fonction pour creer la matrice de transition
int ***creerMatrice3D(int lignes, int colonnes)
{
    // Allouer de la mémoire et copier les valeurs
    int ***matrice = (int ***)calloc(lignes, sizeof(int **));

    for (int i = 0; i < lignes; i++)
    {
        matrice[i] = (int **)calloc(colonnes, sizeof(int *));
    }

    // mettre toute les valeurs de la matrice a -1
    for (int i = 0; i < lignes; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
            matrice[i][j] = (int *)calloc(1, sizeof(int));
            matrice[i][j][0] = -1;
        }
    }

    return matrice;
}

int **creerMatrice2D(int lignes, int colonnes)
{
    // Allouer de la mémoire et copier les valeurs
    int **matrice = (int **)calloc(lignes, sizeof(int *));

    for (int i = 0; i < lignes; i++)
    {
        matrice[i] = (int *)calloc(colonnes, sizeof(int));
        for (int j = 0; j < colonnes; j++)
        {
            matrice[i][j] = 1;
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
t_AEF *initAEF(char *nom, int *q, int q0, char *alphabet, int ***matriceTransition, int *f, int taille, int **nbElementsMatriceTransition, int nbF)
{
    t_AEF *aef = (t_AEF *)malloc(sizeof(t_AEF));

    aef->nom = (char *)malloc(strlen(nom) + 1);
    strcpy(aef->nom, nom);

    aef->alphabet = (char *)malloc(strlen(alphabet) + 1);
    strcpy(aef->alphabet, alphabet);

    aef->nbElementsMatriceTransition = nbElementsMatriceTransition;
    aef->q = q;
    aef->q0 = q0;
    aef->etat = aef->q0;
    aef->f = f;
    aef->taille = taille;
    aef->matriceTransition = matriceTransition;
    aef->nbF = nbF;

    return aef;
}

// fonction pour supprimer un aef
void suppAEF(t_AEF *aef)
{
    // Libération de la mémoire
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < aef->taille; j++)
        {
            free(aef->matriceTransition[i][j]);
        }
        free(aef->matriceTransition[i]);
    }
    free(aef->matriceTransition);

    for (int i = 0; i < aef->taille; i++)
    {
        free(aef->nbElementsMatriceTransition[i]);
    }
    free(aef->matriceTransition);

    free(aef->q);
    free(aef->f);

    free(aef->alphabet);

    free(aef);
}

// fonction pour obtenir l'indice d'un caractere
int getIndex(char *alphabet, char entree)
{
    int index = 0;
    for (int i = 0; i < strlen(alphabet); i++)
    {
        if (entree == alphabet[i])
        {
            return i;
        }
    }
    return -1; // n'a rien trouvé ou plusieurs valeurs sont renvoyés (automate non deterministe)
}

// fonction pour faire des transitions
int transition(t_AEF *aef, char entree)
{
    if (sizeof(aef->nbElementsMatriceTransition[aef->etat][getIndex(aef->alphabet, entree)]) != 1)
    {
        printf("automate non deterministe %d, %c\n", aef->etat, entree);
        return 1;
    }
    if (getIndex(aef->alphabet, entree) != -1)
    {
        if (aef->matriceTransition[aef->etat][getIndex(aef->alphabet, entree)][0] != -1)
        {

            aef->etat = aef->matriceTransition[aef->etat][getIndex(aef->alphabet, entree)][0];

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

t_AEF *lireFichier(char *dir)
{
    t_AEF *aef = NULL;
    int taille = 1;
    int *q = NULL;
    int q0 = 0;
    char alphabet[100] = "";
    int *f = NULL;
    char nom[100] = "";
    int ***matrice3D = NULL;
    int **matrice2D = NULL;
    int nbF = 1;

    // chercher tout les fichiers
    FILE *fichier = fopen(dir, "r");

    if (fichier != NULL)
    {
        char chaine[100] = "";

        fscanf(fichier, "%s", nom);

        // on stocke les valeurs du fichier dans un tableau
        fscanf(fichier, "%s", alphabet);

        fscanf(fichier, "%d", &taille);

        int *q = creerTableauQ(taille);

        fscanf(fichier, "%d", &q0);

        // il y a un trou dans le fichier
        fgets(chaine, 100, fichier);

        int *f = malloc(sizeof(int));

        fgets(chaine, 100, fichier);
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
        nbF = compteur - 1;

        matrice2D = creerMatrice2D(taille, strlen(alphabet));

        int x0 = 0;
        int x1 = 0;
        char c = 'c';
        matrice3D = (int ***)creerMatrice3D(taille, strlen(alphabet));

        // probleme a corriger
        while (fgets(chaine, sizeof(chaine), fichier) != NULL)
        {
            sscanf(chaine, "%d %c %d", &x0, &c, &x1);
            // printf("-------------------%d\n", matrice2D[x0][getIndex(alphabet, c)]);
            if (matrice2D[x0][getIndex(alphabet, c)] == 1 && matrice3D[x0][getIndex(alphabet, c)][0] == -1)
            {
                matrice3D[x0][getIndex(alphabet, c)][0] = x1;
            }
            else if (matrice2D[x0][getIndex(alphabet, c)] >= 1 && matrice3D[x0][getIndex(alphabet, c)][0] != -1)
            {
                matrice2D[x0][getIndex(alphabet, c)] += 1;
                realloc(matrice3D[x0][getIndex(alphabet, c)], matrice2D[x0][getIndex(alphabet, c)]);
                matrice3D[x0][getIndex(alphabet, c)][matrice2D[x0][getIndex(alphabet, c)] - 1] = x1;
            }
        }

        aef = initAEF(nom, q, q0, alphabet, matrice3D, f, taille, matrice2D, nbF);

        fclose(fichier);
    }
    else
    {
        printf("fichier non trouve\n");
    }

    return aef;
}

void afficherAEF(t_AEF *aef)
{
    printf("nom : %s\n", aef->nom);
    printf("alphabet : %s\n", aef->alphabet);
    printf("taille : %d\n", aef->taille);
    printf("q : ");
    for (int i = 0; i < aef->taille; i++)
    {
        printf("%d ", aef->q[i]);
    }
    printf("\n");
    printf("q0 : %d\n", aef->q0);
    printf("f : ");
    for (int i = 0; i < 2; i++)
    {
        printf("%d ", aef->f[i]);
    }
    printf("\n");
    printf("matrice de transition: \n");
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            printf("(");
            for (int k = 0; k < aef->nbElementsMatriceTransition[i][j]; k++)
            {
                printf("%d ", aef->matriceTransition[i][j][k]);
            }
            printf(")");
        }
        printf("\n");
    }

    printf("matrice nbElement dans matrice de transition: \n");
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            printf("%d ", aef->nbElementsMatriceTransition[i][j]);
        }
        printf("\n");
    }
}

t_AEF *saisirAEF()
{
    int taille = 1;
    int *q = NULL;
    int q0 = 0;
    char alphabet[100] = "";
    int *f = NULL;
    char nom[100] = "";
    int ***matrice3D = NULL;
    int **matrice2D = NULL;

    printf("entre le nom\n");
    fflush(stdin);
    scanf("%s", nom);

    printf("entrer l'alphabet\n");
    fflush(stdin);
    scanf("%s", alphabet);

    printf("entrer la taille\n");
    fflush(stdin);
    scanf("%d", &taille);

    q = creerTableauQ(taille);

    printf("entrer q0\n");
    fflush(stdin);
    scanf("%d", &q0);

    printf("combien d'etat finaux ?\n");
    int nbF = 0;
    fflush(stdin);
    scanf("%d", &nbF);
    f = (int *)calloc(nbF, sizeof(int));
    printf("f : \n");
    for (int i = 0; i < nbF; i++)
    {
        printf("entrer f[%d]\n", i);
        fflush(stdin);
        scanf("%d", &f[i]);
    }

    printf("\n");
    printf("matrice2D: \n");

    matrice3D = (int ***)creerMatrice3D(taille, strlen(alphabet));
    matrice2D = (int **)creerMatrice2D(taille, strlen(alphabet));

    int x0 = 0;
    int x1 = 0;
    char c = 'c';
    char continuer = 'y';
    do
    {
        printf("entrer votre matrice de transition\n");
        fflush(stdin);
        scanf("%d %c %d", &x0, &c, &x1);
        if (matrice2D[x0][getIndex(alphabet, c)] == 1 && matrice3D[x0][getIndex(alphabet, c)][0] == -1)
        {
            matrice3D[x0][getIndex(alphabet, c)][0] = x1;
        }
        else if (matrice2D[x0][getIndex(alphabet, c)] >= 1 && matrice3D[x0][getIndex(alphabet, c)][0] != -1)
        {
            matrice2D[x0][getIndex(alphabet, c)] += 1;
            realloc(matrice3D[x0][getIndex(alphabet, c)], matrice2D[x0][getIndex(alphabet, c)]);
            matrice3D[x0][getIndex(alphabet, c)][matrice2D[x0][getIndex(alphabet, c)] - 1] = x1;
        }
        printf("voulez vous continuer (o/n)?\n");
        fflush(stdin);
        scanf("%c", &continuer);
    } while (continuer == 'o');
    system("cls");

    t_AEF *aef = initAEF(nom, q, q0, alphabet, matrice3D, f, taille, matrice2D, nbF);
    return aef;
}

void enregistrerAEF(t_AEF *aef)
{
    printf("entrer le nom du fichier .txt\n");
    fflush(stdin);
    char name_file[100] = "";
    scanf("%s", name_file);

    printf("automate enregistre\n");

    FILE *save_file = fopen(name_file, "w");
    fprintf(save_file, "%s\n", aef->nom);
    fprintf(save_file, "%s\n", aef->alphabet);
    fprintf(save_file, "%d\n", aef->taille);
    fprintf(save_file, "%d\n", aef->q0);
    for (int i = 0; i < aef->nbF; i++)
    {
        fprintf(save_file, "%d ", aef->f[i]);
    }
    fprintf(save_file, "\n");
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            for (int k = 0; k < aef->nbElementsMatriceTransition[i][j]; k++)
            {
                if (aef->matriceTransition[i][j][k] != -1)
                {
                    fprintf(save_file, "%d %c %d\n", i, aef->alphabet[j], aef->matriceTransition[i][j][k]);
                }
            }
        }
    }
    fclose(save_file);
}

void supprimerAEF(t_AEF **liste_aef, t_AEF *aef, int *nbAEF)
{
    for (int i = 0; i < *nbAEF; i++)
    {
        if (liste_aef[i] == aef)
        {
            aef = NULL;
            for (int j = i; j < *nbAEF - 1; j++)
            {
                liste_aef[i] = liste_aef[i + 1];
            }
            liste_aef[*nbAEF - 1] = NULL;
            break;
        }
    }
    (*nbAEF)--;
}
