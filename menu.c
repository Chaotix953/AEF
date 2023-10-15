#include "menu.h"

// Fonction pour afficher le menu principal
void afficherMenu(int choix, int nbAEF, t_AEF **liste_aef)
{
    system("cls"); // Effacer la console

    printf("Editeur d'automate\n");

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

    printf("automate charge %d\n", nbAEF);
    for (int i = 0; i < nbAEF; i++)
    {
        printf("    %s\n", liste_aef[i]->nom);
    }
}

void afficherModifier(int choix, int nbAEF, t_AEF **liste_aef)
{
    system("cls"); // Effacer la console

    printf("selectionner un automate :\n");

    for (int i = 0; i < nbAEF; i++)
    {
        if (i == choix)
        {
            printf(">");
        }
        else
        {
            printf(" ");
        }
        printf("%s\n", liste_aef[i]->nom);
    }
}