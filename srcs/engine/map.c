/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:56:58 by besellem          #+#    #+#             */
/*   Updated: 2022/02/21 23:04:52 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

struct s_lookup_texture
{
	int	texture_char;
	int	texture_id;
};

struct	s_textures
{
	int		id;
	char	*path;
};


static t_img	*__get_texture__(t_msweeper *ms, char c)
{
	static const struct s_lookup_texture	g_lookup_txtrs[] = {
		{'B', TXTR_BOMB},
		{'F', TXTR_FLAG},
		{'0', TXTR_EMPTY},
		{'1', TXTR_NUM_1},
		{'2', TXTR_NUM_2},
		{'3', TXTR_NUM_3},
		{'4', TXTR_NUM_4},
		{'5', TXTR_NUM_5},
		{'6', TXTR_NUM_6},
		{'7', TXTR_NUM_7},
		{'8', TXTR_NUM_8},
		{0, 0}
	};
	int										i;

	i = 0;
	while (g_lookup_txtrs[i].texture_char)
	{
		if (g_lookup_txtrs[i].texture_char == c)
			return (&ms->txtrs[g_lookup_txtrs[i].texture_id]);
		++i;
	}
	return (NULL);
}

static void	__put_texture__(t_msweeper *ms, int x, int y, t_img *txtr)
{
	const double	ratio_x = ((double)ms->win_w / ms->map_size_x);
	const double	ratio_y = ((double)ms->win_h / ms->map_size_y);
	double			tx_x;
	double			tx_y;
	char			*ptr;

	tx_y = 0.0;
	while (tx_y < ratio_y)
	{
		tx_x = 0.0;
		while (tx_x < ratio_x)
		{
			ptr = txtr->addr;
			ptr += (size_t)((tx_y / ratio_y) * txtr->y) * txtr->size_line;
			ptr += (size_t)((tx_x / ratio_x) * txtr->x) * (txtr->bpp / 8);
			ft_pixel_put(
				ms,
				(x * ratio_x) + tx_x,
				(y * ratio_y) + tx_y,
				*(uint32_t *)ptr
				);
			tx_x += ft_fmax(ratio_x, txtr->x) / ft_fmax(txtr->x, ratio_x);
		}
		tx_y += ft_fmax(ratio_y, txtr->y) / ft_fmax(txtr->y, ratio_y);
	}
}

static void	put_map(t_msweeper *ms)
{
	const t_map_type	**map = (const t_map_type **)ms->map;
	int					x;
	int					y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x].c)
		{
			if (map[y][x].mode == MODE_HIDDEN)
			{
				__put_texture__(ms, x, y, &ms->txtrs[TXTR_HIDDEN]);
			}
			else
			{
				__put_texture__(ms, x, y, __get_texture__(ms, map[y][x].c));
			}
			++x;
		}
		++y;
	}
}

void	display_minimap(t_msweeper *ms)
{
	put_map(ms);
}
