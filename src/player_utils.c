/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:37:58 by skimura           #+#    #+#             */
/*   Updated: 2025/07/12 17:18:27 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_collectible(t_game *g, int x, int y);
void	handle_exit(t_game *g);

void	handle_player_movement(t_game *g, int x, int y)
{
	char	cell;

	cell = g->map.grid[y][x];
	if (cell == 'C')
		handle_collectible(g, x, y);
	else if (cell == 'E')
	{
		handle_exit(g);
		return ;
	}
	else if (cell == 'X')
	{
		ft_printf("<GAME OVER> [-12,000]\n");
		clean_exit(g);
		return ;
	}
	g->map.grid[g->player.y][g->player.x] = '0';
	g->map.grid[y][x] = 'P';
	g->player.x = x;
	g->player.y = y;
	g->player.move_count++;
	ft_printf("Moves: %d\n", g->player.move_count);
	render_map(g);
}

void	handle_collectible(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->item_count)
	{
		if (g->items[i].x == x && g->items[i].y == y && !g->items[i].collected)
		{
			g->items[i].collected = 1;
			g->collected_items++;
			break ;
		}
		i++;
	}
}

void	handle_exit(t_game *g)
{
	if (g->collected_items >= g->total_items)
	{
		ft_printf("<Game Clear> [+12,000]\n");
		clean_exit(g);
	}
	else
		ft_printf("Collect all items first! (%d/%d)\n", g->collected_items,
			g->total_items);
}
