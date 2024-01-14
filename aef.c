#include "aef.h"

// fonction pour creer la matrice de transition
int ***creerMatrice3D(int lignes, int colonnes, int x)
{
    // Allouer de la mémoire et copier les valeurs
    int ***matrice = (int ***)malloc(lignes * sizeof(int **));

    for (int i = 0; i < lignes; i++)
    {
        matrice[i] = (int **)malloc(colonnes * sizeof(int *));
        for (int j = 0; j < colonnes; j++)
        {
            matrice[i][j] = (int *)malloc(sizeof(int));
            matrice[i][j][0] = x;
        }
    }

    return matrice;
}

// fonction pour creer la matrice du nombre d'elements de la matrice de transition
int **creerMatrice2D(int lignes, int colonnes, int x)
{
    // Allouer de la mémoire et copier les valeurs
    int **matrice = (int **)malloc(lignes * sizeof(int *));

    for (int i = 0; i < lignes; i++)
    {
        matrice[i] = (int *)malloc(colonnes * sizeof(int));
        for (int j = 0; j < colonnes; j++)
        {
            matrice[i][j] = x;
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
t_AEF *initAEF(char *nom, int *q, int *q0, int nbq0, char *alphabet, int ***matriceTransition, int *f, int taille, int **nbElementsMatriceTransition, int nbF)
{
    t_AEF *aef = (t_AEF *)malloc(sizeof(t_AEF));

    aef->nom = (char *)malloc(strlen(nom) + 1);
    strcpy(aef->nom, nom);

    aef->alphabet = (char *)malloc(strlen(alphabet) + 1);
    strcpy(aef->alphabet, alphabet);

    aef->nbElementsMatriceTransition = nbElementsMatriceTransition;
    aef->q = q;
    aef->q0 = q0;
    aef->nbq0 = nbq0;
    aef->etat = aef->q0[0];
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
    free(aef->nbElementsMatriceTransition);

    free(aef->q);
    free(aef->f);

    free(aef->alphabet);
    free(aef->q0);

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
    if (getIndex(aef->alphabet, entree) == -1)
    {
        printf("%c caractere non inclus dans l'alphabet\n", entree);
    }
    if (aef->nbElementsMatriceTransition[aef->etat][getIndex(aef->alphabet, entree)] != 1)
    {
        printf("transition non determine %d, %c\n", aef->etat, entree);
    }

    if (getIndex(aef->alphabet, entree) != -1)
    {
        if (aef->matriceTransition[aef->etat][getIndex(aef->alphabet, entree)][0] != -1)
        {
            printf("transition de %d(%c) ->", aef->etat, entree);
            aef->etat = aef->matriceTransition[aef->etat][getIndex(aef->alphabet, entree)][0];
            printf(" %d\n", aef->etat);
        }
        else
        {
            printf("transition non definit %d, %c\n", aef->etat, entree);
        }
    }
}

// fonction pour charger un AEF depuis un fichier
t_AEF *lireFichier(char *dir)
{
    t_AEF *aef = NULL;
    int taille = 1;
    int *q = NULL;
    int *q0 = NULL;
    char alphabet[100] = "";
    int *f = NULL;
    char nom[100] = "";
    int ***matrice3D = NULL;
    int **matrice2D = NULL;
    int nbF = 1;
    int nbq0 = 1;

    FILE *fichier = fopen(dir, "r");

    if (fichier != NULL)
    {
        char chaine[100] = "";

        // Lecture des valeurs du fichier
        fscanf(fichier, "%s", nom);
        fscanf(fichier, "%s", alphabet);
        fscanf(fichier, "%d", &taille);
        q = creerTableauQ(taille);

        fgets(chaine, sizeof(chaine), fichier); // ligne vide

        q0 = (int *)malloc(taille * sizeof(int));
        int compteur = 0;
        fgets(chaine, sizeof(chaine), fichier);
        char *token = strtok(chaine, " ");
        while (token != NULL)
        {
            q0[compteur] = atoi(token);
            compteur++;
            token = strtok(NULL, " ");
            q0 = (int *)realloc(q0, (compteur + 1) * sizeof(int));
        }
        int nbq0 = compteur;

        // Allocation et lecture du tableau f
        f = (int *)malloc(taille * sizeof(int));
        compteur = 0;
        fgets(chaine, sizeof(chaine), fichier);
        token = strtok(chaine, " ");
        while (token != NULL)
        {
            f[compteur] = atoi(token);
            compteur++;
            f = (int *)realloc(f, (compteur + 1) * sizeof(int));
            token = strtok(NULL, " ");
        }
        nbF = compteur;

        // Allocation et initialisation de la matrice2D
        matrice2D = creerMatrice2D(taille, strlen(alphabet), 1);

        for (int i = 0; i < taille; i++)
        {
            for (int j = 0; j < strlen(alphabet); j++)
            {
                matrice2D[i][j] = 1;
            }
        }

        int x0 = 0;
        int x1 = 0;
        char c = 'c';
        matrice3D = (int ***)creerMatrice3D(taille, strlen(alphabet), -1);

        // Lecture de la suite du fichier et construction de matrice3D
        while (fgets(chaine, sizeof(chaine), fichier) != NULL)
        {
            sscanf(chaine, "%d %c %d", &x0, &c, &x1);
            int index = getIndex(alphabet, c);

            if (matrice2D[x0][index] == 1 && matrice3D[x0][index][0] == -1)
            {
                matrice3D[x0][index][0] = x1;
            }
            else if (matrice2D[x0][index] >= 1 && matrice3D[x0][index][0] != -1 && contient(matrice3D[x0][index], matrice2D[x0][index], x1) != 1)
            {
                matrice2D[x0][index] += 1;
                matrice3D[x0][index] = (int *)realloc(matrice3D[x0][index], matrice2D[x0][index] * sizeof(int));
                matrice3D[x0][index][matrice2D[x0][index] - 1] = x1;
            }
        }

        for (int i = 0; i < taille; i++)
        {
            for (int j = 0; j < strlen(alphabet); j++)
            {
                matrice3D[i][j] = (int *)supprimerDoublons(&matrice3D[i][j][0], &matrice2D[i][j]);
                // matrice3D[i][j] = (int *)supprimerValeur(&matrice3D[i][j][0], &matrice2D[i][j], 0);
                trierOrdreCroissant(&matrice3D[i][j][0], &matrice2D[i][j]);
            }
        }

        aef = initAEF(nom, q, q0, nbq0, alphabet, matrice3D, f, taille, matrice2D, nbF);

        for (int i = 0; i < aef->nbq0; i++)
        {
            aef->q0 = (int *)supprimerDoublons(aef->q0, &(aef->nbq0));
            trierOrdreCroissant(aef->q0, &(aef->nbq0));
        }

        for (int i = 0; i < aef->nbF; i++)
        {
            aef->f = (int *)supprimerDoublons(aef->f, &(aef->nbF));
            trierOrdreCroissant(aef->f, &(aef->nbF));
        }

        fclose(fichier);
    }
    else
    {
        printf("Fichier non trouvé\n");
    }

    return aef;
}

// fonction pour afficher toute les caracteristiques d'un AEF
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
    printf("nbq0 : %d\n", aef->nbq0);
    printf("q0 : ");
    for (int i = 0; i < aef->nbq0; i++)
    {
        printf("%d ", aef->q0[i]);
    }
    printf("\nnbF : %d\n", aef->nbF);
    printf("f : ");
    for (int i = 0; i < aef->nbF; i++)
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

// fonction pour creer un AEF
t_AEF *saisirAEF() // bug
{
    int taille = 1;
    int *q = NULL;
    int *q0 = NULL;
    char alphabet[100] = "";
    int *f = NULL;
    char nom[100] = "";
    int ***matrice3D = NULL;
    int **matrice2D = NULL;
    int nbq0 = 0;
    int nbF = 0;

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

    printf("combien d'etat initiaux ?\n");
    fflush(stdin);
    scanf("%d", &nbq0);
    q0 = (int *)malloc(nbq0 * sizeof(int));
    printf("q : \n");
    for (int i = 0; i < nbq0; i++)
    {
        printf("entrer q0[%d]\n", i);
        fflush(stdin);
        scanf("%d", &q0[i]);
    }

    printf("combien d'etat finaux ?\n");
    fflush(stdin);
    scanf("%d", &nbF);
    f = (int *)malloc(nbF * sizeof(int));
    printf("f : \n");
    for (int i = 0; i < nbF; i++)
    {
        printf("entrer f[%d]\n", i);
        fflush(stdin);
        scanf("%d", &f[i]);
    }

    printf("\n");

    matrice3D = (int ***)creerMatrice3D(taille, strlen(alphabet), -1);
    matrice2D = (int **)creerMatrice2D(taille, strlen(alphabet), 1);

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

    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < strlen(alphabet); j++)
        {
            matrice3D[i][j] = (int *)supprimerDoublons(&matrice3D[i][j][0], &matrice2D[i][j]);
            trierOrdreCroissant(&matrice3D[i][j][0], &matrice2D[i][j]);
        }
    }

    t_AEF *aef = initAEF(nom, q, q0, nbq0, alphabet, matrice3D, f, taille, matrice2D, nbF);

    for (int i = 0; i < aef->nbq0; i++)
    {
        aef->q0 = (int *)supprimerDoublons(aef->q0, &(aef->nbq0));
        trierOrdreCroissant(aef->q0, &(aef->nbq0));
    }

    for (int i = 0; i < aef->nbF; i++)
    {
        aef->f = (int *)supprimerDoublons(aef->f, &(aef->nbF));
        trierOrdreCroissant(aef->f, &(aef->nbF));
    }

    return aef;
}

// fonction pour enregistrer un AEF dans un fichier
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
    for (int i = 0; i < aef->nbq0; i++)
    {
        fprintf(save_file, "%d ", aef->q0[i]);
    }
    fprintf(save_file, "\n");
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

// fonction pour supprimer tout les AEF chargé dans le menu
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
}

// fonction pour reconnaitre un mot par un automate
int reconnaitreMot(t_AEF *aef, char *mot)
{
    for (int i = 0; i < strlen(mot); i++)
    {
        transition(aef, mot[i]);
    }
    for (int j = 0; j < strlen(aef->alphabet); j++)
    {
        if (aef->etat == aef->f[j])
        {
            return 1;
        }
    }
    return 0;
}

// fonction pour reconnaitre si un automate est complet
int verifAutomateComplet(t_AEF *aef)
{

    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            for (int k = 0; k < aef->nbElementsMatriceTransition[i][j]; k++)
            {
                if (aef->matriceTransition[i][j][k] == -1)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

// fonction pour transformer un automate complet
t_AEF *transformerAutomateComplet(t_AEF *aef)
{
    int taille = aef->taille + 1;

    int *q = creerTableauQ(taille);

    int *q0 = (int *)malloc(aef->nbq0 * sizeof(int));
    memcpy(q0, aef->q0, aef->nbq0 * sizeof(int));

    int nbq0 = aef->nbq0;

    char *alphabet = (char *)malloc(strlen(aef->alphabet));
    strcpy(alphabet, aef->alphabet);

    int *f = (int *)malloc(sizeof(int));
    memcpy(f, aef->f, aef->nbF * sizeof(int));

    char nom[100] = "automate_transformer_complet";

    int **matrice2D = creerMatrice2D(taille, strlen(aef->alphabet), 1);
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            matrice2D[i][j] = aef->nbElementsMatriceTransition[i][j];
        }
    }

    int ***matrice3D = creerMatrice3D(taille, strlen(aef->alphabet), -1);
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            for (int k = 0; k < aef->nbElementsMatriceTransition[i][j]; k++)
            {
                matrice3D[i][j] = (int *)realloc(matrice3D[i][j], aef->nbElementsMatriceTransition[i][j] * sizeof(int));
                matrice3D[i][j][k] = aef->matriceTransition[i][j][k];
            }
        }
    }

    int nbF = aef->nbF;

    t_AEF *aef_comp = initAEF(nom, q, q0, nbq0, alphabet, matrice3D, f, taille, matrice2D, nbF);

    for (int i = 0; i < aef_comp->taille; i++)
    {
        for (int j = 0; j < strlen(aef_comp->alphabet); j++)
        {
            if (aef_comp->matriceTransition[i][j][0] == -1)
            {
                aef_comp->matriceTransition[i][j][0] = aef->taille;
            }
        }
    }

    return aef_comp;
}

// fonction pour verifier si un AEF est deterministe
int verifAutomateDeterministe(t_AEF *aef)
{
    if (aef->nbq0 > 1)
    {
        return 0;
    }
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            if (aef->nbElementsMatriceTransition[i][j] > 1)
            {
                return 0;
            }
        }
    }
    return 1;
}

// fonction pour transformer un AEF deterministe
t_AEF *transformerAutomateDeterministe(t_AEF *aef)
{
    t_AEF *aef_det = NULL;
    int taille = pow(2, aef->taille);

    int *q = creerTableauQ(taille);

    int *q0 = (int *)malloc(aef->nbq0 * sizeof(int));
    memcpy(q0, aef->q0, aef->nbq0 * sizeof(int));
    for (int i = 0; i < aef->nbq0; i++)
    {
        q0[i]++;
    }

    int nbq0 = aef->nbq0;

    char *alphabet = (char *)malloc(strlen(aef->alphabet));
    strcpy(alphabet, aef->alphabet);

    int *f = (int *)malloc(sizeof(int));

    char nom[100] = "automate_transforme_deterministe";

    int **matrice2D = creerMatrice2D(taille, strlen(aef->alphabet), 1);
    int ***matrice3D = creerMatrice3D(taille, strlen(aef->alphabet), 0);

    int nbF = 1;

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
        int nbComb = factoriel(aef->taille) / (factoriel(p) * factoriel(aef->taille - p));

        int **result = combinaisons_v2(p, aef->q, aef->taille, nbComb);

        for (int i = 0; i < nbComb; i++)
        {
            for (int j = 0; j < p; j++)
            {
                result[i][j] = result[i][j] + 1;
            }
        }

        for (int i = 0; i < nbComb; i++)
        {
            for (int j = 0; j < strlen(alphabet); j++)
            {
                int indice = 0;
                for (int k = 0; k < p; k++)
                {
                    // Allouer de l'espace pour les éléments dans la matrice destination
                    int *destination_data = (int *)malloc((matrice2D[index + i][j] + matrice2D[result[i][k]][j]) * sizeof(int));

                    // Copier les éléments existants dans la destination
                    memcpy(destination_data, matrice3D[index + i][j], matrice2D[index + i][j] * sizeof(int));

                    // Copier les éléments de la source à la destination
                    memcpy(destination_data + matrice2D[index + i][j], matrice3D[result[i][k]][j], matrice2D[result[i][k]][j] * sizeof(int));

                    // Mettre à jour la matrice3D et matrice2D pour la destination
                    free(matrice3D[index + i][j]);
                    matrice3D[index + i][j] = destination_data;
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

    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            matrice3D[i][j] = (int *)supprimerDoublons(&matrice3D[i][j][0], &matrice2D[i][j]);
            matrice3D[i][j] = (int *)supprimerValeur(&matrice3D[i][j][0], &matrice2D[i][j], 0);
            trierOrdreCroissant(&matrice3D[i][j][0], &matrice2D[i][j]);
        }
    }

    int ***tabComb = (int ***)creerTabComb(aef->q, aef->taille);

    // copier les tabComb dans la matrice de transition
    for (int i = 0; i < taille; i++) // anomalie
    {
        for (int j = 0; j < strlen(alphabet); j++)
        {
            for (int k = 1; k < taille; k++)
            {
                if (memcmp(matrice3D[i][j], tabComb[k][1], matrice2D[i][j] * sizeof(int)) == 0 && matrice2D[i][j] == tabComb[k][0][0])
                {
                    matrice2D[i][j] = 1;
                    matrice3D[i][j] = (int *)realloc((int *)&matrice3D[i][j][0], sizeof(int));
                    matrice3D[i][j][0] = k;
                }
            }
        }
    }

    for (int i = 1; i < taille; i++)
    {
        // printf("%d {", tabComb[i][0][0]);
        for (int j = 0; j < tabComb[i][0][0]; j++)
        {
            if (contient(aef->f, nbF, tabComb[i][1][j] - 1) == 1)
            {
                // printf("i == %d %d est inclus dans ", i, tabComb[i][1][j]);
                f[nbF - 1] = i;
                nbF = nbF + 1;
                f = (int *)realloc(f, nbF * sizeof(int));
                // printf("%d ", tabComb[i][1][j]);
                break;
            }
        }
        // printf("} \n");
    }

    printf("\n");
    for (int i = 0; i < taille; i++)
    {
        printf("i=%d, card=%d, ", i, tabComb[i][0][0]);
        if (memcmp(tabComb[i][1], q0, nbq0 * sizeof(int)) == 0)
        {
            nbq0 = 1;
            q0[0] = i;
            q0 = (int *)realloc(q0, sizeof(int));
        }
        for (int k = 0; k < tabComb[i][0][0]; k++)
        {
            printf("%d ", tabComb[i][1][k]);
        }
        printf("\n");
    }
    printf("\n");

    aef_det = initAEF(nom, q, q0, nbq0, alphabet, matrice3D, f, taille, matrice2D, nbF - 1);

    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            free(tabComb[i][j]);
        }
        free(tabComb[i]);
    }
    free(tabComb);

    return aef_det;
}

// fonction pour creer un tableau de combinaison
int ***creerTabComb(int *tab, int lignes)
{
    int ***tabComb = creerMatrice3D(pow(2, lignes), 2, 0);

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

// fonction pour calculer une factoriel
int factoriel(int n)
{
    int x = 1;
    for (int i = 1; i < n; i++)
    {
        x = x * (i + 1);
    }
    return x;
}

// fonction pour creer comb_count p_uplet
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

// fonction pour detecter une valeur et renvoi sa position
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

// fonction pour supprimer des doublons dans une liste
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

// fonction pour supprimer une valeur
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

// fonction pour trier par ordre croissant un tableau
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

// fonction pour transformer une matrice de transition en matrice d'adjacence
int **matriceTransition2MatriceAdjacence(int ***matriceTransition, int **matriceNbElement, int ligne, int colonnes, char *alphabet)
{
    int **matriceAdjacence = creerMatrice2D(ligne, ligne, 0); // Initialisez à 0

    for (int i = 0; i < ligne; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
            for (int k = 0; k < matriceNbElement[i][j]; k++)
            {
                int transitionDest = matriceTransition[i][j][k];
                matriceAdjacence[i][transitionDest] = alphabet[j];
            }
        }
    }
    return matriceAdjacence;
}

// fonction pour parcourir un graphe en DFS
int DFS(int i, int *visited, int **G, int nbSommet, int dest)
{
    if (i == dest)
    {
        return 1;
    }

    // printf("%d ", i);
    visited[i] = 1;

    for (int j = 0; j < nbSommet; j++)
    {
        if (!visited[j] && G[i][j] > 0)
        {
            if (DFS(j, visited, G, nbSommet, dest))
            {
                return 1;
            }
        }
    }

    return 0;
}

// fonction pour supprimer une ligne d'un tableau
void supprimerLigne(int **matrice2D, int *lignes, int colonnes, int indexDelete)
{
    if (indexDelete < 0 || indexDelete >= *lignes)
    {
        printf("L'indice de la ligne à supprimer est invalide.\n");
        return;
    }

    // Décaler les lignes vers le haut pour remplir la ligne supprimée
    for (int i = indexDelete; i < *lignes - 1; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
            matrice2D[i][j] = matrice2D[i + 1][j];
        }
    }

    // Réduire le nombre de lignes
    (*lignes)--;
}

void supprimerDansMatriceTransition(t_AEF *aef, int val)
{
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            aef->matriceTransition[i][j] = (int *)supprimerValeur(aef->matriceTransition[i][j], &(aef->nbElementsMatriceTransition[i][j]), val);
        }
    }
}

t_AEF *transformerAutomateEmonde(t_AEF *aef)
{
    int taille = aef->taille;

    int *q = creerTableauQ(aef->taille);

    int *q0 = (int *)malloc(aef->nbq0 * sizeof(int));
    memcpy(q0, aef->q0, aef->nbq0 * sizeof(int));

    int nbq0 = aef->nbq0;

    char *alphabet = (char *)malloc(strlen(aef->alphabet));
    strcpy(alphabet, aef->alphabet);

    int *f = (int *)malloc(aef->nbF * sizeof(int));
    memcpy(f, aef->f, aef->nbF * sizeof(int));

    char nom[100] = "automate_transformer_emonder";

    int **matrice2D = creerMatrice2D(taille, strlen(aef->alphabet), 1);
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            matrice2D[i][j] = aef->nbElementsMatriceTransition[i][j];
        }
    }

    int ***matrice3D = creerMatrice3D(taille, strlen(aef->alphabet), 0); // verifier 0
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            for (int k = 0; k < aef->nbElementsMatriceTransition[i][j]; k++)
            {
                matrice3D[i][j] = (int *)realloc(matrice3D[i][j], aef->nbElementsMatriceTransition[i][j] * sizeof(int));
                matrice3D[i][j][k] = aef->matriceTransition[i][j][k];
            }
        }
    }

    int nbF = aef->nbF;

    t_AEF *aef_em = initAEF(nom, q, q0, nbq0, alphabet, matrice3D, f, taille, matrice2D, nbF);

    int **matriceAdjacence = matriceTransition2MatriceAdjacence(aef->matriceTransition, aef->nbElementsMatriceTransition, aef->taille, strlen(aef->alphabet), aef->alphabet);

    printf(" etat accessible: \n");
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < aef->nbq0; j++)
        {
            int *visited = calloc(aef->taille, sizeof(int));
            printf("on cherche un chemin de %d a %d: ", aef->q0[j], aef->q[i]);
            int isAccessible = DFS(0, visited, matriceAdjacence, aef->taille, aef->q[i]);
            if (isAccessible == 0)
            {
                supprimerDansMatriceTransition(aef_em, i);
                for (int k = 0; k < strlen(aef_em->alphabet); k++)
                {
                    aef_em->nbElementsMatriceTransition[i][k] = 1;
                    aef_em->matriceTransition[i][k] = (int *)realloc(aef_em->matriceTransition[i][k], sizeof(int));
                    aef_em->matriceTransition[i][k][0] = -1;
                }
            }
            printf("{%d}\n", isAccessible);
            free(visited);
        }
    }

    printf(" etat co-accessible: \n");
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < aef->nbF; j++)
        {
            int *visited = calloc(aef->taille, sizeof(int));
            printf("on cherche un chemin de %d a %d: ", aef->q[i], aef->f[j]);
            int isCoAccessible = DFS(aef->q[i], visited, matriceAdjacence, aef->taille, aef->f[j]);
            if (isCoAccessible == 0)
            {
                supprimerDansMatriceTransition(aef_em, i);
                for (int k = 0; k < strlen(aef_em->alphabet); k++)
                {
                    aef_em->nbElementsMatriceTransition[i][k] = 1;
                    aef_em->matriceTransition[i][k] = (int *)realloc(aef_em->matriceTransition[i][k], sizeof(int));
                    aef_em->matriceTransition[i][k][0] = -1;
                }
            }
            printf("{%d}\n", isCoAccessible);
            free(visited);
        }
    }

    for (int i = 0; i < aef->taille; i++)
    {
        free(matriceAdjacence[i]);
    }
    free(matriceAdjacence);

    return aef_em;
}

t_AEF *complementaireAEF(t_AEF *aef)
{
    int taille = aef->taille;

    int *q = creerTableauQ(aef->taille);

    int nbq0 = aef->nbF;

    int *q0 = (int *)malloc(aef->nbF * sizeof(int));
    memcpy(q0, aef->f, aef->nbF * sizeof(int));

    char *alphabet = (char *)malloc(strlen(aef->alphabet));
    strcpy(alphabet, aef->alphabet);

    int nbF = aef->nbq0;

    int *f = (int *)malloc(aef->nbq0 * sizeof(int));
    memcpy(f, aef->q0, aef->nbq0 * sizeof(int));

    char nom[100] = "automate_transformer_complementaire";

    int **matrice2D = creerMatrice2D(taille, strlen(aef->alphabet), 1);
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            matrice2D[i][j] = aef->nbElementsMatriceTransition[i][j];
        }
    }

    int ***matrice3D = creerMatrice3D(taille, strlen(aef->alphabet), 0); // verifier 0
    for (int i = 0; i < aef->taille; i++)
    {
        for (int j = 0; j < strlen(aef->alphabet); j++)
        {
            for (int k = 0; k < aef->nbElementsMatriceTransition[i][j]; k++)
            {
                matrice3D[i][j] = (int *)realloc(matrice3D[i][j], aef->nbElementsMatriceTransition[i][j] * sizeof(int));
                matrice3D[i][j][k] = aef->matriceTransition[i][j][k];
            }
        }
    }

    t_AEF *aef_comp = initAEF(nom, q, q0, nbq0, alphabet, matrice3D, f, taille, matrice2D, nbF);

    return aef_comp;
}