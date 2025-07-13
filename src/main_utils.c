/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:13:52 by skimura           #+#    #+#             */
/*   Updated: 2025/07/13 17:35:23 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game);
int		game_loop(t_game *game);
void	save_direction_offset(t_direction direction, int *dx, int *dy);
void	free_map(t_map *map);

int	allow_filename(char *filename)
{
	char	*extension;
	int		len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	extension = filename + len - 4;
	if (ft_strcmp(extension, ".ber") != 0)
		return (0);
	return (1);
}

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->player.direction = -1;
}

int	game_loop(t_game *game)
{
	static int	enemy_timer = 0;

	if (game->player.direction_timer > 0)
	{
		game->player.direction_timer--;
		if (game->player.direction_timer == 0)
		{
			game->player.direction = DEFAULT;
			render_map(game);
		}
	}
	enemy_timer++;
	if (enemy_timer >= ENEMY_SPEED)
	{
		move_enemy(game);
		render_map(game);
		enemy_timer = 0;
	}
	return (0);
}

void	save_direction_offset(t_direction direction, int *dx, int *dy)
{
	*dx = 0;
	*dy = 0;
	if (direction == RIGHT)
		*dx = 1;
	else if (direction == DOWN)
		*dy = 1;
	else if (direction == LEFT)
		*dx = -1;
	else if (direction == UP)
		*dy = -1;
}

void	free_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
}
