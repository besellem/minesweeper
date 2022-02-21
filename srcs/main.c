/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:25:57 by besellem          #+#    #+#             */
/*   Updated: 2022/02/21 23:08:58 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

void	ft_mlx_start(t_msweeper *ms)
{
	mlx_do_key_autorepeaton(ms->mlx);
	ms->win = mlx_new_window(ms->mlx, ms->win_w, ms->win_h, "minesweeper");
	ms->img.ptr = mlx_new_image(ms->mlx, ms->win_w, ms->win_h);
	ms->img.addr = mlx_get_data_addr(ms->img.ptr,
			&ms->img.bpp,
			&ms->img.size_line,
			&ms->img.endian);
	print_map(ms);
	update_frame(ms);
	mlx_hook(ms->win, 2, (1L << 0), handle_key_press, ms);
	// mlx_hook(ms->win, 3, (1L << 1), handle_key_release, ms);
	mlx_hook(ms->win, EVT_RED_CROSS, (1L << 2), ft_red_cross, ms);
	mlx_mouse_hook(ms->win, handle_mouse_hook, ms);
	mlx_loop_hook(ms->mlx, engine_loop, ms);
	mlx_loop(ms->mlx);
}

void	generate_bombs(t_msweeper *ms)
{
	const size_t	bombs_nbr = ms->map_size_x * ms->map_size_y * ms->bombs_ratio;
	size_t			bombs_placed;
	long			x;
	long			y;

	ft_printf("Generating %zu bombs...\n", bombs_nbr);
	bombs_placed = 0;
	while (bombs_placed < bombs_nbr)
	{
		x = random() % ms->map_size_x;
		y = random() % ms->map_size_y;
		if (ms->map[y][x].c != 'B')
		{
			ms->map[y][x].c = 'B';
			++bombs_placed;
		}
	}
}

static int		get_bombs_nbr(t_msweeper *ms, int x, int y)
{
	int	bombs_nbr;

	bombs_nbr = 0;
	if (y > 0 && 'B' == ms->map[y - 1][x].c)
		++bombs_nbr;
	if (y < ms->map_size_y - 1 && 'B' == ms->map[y + 1][x].c)
		++bombs_nbr;
	if (x > 0 && 'B' == ms->map[y][x - 1].c)
		++bombs_nbr;
	if (x < ms->map_size_x - 1 && 'B' == ms->map[y][x + 1].c)
		++bombs_nbr;
	if (y > 0 && x > 0 && 'B' == ms->map[y - 1][x - 1].c)
		++bombs_nbr;
	if (y > 0 && x < ms->map_size_x - 1 && 'B' == ms->map[y - 1][x + 1].c)
		++bombs_nbr;
	if (y < ms->map_size_y - 1 && x > 0 && 'B' == ms->map[y + 1][x - 1].c)
		++bombs_nbr;
	if (y < ms->map_size_y - 1 && x < ms->map_size_x - 1 && 'B' == ms->map[y + 1][x + 1].c)
		++bombs_nbr;
	return (bombs_nbr);
}

void	place_nbrs(t_msweeper *ms)
{
	int	x;
	int	y;

	ft_printf("Placing numbers...\n");
	y = 0;
	while (y < ms->map_size_y)
	{
		x = 0;
		while (x < ms->map_size_x)
		{
			// ms->map[y][x].mode = MODE_HIDDEN;
			ms->map[y][x].mode = MODE_VISIBLE;
			if ('B' != ms->map[y][x].c)
			{
				ms->map[y][x].c = get_bombs_nbr(ms, x, y) + '0';
			}
			++x;
		}
		++y;
	}
}

void	generate(t_msweeper *ms)
{
	int	i;

	ms->map = (t_map_type **)ft_calloc(ms->map_size_y + 1, sizeof(t_map_type *));
	if (!ms->map)
		_error("Malloc error", ms, __FILE__, __LINE__);
	i = 0;
	while (i < ms->map_size_y)
	{
		ms->map[i] = (t_map_type *)ft_calloc(ms->map_size_x + 1, sizeof(t_map_type));
		if (!ms->map[i])
		{
			ft_strsfree(i, (char **)ms->map);
			_error("Malloc error", ms, __FILE__, __LINE__);
		}
		++i;
	}
	generate_bombs(ms);
	place_nbrs(ms);
}

int	main(int ac, char **av)
{
	t_msweeper	ms;

	srandom(time(NULL));
	ft_parse(ac, av, &ms);
	generate(&ms);
	ft_putendl(ENV_MSG);
	ft_mlx_start(&ms);
	return (0);
}
