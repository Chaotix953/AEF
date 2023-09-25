#include "menu.h"

// Fonction pour afficher le menu principal
void afficherMenu(int choix)
{
    system("cls"); // Effacer la console

    // printf("Editeur d'Automates d'Etats Finis (AEF)\n\n");
    // printf("1. Saisir un AEF\n");
    // printf("2. Importer un AEF depuis un fichier\n");
    // printf("3. Modifier un AEF\n");
    // printf("4. Sauvegarder un AEF dans un fichier\n");
    // printf("5. Supprimer un AEF\n");
    // printf("6. Quitter\n\n");
    printf("Editeur de AEF\n");

    for (int i = 1; i <= 6; i++)
    {
        if (i == choix)
        {
            // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); // Couleur du texte sélectionné
            printf("> ");
        }
        else
        {
            // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY); // Couleur du texte non sélectionné
            printf("  ");
        }
        switch (i)
        {
        case 1:
            printf("Saisir un AEF");
            break;
        case 2:
            printf("Importer un AEF");
            break;
        case 3:
            printf("Modifier un AEF");
            break;
        case 4:
            printf("Sauvegarder un AEF");
            break;
        case 5:
            printf("Supprimer un AEF");
            break;
        case 6:
            printf("Quitter");
            break;
        }
        printf("\n");
    }
}

