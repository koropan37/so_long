/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:26:51 by skimura           #+#    #+#             */
/*   Updated: 2025/07/07 16:06:46 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// アイテムを追加する
void	add_item(t_game *game, t_item_type type, int x, int y)
{
	t_item	*new_items;
	int		i;

	// 新しいサイズで配列を再確保（現在の数+1）
	new_items = malloc(sizeof(t_item) * (game->item_count + 1));
	if (!new_items)
		return ;
	// 既存のデータをコピー
	i = 0;
	while (i < game->item_count)
	{
		new_items[i] = game->items[i];
		i++;
	}
	// 古い配列を解放
	if (game->items)
		free(game->items);
	// 新しい配列を設定
	game->items = new_items;
	// 新しいアイテムの情報を設定
	game->items[game->item_count].type = type;
	game->items[game->item_count].x = x;
	game->items[game->item_count].y = y;
	game->items[game->item_count].collected = 0;
	// アイテム数をカウント
	game->item_count++;
	game->total_items++;
	// マップにはCとして記録
	game->map.grid[y][x] = 'C';
}

// アイテムの収集処理
int	collect_item(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->item_count)
	{
		if (g->items[i].x == x && g->items[i].y == y && !g->items[i].collected)
		{
			// アイテムを収集済みにする
			g->items[i].collected = 1;
			g->collected_items++;
			ft_printf("Item collected! (%d/%d)\n", g->collected_items,
				g->total_items);
			return (1);
		}
		i++;
	}
	return (0);
}

// アイテムが全て収集されているか確認
int	is_all_items_collected(t_game *g)
{
	return (g->collected_items >= g->total_items);
}

// アイテムのメモリを解放
void	free_items(t_game *game)
{
	if (game->items)
	{
		free(game->items);
		game->items = NULL;
	}
}
