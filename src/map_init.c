/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:04:08 by skimura           #+#    #+#             */
/*   Updated: 2025/07/13 18:15:47 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_map_size(t_game *game, char *filename);
static int	process_map_line(t_game *game, char *line, int y);
static int	load_map_data(t_game *game, char *filename);

int	init_map(t_game *game, char *filename)
{
	if (!get_map_size(game, filename))
		return (0);
	game->map.grid = malloc(sizeof(char *) * game->map.height);
	if (!game->map.grid)
		return (0);
	if (!load_map_data(game, filename))
	{
		free_map(&game->map);
		return (0);
	}
	return (1);
}

static int	get_map_size(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (y == 0)
			game->map.width = ft_strlen(line) - 1;
		free(line);
		y++;
		line = get_next_line(fd);
	}
	game->map.height = y;
	close(fd);
	return (1);
}

static int	load_map_data(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!process_map_line(game, line, y))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

static int	process_map_line(t_game *game, char *line, int y)
{
	int	x;

	game->map.grid[y] = malloc(sizeof(char) * (game->map.width + 1));
	if (!game->map.grid[y])
		return (0);
	x = 0;
	while (x < game->map.width && line[x] != '\n' && line[x] != '\0')
	{
		game->map.grid[y][x] = line[x];
		x++;
	}
	game->map.grid[y][x] = '\0';
	x = 0;
	while (x < game->map.width)
	{
		parse_map(game, game->map.grid[y][x], x, y);
		x++;
	}
	return (1);
}
