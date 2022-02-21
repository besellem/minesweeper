/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 02:08:15 by besellem          #+#    #+#             */
/*   Updated: 2022/02/21 22:58:56 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

int	is_extension(const char *file, const char *extension)
{
	size_t	file_len;
	size_t	ext_len;

	if (!file || !extension)
		return (FALSE);
	file_len = ft_strlen(file);
	ext_len = ft_strlen(extension);
	if (file_len < ext_len)
		return (FALSE);
	return (FALSE == ft_strncmp(file + file_len - ext_len, extension, ext_len));
}

void	print_map(t_msweeper *ms)
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
				ft_printf(B_RED"%c"CLR_COLOR, ms->map[y][x].c);
			else
				ft_putchar(ms->map[y][x].c);
			++x;
		}
		write(1, "\n", 1);
		++y;
	}
	write(1, "\n", 1);
}
