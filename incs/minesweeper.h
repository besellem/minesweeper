/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minesweeper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:56:20 by besellem          #+#    #+#             */
/*   Updated: 2022/02/22 17:37:13 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINESWEEPER_H
# define MINESWEEPER_H

/*
** -- INCLUDES --
*/
# include <libft.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>
# include <time.h>
# include <stdbool.h>

/*
** -- DEFINES --
*/
# define MIN_BOARD_SIZE      5
# define MAX_BOARD_SIZE      40
# define DEFAULT_BOARD_SIZE  16

# define EASY_BOMB_RATIO     0.06
# define MEDIUM_BOMB_RATIO   0.18
# define HARD_BOMB_RATIO     0.35
# define DEFAULT_BOMB_RATIO  MEDIUM_BOMB_RATIO

/*
** Key mapping for macOS & Linux envs
*/
# if defined(__APPLE__) && defined(__MACH__)
#  define ENV_MSG       "\033[1;32m[macOS environment]\033[0m"
#  define SOUND_CMD     "afplay"
#  define KEY_ESC       53
#  define KEY_W         13
#  define KEY_A         0
#  define KEY_S         1
#  define KEY_D         2
#  define EVT_RED_CROSS 17
# else
#  define ENV_MSG       "\033[1;32m[Linux environment]\033[0m"
#  define SOUND_CMD     "aplay"
#  define KEY_ESC       65307
#  define KEY_W         119
#  define KEY_A         97
#  define KEY_S         115
#  define KEY_D         100
#  define EVT_RED_CROSS 33
# endif

# define LEFT_CLICK      1
# define RIGHT_CLICK     2

# define TEXTURE_BOMB   "./assets/bomb.xpm"
# define TEXTURE_FLAG   "./assets/flag.xpm"
# define TEXTURE_HIDDEN "./assets/hidden.xpm"
# define TEXTURE_EMPTY  "./assets/type0.xpm"
# define TEXTURE_NUM_1  "./assets/type1.xpm"
# define TEXTURE_NUM_2  "./assets/type2.xpm"
# define TEXTURE_NUM_3  "./assets/type3.xpm"
# define TEXTURE_NUM_4  "./assets/type4.xpm"
# define TEXTURE_NUM_5  "./assets/type5.xpm"
# define TEXTURE_NUM_6  "./assets/type6.xpm"
# define TEXTURE_NUM_7  "./assets/type7.xpm"
# define TEXTURE_NUM_8  "./assets/type8.xpm"

enum
{
	TXTR_BOMB = 1,
	TXTR_FLAG,
	TXTR_HIDDEN,
	TXTR_EMPTY,
	TXTR_NUM_1,
	TXTR_NUM_2,
	TXTR_NUM_3,
	TXTR_NUM_4,
	TXTR_NUM_5,
	TXTR_NUM_6,
	TXTR_NUM_7,
	TXTR_NUM_8,
	__TXTR_MAX__
};

enum
{
	MODE_HIDDEN,
	MODE_VISIBLE,
	MODE_FLAG
};

/*
** x:			width of the texture (in pixels)
** y:			height of the texture (in pixels)
** size_line:	number of bytes used to store one line of the image in memory
** bpp:			number of bits needed to represent a pixel color
*/
typedef struct s_img
{
	int		x;
	int		y;
	int		size_line;
	int		bpp;
	int		endian;
	void	*ptr;
	char	*addr;
}				t_img;

typedef struct __attribute__((packed)) s_map_type
{
	unsigned char	c;
	unsigned char	mode : 2;
}				t_map_type;

/*
** win_w:			resolution width (if > screen, is truncated)
** win_h:			resolution height (if > screen, is truncated)
** map:				map[row][column]
** map_size_x:		horizontal size of the map
** map_size_y:		vertical size of the map
** mlx:				pointer created by mlx_init()
** win:				pointer of the window
** img:				image to print out
** txtrs:			all the textures and their specs
*/
typedef struct s_msweeper
{
	int			win_w;
	int			win_h;
	t_map_type	**map;
	int			map_size_x;
	int			map_size_y;
	void		*mlx;
	void		*win;
	float		bombs_ratio;
	t_img		img;
	t_img		txtrs[__TXTR_MAX__];
}				t_msweeper;

/*
** -- PROTOTYPES --
** Common
*/
void			print_map(t_msweeper *ms);

/*
** Others
*/
int				is_extension(const char *file, const char *extension);
void			ft_free_all(t_msweeper *ms);

/*
** Parser & Checkers
*/
int				ft_parse(int ac, char **av, t_msweeper *ms);
void			generate_board(t_msweeper *ms);

/*
** Events
*/
int				handle_key_press(int key, t_msweeper *ms);
int				handle_mouse_hook(int key, int x, int y, t_msweeper *ms);
void			_error(char *err, t_msweeper *ms, char *file, int line);
void			ft_quit(t_msweeper *ms);
int				ft_red_cross(t_msweeper *ms);

/*
** Engine & Display
*/
void			ft_pixel_put(t_msweeper *ms, int x, int y, uint32_t color);
void			update_frame(t_msweeper *ms);
int				engine_loop(t_msweeper *ms);
void			flood_fill_wrapper(t_msweeper *ms, int x, int y);
void			display(t_msweeper *ms);

#endif
