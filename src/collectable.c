/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:26:51 by skimura           #+#    #+#             */
/*   Updated: 2025/07/07 21:00:27 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_item(t_game *game, t_item_type type, int x, int y)
{
	t_item	*new_items;
	int		i;

	new_items = malloc(sizeof(t_item) * (game->item_count + 1));
	if (!new_items)
		return ;
	i = 0;
	while (i < game->item_count)
	{
		new_items[i] = game->items[i];
		i++;
	}
	if (game->items)
		free(game->items);
	game->items = new_items;
	game->items[game->item_count].type = type;
	game->items[game->item_count].x = x;
	game->items[game->item_count].y = y;
	game->items[game->item_count].collected = 0;
	game->item_count++;
	game->total_items++;
	game->map.grid[y][x] = 'C';
}

void	free_items(t_game *game)
{
	if (game->items)
	{
		free(game->items);
		game->items = NULL;
	}
}
