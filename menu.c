#include "menu.h"

// Fonction pour afficher le menu principal
void afficherMenu(int choix, int nbAEF, t_AEF **liste_aef)
{
    system("cls"); // Effacer la console

    printf("Richy Razafindandy\n");
    printf("Wissal Zidar\n");
    printf("Ikbal El Khalidi\n");
    printf("Hanae Rguig\n");
    printf("David Boucard\n");
    printf("Aymane Outimjichtt\n");

    printf("\t\tEditeur d'Automate\n");

    for (int i = 1; i <= 21; i++)
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
            printf("entrer des caracteres dans un automate");
            break;
        case 7:
            printf("verifier si un automate est complet");
            break;
        case 8:
            printf("rendre un automate complet");
            break;
        case 9:
            printf("verifier si un automate est deterministe");
            break;
        case 10:
            printf("rendre un automate deterministe");
            break;
        case 11:
            printf("complement d'un automate");
            break;
        case 12:
            printf("miroir d'un automate");
            break;
        case 13:
            printf("produit de 2 automates");
            break;
        case 14:
            printf("concatenation de 2 automates");
            break;
        case 15:
            printf("extraire une expression reguliere");
            break;
        case 16:
            printf("reconnaitre un langage dans un automate");
            break;
        case 17:
            printf("verifier si 2 automates sont equivalents");
            break;
        case 18:
            printf("rendre un automate emonde");
            break;
        case 19:
            printf("rendre un automate minimal");
            break;
        case 20:
            printf("Afficher un AEF");
            break;
        case 21:
            printf("Quitter");
            break;
        }
        printf("\n");
    }

    printf("\tautomate charge %d\n", nbAEF);

    for (int i = 0; i < nbAEF; i++)
    {
        printf("\t%s\n", liste_aef[i]->nom);
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