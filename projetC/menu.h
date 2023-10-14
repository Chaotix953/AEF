#ifndef MENU
#define MENU

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // Pour utiliser _getch()
#include <windows.h> // Pour gérer les fonctions Windows Console
#include "aef.h"

void afficherMenu(int choix, int nbAEF, t_AEF **liste_aef);

#endif