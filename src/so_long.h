/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:44:27 by skimura           #+#    #+#             */
/*   Updated: 2025/07/13 18:02:10 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "/home/skimura/minilibx-linux/mlx.h"
# include "/home/skimura/mylibft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TILE 64
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_DESTROY 17
# define PLAYER_SPEED 1500
# define ENEMY_SPEED 500
# define DEFAULT -1
# define UI_START 8
# define UI_WIDTH 8
# define UI_HEIGHT 6
# define UI_NUMBER_X 150
# define UI_NUMBER_Y 150
# define EVENT_MASK_KEYPRESS 1L
# define EVENT_MASK_NONE 0L

typedef enum e_item_type
{
	NONE = 0,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	MAX
}				t_item_type;

typedef enum e_direction
{
	RIGHT = 0,
	DOWN,
	LEFT,
	UP
}				t_direction;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			exit_x;
	int			exit_y;
}				t_map;

typedef struct s_item
{
	t_item_type	type;
	int			x;
	int			y;
	int			collected;
}				t_item;

typedef struct s_player
{
	int			x;
	int			y;
	int			move_count;
	t_direction	direction;
	int			direction_timer;
}				t_player;

typedef struct s_enemy
{
	int			x;
	int			y;
	int			start_x;
	int			start_y;
	int			direction;
	int			move_counter;
}				t_enemy;

typedef struct s_ui
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			digit_width;
	int			number_x;
	int			number_y;
}				t_ui;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_enemy		enemy;
	t_item		*items;
	int			collected_items;
	int			total_items;
	int			item_count;
	void		*floor_img;
	void		*wall_img;
	void		*player_img;
	void		*collectible_img;
	void		*exit_img;
	void		*enemy_img;
	void		*item_img[MAX];
	void		*player_img_left;
	void		*player_img_right;
	void		*player_img_up;
	void		*player_img_down;
	void		*number_img[MAX];
	t_ui		ui;
}				t_game;

// main.c
void			free_map(t_map *map);
void			free_items(t_game *game);
void			init_game(t_game *game);
int				init_map(t_game *game, char *filename);
int				game_loop(t_game *game);
void			save_direction_offset(t_direction direction, int *dx, int *dy);
// close.c
int				close_window(t_game *game);
void			clean_exit(t_game *g);
// collectable.c
void			parse_map(t_game *game, char c, int x, int y);
void			add_item(t_game *game, t_item_type type, int x, int y);
void			render_item(t_game *game, int x, int y);
// read_xpm.c
void			load_images(t_game *game);
void			allow_images_loaded(t_game *game);
// read_map.c
void			render_map(t_game *game);
void			render_ui_in_map(t_game *game);
void			render_floor(t_game *game, int x, int y);
void			render_wall(t_game *game, int x, int y);
void			render_player(t_game *game, int x, int y);
void			render_exit(t_game *game, int x, int y);
void			render_enemy(t_game *game, int x, int y);
// validate_map.c
int				allow_filename(char *filename);
int				allow_map_format(t_game *game);
int				validate_map(t_game *game);
// player.c
int				handle_key(int keycode, void *param);
void			handle_player_movement(t_game *g, int new_x, int new_y);
// enemy.c
void			move_enemy(t_game *game);
int				try_enemy_move(t_game *game);
int				save_next_enemy_position(t_game *game, int *new_x, int *new_y);

#endif
