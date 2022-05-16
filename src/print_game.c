#include "picross.h"

/*Boucle principale pour afficher la grille de jeu*/
void print_game_tab(struct s_game *game, struct s_game_board *game_board, int finish)
{
	int i;
	int pos_y;
	int rules_y;
	int rules_x;
	i = 0;
	pos_y = game_board->start_y;
	rules_y = game_board->max_rule_y + game_board->start_y;
	if (finish == 1)
		attron(COLOR_PAIR(2));
	while (i <= game->size_y)
	{
		move_to_coordonate(game_board->start_x, rules_y);
		print_game_tab_x(game, game_board);
		if (i < game->size_y)
			print_rules_x(game, game_board, rules_y, i);
		i++;
		rules_y += game_board->size_of_case_y;
	}
	i = 0;
	while (i < game_board->total_char_y)
	{
		move_to_coordonate(game_board->rules_x, pos_y);
		print_game_tab_y(game, game_board, pos_y);
		i++;
		pos_y++;
	}
	i = 0;
	pos_y = game_board->start_y;
	rules_x = game_board->rules_x;
	while (i < game->size_x)
	{
		print_rules_y(game, rules_x, game_board->size_of_case_x, pos_y, i);
		i++;
		rules_x += game_board->size_of_case_x;
	}
	print_case(game, game_board, finish);
	if (finish == 1)
		attroff(COLOR_PAIR(2));
	refresh();
}

/*Affiche les cases, en blanc si le joueur a selectione la case, en vert si le jeu est fini*/
void print_case(struct s_game *game, struct s_game_board *game_board, int finish)
{
	int i = 0;
	int j = 0;
	int color_pair;
	if (finish == 1)
		color_pair = 6;
	else
		color_pair = 5;
	while (i < game->size_y)
	{
		j = 0;
		while (j < game->size_x)
		{
			if (game->play_tab[i][j] == 1)
				fill_case(game_board, i, j, color_pair);
			else
				fill_case(game_board, i, j, 1);
			j++;
		}
		i++;
	}
}

/*Rempli une case avec la couleur definie par color_pair*/
void fill_case(struct s_game_board *game_board, int i, int j, int color_pair)
{
	int x = 0;
	int y = 0;
	int first_x = game_board->start_x + game_board->max_rule_x;
	int first_y = game_board->start_y + game_board->max_rule_y;
	first_x += (j * game_board->size_of_case_x) + 1;
	first_y += (i * game_board->size_of_case_y) + 1;
	attron(COLOR_PAIR(color_pair));
	while (y < game_board->size_of_case_y - 1)
	{
		x = 0;
		while (x < game_board->size_of_case_x - 1)
		{
			move_to_coordonate(first_x + x, first_y + y);
			addch(' ');
			x++;
		}
		y++;
	}
	attroff(COLOR_PAIR(color_pair));
}

/*Affiche toutes les lignes du jeu*/
void print_game_tab_x(struct s_game *game, struct s_game_board *game_board)
{
	int i;
	int j;
	int count;

	count = 0;
	j = 0;
	i = 0;
	while (i < game_board->max_rule_x)
	{
		addch('-');
		i++;
	}
	while (count <= game->size_x)
	{
		if (j == game_board->size_of_case_x || j == 0)
		{
			addch('+');
			j = 0;
			count++;
		}
		else
			addch('-');
		j++;
	}
	refresh();
}

/*Affiche les regles verticales*/
void print_game_tab_y(struct s_game *game, struct s_game_board *game_board, int pos_y)
{
	int count = 0;
	int rules_x;

	rules_x = game_board->rules_x;
	//Cette ligne recupere le char courrant a la position [rules_x, pos_y]
	//Si le charactere est un '+' on est sur une intersection, alors on retourne pour ne pas afficher les '|'
	int ch = mvwinch(stdscr, pos_y, rules_x) & A_CHARTEXT;
	if (ch == '+')
		return;
	while (count <= game->size_x)
	{
		addch('|');
		rules_x += game_board->size_of_case_x;
		move_to_coordonate(rules_x, pos_y);
		count++;
	}
	refresh();
}

/*Affiche les regles horizontales*/
void print_rules_x(struct s_game *game, struct s_game_board *game_board, int rules_y, int i)
{
	int j;

	j = 0;
	move_to_coordonate(game_board->start_x, rules_y + (game_board->size_of_case_y / 2));
	if (game->rules_horizontal[i][j] == -1)
	{
		printw("0");
	}
	while (game->rules_horizontal[i][j] != -1)
	{
		printw("%d", game->rules_horizontal[i][j]);
		j++;
		if (game->rules_horizontal[i][j] != -1)
			printw(" ");
	}
	move_to_coordonate(game_board->start_x, rules_y);
}

/*Affiche les regles verticales*/
void print_rules_y(struct s_game *game, int rules_x, int size_of_case_x, int pos_y, int i)
{
	int j;
	j = 0;
	if (game->rules_vertical[i][j] == -1)
	{
		move_to_coordonate(rules_x + (size_of_case_x / 2), pos_y);
		printw("0");
		return;
	}
	while (game->rules_vertical[i][j] != -1)
	{
		move_to_coordonate(rules_x + (size_of_case_x / 2), pos_y);
		printw("%d", game->rules_vertical[i][j]);
		j++;
		pos_y += 2;
	}
}