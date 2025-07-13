/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 03:48:11 by skimura           #+#    #+#             */
/*   Updated: 2025/07/12 19:51:44 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_cell(t_game *game, int x, int y);
void		render_item(t_game *game, int x, int y);

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			render_cell(game, x, y);
			x++;
		}
		y++;
	}
	render_ui_in_map(game);
}

static void	render_cell(t_game *game, int x, int y)
{
	char	cell;

	cell = game->map.grid[y][x];
	render_floor(game, x, y);
	if (cell == '1')
		render_wall(game, x, y);
	else if (cell == 'P')
		render_player(game, x, y);
	else if (cell == 'E')
		render_exit(game, x, y);
	else if (cell == 'X')
		render_enemy(game, x, y);
	else if (cell == 'C')
		render_item(game, x, y);
}

void	render_item(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->item_count)
	{
		if (game->items[i].x == x && game->items[i].y == y
			&& !game->items[i].collected)
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->item_img[game->items[i].type], x * TILE, y * TILE);
			return ;
		}
		i++;
	}
}
