/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:44:27 by skimura           #+#    #+#             */
/*   Updated: 2025/07/07 17:59:47 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "/home/skimura/minilibx-linux/mlx.h"
# include "/home/skimura/mylibft/include/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TILE 64
# define ALLOC_SIZE 16
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

# define ENEMY_SPEED 500
// X11イベント定義を追加
# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

typedef enum e_item_type
{
	ITEM_NONE = 0,
	ITEM_ONE,   // 1筒
	ITEM_TWO,   // 2筒
	ITEM_THREE, // 3筒
	ITEM_FOUR,  // 4筒
	ITEM_FIVE,  // 5筒
	ITEM_SIX,   // 6筒
	ITEM_SEVEN, // 7筒
	ITEM_EIGHT, // 8筒
	ITEM_NINE,  // 9筒
	ITEM_MAX
}			t_item_type;

// アイテムを表す構造体
typedef struct s_item
{
	t_item_type type; // アイテムの種類
	int x;            // マップ上のX座標
	int y;            // マップ上のY座標
	int collected;    // 収集済みフラグ
}			t_item;

// プレイヤーを表す構造体
typedef struct s_player
{
	int x;          // X座標
	int y;          // Y座標
	int move_count; // 移動回数
}			t_player;

// マップを表す構造体
typedef struct s_map
{
	char **grid;     // マップの2次元配列
	int width;       // マップの幅
	int height;      // マップの高さ
	int exit_x;      // 出口のX座標
	int exit_y;      // 出口のY座標
	int is_valid;    // マップが有効かどうか
	int is_solvable; // マップが解決可能かどうか
}			t_map;

// 敵を表す構造体
typedef struct s_enemy
{
	int x;                  // X座標
	int y;                  // Y座標
	int start_x;            // 開始位置X
	int start_y;            // 開始位置Y
	int direction;          // 現在の方向（0=右、1=下、2=左、3=上）
	int steps_in_direction; // 現在の方向に進んだ歩数
	int side_length;        // 正方形の一辺の長さ（17）
	int move_counter;       // 移動タイマー
}			t_enemy;

// 敵の移動方向を定義
typedef enum e_direction
{
	RIGHT = 0,
	DOWN = 1,
	LEFT = 2,
	UP = 3
}			t_direction;

typedef struct s_game
{
	void *mlx;           // MLXインスタンス
	void *win;           // ウィンドウインスタンス
	t_map map;           // マップ情報
	t_player player;     // プレイヤー情報
	t_enemy enemy;       // 敵情報
	int collected_items; // 収集したアイテム数
	int total_items;     // マップ上の全アイテム数
	t_item *items;       // アイテム配列
	int item_count;      // アイテム総数
	void	*floor_img;
	void	*wall_img;
	void	*player_img;
	void	*collectible_img;
	void	*exit_img;
	void	*enemy_img;
	void *item_img[ITEM_MAX]; // 数字アイテム用画像配列
}			t_game;

// 関数プロトタイプ
// main.c
int			handle_key(int keycode, void *param);
void		try_move_player(t_game *g, int dx, int dy);
void		handle_player_movement(t_game *g, int new_x, int new_y);
void		free_map(t_map *map);
void		free_items(t_game *game);
void		init_game(t_game *game);
int			init_map(t_game *game, char *filename);

// collectable.c
void		parse_map(t_game *game, char c, int x, int y);
void		add_item(t_game *game, t_item_type type, int x, int y);
void		render_item(t_game *game, int x, int y);
int			collect_item(t_game *g, int x, int y);
int			is_all_items_collected(t_game *g);

// read_xpm.c
void		load_images(t_game *game);

// read_map.c
void		render_map(t_game *game);
void		render_floor(t_game *game, int x, int y);
void		render_wall(t_game *game, int x, int y);
void		render_player(t_game *game, int x, int y);
void		render_exit(t_game *game, int x, int y);
void		render_enemy(t_game *game, int x, int y);

// close.c
int			close_window(t_game *game);
void		clean_exit(t_game *g);

// enemy.c
void		init_enemy(t_game *game, int x, int y);
void		move_enemy(t_game *game);
int			enemy_move_timer(t_game *game);
int			get_next_enemy_position(t_game *game, int *new_x, int *new_y);
void		place_enemy_at_boundary(t_game *game);
void		force_enemy_to_patrol_area(t_game *game);

#endif
