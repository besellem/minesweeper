/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:18:26 by besellem          #+#    #+#             */
/*   Updated: 2022/02/21 23:46:33 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minesweeper.h"

int	handle_key_press(int key, t_msweeper *ms)
{
	ft_printf("%d %p\n", key, ms);
	if (KEY_ESC == key)
	{
		ft_quit(ms);
	}
	return (0);
}

int	handle_key_release(int key, t_msweeper *ms)
{
	ft_printf("%d %p\n", key, ms);
	(void)key;
	(void)ms;
	return (0);
}

int	handle_mouse_hook(int key, int x, int y, t_msweeper *ms)
{
	const int	map_x = x / ((double)ms->win_w / ms->map_size_x);
	const int	map_y = y / ((double)ms->win_h / ms->map_size_y);

	if (x < 0 || y < 0 || x > ms->win_w || y > ms->win_h)
		return (1);

	ft_printf("key: %d, x: %3d, y: %3d, map_x: %2d, map_y: %2d\n",
		key, x, y, map_x, map_y);

	if (key == LEFT_CLICK)
	{
		ms->map[map_y][map_x].mode = MODE_VISIBLE;
		if (ms->map[map_y][map_x].c == 'B')
			return (1);
	}
	else if (key == RIGHT_CLICK)
	{
		if (ms->map[map_y][map_x].mode == MODE_FLAG)
			ms->map[map_y][map_x].mode = MODE_HIDDEN;
		else if (ms->map[map_y][map_x].mode == MODE_HIDDEN)
			ms->map[map_y][map_x].mode = MODE_FLAG;
	}
	return (0);
}
