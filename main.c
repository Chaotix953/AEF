#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aef.h"
#include "menu.h"
#include <conio.h> // Pour utiliser _getch()
#include <windows.h>

// fonction principale
int main()
{
    // initialiser les variables avec un fichier texte
    // int taille = 4;
    // int *q = creerTableauQ(taille);
    // char entre[] = "BAAB";
    // char alphabet[] = "AB";
    // int f[] = {2, 3};
    // char nom[] = "automate 1";
    // int q0 = 0;

    int choix = 1;
    t_AEF **liste_aef = (t_AEF **)malloc(5 * sizeof(t_AEF *));
    int nbAEF = 0;
    while (1)
    {
        afficherMenu(choix, nbAEF, liste_aef);
        int key = _getch(); // Attend une touche du clavier

        switch (key)
        {
        case 72: // Flèche haut
            choix = (choix > 1) ? choix - 1 : 20;
            break;
        case 80: // Flèche bas
            choix = (choix < 20) ? choix + 1 : 1;
            break;
        case 13: // Touche Entrée
            if (choix == 1)
            {
                system("cls");
                nbAEF++;
                liste_aef = (t_AEF **)realloc(liste_aef, nbAEF * sizeof(t_AEF *));
                liste_aef[nbAEF - 1] = (t_AEF *)malloc(sizeof(t_AEF));
                liste_aef[nbAEF - 1] = saisirAEF();
                afficherAEF(liste_aef[nbAEF - 1]);
                system("pause");
            }
            else if (choix == 2)
            {
                system("cls");
                printf("entrer le nom du fichier .txt a importer\n");
                fflush(stdin);
                char dir[100] = "";
                scanf("%s", &dir);
                nbAEF++;
                liste_aef = (t_AEF **)realloc(liste_aef, nbAEF * sizeof(t_AEF *));
                liste_aef[nbAEF - 1] = (t_AEF *)malloc(sizeof(t_AEF));
                liste_aef[nbAEF - 1] = lireFichier(dir);
                if (liste_aef[nbAEF - 1] == NULL)
                {
                    printf("fichier non trouvé\n");
                }
                afficherAEF(liste_aef[nbAEF - 1]);
                system("pause");
            }
            else if (choix == 3)
            {
                if (nbAEF > 0)
                {
                    int choix2 = 0;
                    int key2 = 0;
                    while (key2 != 13)
                    {
                        afficherModifier(choix2, nbAEF, liste_aef);
                        key2 = _getch();
                        switch (key2)
                        {
                        case 72: // Flèche haut
                            choix2 = (choix2 > 0) ? choix2 - 1 : nbAEF - 1;
                            break;
                        case 80: // Flèche bas
                            choix2 = (choix2 < nbAEF) ? choix2 + 1 : 0;
                            break;
                        }
                    }
                    t_AEF *new_aef = saisirAEF();
                    printf("ancien automate :\n");
                    afficherAEF(liste_aef[choix2]);
                    printf("\nnouvel automate :\n");
                    afficherAEF(new_aef);
                    printf("voulez vous apporter les modifications suivantes ? (o/n)\n");
                    fflush(stdin);
                    char conf = 'n';
                    scanf("%c", &conf);
                    if (conf == 'o')
                    {
                        printf("automate modifier\n");
                        liste_aef[choix2] = new_aef;
                    }
                    else
                    {
                        printf("modification non apporte\n");
                    }
                }
                else
                {
                    printf("aucun automate n'a ete charge\n");
                }
                system("pause");
            }
            else if (choix == 4)
            {
                if (nbAEF > 0)
                {
                    int choix2 = 0;
                    int key2 = 0;
                    while (key2 != 13)
                    {
                        afficherModifier(choix2, nbAEF, liste_aef);
                        key2 = _getch();
                        switch (key2)
                        {
                        case 72: // Flèche haut
                            choix2 = (choix2 > 0) ? choix2 - 1 : nbAEF - 1;
                            break;
                        case 80: // Flèche bas
                            choix2 = (choix2 < nbAEF) ? choix2 + 1 : 0;
                            break;
                        }
                    }
                    afficherAEF(liste_aef[choix2]);
                    printf("voulez vous enregistrer l'automate suivant ? (o/n)\n");
                    fflush(stdin);
                    char conf = 'n';
                    scanf("%c", &conf);
                    if (conf == 'o')
                    {
                        enregistrerAEF(liste_aef[choix2]);
                    }
                    else
                    {
                        printf("enregistrement non effectue\n");
                    }
                }
                else
                {
                    printf("aucun automate n'a ete charge\n");
                }
                system("pause");
            }
            else if (choix == 5)
            {
                if (nbAEF > 0)
                {
                    int choix2 = 0;
                    int key2 = 0;
                    while (key2 != 13)
                    {
                        afficherModifier(choix2, nbAEF, liste_aef);
                        key2 = _getch();
                        switch (key2)
                        {
                        case 72: // Flèche haut
                            choix2 = (choix2 > 0) ? choix2 - 1 : nbAEF - 1;
                            break;
                        case 80: // Flèche bas
                            choix2 = (choix2 < nbAEF) ? choix2 + 1 : 0;
                            break;
                        }
                    }
                    afficherAEF(liste_aef[choix2]);
                    printf("voulez vous supprimer l'automate suivant ? (o/n)\n");
                    fflush(stdin);
                    char conf = 'n';
                    scanf("%c", &conf);
                    if (conf == 'o')
                    {
                        printf("automate supprime\n");
                        supprimerAEF(liste_aef, liste_aef[choix2], &nbAEF);
                    }
                    else
                    {
                        printf("suppression non selectionne\n");
                    }
                }
                else
                {
                    printf("aucun automate n'a ete charge\n");
                }
                system("pause");
            }
            else if (choix == 20)
            {
                for (int i = 0; i < nbAEF; i++)
                {
                    free(liste_aef[i]);
                }
                free(liste_aef);

                return 0;
            }
            break;
        }
    }

    // t_AEF *aef = lireFichier("matrice_emonder.txt");

    // afficherAEF(aef);

    // printf(" etat accessible: \n");
    // for (int i = 0; i < aef->taille; i++)
    // {
    //     int **matriceAdjacence = matriceTransition2MatriceAdjacence(aef->matriceTransition, aef->nbElementsMatriceTransition, aef->taille, strlen(aef->alphabet), aef->alphabet);
    //     int *visited = calloc(aef->taille, sizeof(int));
    //     printf("on cherche un chemin de %d a %d: ", aef->q0, aef->q[i]);
    //     printf("{%d}\n", DFS(0, visited, matriceAdjacence, aef->taille, aef->q[i]));

    //     for (int i = 0; i < aef->taille; i++)
    //     {
    //         free(matriceAdjacence[i]);
    //     }
    //     free(matriceAdjacence);
    //     free(visited);
    // }

    // printf(" etat co-accessible: \n");
    // for (int i = 0; i < aef->taille; i++)
    // {
    //     for (int j = 0; j < aef->nbF; j++)
    //     {
    //         int **matriceAdjacence = matriceTransition2MatriceAdjacence(aef->matriceTransition, aef->nbElementsMatriceTransition, aef->taille, strlen(aef->alphabet), aef->alphabet);
    //         int *visited = calloc(aef->taille, sizeof(int));
    //         printf("on cherche un chemin de %d a %d: ", aef->q[i], aef->f[j]);
    //         printf("{%d}\n", DFS(aef->q[i], visited, matriceAdjacence, aef->taille, aef->f[j]));

    //         for (int i = 0; i < aef->taille; i++)
    //         {
    //             free(matriceAdjacence[i]);
    //         }
    //         free(matriceAdjacence);
    //         free(visited);
    //     }
    // }

    // printf("\naffichage matrice de transition :\n");
    // for (int i = 0; i < aef_det->taille; i++)
    // {
    //     printf("%d ", i);
    //     for (int j = 0; j < strlen(aef_det->alphabet); j++)
    //     {
    //         printf("(%d)\t", aef_det->nbElementsMatriceTransition[i][j]);
    //         printf("{");
    //         for (int k = 0; k < aef_det->nbElementsMatriceTransition[i][j]; k++)
    //         {
    //             printf("%d ", aef_det->matriceTransition[i][j][k]);
    //         }
    //         printf("}\t");
    //     }
    //     printf("\n");
    // }

    // suppAEF(aef);

    return 0;
}