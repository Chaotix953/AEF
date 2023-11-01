#include "aef.h"

// fonction pour creer la matrice de transition
int ***creerMatrice3D(int lignes, int colonnes)
{
    // Allouer de la mémoire et copier les valeurs
    int ***matrice = (int ***)malloc(lignes * sizeof(int **));

    for (int i = 0; i < lignes; i++)
    {
        matrice[i] = (int **)malloc(colonnes * sizeof(int *));
        for (int j = 0; j < colonnes; j++)
        {
            matrice[i][j] = (int *)malloc(sizeof(int));
            matrice[i][j][0] = -1;
        }
    }

    return matrice;
}

int **creerMatrice2D(int lignes, int colonnes)
{
    // Allouer de la mémoire et copier les valeurs
    int **matrice = (int **)malloc(lignes * sizeof(int *));

    for (int i = 0; i < lignes; i++)
    {
        matrice[i] = (int *)malloc(colonnes * sizeof(int));
        for (int j = 0; j < colonnes; j++)
        {
            matrice[i][j] = 0;
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

int detecterOccurence(int *tab, int tailleTab, int val)
{
    for (int i = 0; i < tailleTab; i++)
    {
        if (tab[i] == val)
        {
            return 1;
        }
        return 0;
    }
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
        for (int j = 0; j < strlen(aef->alphabet); j++)
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
void transition(t_AEF *aef, char entree)
{
    if (aef->nbElementsMatriceTransition[aef->etat][getIndex(aef->alphabet, entree)] != 1)
    {
        printf("transition non determine %d, %c\n", aef->etat, entree);
    }
    if (getIndex(aef->alphabet, entree) != -1)
    {
        if (aef->matriceTransition[aef->etat][getIndex(aef->alphabet, entree)][0] != -1)
        {
            aef->etat = aef->matriceTransition[aef->etat][getIndex(aef->alphabet, entree)][0];
        }
        else
        {
            printf("transition non definit %d, %c\n", aef->etat, entree);
        }
    }
    else
    {
        printf("mot non reconnu par l'automate\n");
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
                f = (int *)realloc(f, compteur + 1);
            }
        }
        nbF = compteur - 1;

        matrice2D = creerMatrice2D(taille, strlen(alphabet));
        for (int i = 0; i < taille; i++)
        {
            for (int j = 0; j < strlen(alphabet); j++)
            {
                matrice2D[i][j] = matrice2D[i][j] + 1;
            }
        }

        int x0 = 0;
        int x1 = 0;
        char c = 'c';
        matrice3D = (int ***)creerMatrice3D(taille, strlen(alphabet));

        // probleme a corriger
        while (fgets(chaine, sizeof(chaine), fichier) != NULL)
        {
            sscanf(chaine, "%d %c %d", &x0, &c, &x1);
            if (matrice2D[x0][getIndex(alphabet, c)] == 1 && matrice3D[x0][getIndex(alphabet, c)][0] == -1)
            {
                matrice3D[x0][getIndex(alphabet, c)][0] = x1;
            }
            // regler le pb ligne 217 matrice3D[x0][getIndex(alphabet, c)][matrice2D[x0][getIndex(alphabet, c)] - 2] != x1 qui empeche d'entrer 1 fois la meme valeur
            else if (matrice2D[x0][getIndex(alphabet, c)] >= 1 && matrice3D[x0][getIndex(alphabet, c)][0] != -1 && detecterOccurence((int *)matrice3D[x0][getIndex(alphabet, c)], matrice2D[x0][getIndex(alphabet, c)], x1) != 1)
            {
                matrice2D[x0][getIndex(alphabet, c)] += 1;
                matrice3D[x0][getIndex(alphabet, c)] = (int *)realloc(matrice3D[x0][getIndex(alphabet, c)], matrice2D[x0][getIndex(alphabet, c)]);
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
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < strlen(alphabet); j++)
        {
            matrice2D[i][j] = matrice2D[i][j] + 1;
        }
    }

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
            matrice3D[x0][getIndex(alphabet, c)] = (int *)realloc(matrice3D[x0][getIndex(alphabet, c)], matrice2D[x0][getIndex(alphabet, c)]);
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

int reconnaitreMot(t_AEF *aef, char *mot)
{
    for (int i = 0; i < strlen(mot); i++)
    {
        transition(aef, mot[i]);
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            if (aef->etat == aef->f[j])
            {
                printf("mot reconnu par l'automate\n");
                return 1;
            }
        }
    }
    return 0;
}

int verifAutomateComplet(t_AEF *aef)
{
    if (verifAutomateDeterministe(aef) == 1)
    {
        for (int i = 0; i < aef->taille; i++)
        {
            for (int j = 0; j < strlen(aef->alphabet); j++)
            {
                for (int k = 0; k < aef->nbElementsMatriceTransition[i][j]; k++)
                {
                    if (aef->matriceTransition[i][j][k] == -1)
                    {
                        printf("automate non complet\n");
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

void transformerAutomateComplet(t_AEF *aef)
{
    aef->taille++;

    int ***newMatrice3D = creerMatrice3D(aef->taille, strlen(aef->alphabet));
    for (int i = 0; i < aef->taille - 1; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            for (int k = 0; k < aef->nbElementsMatriceTransition[i][j]; k++)
            {
                newMatrice3D[i][j][k] = aef->matriceTransition[i][j][k];
            }
        }
    }
    for (int i = 0; i < strlen(aef->alphabet); i++)
    {
        newMatrice3D[aef->taille - 1][i][0] = aef->taille - 1;
    }
    aef->matriceTransition = newMatrice3D;

    int **newMatrice2D = creerMatrice2D(aef->taille, strlen(aef->alphabet));
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            newMatrice2D[i][j] = newMatrice2D[i][j] + 1;
        }
    }

    for (int i = 0; i < aef->taille - 1; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            newMatrice2D[i][j] = aef->nbElementsMatriceTransition[i][j];
        }
    }
    for (int i = 0; i < strlen(aef->alphabet); i++)
    {
        newMatrice2D[aef->taille - 1][i] = 1;
    }
    aef->nbElementsMatriceTransition = newMatrice2D;

    aef->q = (int *)realloc(aef->q, aef->taille * sizeof(int));
    aef->q[aef->taille - 1] = aef->taille - 1;
}

int verifAutomateDeterministe(t_AEF *aef)
{
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            if (aef->nbElementsMatriceTransition[i][j] > 1)
            {
                printf("automate non deterministe\n");
                return 0;
            }
        }
    }
    return 1;
}

t_AEF *transformerAutomateDeterministe(t_AEF *aef, int *nbAEF)
{
    (*nbAEF)++;
    t_AEF *aef_det = NULL;
    int taille = pow(2, aef->taille);
    int *q = creerTableauQ(taille);

    int q0 = 0;

    char *alphabet = (char *)malloc(strlen(aef->alphabet) + 1); // +1 pour le caractère nul de fin
    strcpy(alphabet, aef->alphabet);

    int *f = aef->f;
    char nom[100] = "automate_det";

    int **matrice2D = creerMatrice2D(taille, strlen(aef->alphabet));
    int ***matrice3D = creerMatrice3D(taille, strlen(aef->alphabet));

    for (int i = 0; i < strlen(alphabet); i++)
    {
        matrice2D[0][i] = 1;
        matrice3D[0][i][0] = 0;
    }

    int nbF = aef->nbF;

    // Copie des premières lignes de la matrice de transition dans matrice3D
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            matrice2D[i + 1][j] = aef->nbElementsMatriceTransition[i][j];
            matrice3D[i + 1][j] = (int *)realloc(matrice3D[i + 1][j], matrice2D[i + 1][j] * sizeof(int));
            memcpy(matrice3D[i + 1][j], aef->matriceTransition[i][j], aef->nbElementsMatriceTransition[i][j] * sizeof(int));
            for (int k = 0; k < matrice2D[i + 1][j]; k++)
            {
                matrice3D[i + 1][j][k] += 1;
            }
        }
    }

    int index = aef->taille + 1;

    for (int p = 2; p < aef->taille + 1; p++)
    {
        int nbComb = factoriel(aef->taille) / (factoriel(p) * factoriel(strlen(aef->alphabet) - p));

        int **result = combinaisons_v2(p, aef->q, aef->taille, nbComb);

        // Incrémentation des valeurs de matrice3D de +1
        for (int i = 0; i < nbComb; i++)
        {
            for (int j = 0; j < p; j++)
            {
                result[i][j] += 1;
            }
        }

        for (int i = 0; i < nbComb; i++)
        {
            for (int j = 0; j < strlen(alphabet); j++)
            {
                int indice = 0;
                for (int k = 0; k < p; k++)
                {
                    memcpy(&matrice3D[index + i][j][indice], matrice3D[result[i][k]][j], matrice2D[result[i][k]][j] * sizeof(int));
                    indice += matrice2D[result[i][k]][j];
                    matrice2D[index + i][j] += matrice2D[result[i][k]][j];
                }
            }
        }

        index += nbComb;

        for (int i = 0; i < nbComb; i++)
        {
            free(result[i]);
        }
        free(result);
    }

    for (int i = 1; i < taille; i++) // anomalie
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            matrice3D[i][j] = (int *)supprimerValeur(&matrice3D[i][j][0], &matrice2D[i][j], 0);
            matrice3D[i][j] = (int *)supprimerDoublons(&matrice3D[i][j][0], &matrice2D[i][j]);
            trierOrdreCroissant(&matrice3D[i][j][0], &matrice2D[i][j]);
        }
    }

    int ***tabComb = (int ***)creerTabComb(aef->q, aef->taille);

    for (int i = 0; i < taille; i++)
    {
        printf("%d {", tabComb[i][0][0]);
        for (int j = 0; j < tabComb[i][0][0]; j++)
        {
            printf("%d ", tabComb[i][1][j]);
        }
        printf("} \n");
    }

    for (int i = 0; i < taille; i++) // anomalie
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            for (int k = 1; k < taille; k++)
            {
                if (memcmp(matrice3D[i][j], tabComb[k][1], matrice2D[i][j] * sizeof(int)) == 0 && matrice2D[i][j] == tabComb[k][0][0])
                {
                    // printf("k = %d, cmp == %d\n", k, memcmp(&matrice3D[4][0][0], &tabComb[k][1][0], matrice2D[i][j] * sizeof(int)));
                    matrice2D[i][j] = 1;
                    matrice3D[i][j] = (int *)realloc((int *)&matrice3D[i][j][0], sizeof(int));
                    matrice3D[i][j][0] = k;
                }
            }
        }
    }

    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            free(tabComb[i][j]);
        }
        free(tabComb[i]);
    }
    free(tabComb);

    aef_det = initAEF(nom, q, q0, alphabet, matrice3D, f, taille, matrice2D, nbF);

    return aef_det;
}

int ***creerTabComb(int *tab, int lignes)
{
    int ***tabComb = creerMatrice3D(pow(2, lignes), 2);

    int index = 0;

    for (int p = 0; p <= lignes; p++)
    {
        int comb_count = factoriel(lignes) / (factoriel(p) * factoriel(lignes - p));

        int **result = combinaisons_v2(p, tab, lignes, comb_count);

        for (int j = 0; j < comb_count; j++)
        {
            if (index == 0)
            {
                tabComb[index][0][0] = 1;
                tabComb[index][1][0] = 0;
            }
            else
            {
                tabComb[index][0][0] = p;
                tabComb[index][1] = (int *)realloc(&tabComb[index][1][0], p * sizeof(int));
                memcpy(tabComb[index][1], result[j], p * sizeof(int));
            }
            index++;
        }

        for (int i = 0; i < comb_count; i++)
        {
            free(result[i]);
        }
        free(result);
    }

    for (int i = 1; i < pow(2, lignes); i++)
    {
        for (int j = 0; j < tabComb[i][0][0]; j++)
        {
            tabComb[i][1][j] = tabComb[i][1][j] + 1;
        }
    }

    return tabComb;
}

int factoriel(int n)
{
    int x = 1;
    for (int i = 1; i < n; i++)
    {
        x = x * (i + 1);
    }
    return x;
}

int **combinaisons_v2(int p, int *e, int n, int comb_count)
{
    int *indices = NULL; // Tableau pour stocker les indices

    // Allouer de la mémoire pour la liste_combinaisons
    int **liste_combinaisons = (int **)malloc(comb_count * sizeof(int *));

    // Allouer de la mémoire pour les indices
    indices = (int *)malloc(sizeof(int) * p);

    // Initialiser les indices avec les premiers p indices
    for (int i = 0; i < p; i++)
    {
        indices[i] = i;
    }

    int comb_index = 0; // Index pour suivre les combinaisons générées

    // Générer et stocker la première combinaison
    liste_combinaisons[comb_index] = (int *)malloc(sizeof(int) * p);
    for (int i = 0; i < p; i++)
    {
        liste_combinaisons[comb_index][i] = e[indices[i]];
    }
    comb_index++;

    if (p == n)
    {
        return liste_combinaisons;
    }

    int i = p - 1;

    while (i != -1)
    {
        indices[i] += 1;

        for (int j = i + 1; j < p; j++)
        {
            indices[j] = indices[j - 1] + 1;
        }

        if (indices[i] == (n - p + i))
        {
            i = i - 1;
        }
        else
        {
            i = p - 1;
        }

        // Générer et stocker la combinaison actuelle
        liste_combinaisons[comb_index] = (int *)malloc(sizeof(int) * p);
        for (int k = 0; k < p; k++)
        {
            liste_combinaisons[comb_index][k] = e[indices[k]];
        }
        comb_index++;
    }

    free(indices); // Libérer la mémoire allouée pour les indices

    return liste_combinaisons;
}

int contient(int *tab, int taille, int valeur)
{
    for (int i = 0; i < taille; i++)
    {
        if (tab[i] == valeur)
        {
            return 1; // Le tableau contient la valeur
        }
    }
    return 0; // Le tableau ne contient pas la valeur
}

int *supprimerDoublons(int *tab, int *taille)
{
    if (*taille == 1)
    {
        return tab;
    }

    int newSize = 0;
    int *result = (int *)malloc(*taille * sizeof(int));

    for (int i = 0; i < *taille; i++)
    {
        if (!contient(result, newSize, tab[i]))
        {
            result[newSize] = tab[i];
            newSize++;
        }
    }

    *taille = newSize; // Met à jour la taille du tableau
    result = (int *)realloc(result, *taille * sizeof(int));

    return result;
}

int *supprimerValeur(int *tab, int *taille, int valeur)
{
    if (*taille == 1)
    {
        return tab;
    }

    int newSize = 0;
    int *result = (int *)malloc(*taille * sizeof(int));

    for (int i = 0; i < *taille; i++)
    {
        if (tab[i] != valeur)
        {
            result[newSize] = tab[i];
            newSize++;
        }
    }

    *taille = newSize;
    result = (int *)realloc(result, *taille * sizeof(int));

    return result;
}

void trierOrdreCroissant(int *tab, int *taille)
{
    for (int i = 0; i < *taille - 1; i++)
    {
        for (int j = 0; j < *taille - i - 1; j++)
        {
            if (tab[j] > tab[j + 1])
            {
                int tmp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = tmp;
            }
        }
    }
}
