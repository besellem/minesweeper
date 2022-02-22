/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_board.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:29:34 by besellem          #+#    #+#             */
/*   Updated: 2022/02/22 16:31:15 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

static void	_generate_bombs(t_msweeper *ms)
{
	const size_t	bombs_nbr = ms->map_size_x * ms->map_size_y * ms->bombs_ratio;
	size_t			bombs_placed;
	long			x;
	long			y;

	ft_printf("Generating %zu bombs on a board of %d (%d*%d)...\n",
		bombs_nbr,
		ms->map_size_x * ms->map_size_y,
		ms->map_size_x,
		ms->map_size_y);
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

static int	_get_bombs_nbr(t_msweeper *ms, int x, int y)
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

static void	_place_nbrs(t_msweeper *ms)
{
	int	x;
	int	y;

	y = 0;
	while (y < ms->map_size_y)
	{
		x = 0;
		while (x < ms->map_size_x)
		{
			ms->map[y][x].mode = MODE_HIDDEN;
			if ('B' != ms->map[y][x].c)
			{
				ms->map[y][x].c = _get_bombs_nbr(ms, x, y) + '0';
			}
			++x;
		}
		++y;
	}
}

void	generate_board(t_msweeper *ms)
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
	_generate_bombs(ms);
	_place_nbrs(ms);
}
