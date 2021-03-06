/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:02:16 by besellem          #+#    #+#             */
/*   Updated: 2022/02/22 16:27:27 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

static int	check_loss(t_msweeper *ms)
{
	int	x;
	int	y;

	y = 0;
	while (y < ms->map_size_y)
	{
		x = 0;
		while (x < ms->map_size_x)
		{
			if (ms->map[y][x].c == 'B' && ms->map[y][x].mode == MODE_VISIBLE)
				return (TRUE);
			++x;
		}
		++y;
	}
	return (FALSE);
}

static int	check_win(t_msweeper *ms)
{
	int	x;
	int	y;

	y = 0;
	while (y < ms->map_size_y)
	{
		x = 0;
		while (x < ms->map_size_x)
		{
			if (ms->map[y][x].c == 'B' && ms->map[y][x].mode != MODE_FLAG)
				return (FALSE);
			else if (ms->map[y][x].c != 'B' && ms->map[y][x].mode != MODE_VISIBLE)
				return (FALSE);
			++x;
		}
		++y;
	}
	return (TRUE);
}

static int	get_all_visible(t_msweeper *ms)
{
	int	x;
	int	y;

	y = 0;
	while (y < ms->map_size_y)
	{
		x = 0;
		while (x < ms->map_size_x)
		{
			ms->map[y][x].mode = MODE_VISIBLE;
			++x;
		}
		++y;
	}
	return (FALSE);
}

void	update_frame(t_msweeper *ms)
{
	if (check_loss(ms))
	{
		get_all_visible(ms);
	}
	else if (check_win(ms))
	{
		ft_printf(B_YELLOW "You won !" CLR_COLOR "\n");
		sleep(1);
		ft_quit(ms);
	}
	display(ms);
	mlx_put_image_to_window(ms->mlx, ms->win, ms->img.ptr, 0, 0);
}

int	engine_loop(t_msweeper *ms)
{
	update_frame(ms);
	return (0);
}
