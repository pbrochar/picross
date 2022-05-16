#include "picross.h"

/*Affiche les bordures horizontales*/
void print_horizontal_border(int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (i != 0 && i != size - 1)
			addch('-');
		else
			addch('+');
		i++;
	}
}

/*Affiche les bordures verticales*/
void print_vertical_border(int x, int y, int size)
{
	printw("|");
	move_to_coordonate(x + size - 1, y);
	printw("|");
	move_to_coordonate(x + 1, y);
}

/*Affiche le nom du jeu*/
void print_game_name(int x)
{
	// Pour centrer le nom du jeu
	x -= 17;
	attron(A_BOLD | COLOR_PAIR(2));
	move_to_coordonate(x, 0);
	printw(" ___  ___  ___  ___   ___   ___  ___\n");
	move_to_coordonate(x, 1);
	printw("| _ \\|_ _|/ __|| _ \\ / _ \\ / __|/ __|\n");
	move_to_coordonate(x, 2);
	printw("|  _/ | || (__ |   /| (_) |\\__ \\\\__ \\\n");
	move_to_coordonate(x, 3);
	printw("|_|  |___|\\___||_|_\\ \\___/ |___/|___/\n");
	attroff(A_BOLD | COLOR_PAIR(2));
}

/*Affiche la FAQ*/
void print_faq(int y)
{
	move_to_coordonate(0, y);
	printw("Modes de jeu :\n\n");
	printw("\tAleatoire - genere une grille aleatoire de Picross.\n");
	printw("\tImage     - grille de Picross de notre base de donnee.\n");
}

/*Fonction principale pour afficher le menu*/
int print_menu(int cols)
{
	int startx, starty;
	starty = 8;
	startx = cols / 2;
	int size = 15;

	print_game_name(startx);
	
	//On set la couleur bleu
	attron(COLOR_PAIR(4));

	// Pour centrer le menu
	startx -= 7;
	move_to_coordonate(startx, starty);
	// On affiche le haut du menu
	print_horizontal_border(size);
	
	starty++;
	move_to_coordonate(startx, starty);
	//On affiche les bords du menu
	print_vertical_border(startx, starty, size);

	starty++;
	move_to_coordonate(startx, starty);
	//On affiche les bords du menu
	print_vertical_border(startx, starty, size);
	//On affiche le texte du menu
	printw("  ALEATOIRE");

	
	starty++;
	move_to_coordonate(startx, starty);
	//On affiche les bords du menu
	print_vertical_border(startx, starty, size);


	starty++;
	move_to_coordonate(startx, starty);
	// On affiche les bords du menu
	print_vertical_border(startx, starty, size);
	// On affiche le texte du menu
	printw("    IMAGE");


	starty++;
	move_to_coordonate(startx, starty);
	//On affiche les bords du menu
	print_vertical_border(startx, starty, size);

	starty++;
	move_to_coordonate(startx, starty);
	//On affiche les bords du menu
	print_vertical_border(startx, starty, size);
	//On affiche le texte du menu
	attroff(COLOR_PAIR(4));
	attron(A_DIM);
	printw("   QUITTER");
	attroff(A_DIM);
	
	attron(COLOR_PAIR(4));
	starty++;
	move_to_coordonate(startx, starty);
	//On affiche les bords du menu
	print_vertical_border(startx, starty, size);
	starty++;
	move_to_coordonate(startx, starty);
	// On affiche le bas du menu
	print_horizontal_border(size);

	// On enleve la couleur bleu
	attroff(COLOR_PAIR(4));

	// On affiche la "FAQ"
	print_faq(starty + 4);
	return 0;
}