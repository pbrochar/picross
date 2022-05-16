#include "picross.h"

/**Initialisation de ncurses**/
void ncurses_initialiser()
{
	initscr();            /* Démarre le mode ncurses */
	cbreak();             /* Pour les saisies clavier (desac. mise en buffer) */
	noecho();             /* Désactive l'affichage des caractères saisis */
	keypad(stdscr, TRUE); /* Active les touches spécifiques */
	refresh();            /* Met a jour l'affichage */
	curs_set(FALSE);      /* Masque le curseur */
}

/**Initialisation des couleurs**/
void ncurses_couleurs()
{
	/* Vérification du support de la couleur */
	if (has_colors() == FALSE)
	{
		endwin();
		fprintf(stderr, "Le terminal ne supporte pas les couleurs.\n");
		exit(EXIT_FAILURE);
	}

	/* Activation des couleurs */
	start_color();
	// init_color(COLOR_BLACK, 1000, 1000, 1000);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
}

/**Initialisation de la souris**/
void ncurses_souris()
{
	if (!mousemask(ALL_MOUSE_EVENTS, NULL))
	{
		endwin();
		fprintf(stderr, "Erreur lors de l'initialisation de la souris.\n");
		exit(EXIT_FAILURE);
	}

	if (has_mouse() != TRUE)
	{
		endwin();
		fprintf(stderr, "Aucune souris n'est détectée.\n");
		exit(EXIT_FAILURE);
	}
}

/*Pour récupérer les données saisies par l'utilisateur sans bloquer le jeu*/
char key_pressed()
{
	struct termios oldterm, newterm;
	int oldfd;
	char c, result = 0;
	tcgetattr(STDIN_FILENO, &oldterm);
	newterm = oldterm;
	newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
	fcntl(STDIN_FILENO, F_SETFL, oldfd);
	if (c != EOF)
	{
		ungetc(c, stdin);
		result = getchar();
	}
	return result;
}

/*Bouge le curseur aux coordonees [x,y]*/
void move_to_coordonate(int x, int y)
{
	move(y, x);
	refresh();
}

/*Alloue un tableau a 2 dimensions de taille size_x/size_y*/
int **init_game_tab(int size_x, int size_y)
{
	int **game_tab;
	int i = 0;

	game_tab = malloc(sizeof(int *) * size_y);
	if (game_tab == NULL)
		return (NULL);
	while (i < size_y)
	{
		game_tab[i] = malloc(sizeof(int) * size_x);
		if (game_tab[i] == NULL)
			return (NULL);
		i++;
	}
	return (game_tab);
}

/*Initialise toutes les valeurs d'un tableau a 2 dimensions a 0 */
int set_tab_to_0(struct s_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->size_y)
	{
		j = 0;
		while (j < game->size_x)
		{
			game->play_tab[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

/*Met aleatoirement les valeur 0 ou 1 dans un tableau a 2 dimensions*/
int random_fill(struct s_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->size_y)
	{
		j = 0;
		while (j < game->size_x)
		{
			game->picross_tab[i][j] = rand() % 2;
			j++;
		}
		i++;
	}
	return (0);
}

/*Libere la memoire d'un tableau a 2 dimensions.*/
void free_tab(int **tab, int size_y)
{
	int i;

	i = 0;
	while (i < size_y)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/*Libere la memoire des structures du jeu.*/
void free_data(struct s_game *game, struct s_game_board *game_board)
{
	free_tab(game->picross_tab, game->size_y);
	free_tab(game->play_tab, game->size_y);
	free_tab(game->rules_horizontal, game->size_y);
	free_tab(game->rules_vertical, game->size_x);
	free(game);
	free(game_board);
}













