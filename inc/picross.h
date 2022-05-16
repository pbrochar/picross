#ifndef PICROSS_H
# define PICROSS_H

# include "includes.h"

/*Structure du jeu*/
struct s_game {
	int **picross_tab; //Tableau 2 dimensions representant la grille de jeu
	int **play_tab; //Tableau 2 dimensions representant la grille du joueur
	int **rules_horizontal; //Tableau 2 dimensions representant les regles horizontales du jeu
	int **rules_vertical; //Tableau 2 dimensions representant les regles verticales du jeu
	int	size_x; //Taille x du jeu
	int size_y; //Taille y du jeu
};

/*Structure du plateau de jeu*/
struct s_game_board {
	int max_rule_x; //Nombre de regles maximales de toutes les lignes
	int max_rule_y; //Nombre de regles maximales de toutes les colonnes
	int size_of_case_x; //Taille en largeur d'une case
	int size_of_case_y; //Taille en hauteur d'une case
	int total_char_x; //Nombre total de charactere sur une ligne
	int total_char_y; //Nombre total de caractere sur une colonne
	int rules_x; //Position de depart d'affichage des cases apres les regles en x -> represente le bord haut/gauche de la premiere case
	int start_x; //Position de depart en x pour afficher le plateau de jeu
	int start_y; //Position de depart en y pour afficher le plateau de jeu
};

/*
** from src/game.c
*/
int			check_game(struct s_game *game);
int			click_souris();
int			play_game(struct s_game *game, struct s_game_board *game_board);
void		LANCEMENT_JEU();
void		change_case_from_coordonate(struct s_game *game, struct s_game_board *game_board, int L, int C);

/*
** from src/init_game.c
*/
int			fill_rules_data(struct s_game *game);
int			generate_picross(struct s_game *game);
int			get_number_of_rule_x(struct s_game *game, int i);
int			get_number_of_rule_y(struct s_game *game, int i);
int			get_rules_max_x(struct s_game *game);
int			get_rules_max_y(struct s_game *game);
int			picross_from_file(struct s_game *game);
void		get_game_board_data(struct s_game *game, struct s_game_board *game_board, int lines, int cols);
void		get_rules_x(struct s_game *game, int i);
void		get_rules_y(struct s_game *game, int i);

/*
** from src/menu.c
*/
int			print_menu(int cols);
void		print_faq(int y);
void		print_game_name(int x);
void		print_horizontal_border(int size);
void		print_vertical_border(int x, int y, int size);

/*
** from src/print_game.c
*/
void		fill_case(struct s_game_board *game_board, int i, int j, int color_pair);
void		print_case(struct s_game *game, struct s_game_board *game_board, int finish);
void		print_game_tab(struct s_game *game, struct s_game_board *game_board, int finish);
void		print_game_tab_x(struct s_game *game, struct s_game_board *game_board);
void		print_game_tab_y(struct s_game *game, struct s_game_board *game_board, int pos_y);
void		print_rules_x(struct s_game *game, struct s_game_board *game_board, int rules_y, int i);
void		print_rules_y(struct s_game *game, int rules_x, int size_of_case_x, int pos_y, int i);

/*
** from src/utils.c
*/
char		key_pressed();
int			**init_game_tab(int size_x, int size_y);
int			random_fill(struct s_game *game);
int			set_tab_to_0(struct s_game *game);
void		free_data(struct s_game *game, struct s_game_board *game_board);
void		free_tab(int **tab, int size_y);
void		move_to_coordonate(int x, int y);
void		ncurses_couleurs();
void		ncurses_initialiser();
void		ncurses_souris();

#endif