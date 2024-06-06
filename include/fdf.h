/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:29:57 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/06 11:20:41 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# define WIDTH 1280
# define HEIGHT 720
# define DEFAULT_OFFSETX 200
# define DEFAULT_OFFSETY 0
# define DEFAULT_SPACE 10
# define SIZE_ARR 1000000
# define DEFAULT_DEG_X 35.264
# define DEFAULT_DEG_Z 45
# define ANGLE_X 0.615
# define ANGLE_Z M_PI_4
# define AXIS_X 0
# define AXIS_Y 1
# define AXIS_Z 2


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
	KEY_O = 111,
	KEY_E = 101,
	KEY_Q = 113,
	KEY_W = 119,
	KEY_S = 115,
	KEY_A = 97,
	KEY_D = 100
}			t_key_linux;

typedef enum e_key_macos
{
	ESCM = 53,
	KEYM_I = 34,
	KEYM_O = 31,
	KEYM_W = 13,
	KEYM_A = 0,
	KEYM_S = 1,
	KEYM_D = 2,
	KEYM_Q = 12,
	KEYM_E = 14
}			t_key_macos;

typedef struct s_point
{
	int				i;
	int				j;
	int				k;
	double			x;
	double			y;
	double			z;
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
	int		offset[2];
	bool	refresh;
	int		sp; //space between points
	int		center[2];
	float	rx;
	float	ry;
	float	rz;
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
void			display(t_fdata *d, char *filename);
int				refresh_display(t_fdata *d);
int				draw_lines(t_fdata *d);
/*/////////////////////////////////// HUD ////////////////////////////////////*/
void			display_hud(t_fdata *d);
/*////////////////////////////////// COLORS //////////////////////////////////*/
int				trgb_to_i(int t, int r, int g, int b);
int				i_to_trgb(int color, int *r, int *g, int *b);
int				gradient(int c0, int c1, float distance, int ipixel);
/*//////////////////////////////// ROTATIONS /////////////////////////////////*/
void			rotate_x(t_point *p, float angle);
void			rotate_y(t_point *p, float angle);
void			rotate_z(t_point *p, float angle);
void			rotate_img(t_fdata *d, int axis, bool from_start);
/*////////////////////////////////// UTILS ///////////////////////////////////*/
void			put_pixel_img(t_img *img, int x, int y, int color);
void			config_img(t_fdata *d);
void			create_image(t_fdata *d);
void			normalize_coords(t_fdata *d, t_point *origin);

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
float			ft_rad(float angle);

#endif
