#include "picross.h"

int L, C; /*L pour désigner la ligne et C la colonne du clic de la souris*/

/**Pour récupérer les coordonnées (x,y) du clic de la souris**/
int click_souris()
{
	MEVENT event;
	int ch;

	while ((ch = getch()) != KEY_F(1))
	{
		switch (ch)
		{
		case KEY_F(2): /*Pour quitter la boucle*/
			return 1;
		case KEY_MOUSE:
			if (getmouse(&event) == OK)
			{
				C = event.x;
				L = event.y;
				if (event.bstate & BUTTON1_CLICKED)
				{
					return 0;
				}
			}
		}
	}
	return 0;
}

/*Verifie si le jeu est fini*/
int check_game(struct s_game *game)
{
	int i = 0;
	int j = 0;
	while (i < game->size_y)
	{
		j = 0;
		while (j < game->size_x)
		{
			if (game->picross_tab[i][j] != game->play_tab[i][j])
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

/*Permet de determiner changer le mode d'une case en fonction des coordonees du clique*/
void change_case_from_coordonate(struct s_game *game, struct s_game_board *game_board, int L, int C)
{
	int first_x = game_board->start_x + game_board->max_rule_x;
	int first_y = game_board->start_y + game_board->max_rule_y;
	int pos_x = C - first_x;
	int pos_y = L - first_y;
	int i = 0;
	int j = 0;
	int total_x = game_board->size_of_case_x * game->size_x;
	int total_y = game_board->size_of_case_y * game->size_y;
	int case_x = game_board->size_of_case_x;
	int case_y = game_board->size_of_case_y;

	if (pos_x < 0 || pos_x > total_x || pos_y < 0 || pos_y > total_y)
		return ;
	else 
	{
		while (1)
		{
			if (pos_x < case_x)
				break;
			else 
			{
				case_x += game_board->size_of_case_x;
				i++;
			}
		}
		while(1)
		{
			if (pos_y < case_y)
				break;
			else 
			{
				case_y += game_board->size_of_case_y;
				j++;
			}

		}
		if (game->play_tab[j][i] == 0)
			game->play_tab[j][i] = 1;
		else
			game->play_tab[j][i] = 0;
	}
}

/*Boucle principale du jeu*/
int play_game(struct s_game *game, struct s_game_board *game_board)
{
	clear();
	print_game_tab(game, game_board, 0);
	while (click_souris() == 0)
	{
		change_case_from_coordonate(game, game_board, L, C);
		print_game_tab(game, game_board, 0);
		if (check_game(game) == 0)
			break;
	}
	clear();
	print_game_tab(game, game_board, 1);
	if (click_souris() == 0)
		clear();
	return (0);
}

/*Boucle principale du lancement du jeu*/
void LANCEMENT_JEU()
{
	int center_x = (COLS / 2) - 7;
	struct s_game *game;
	struct s_game_board *game_board;

	//On alloue les structures et on return si il y a un probleme avec malloc.
	game = malloc(sizeof(struct s_game));
	game_board = malloc(sizeof(struct s_game_board));
	if (game == NULL || game_board == NULL)
		return;
	print_menu(COLS);
	while (click_souris() == 0)
	{
		//Coordonnees dans le menu pour lancer le mode aleatoire.
		if (L == 10 && (C >= center_x && C <= center_x + 14))
		{
			clear();
			generate_picross(game);
			fill_rules_data(game);
			get_game_board_data(game, game_board, LINES, COLS);
			play_game(game, game_board);
		}
		//Coordonnees dans le menu pour lancer le mode image.
		else if (L == 12 && (C >= center_x && C <= center_x + 14))
		{
			clear();
			picross_from_file(game);
			fill_rules_data(game);
			get_game_board_data(game, game_board, LINES, COLS);
			play_game(game, game_board);
		}
		//Coordonnees dans le menu pour quitter le jeu.
		else if (L == 14 && (C >= center_x && C <= center_x + 14))
			break;
		print_menu(COLS);
		refresh();
	}
	//On libere toute la memoire allouee.
	free_data(game, game_board);
}