/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:02:16 by besellem          #+#    #+#             */
/*   Updated: 2022/02/21 23:50:38 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

int	check_win(t_msweeper *ms)
{
	int	x;
	int	y;

	y = 0;
	while (y < ms->map_size_y)
	{
		x = 0;
		while (x < ms->map_size_x)
		{
			if (ms->map[y][x].c == 'B')
				return (FALSE);
			++x;
		}
		++y;
	}
	return (TRUE);
}

void	update_frame(t_msweeper *ms)
{
	// if ('E' == ms->map[ms->pos_y][ms->pos_x] && 0 == ms->collectibles)
	// {
	// 	ft_printf(F_GREEN""B_RED"\nYOU WON in %zu moves!"CLR_COLOR"\n",
	// 		ms->move_nbr);
	// 	ft_quit(ms);
	// }
	display_minimap(ms);
	mlx_put_image_to_window(ms->mlx, ms->win, ms->img.ptr, 0, 0);
}

int	engine_loop(t_msweeper *ms)
{
	update_frame(ms);
	return (0);
}
