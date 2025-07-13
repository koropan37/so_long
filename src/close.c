/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 04:01:44 by skimura           #+#    #+#             */
/*   Updated: 2025/07/12 22:16:04 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_images(t_game *game);
static void	destroy_basic_images(t_game *game);
static void	destroy_mlx_resources(t_game *game);
void		clean_exit(t_game *game);

int	close_window(t_game *game)
{
	clean_exit(game);
	return (0);
}

void	clean_exit(t_game *game)
{
	if (!game)
		exit(0);
	if (game->mlx)
		destroy_images(game);
	free_map(&game->map);
	free_items(game);
	destroy_mlx_resources(game);
	exit(0);
}

static void	destroy_images(t_game *game)
{
	int	i;

	destroy_basic_images(game);
	i = 0;
	while (i < 10)
	{
		if (game->number_img[i])
			mlx_destroy_image(game->mlx, game->number_img[i]);
		i++;
	}
	i = ONE;
	while (i < MAX)
	{
		if (game->item_img[i])
			mlx_destroy_image(game->mlx, game->item_img[i]);
		i++;
	}
}

static void	destroy_basic_images(t_game *game)
{
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->player_img_left)
		mlx_destroy_image(game->mlx, game->player_img_left);
	if (game->player_img_right)
		mlx_destroy_image(game->mlx, game->player_img_right);
	if (game->player_img_up)
		mlx_destroy_image(game->mlx, game->player_img_up);
	if (game->player_img_down)
		mlx_destroy_image(game->mlx, game->player_img_down);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->enemy_img)
		mlx_destroy_image(game->mlx, game->enemy_img);
}

static void	destroy_mlx_resources(t_game *game)
{
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}
