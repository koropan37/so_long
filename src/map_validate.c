/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:31:29 by skimura           #+#    #+#             */
/*   Updated: 2025/07/13 19:20:15 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	dfs_fill(t_game *game, int *visited, int x, int y);
static int	validate_items(const t_game *game, const int *visited, int w);
static int	validate_exit(const t_game *game, const int *visited, int w, int h);

int	validate_map(t_game *game)
{
	int	w;
	int	h;
	int	*visited;
	int	ok;

	w = game->map.width;
	h = game->map.height;
	visited = ft_calloc(w * h, sizeof(int));
	if (!visited)
		return (0);
	dfs_fill(game, visited, game->player.x, game->player.y);
	ok = validate_items(game, visited, w) && validate_exit(game, visited, w, h);
	free(visited);
	return (ok);
}

static void	dfs_fill(t_game *game, int *visited, int x, int y)
{
	int			w;
	int			h;
	int			dx;
	int			dy;
	t_direction	i;

	w = game->map.width;
	h = game->map.height;
	if (x < 0 || x >= w || y < 0 || y >= h)
		return ;
	if (visited[y * w + x])
		return ;
	if (game->map.grid[y][x] == '1' || game->map.grid[y][x] == 'E')
		return ;
	visited[y * w + x] = 1;
	i = RIGHT;
	while (i <= UP)
	{
		save_direction_offset(i, &dx, &dy);
		dfs_fill(game, visited, x + dx, y + dy);
		i++;
	}
}

static int	validate_items(const t_game *game, const int *visited, int w)
{
	int	i;

	i = 0;
	while (i < game->item_count)
	{
		if (!visited[game->items[i].y * w + game->items[i].x])
			return (0);
		i++;
	}
	return (1);
}

static int	validate_exit(const t_game *game, const int *visited, int w, int h)
{
	int			ex;
	int			ey;
	int			dx;
	int			dy;
	t_direction	i;

	i = RIGHT;
	ex = game->map.exit_x;
	ey = game->map.exit_y;
	while (i <= UP)
	{
		save_direction_offset(i, &dx, &dy);
		if (ex + dx >= 0 && ex + dx < w && ey + dy >= 0 && ey + dy < h
			&& visited[(ey + dy) * w + (ex + dx)])
			return (1);
		i++;
	}
	return (0);
}
