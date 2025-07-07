/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:28:02 by skimura           #+#    #+#             */
/*   Updated: 2025/07/07 18:02:44 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// アイテム収集の処理
static void	handle_collectible(t_game *g, int new_x, int new_y)
{
	int	i;

	i = 0;
	while (i < g->item_count)
	{
		if (g->items[i].x == new_x && g->items[i].y == new_y
			&& !g->items[i].collected)
		{
			g->items[i].collected = 1;
			g->collected_items++;
			ft_printf("Item collected! (%d/%d)\n", g->collected_items,
				g->total_items);
			break ;
		}
		i++;
	}
}

// 出口に到達した時の処理
static void	handle_exit(t_game *g)
{
	if (g->collected_items >= g->total_items)
	{
		ft_printf("Congratulations! Game clear!\n");
		clean_exit(g);
	}
	else
	{
		ft_printf("Collect all items first! (%d/%d)\n", g->collected_items,
			g->total_items);
		return ; // 出口には入れないので移動しない
	}
}

// 敵との衝突処理
static void	handle_enemy_collision(t_game *g)
{
	ft_printf("Game Over! You touched the enemy!\n");
	clean_exit(g);
}

// プレイヤーの移動を実行して効果を適用
void	handle_player_movement(t_game *g, int new_x, int new_y)
{
	char	target_cell;

	target_cell = g->map.grid[new_y][new_x];
	// 特殊なセルの処理
	if (target_cell == 'C')
	{
		handle_collectible(g, new_x, new_y);
	}
	else if (target_cell == 'E')
	{
		handle_exit(g);
		return ; // 出口処理で移動しない場合があるため、ここでreturn
	}
	else if (target_cell == 'X')
	{
		handle_enemy_collision(g);
		return ; // ゲームオーバーなのでreturn
	}
	// プレイヤーの移動
	g->map.grid[g->player.y][g->player.x] = '0';
	g->map.grid[new_y][new_x] = 'P';
	g->player.x = new_x;
	g->player.y = new_y;
	g->player.move_count++;
	ft_printf("Moves: %d\n", g->player.move_count);
	// マップを再描画
	render_map(g);
}

// プレイヤーの移動を試行
void	try_move_player(t_game *g, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = g->player.x + dx;
	new_y = g->player.y + dy;
	// 移動先チェック
	if (new_y < 0 || new_y >= g->map.height || new_x < 0
		|| new_x >= g->map.width)
		return ;
	if (g->map.grid[new_y][new_x] == '1')
		return ;
	// 移動先のセルに基づいた処理
	handle_player_movement(g, new_x, new_y);
}

int	handle_key(int keycode, void *param)
{
	t_game	*g;
	int		new_x;
	int		new_y;

	g = (t_game *)param;
	if (!g)
		return (0);
	new_x = g->player.x;
	new_y = g->player.y;
	if (keycode == KEY_ESC)
		clean_exit(g);
	else if (keycode == KEY_W || keycode == KEY_UP)
		new_y--;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		new_y++;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		new_x--;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		new_x++;
	if (new_y < 0 || new_y >= g->map.height || new_x < 0
		|| new_x >= g->map.width)
		return (0);
	if (g->map.grid[new_y][new_x] == '1')
		return (0);
	handle_player_movement(g, new_x, new_y);
	return (0);
}
