/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 21:31:15 by besellem          #+#    #+#             */
/*   Updated: 2022/02/22 17:35:41 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

#define INITIAL_WIDTH  800
#define INITIAL_HEIGHT 800

struct	s_textures
{
	int		id;
	char	*path;
};

static void	fill_texture(t_msweeper *ms, t_img *tx, char *path)
{
	const int	fd = open(path, O_RDONLY | O_NOFOLLOW);

	if (SYSCALL_ERR == fd || close(fd))
		_error("Unable to open a texture", ms, __FILE__, __LINE__);
	if (is_extension(path, ".xpm"))
	{
		tx->ptr = mlx_xpm_file_to_image(ms->mlx, path, &tx->x, &tx->y);
		if (!tx->ptr)
			_error("Unable to open a texture", ms, __FILE__, __LINE__);
	}
	else
	{
		ft_printf("[%s] ", path);
		_error("Not a valid texture file", ms, __FILE__, __LINE__);
	}
	tx->addr = mlx_get_data_addr(tx->ptr, &tx->bpp, &tx->size_line,
			&tx->endian);
	if (!tx->addr)
		_error("Malloc error", ms, __FILE__, __LINE__);
}

static int	load_textures(t_msweeper *ms)
{
	static const struct s_textures	g_txtrs[] = {
		{TXTR_BOMB, TEXTURE_BOMB},
		{TXTR_FLAG, TEXTURE_FLAG},
		{TXTR_HIDDEN, TEXTURE_HIDDEN},
		{TXTR_EMPTY, TEXTURE_EMPTY},
		{TXTR_NUM_1, TEXTURE_NUM_1},
		{TXTR_NUM_2, TEXTURE_NUM_2},
		{TXTR_NUM_3, TEXTURE_NUM_3},
		{TXTR_NUM_4, TEXTURE_NUM_4},
		{TXTR_NUM_5, TEXTURE_NUM_5},
		{TXTR_NUM_6, TEXTURE_NUM_6},
		{TXTR_NUM_7, TEXTURE_NUM_7},
		{TXTR_NUM_8, TEXTURE_NUM_8},
		{0, NULL}
	};
	int								i;

	i = 0;
	while (g_txtrs[i].id)
	{
		fill_texture(ms, &ms->txtrs[g_txtrs[i].id], g_txtrs[i].path);
		++i;
	}
	return (TRUE);
}

static void	_error_usage(char *err, t_msweeper *ms, char *file, int line)
{
	ft_printf("Usage: ./minesweeper [board_size] [level]\n");
	ft_printf("  board_size: 5 to 40 (%d by default)\n", DEFAULT_BOARD_SIZE);
	ft_printf("  level: --easy, --medium or --hard (--medium by default)\n");
	_error(err, ms, file, line);
}

static void	parse_args(int ac, char **av, t_msweeper *ms)
{
	int	board_size;

	board_size = DEFAULT_BOARD_SIZE;
	ms->bombs_ratio = DEFAULT_BOMB_RATIO;
	if (ac >= 2)
	{
		board_size = ft_atoi(av[1]);
		if (!ft_strisdigit(av[1]) || board_size < MIN_BOARD_SIZE || board_size > MAX_BOARD_SIZE)
			_error_usage("Invalid board size", NULL, NULL, 0);
	}
	if (ac == 3)
	{
		if (ft_strcmp(av[2], "--easy") == 0)
			ms->bombs_ratio = EASY_BOMB_RATIO;
		else if (ft_strcmp(av[2], "--medium") == 0)
			ms->bombs_ratio = MEDIUM_BOMB_RATIO;
		else if (ft_strcmp(av[2], "--hard") == 0)
			ms->bombs_ratio = HARD_BOMB_RATIO;
		else
			_error_usage("Invalid level provided", NULL, NULL, 0);
	}
	if (ac > 3)
		_error_usage("Invalid arguments", NULL, NULL, 0);
	ms->map_size_x = board_size;
	ms->map_size_y = board_size;
}

int	ft_parse(int ac, char **av, t_msweeper *ms)
{
	ft_bzero(ms, sizeof(t_msweeper));
	ms->win_w = INITIAL_WIDTH;
	ms->win_h = INITIAL_HEIGHT;
	parse_args(ac, av, ms);
	ms->mlx = mlx_init();
	if (!ms->mlx)
		_error("Unable to start mlx", ms, __FILE__, __LINE__);
	load_textures(ms);
	return (TRUE);
}
