/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:29:57 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/27 18:02:24 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# define WIDTH 1280
# define HEIGHT 720
# define DEFAULT_OFFSET 15
# define DEFAULT_SCALE 1
# define DEFAULT_SPACEX 2
# define DEFAULT_SPACEY 2
# define SIZE_ARR 50000


typedef enum e_event
{
	KEYDOWN = 2,
	KEYUP = 3,
	MOUSEDOWN = 4,
	MOUSEUP = 5,
	MOUSEMOVE = 6,
	EXPOSE = 12,
	DESTROY = 17
}				t_event;

typedef enum e_key_linux
{
	ESC = 65307,
	KEY_I = 105,
	KEY_O = 111
}			t_key_linux;

typedef enum e_key_macos
{
	ESCM = 53,
	KEYM_I = 34,
	KEYM_O = 31
}			t_key_macos;

typedef struct s_point
{
	int				i;
	int				j;
	int				h;
	int				x;
	int				y;
	int				z;
	unsigned int	color;
	bool			visible;
}				t_point;

typedef struct s_pts_arr
{
	int	r; //rows
	int	c; //cols
	int	size;
	t_point	*arr;
}				t_pts_arr;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp; //bits_per_pixel
	int		size; //size_line
	int		end; //endian
	int		spx; //space between 2 points on x
	int		spy; //space between 2 points on y
	float	scale;
	int		offset;
}				t_img;

typedef struct s_fdata
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_pts_arr	pts;
	int			fd;
	t_list		*trash;
}				t_fdata;

/************************************ MAIN ************************************/
int				parse_map(t_fdata *data);

/************************** GARBAGE COLLECTOR *********************************/
void			*ft_mylloc(size_t size, t_list **trash);
void			*ft_cylloc(size_t nmemb, size_t size, t_list **trash);
void			*ft_add_garbage(t_list **trash, void *ptr);
void			ft_free_garbage(void *ptr, t_list **trash);
void			ft_empty_trash(t_list **trash);

/********************************** DISPLAY ***********************************/
int				trgb_to_i(int t, int r, int g, int b);
int				i_to_trgb(int color, int *r, int *g, int *b);
void			put_pixel_img(t_img *img, int x, int y, int color);
int				put_points(t_fdata *d);
int				draw_lines(t_fdata *d);
int				gradient(int c0, int c1, float distance, int ipixel);
int				refresh_display(t_fdata *d);

/******************************* EVENTS HANDLING ******************************/
int				handle_close(t_fdata *data);
int				handle_key(int keycode, t_fdata *data);

/************************** COMPATIBILITY FUNCTIONS ***************************/
int				mlx2_destroy_display(void *xvar);

/****************************** POINTS FUNCTIONS ******************************/
t_point			*new_point(t_point **res, t_point p, t_fdata *data);
t_point			*dyn_alloc_point_arr(t_pts_arr *pts, t_fdata *d);

/*********************************** UTILS ************************************/
int				ft_atoi_forward(const char *nptr, int *i);
unsigned int	ft_atou_base_forward(const char *nptr, const char *base, int *i);
t_list			*ft_lstnew2(void *content, t_list **trash);
int				end_fdf(t_fdata *data, int exit_code);
int				stop_perror(char *msg, t_fdata *data, int error);
int				stop_error(char *msg, t_fdata *data);
int				ft_sign(int n);

#endif
