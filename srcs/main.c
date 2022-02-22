/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:25:57 by besellem          #+#    #+#             */
/*   Updated: 2022/02/22 17:34:46 by besellem         ###   ########.fr       */
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
	update_frame(ms);
	mlx_hook(ms->win, 2, (1L << 0), handle_key_press, ms);
	mlx_hook(ms->win, EVT_RED_CROSS, (1L << 2), ft_red_cross, ms);
	mlx_mouse_hook(ms->win, handle_mouse_hook, ms);
	mlx_loop_hook(ms->mlx, engine_loop, ms);
	mlx_loop(ms->mlx);
}

int		main(int ac, char **av)
{
	t_msweeper	ms;

	srandom(time(NULL));
	ft_parse(ac, av, &ms);
	generate_board(&ms);
	ft_mlx_start(&ms);
	return (0);
}
