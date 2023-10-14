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
            choix = (choix > 1) ? choix - 1 : 6;
            break;
        case 80: // Flèche bas
            choix = (choix < 6) ? choix + 1 : 1;
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
                const char *directory_path = "C:/Users/richy/OneDrive/Bureau/prog/c/AEF/projetC"; // Remplacez par le chemin de votre répertoire

                DIR *directory;
                struct dirent *entry;

                directory = opendir(directory_path);
                if (directory == NULL)
                {
                    perror("Erreur lors de l'ouverture du répertoire");
                    return 1;
                }

                printf("Fichiers .txt dans le répertoire %s :\n", directory_path);

                while ((entry = readdir(directory)) != NULL)
                {
                    if (entry->d_type == DT_REG)
                    { // Vérifiez si l'entrée est un fichier régulier
                        if (strstr(entry->d_name, ".txt") != NULL)
                        {
                            printf("%s\n", entry->d_name);
                        }
                    }
                }

                closedir(directory);

                nbAEF++;
                liste_aef = (t_AEF **)realloc(liste_aef, nbAEF * sizeof(t_AEF *));
                liste_aef[nbAEF - 1] = (t_AEF *)malloc(sizeof(t_AEF));
                liste_aef[nbAEF - 1] = lireFichier();
                afficherAEF(liste_aef[nbAEF - 1]);
                system("pause");
            }
            else if (choix == 3)
            {
            }
            else if (choix == 4)
            {
                // Code pour sauvegarder un AEF dans un fichier
            }
            else if (choix == 5)
            {
                // Code pour supprimer un AEF
            }
            else if (choix == 6)
            {
                // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY); // Couleur du texte non sélectionné
                // printf("  ");
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

    return 0;
}
