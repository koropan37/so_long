/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ui.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:47:10 by skimura           #+#    #+#             */
/*   Updated: 2025/07/12 22:53:32 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_ui_area(t_ui *ui);
static void	draw_ui_background(t_game *game);
static void	draw_multi_digit_number(t_game *game, int number);

void	render_ui_in_map(t_game *game)
{
	init_ui_area(&game->ui);
	draw_ui_background(game);
	draw_multi_digit_number(game, game->player.move_count);
}

static void	init_ui_area(t_ui *ui)
{
	ui->x = UI_START * TILE;
	ui->y = UI_START * TILE;
	ui->width = UI_WIDTH * TILE;
	ui->height = UI_HEIGHT * TILE;
	ui->digit_width = TILE;
	ui->number_x = ui->x + UI_NUMBER_X;
	ui->number_y = ui->y + UI_NUMBER_Y;
}

static void	draw_ui_background(t_game *game)
{
	int	i;
	int	j;
	int	tiles_x;
	int	tiles_y;

	tiles_x = game->ui.width / TILE;
	tiles_y = game->ui.height / TILE;
	i = 0;
	while (i < tiles_x)
	{
		j = 0;
		while (j < tiles_y)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor_img,
				game->ui.x + (i * TILE), game->ui.y + (j * TILE));
			j++;
		}
		i++;
	}
}

static void	draw_multi_digit_number(t_game *game, int number)
{
	char	*num_str;
	int		i;
	int		digit;

	num_str = ft_itoa(number);
	i = 0;
	while (num_str[i])
	{
		digit = num_str[i] - '0';
		if (digit >= 0 && digit <= 9)
			mlx_put_image_to_window(game->mlx, game->win,
				game->number_img[digit], game->ui.number_x + (i
					* game->ui.digit_width), game->ui.number_y);
		i++;
	}
	free(num_str);
}
