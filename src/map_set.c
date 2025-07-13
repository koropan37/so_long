/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:53:13 by skimura           #+#    #+#             */
/*   Updated: 2025/07/13 16:08:45 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	setup_item(t_game *game, char c, int x, int y);
static void	setup_exit(t_game *game, int x, int y);
static void	setup_player(t_game *game, int x, int y);
static void	setup_enemy(t_game *game, int x, int y);

void	parse_map(t_game *game, char c, int x, int y)
{
	game->map.grid[y][x] = c;
	if (c == '0')
		game->map.grid[y][x] = '0';
	else if (c == '1')
		game->map.grid[y][x] = '1';
	else if (c == 'P')
		setup_player(game, x, y);
	else if (c == 'E')
		setup_exit(game, x, y);
	else if (c == 'C' || (c >= '2' && c <= '9'))
		setup_item(game, c, x, y);
	else if (c == 'X')
		setup_enemy(game, x, y);
}

static void	setup_player(t_game *game, int x, int y)
{
	game->player.x = x;
	game->player.y = y;
	game->map.grid[y][x] = 'P';
}

static void	setup_exit(t_game *game, int x, int y)
{
	game->map.exit_x = x;
	game->map.exit_y = y;
	game->map.grid[y][x] = 'E';
}

static void	setup_item(t_game *game, char c, int x, int y)
{
	if (c == 'C')
		add_item(game, ONE, x, y);
	else if (c == '2')
		add_item(game, TWO, x, y);
	else if (c == '3')
		add_item(game, THREE, x, y);
	else if (c == '4')
		add_item(game, FOUR, x, y);
	else if (c == '5')
		add_item(game, FIVE, x, y);
	else if (c == '6')
		add_item(game, SIX, x, y);
	else if (c == '7')
		add_item(game, SEVEN, x, y);
	else if (c == '8')
		add_item(game, EIGHT, x, y);
	else if (c == '9')
		add_item(game, NINE, x, y);
}

static void	setup_enemy(t_game *game, int x, int y)
{
	game->enemy.x = x;
	game->enemy.y = y;
	game->enemy.start_x = x;
	game->enemy.start_y = y;
	game->enemy.direction = DOWN;
	game->enemy.move_counter = 0;
}
