/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:18:26 by besellem          #+#    #+#             */
/*   Updated: 2022/02/21 22:05:15 by besellem         ###   ########.fr       */
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
	ft_printf("key: %d, x: %d, y: %d, ms: %p\n", key, x, y, ms);
	
	if (key == 1) // left click
	{
		
	}
	else if (key == 2) // right click
	{
		
	}
	return (0);
}
