/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:30:45 by skimura           #+#    #+#             */
/*   Updated: 2025/07/13 20:06:39 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int			try_enemy_move(t_game *game);
int			save_next_enemy_position(t_game *game, int *new_x, int *new_y);
static void	execute_enemy_move(t_game *game, int new_x, int new_y);
static void	load_player_collision(t_game *game, int new_x, int new_y);

void	move_enemy(t_game *game)
{
	int	attempts;

	attempts = 0;
	while (attempts < 4)
	{
		if (try_enemy_move(game))
			return ;
		game->enemy.direction = (game->enemy.direction + 1) % 4;
		attempts++;
	}
}

int	try_enemy_move(t_game *game)
{
	int	new_x;
	int	new_y;

	if (save_next_enemy_position(game, &new_x, &new_y))
	{
		execute_enemy_move(game, new_x, new_y);
		load_player_collision(game, new_x, new_y);
		return (1);
	}
	return (0);
}

int	save_next_enemy_position(t_game *game, int *new_x, int *new_y)
{
	int	dx;
	int	dy;

	save_direction_offset(game->enemy.direction, &dx, &dy);
	*new_x = game->enemy.x + dx;
	*new_y = game->enemy.y + dy;
	if (*new_x < 0 || *new_x >= game->map.width || *new_y < 0
		|| *new_y >= game->map.height)
		return (0);
	if (game->map.grid[*new_y][*new_x] == '1')
		return (0);
	return (1);
}

static void	execute_enemy_move(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[game->enemy.y][game->enemy.x] == 'X')
		game->map.grid[game->enemy.y][game->enemy.x] = '0';
	game->enemy.x = new_x;
	game->enemy.y = new_y;
	game->map.grid[new_y][new_x] = 'X';
}

static void	load_player_collision(t_game *game, int new_x, int new_y)
{
	if (new_x == game->player.x && new_y == game->player.y)
	{
		ft_printf("<GAME OVER> [-12,000]\n");
		clean_exit(game);
	}
}
