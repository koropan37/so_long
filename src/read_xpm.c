/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 03:50:45 by skimura           #+#    #+#             */
/*   Updated: 2025/07/07 18:00:16 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_basic_images(t_game *game);
static void	load_item_images(t_game *game);
static void	check_images_loaded(t_game *game);

void	load_images(t_game *game)
{
	load_basic_images(game);
	load_item_images(game);
	check_images_loaded(game);
}

static void	load_basic_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->wall_img = mlx_xpm_file_to_image(game->mlx, "xpm/wall.xpm",
			&img_width, &img_height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "xpm/floor.xpm",
			&img_width, &img_height);
	game->player_img = mlx_xpm_file_to_image(game->mlx, "xpm/pai_chun.xpm",
			&img_width, &img_height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "xpm/pai_haku.xpm",
			&img_width, &img_height);
	game->enemy_img = mlx_xpm_file_to_image(game->mlx, "xpm/so_5.xpm",
			&img_width, &img_height);
}

static void	load_item_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->item_img[ITEM_ONE] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_1.xpm",
			&img_width, &img_height);
	game->item_img[ITEM_TWO] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_2.xpm",
			&img_width, &img_height);
	game->item_img[ITEM_THREE] = mlx_xpm_file_to_image(game->mlx,
			"xpm/pin_3.xpm", &img_width, &img_height);
	game->item_img[ITEM_FOUR] = mlx_xpm_file_to_image(game->mlx,
			"xpm/pin_4.xpm", &img_width, &img_height);
	game->item_img[ITEM_FIVE] = mlx_xpm_file_to_image(game->mlx,
			"xpm/pin_5.xpm", &img_width, &img_height);
	game->item_img[ITEM_SIX] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_6.xpm",
			&img_width, &img_height);
	game->item_img[ITEM_SEVEN] = mlx_xpm_file_to_image(game->mlx,
			"xpm/pin_7.xpm", &img_width, &img_height);
	game->item_img[ITEM_EIGHT] = mlx_xpm_file_to_image(game->mlx,
			"xpm/pin_8.xpm", &img_width, &img_height);
	game->item_img[ITEM_NINE] = mlx_xpm_file_to_image(game->mlx,
			"xpm/pin_9.xpm", &img_width, &img_height);
}

static void	check_images_loaded(t_game *game)
{
	int	i;

	if (!game->wall_img || !game->floor_img || !game->player_img
		|| !game->exit_img || !game->enemy_img)
	{
		ft_printf("Error: Failed to load basic images\n");
		clean_exit(game);
	}
	i = ITEM_ONE;
	while (i < ITEM_MAX)
	{
		if (!game->item_img[i])
		{
			ft_printf("Error: Failed to load item image %d\n", i);
			clean_exit(game);
		}
		i++;
	}
}
