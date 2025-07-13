/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 03:50:45 by skimura           #+#    #+#             */
/*   Updated: 2025/07/13 15:15:57 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_basic_images(t_game *game);
static void	load_item_images(t_game *game);
static void	load_number_images(t_game *game);

void	load_images(t_game *game)
{
	load_basic_images(game);
	load_item_images(game);
	load_number_images(game);
	allow_images_loaded(game);
}

static void	load_basic_images(t_game *game)
{
	int	w;
	int	h;

	game->wall_img = mlx_xpm_file_to_image(game->mlx, "xpm/wall.xpm", &w, &h);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "xpm/floor.xpm", &w, &h);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "xpm/pai_haku.xpm", &w,
			&h);
	game->enemy_img = mlx_xpm_file_to_image(game->mlx, "xpm/so_5.xpm", &w, &h);
	game->player_img = mlx_xpm_file_to_image(game->mlx, "xpm/pai_chun.xpm", &w,
			&h);
	game->player_img_left = mlx_xpm_file_to_image(game->mlx, "xpm/pai_left.xpm",
			&w, &h);
	game->player_img_right = mlx_xpm_file_to_image(game->mlx,
			"xpm/pai_right.xpm", &w, &h);
	game->player_img_up = mlx_xpm_file_to_image(game->mlx, "xpm/pai_up.xpm", &w,
			&h);
	game->player_img_down = mlx_xpm_file_to_image(game->mlx, "xpm/pai_down.xpm",
			&w, &h);
}

static void	load_item_images(t_game *game)
{
	int	w;
	int	h;

	game->item_img[ONE] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_1.xpm", &w,
			&h);
	game->item_img[TWO] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_2.xpm", &w,
			&h);
	game->item_img[THREE] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_3.xpm",
			&w, &h);
	game->item_img[FOUR] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_4.xpm", &w,
			&h);
	game->item_img[FIVE] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_5.xpm", &w,
			&h);
	game->item_img[SIX] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_6.xpm", &w,
			&h);
	game->item_img[SEVEN] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_7.xpm",
			&w, &h);
	game->item_img[EIGHT] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_8.xpm",
			&w, &h);
	game->item_img[NINE] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_9.xpm", &w,
			&h);
}

static void	load_number_images(t_game *game)
{
	int	w;
	int	h;

	game->number_img[NONE] = mlx_xpm_file_to_image(game->mlx,
			"xpm/pai_haku.xpm", &w, &h);
	game->number_img[ONE] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_1.xpm",
			&w, &h);
	game->number_img[TWO] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_2.xpm",
			&w, &h);
	game->number_img[THREE] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_3.xpm",
			&w, &h);
	game->number_img[FOUR] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_4.xpm",
			&w, &h);
	game->number_img[FIVE] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_5.xpm",
			&w, &h);
	game->number_img[SIX] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_6.xpm",
			&w, &h);
	game->number_img[SEVEN] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_7.xpm",
			&w, &h);
	game->number_img[EIGHT] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_8.xpm",
			&w, &h);
	game->number_img[NINE] = mlx_xpm_file_to_image(game->mlx, "xpm/pin_9.xpm",
			&w, &h);
}
