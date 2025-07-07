/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skimura <skimura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 03:48:39 by skimura           #+#    #+#             */
/*   Updated: 2025/07/07 16:00:37 by skimura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// マップのメモリを解放
void	free_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
}

// 必要な関数の実装例
void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->player.move_count = 0;
	game->collected_items = 0;
	game->total_items = 0;
	game->item_count = 0;
}

int	init_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int		y;
	int		x;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	// まず高さを計算
	y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (y == 0)
			game->map.width = ft_strlen(line) - 1; // 改行文字を除く
		free(line);
		y++;
	}
	game->map.height = y;
	close(fd);
	// マップのメモリ確保
	game->map.grid = malloc(sizeof(char *) * game->map.height);
	if (!game->map.grid)
		return (0);
	// 再度ファイルを開いて実際の読み込み
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(game->map.grid);
		return (0);
	}
	y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		// 各行のメモリ確保
		game->map.grid[y] = malloc(sizeof(char) * (game->map.width + 1));
		if (!game->map.grid[y])
		{
			free(line);
			close(fd);
			return (0);
		}
		// 文字を一つずつ処理
		x = 0;
		while (x < game->map.width && line[x] != '\n' && line[x] != '\0')
		{
			parse_map(game, line[x], x, y);
			x++;
		}
		game->map.grid[y][x] = '\0';
		free(line);
		y++;
	}
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Usage: ./so_long map_file.ber\n");
		return (1);
	}
	// ゲーム初期化
	init_game(&game);
	// マップ読み込み
	if (!init_map(&game, argv[1]))
	{
		ft_printf("Error: Invalid map\n");
		free_map(&game.map);
		return (1);
	}
	// MLX初期化
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		ft_printf("Error: Failed to initialize MLX\n");
		free_map(&game.map);
		free_items(&game);
		return (1);
	}
	// 画像読み込み
	load_images(&game);
	// ウィンドウ作成
	game.win = mlx_new_window(game.mlx, game.map.width * TILE, game.map.height
			* TILE, "so_long");
	if (!game.win)
	{
		ft_printf("Error: Failed to create window\n");
		clean_exit(&game);
		return (1);
	}
	// イベントフック設定
	mlx_hook(game.win, 2, 1L << 0, handle_key, &game);
	// ウィンドウクローズイベントのフック追加
	mlx_hook(game.win, 17, 0, close_window, &game);
	// 敵の移動タイマー設定
	mlx_loop_hook(game.mlx, enemy_move_timer, &game);
	// マップ描画
	render_map(&game);
	// メインループ
	mlx_loop(game.mlx);
	return (0);
}
