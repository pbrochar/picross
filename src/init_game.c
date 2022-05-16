#include "picross.h"

/*Permet de generer un picross aleatoirement*/
int generate_picross(struct s_game *game)
{
	int upper = 10;
	int lower = 5;

	srand(time(NULL));
	game->size_x = rand() % (upper - lower + 1) + lower;
	game->size_y = rand() % (upper - lower + 1) + lower;
	game->picross_tab = init_game_tab(game->size_x, game->size_y);
	game->play_tab = init_game_tab(game->size_x, game->size_y);
	if (game->picross_tab == NULL || game->play_tab == NULL)
		return (-1);
	random_fill(game);
	set_tab_to_0(game);
	return (0);
}

/*Permet de recuperer un picross depuis un fichier
Pour ajouter une nouvelle grille : 
- Creer la grille dans le dossier ./images avec le format adapte : premiere ligne taille_x taille_y, et sur les autres lignes la grille avec 0 (case vide) et 1 (case pleine)
- Ajouter le path dans le tableau char *images[]
- Mettre le nombre de grille dans la variable number_of_files
*/
int picross_from_file(struct s_game *game)
{
	FILE *image;
	char *images[] = {"images/pic1", "images/pic2", "images/pic3", "images/pic4"};
	int number_of_files = 4;
	int file_number = rand() % number_of_files;
	int i = 0;
	int j = 0;

	image = fopen(images[file_number], "r");
	if (image == NULL)
		return (-1);
	fscanf(image, "%d %d\n", &game->size_x, &game->size_y);
	if (game->size_x <= 0 || game->size_y <= 0)
		return (-1);
	game->picross_tab = init_game_tab(game->size_x, game->size_y);
	game->play_tab = init_game_tab(game->size_x, game->size_y);
	if (game->picross_tab == NULL || game->play_tab == NULL)
		return (-1);
	while (i < game->size_y)
	{
		j = 0;
		while (j < game->size_x)
		{
			fscanf(image, "%d", &game->picross_tab[i][j]);
			j++;
		}
		i++;
	}
	fclose(image);
	set_tab_to_0(game);
	return (0);
}

/*Permet de calculer toutes les variables necessaire pour afficher la grille centree sur l'ecran*/
void get_game_board_data(struct s_game *game, struct s_game_board *game_board, int lines, int cols)
{
	game_board->max_rule_x = get_rules_max_x(game);
	game_board->max_rule_y = get_rules_max_y(game);
	game_board->size_of_case_x = (cols - (game_board->max_rule_x)-1) / game->size_x;
	game_board->size_of_case_y = (lines - (game_board->max_rule_y)-1) / game->size_y;
	if (game_board->size_of_case_x > game_board->size_of_case_y * 2)
		game_board->size_of_case_x /= 2;
	else if (game_board->size_of_case_x * 2 > game_board->size_of_case_y)
		game_board->size_of_case_y /= 2;
	if (game_board->size_of_case_x % 2 == 1)
		game_board->size_of_case_x--;
	if (game_board->size_of_case_y % 2 == 1)
		game_board->size_of_case_y--;
	game_board->total_char_x = (game_board->size_of_case_x * game->size_x) + game_board->max_rule_x;
	game_board->total_char_y = (game_board->size_of_case_y * game->size_y) + game_board->max_rule_y;
	if (game_board->total_char_y < lines)
		game_board->start_y = (lines - game_board->total_char_y) / 2;
	else
		game_board->start_y = 0;
	game_board->start_x = (cols - game_board->total_char_x) / 2;
	game_board->rules_x = game_board->max_rule_x + game_board->start_x;
}

/*Permet de recuperer le nombre de regles sur une ligne*/
int get_number_of_rule_x(struct s_game *game, int i)
{
	int j = 0;
	int count = 0;

	while (j < game->size_x)
	{
		if (game->picross_tab[i][j] == 1)
		{
			count++;
			while (j < game->size_x && game->picross_tab[i][j] != 0)
				j++;
		}
		j++;
	}
	return (count + 1);
}

/*Permet de recuperer le nombre de regles sur une colonne*/
int get_number_of_rule_y(struct s_game *game, int i)
{
	int j = 0;
	int count = 0;

	while (j < game->size_y)
	{
		if (game->picross_tab[j][i] == 1)
		{
			count++;
			while (j < game->size_y && game->picross_tab[j][i] != 0)
				j++;
		}
		j++;
	}
	return (count + 1);
}

/*Permet de recuperer les regles d'une colonne*/
void get_rules_y(struct s_game *game, int i)
{
	int j = 0;
	int rule_index = 0;

	while (j < game->size_y)
	{
		if (game->picross_tab[j][i] == 1)
		{
			game->rules_vertical[i][rule_index] = 0;
			while (j < game->size_y && game->picross_tab[j][i] != 0)
			{
				game->rules_vertical[i][rule_index]++;
				j++;
			}
			rule_index++;
		}
		j++;
	}
}

/*Permet de recuperer les regles d'une ligne*/
void get_rules_x(struct s_game *game, int i)
{
	int j = 0;
	int rule_index = 0;

	while (j < game->size_x)
	{
		if (game->picross_tab[i][j] == 1)
		{
			game->rules_horizontal[i][rule_index] = 0;
			while (j < game->size_x && game->picross_tab[i][j] != 0)
			{
				game->rules_horizontal[i][rule_index]++;
				j++;
			}
			rule_index++;
		}
		j++;
	}
}

/*Permet de remplir les tableau de regles
Les tableaux sont de taille differentes, donc la derniere case est initialisee a -1 afin de pouvoir les parcourir
*/
int fill_rules_data(struct s_game *game)
{
	int i = 0;
	int count;
	game->rules_horizontal = malloc(sizeof(int *) * game->size_y);
	game->rules_vertical = malloc(sizeof(int *) * game->size_x);
	if (game->rules_horizontal == NULL || game->rules_vertical == NULL)
		return (-1);
	while (i < game->size_y)
	{
		count = get_number_of_rule_x(game, i);
		game->rules_horizontal[i] = malloc(sizeof(int) * (count));
		if (game->rules_horizontal[i] == NULL)
			return (-1);
		game->rules_horizontal[i][count - 1] = -1;
		get_rules_x(game, i);
		i++;
	}
	i = 0;
	while (i < game->size_x)
	{
		count = get_number_of_rule_y(game, i);
		game->rules_vertical[i] = malloc(sizeof(int) * (count));
		if (game->rules_vertical[i] == NULL)
			return (-1);
		game->rules_vertical[i][count - 1] = -1;
		get_rules_y(game, i);
		i++;
	}
	return (0);
}

/*Recupere le nombre MAXIMUM de regle pour toutes les lignes*/
int get_rules_max_x(struct s_game *game)
{
	int i;
	int j;
	int count;
	int max_count;

	i = 0;
	max_count = 0;
	while (i < game->size_y)
	{
		j = 0;
		count = 0;
		while (game->rules_horizontal[i][j] != -1)
		{
			count++;
			j++;
		}
		if (count > max_count)
			max_count = count;
		i++;
	}
	return ((max_count * 2) - 1);
}

/*Recupere le nombre MAXIMUM de regle pour toutes les colonnes*/
int get_rules_max_y(struct s_game *game)
{
	int i;
	int j;
	int count;
	int max_count;

	i = 0;
	max_count = 0;
	while (i < game->size_x)
	{
		j = 0;
		count = 0;
		while (game->rules_vertical[i][j] != -1)
		{
			count++;
			j++;
		}
		if (count > max_count)
			max_count = count;
		i++;
	}
	return ((max_count * 2) - 1);
}