/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 21:18:04 by besellem          #+#    #+#             */
/*   Updated: 2022/02/21 23:06:37 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

static void	__free_imgs__(t_msweeper *ms)
{
	int	i;

	i = 0;
	while (i < __TXTR_MAX__ && ms->txtrs[i].ptr)
	{
		mlx_destroy_image(ms->mlx, ms->txtrs[i].ptr);
		++i;
	}
	if (ms->img.ptr)
		mlx_destroy_image(ms->mlx, ms->img.ptr);
}

/*
** ms->win pointer is not freed here because it's done by mlx_destroy_window()
*/
void	ft_free_all(t_msweeper *ms)
{
	__free_imgs__(ms);
	if (ms->map)
		ft_strsfree(ft_strslen((char **)ms->map), (char **)ms->map);
	if (ms->mlx)
		free(ms->mlx);
}
