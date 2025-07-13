/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 03:48:39 by skimura           #+#    #+#             */
/*   Updated: 2025/07/13 15:44:39 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	setup_map(t_game *game, char *filename);
static int	setup_mlx(t_game *game);
static int	setup_window(t_game *game);
static void	playing_game(t_game *game);

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_fprintf(STDERR_FILENO, "Error: ./so_long map_file.ber\n");
		return (1);
	}
	if (!allow_filename(argv[1]))
	{
		ft_fprintf(STDERR_FILENO, "Error: Invalid filename. use '.ber'\n");
		return (1);
	}
	init_game(&game);
	if (!setup_map(&game, argv[1]))
		return (1);
	if (!setup_mlx(&game))
		return (1);
	if (!setup_window(&game))
		return (1);
	playing_game(&game);
	return (0);
}

static int	setup_map(t_game *game, char *filename)
{
	if (!init_map(game, filename))
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to load map '%s':%s\n",
			filename, strerror(errno));
		return (0);
	}
	if (!allow_map_format(game))
	{
		ft_fprintf(STDERR_FILENO, "Error: Invalid map format in '%s'\n",
			filename);
		free_map(&game->map);
		free_items(game);
		return (0);
	}
	if (!validate_map(game))
	{
		ft_fprintf(STDERR_FILENO, "Error: Map validation failed for '%s'\n",
			filename);
		free_map(&game->map);
		free_items(game);
		return (0);
	}
	return (1);
}

static int	setup_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to initialize MLX library\n");
		free_map(&game->map);
		free_items(game);
		return (0);
	}
	return (1);
}

static int	setup_window(t_game *game)
{
	load_images(game);
	game->win = mlx_new_window(game->mlx, game->map.width * TILE,
			game->map.height * TILE, "so_long");
	if (!game->win)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to create window (%dx%d)\n",
			game->map.width * TILE, game->map.height * TILE);
		clean_exit(game);
		return (0);
	}
	return (1);
}

static void	playing_game(t_game *game)
{
	mlx_hook(game->win, ON_KEYDOWN, EVENT_MASK_KEYPRESS, handle_key, game);
	mlx_hook(game->win, ON_DESTROY, EVENT_MASK_NONE, close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	render_map(game);
	mlx_loop(game->mlx);
}
