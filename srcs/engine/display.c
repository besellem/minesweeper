/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:02 by besellem          #+#    #+#             */
/*   Updated: 2022/02/21 13:57:53 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

/*
** Print a pixel at the coordinates into mlx->img
*/
void	ft_pixel_put(t_msweeper *ms, int x, int y, uint32_t color)
{
	char	*px;

	px = ms->img.addr + y * ms->img.size_line + x * (ms->img.bpp / 8);
	*(uint32_t *)px = color;
}
