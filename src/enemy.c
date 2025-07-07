/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:13:20 by skimura           #+#    #+#             */
/*   Updated: 2025/07/07 17:42:45 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_enemy(t_game *game, int x, int y)
{
	game->enemy.x = x;
	game->enemy.y = y;
	game->enemy.start_x = x;
	game->enemy.start_y = y;
	game->enemy.direction = DOWN;
	game->enemy.steps_in_direction = 0;
	game->enemy.move_counter = 0;
}

// 方向に応じた移動量を計算
static void	get_direction_offset(t_direction direction, int *dx, int *dy)
{
	if (direction == RIGHT)
	{
		*dx = 1;
		*dy = 0;
	}
	else if (direction == DOWN)
	{
		*dx = 0;
		*dy = 1;
	}
	else if (direction == LEFT)
	{
		*dx = -1;
		*dy = 0;
	}
	else if (direction == UP)
	{
		*dx = 0;
		*dy = -1;
	}
}

// 敵の次の位置を計算
int	get_next_enemy_position(t_game *game, int *new_x, int *new_y)
{
	int	dx;
	int	dy;

	get_direction_offset(game->enemy.direction, &dx, &dy);
	*new_x = game->enemy.x + dx;
	*new_y = game->enemy.y + dy;
	// 境界チェック
	if (*new_x < 0 || *new_x >= game->map.width || *new_y < 0
		|| *new_y >= game->map.height)
		return (0);
	// 壁チェック
	if (game->map.grid[*new_y][*new_x] == '1')
		return (0);
	return (1);
}

// 敵を実際に移動させる
static void	execute_enemy_move(t_game *game, int new_x, int new_y)
{
	// 現在位置をクリア
	if (game->map.grid[game->enemy.y][game->enemy.x] == 'X')
		game->map.grid[game->enemy.y][game->enemy.x] = '0';
	// 敵を新しい位置に移動
	game->enemy.x = new_x;
	game->enemy.y = new_y;
	game->map.grid[new_y][new_x] = 'X';
}

// プレイヤーとの衝突をチェック
static void	check_player_collision(t_game *game, int new_x, int new_y)
{
	if (new_x == game->player.x && new_y == game->player.y)
	{
		ft_printf("Game Over! You were caught by the enemy!\n");
		clean_exit(game);
	}
}

// 敵の方向を時計回りに変更
static void	change_enemy_direction(t_game *game)
{
	game->enemy.direction = (game->enemy.direction + 1) % 4;
}

// 敵が移動を試行する
static int	try_enemy_move(t_game *game)
{
	int	new_x;
	int	new_y;

	if (get_next_enemy_position(game, &new_x, &new_y))
	{
		execute_enemy_move(game, new_x, new_y);
		check_player_collision(game, new_x, new_y);
		return (1);
	}
	return (0);
}

// 敵の移動処理
void	move_enemy(t_game *game)
{
	// 現在の方向で移動を試行
	if (try_enemy_move(game))
		return ;
	// 移動できない場合は方向転換（時計回り）
	change_enemy_direction(game);
	// 新しい方向で移動を試行
	if (try_enemy_move(game))
		return ;
	// それでも移動できない場合はもう一度方向転換
	change_enemy_direction(game);
}

// 敵の移動タイマー（MLXのループで呼び出される）
int	enemy_move_timer(t_game *game)
{
	game->enemy.move_counter++;
	if (game->enemy.move_counter >= ENEMY_SPEED)
	{
		move_enemy(game);
		render_map(game);
		game->enemy.move_counter = 0;
	}
	return (0);
}
