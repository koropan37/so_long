/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:07:49 by skimura           #+#    #+#             */
/*   Updated: 2025/07/06 23:08:50 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_floor(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->floor_img, x * TILE, y
		* TILE);
}

void	render_wall(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->wall_img, x * TILE, y
		* TILE);
}

void	render_player(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->player_img, x * TILE, y
		* TILE);
}

void	render_exit(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->exit_img, x * TILE, y
		* TILE);
}

void	render_enemy(t_game *game, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->enemy_img, x * TILE, y
		* TILE);
}
