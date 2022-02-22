/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 21:17:22 by besellem          #+#    #+#             */
/*   Updated: 2022/02/22 13:37:05 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

void	_error(char *err, t_msweeper *ms, char *file, int line)
{
	if (ms)
		ft_free_all(ms);
	ft_putendl_fd(B_RED "Error" CLR_COLOR, 2);
	if (file && line > 0)
		ft_dprintf(2, B_YELLOW"%s:%d: "CLR_COLOR, file, line);
	else if (file && line <= 0)
		ft_dprintf(2, B_YELLOW"%s: "CLR_COLOR, file);
	else if (!file && line > 0)
		ft_dprintf(2, B_YELLOW"line %d in .ber file: "CLR_COLOR, line);
	ft_putendl_fd(err, 2);
	exit(EXIT_FAILURE);
}

void	ft_quit(t_msweeper *ms)
{
	ft_putendl(B_RED"[Quit]"CLR_COLOR);
	if (ms->win)
		mlx_destroy_window(ms->mlx, ms->win);
	ft_free_all(ms);
	exit(EXIT_SUCCESS);
}

int	ft_red_cross(t_msweeper *ms)
{
	ft_putendl(B_RED"[Quit]"CLR_COLOR);
	if (ms->win)
		mlx_destroy_window(ms->mlx, ms->win);
	ft_free_all(ms);
	exit(EXIT_SUCCESS);
	return (0);
}
