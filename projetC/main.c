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
    //             system("cls");
    //             t_AEF *aef = saisirAEF();
    //             system("pause");
    //             // Code pour importer un AEF depuis un fichier
    //             suppAEF(aef);
    //         }
    //         else if (choix == 2)
    //         {
    //             system("cls");
    //             t_AEF *aef = lireFichier();
    //             afficherAEF();
    //             system("pause");
    //             // Code pour importer un AEF depuis un fichier
    //             suppAEF(aef);
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
    // printf("verif : %s\n", aef->nom);

    afficherAEF(aef);

    suppAEF(aef);

    return 0;
}
