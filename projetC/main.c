#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aef.h"
#include "menu.h"
#include <conio.h>  // Pour utiliser _getch()
#include <windows.h>

// fonction principale
int main()
{
    // // initialiser les variables avec un fichier texte
    // int taille = 4;
    // int *q = creerTableauQ(taille);
    // char entre[] = "BAAB";
    // char alphabet[] = "AB";
    // int f[] = {2, 3};

    // t_AEF *aef = initAEF(q, alphabet, f, &taille);

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

    // for (int i = 0; i < strlen(entre); i++)
    // {
    //     if (transition(aef, entre[i]) != 1)
    //     {
    //         break;
    //     }
    // }

    // // Libération de la mémoire
    // suppAEF(aef, 4);

    // int choix = 1;
    // while (1)
    // {
    //     afficherMenu(choix);
    //     int key = _getch(); // Attend une touche du clavier

    //     switch (key)
    //     {
    //     case 72: // Flèche haut
    //         choix = (choix > 1) ? choix - 1 : 6;
    //         break;
    //     case 80: // Flèche bas
    //         choix = (choix < 6) ? choix + 1 : 1;
    //         break;
    //     case 13: // Touche Entrée
    //         if (choix == 1)
    //         {
    //             // Traitez l'AEF saisi ici
    //         }
    //         else if (choix == 2)
    //         {
    //             // Code pour importer un AEF depuis un fichier
    //         }
    //         else if (choix == 3)
    //         {
    //             // Code pour modifier un AEF
    //         }
    //         else if (choix == 4)
    //         {
    //             // Code pour sauvegarder un AEF dans un fichier
    //         }
    //         else if (choix == 5)
    //         {
    //             // Code pour supprimer un AEF
    //         }
    //         else if (choix == 6)
    //         {
    //             // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY); // Couleur du texte non sélectionné
    //             // printf("  ");
    //             return 0;
    //         }
    //         break;
    //     }
    // }

    t_AEF *aef = lireFichier();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d ", aef->matriceTransition[i][j]);
        }
        printf("\n");
    }

    suppAEF(aef);

    return 0;
}
