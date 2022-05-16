#include "picross.h"

int main()
{
	 	ncurses_initialiser(); //Initialisation de ncurses
		clear();
		ncurses_couleurs(); //Initialisation des couleurs
    ncurses_souris(); //Initialisation de la souris
    LANCEMENT_JEU(); //Lancement du jeu
    endwin(); // Suspendre la session ncurses et restaurer le terminal
    return 0;
}