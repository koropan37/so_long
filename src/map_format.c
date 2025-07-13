/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 22:39:25 by skimura           #+#    #+#             */
/*   Updated: 2025/07/13 15:46:44 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	allow_map_chars_and_walls(t_game *game, int w, int h);
static int	count_players_and_exits(t_game *game, int w, int h);

int	allow_map_format(t_game *game)
{
	int	w;
	int	h;

	w = game->map.width;
	h = game->map.height;
	if (!allow_map_chars_and_walls(game, w, h))
		return (0);
	if (!count_players_and_exits(game, w, h))
		return (0);
	return (1);
}

static int	allow_map_chars_and_walls(t_game *game, int w, int h)
{
	char	c;
	int		x;
	int		y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			c = game->map.grid[y][x];
			if (!(c == '0' || c == '1' || c == 'C' || c == 'P' || c == 'E'
					|| c == 'X'))
				return (0);
			if ((y == 0 || y == h - 1 || x == 0 || x == w - 1) && c != '1')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	count_players_and_exits(t_game *game, int w, int h)
{
	int		player;
	int		exit;
	char	c;
	int		x;
	int		y;

	player = 0;
	exit = 0;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			c = game->map.grid[y][x];
			if (c == 'P')
				player++;
			if (c == 'E')
				exit++;
			x++;
		}
		y++;
	}
	return (player == 1 && exit == 1);
}
