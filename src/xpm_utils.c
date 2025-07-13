/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:33:44 by skimura           #+#    #+#             */
/*   Updated: 2025/07/13 15:15:34 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	allow_basic_images(t_game *game);
static void	allow_player_images(t_game *game);
static void	allow_item_images(t_game *game);
static void	allow_number_images(t_game *game);

void	allow_images_loaded(t_game *game)
{
	allow_basic_images(game);
	allow_player_images(game);
	allow_item_images(game);
	allow_number_images(game);
}

static void	allow_basic_images(t_game *game)
{
	if (!game->wall_img || !game->floor_img || !game->player_img
		|| !game->exit_img || !game->enemy_img)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to load basic images: %s\n",
			strerror(errno));
		clean_exit(game);
	}
}

static void	allow_player_images(t_game *game)
{
	if (!game->player_img_left || !game->player_img_right
		|| !game->player_img_up || !game->player_img_down)
	{
		ft_fprintf(STDERR_FILENO, "Error: Failed to load player images: %s\n",
			strerror(errno));
		clean_exit(game);
	}
}

static void	allow_item_images(t_game *game)
{
	int	i;

	i = ONE;
	while (i < MAX)
	{
		if (!game->item_img[i])
		{
			ft_fprintf(STDERR_FILENO, "Error: [pin_%d] : %s\n", i,
				strerror(errno));
			clean_exit(game);
		}
		i++;
	}
}

static void	allow_number_images(t_game *game)
{
	int	i;

	i = NONE;
	while (i < MAX)
	{
		if (!game->number_img[i])
		{
			ft_fprintf(STDERR_FILENO, "Error: [number_%d] : %s\n", i,
				strerror(errno));
			clean_exit(game);
		}
		i++;
	}
}
