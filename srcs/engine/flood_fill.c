/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:24:27 by besellem          #+#    #+#             */
/*   Updated: 2022/02/22 16:24:49 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

static bool	_flood_fill(t_msweeper *ms, char **fill, int x, int y)
{	
	if (x < 0 || x >= ms->map_size_x || y < 0 || y >= ms->map_size_y)
		return (false);
	if (fill[y][x] == true)
		return (false);
	if (ms->map[y][x].c != '0')
	{
		ms->map[y][x].mode = MODE_VISIBLE;
		return (false);
	}
	fill[y][x] = true;
	ms->map[y][x].mode = MODE_VISIBLE;
	_flood_fill(ms, fill, x + 1, y);
	_flood_fill(ms, fill, x - 1, y);
	_flood_fill(ms, fill, x, y + 1);
	_flood_fill(ms, fill, x, y - 1);
	return (true);
}

static char	**_create_fill(t_msweeper *ms)
{
	char	**ptr = ft_calloc(ms->map_size_y + 1, sizeof(char *));
	int		i;

	if (!ptr)
		return (NULL);
	i = 0;
	while (i < ms->map_size_y)
	{
		ptr[i] = (char *)malloc(ms->map_size_x + 1);
		if (!ptr[i])
		{
			ft_strsfree(i, ptr);
			return (NULL);
		}
		ft_memset(ptr[i], false, ms->map_size_x);
		++i;
	}
	return (ptr);
}

void	flood_fill_wrapper(t_msweeper *ms, int x, int y)
{
	char	**fill = _create_fill(ms);

	if (!fill)
		_error("malloc error", ms, __FILE__, __LINE__);
	_flood_fill(ms, fill, x, y);
	ft_strsfree(ms->map_size_y, fill);
}
