/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:53:13 by skimura           #+#    #+#             */
/*   Updated: 2025/07/07 15:56:46 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_item(t_game *game, char c, int x, int y);
static void	set_exit(t_game *game, int x, int y);
static void	set_player(t_game *game, int x, int y);


void	parse_map(t_game *game, char c, int x, int y)
{
	if (c == '0')
		game->map.grid[y][x] = '0';
	else if (c == '1')
		game->map.grid[y][x] = '1';
	else if (c == 'P')
		set_player(game, x, y);
	else if (c == 'E')
		set_exit(game, x, y);
	else if (c == 'C' || (c >= '2' && c <= '9'))
		set_item(game, c, x, y);
	else if (c == 'X')
		init_enemy(game, x, y);
	else
		game->map.grid[y][x] = '0';
}

static void	set_player(t_game *game, int x, int y)
{
	game->player.x = x;
	game->player.y = y;
	game->map.grid[y][x] = 'P';
}

static void	set_exit(t_game *game, int x, int y)
{
	game->map.exit_x = x;
	game->map.exit_y = y;
	game->map.grid[y][x] = 'E';
}

static void	set_item(t_game *game, char c, int x, int y)
{
	if (c == 'C')
		add_item(game, ITEM_ONE, x, y);
	else if (c == '2')
		add_item(game, ITEM_TWO, x, y);
	else if (c == '3')
		add_item(game, ITEM_THREE, x, y);
	else if (c == '4')
		add_item(game, ITEM_FOUR, x, y);
	else if (c == '5')
		add_item(game, ITEM_FIVE, x, y);
	else if (c == '6')
		add_item(game, ITEM_SIX, x, y);
	else if (c == '7')
		add_item(game, ITEM_SEVEN, x, y);
	else if (c == '8')
		add_item(game, ITEM_EIGHT, x, y);
	else if (c == '9')
		add_item(game, ITEM_NINE, x, y);
}
