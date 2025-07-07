/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 04:01:44 by skimura           #+#    #+#             */
/*   Updated: 2025/07/07 17:36:25 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_game *game)
{
	clean_exit(game);
	return (0);
}

void	clean_exit(t_game *g)
{
	int	i;

	i = ITEM_ONE ;
	if (g->floor_img) mlx_destroy_image(g->mlx, g->floor_img);
	if (g->wall_img)
		mlx_destroy_image(g->mlx, g->wall_img);
	if (g->player_img)
		mlx_destroy_image(g->mlx, g->player_img);
	if (g->exit_img)
		mlx_destroy_image(g->mlx, g->exit_img);
	if (g->enemy_img)
		mlx_destroy_image(g->mlx, g->enemy_img);
	while (i < ITEM_MAX)
	{
		if (g->item_img[i])
			mlx_destroy_image(g->mlx, g->item_img[i]);
		i++;
	}
	free_map(&g->map);
	free_items(g);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	exit(0);
}
