/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:28:02 by skimura           #+#    #+#             */
/*   Updated: 2025/07/13 19:46:53 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	process_player_move(t_game *g, int keycode);
static void	save_movement_direction(int keycode, int *dx, int *dy,
				t_direction *direction);
static int	is_valid_move(t_game *g, int x, int y);

int	handle_key(int keycode, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (!g)
		return (0);
	if (keycode == KEY_ESC)
	{
		clean_exit(g);
		return (0);
	}
	process_player_move(g, keycode);
	return (0);
}

static void	process_player_move(t_game *g, int keycode)
{
	int			dx;
	int			dy;
	int			nx;
	int			ny;
	t_direction	direction;

	save_movement_direction(keycode, &dx, &dy, &direction);
	if (dx == 0 && dy == 0)
		return ;
	nx = g->player.x + dx;
	ny = g->player.y + dy;
	if (is_valid_move(g, nx, ny))
	{
		g->player.direction = direction;
		g->player.direction_timer = PLAYER_SPEED;
		handle_player_movement(g, nx, ny);
	}
	else
	{
		g->player.direction = direction;
		g->player.direction_timer = PLAYER_SPEED / 2;
		render_map(g);
	}
}

static void	save_movement_direction(int keycode, int *dx, int *dy,
		t_direction *direction)
{
	*dx = 0;
	*dy = 0;
	if (keycode == KEY_W || keycode == KEY_UP)
		*direction = UP;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		*direction = DOWN;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		*direction = LEFT;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		*direction = RIGHT;
	else
		return ;
	save_direction_offset(*direction, dx, dy);
}

static int	is_valid_move(t_game *g, int x, int y)
{
	if (y < 0 || y >= g->map.height || x < 0 || x >= g->map.width)
		return (0);
	if (g->map.grid[y][x] == '1')
		return (0);
	return (1);
}
