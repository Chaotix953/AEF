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
            choix = (choix > 1) ? choix - 1 : 21;
            break;
        case 80: // Flèche bas
            choix = (choix < 21) ? choix + 1 : 1;
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
                        nbAEF--;
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
            else if (choix == 6)
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
                    printf("entrer le mot dans l'automate :\n");
                    fflush(stdin);
                    char mot[100] = "";
                    scanf("%s", mot);
                    if (reconnaitreMot(liste_aef[choix2], mot) == 1)
                    {
                        printf("%s a ete reconnu par %s\n", mot, liste_aef[choix2]->nom);
                    }
                    else
                    {
                        printf("%s non reconnu par %s\n", mot, liste_aef[choix2]->nom);
                    }
                    system("pause");
                }
            }
            else if (choix == 7) // verif automate complet
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
                    if (verifAutomateComplet(liste_aef[choix2]) == 1)
                    {
                        printf("automate complet\n");
                    }
                    else
                    {
                        printf("automate non complet\n");
                    }
                    system("pause");
                }
            }
            else if (choix == 8) // transformer automate complet
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
                    nbAEF++;
                    liste_aef = (t_AEF **)realloc(liste_aef, nbAEF * sizeof(t_AEF));
                    liste_aef[nbAEF - 1] = (t_AEF *)transformerAutomateComplet(liste_aef[choix2]);
                    afficherAEF(liste_aef[nbAEF - 1]);
                    system("pause");
                }
            }
            else if (choix == 9) // verif automate deterministe
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
                    if (verifAutomateDeterministe(liste_aef[choix2]) == 1)
                    {
                        printf("automate deterministe\n");
                    }
                    else
                    {
                        printf("automate non deterministe\n");
                    }
                    system("pause");
                }
            }
            else if (choix == 10) // rendre automate deterministe
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
                    nbAEF++;
                    liste_aef = (t_AEF **)realloc(liste_aef, nbAEF * sizeof(t_AEF));
                    liste_aef[nbAEF - 1] = (t_AEF *)transformerAutomateDeterministe(liste_aef[choix2]);
                    afficherAEF(liste_aef[nbAEF - 1]);
                    system("pause");
                }
            }
            else if (choix == 11)
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
                    nbAEF++;
                    liste_aef = (t_AEF **)realloc(liste_aef, nbAEF * sizeof(t_AEF));
                    liste_aef[nbAEF - 1] = (t_AEF *) complementaireAEF(liste_aef[choix2]);
                    afficherAEF(liste_aef[nbAEF - 1]);
                    system("pause");
                }
            }
            else if (choix == 18) // rendre automate emonder
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
                    nbAEF++;
                    liste_aef = (t_AEF **)realloc(liste_aef, nbAEF * sizeof(t_AEF));
                    liste_aef[nbAEF - 1] = (t_AEF *)transformerAutomateEmonde(liste_aef[choix2]);
                    afficherAEF(liste_aef[nbAEF - 1]);
                    system("pause");
                }
            }
            else if (choix == 20) // afficher un automate
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
                    system("pause");
                }
            }
            else if (choix == 21)
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

    // t_AEF *aef = lireFichier("matrice2.txt");

    // afficherAEF(aef);

    // t_AEF *aef2 = complementaireAEF(aef);
    // strcpy(aef2->nom, "kfold");

    // afficherAEF(aef2);

    // suppAEF(aef);
    // suppAEF(aef2);

    return 0;
}