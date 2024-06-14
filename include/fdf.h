/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:29:57 by bazaluga          #+#    #+#             */
/*   Updated: 2024/06/14 16:10:33 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# define WIDTH 1280
# define HEIGHT 720
# define DEFAULT_OFFSETX 200
# define DEFAULT_OFFSETY 0
# define DEFAULT_SPACE 1
# define SIZE_ARR 1000000
# define DEFAULT_DEG_X 35.264
# define DEFAULT_DEG_Z 45
# define ANGLE_X 0.615
# define ANGLE_Z M_PI_4
# define AXIS_X 0
# define AXIS_Y 1
# define AXIS_Z 2

typedef enum e_col_type
{
	COLOR_RAW,
	COLOR_AUTO
}						t_col_type;

typedef enum e_palette_pos
{
	POS4 = 0x63372c,
	POS3 = 0x9c5644,
	POS2 = 0xba533a,
	POS1 = 0xedde58,
	POS0 = 0x3ca814
}				t_palette_pos;

typedef enum e_palette_neg
{
	NEG3 = 0x084a66,
	NEG2 = 0x0e7ead,
	NEG1 = 0x3fa1b5,
	NEG0 = 0x3ca814
}				t_palette_neg;

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

typedef enum e_button_linux
{
	MS_WHEEL_UP = 4,
	MS_WHEEL_DN = 5
}				t_button_linux;

# ifdef __linux__

typedef enum e_key
{
	ESC = 65307,
	KEY_SP = 32,
	KEY_I = 105,
	KEY_O = 111,
	KEY_E = 101,
	KEY_Q = 113,
	KEY_W = 119,
	KEY_S = 115,
	KEY_A = 97,
	KEY_D = 100,
	KEY_C = 99,
	KEY_J = 106,
	KEY_K = 107,
	KEY_R = 114,
	KEY_L = 108,
	KEY_P = 112
}				t_key;
# else

typedef enum e_key
{
	ESC = 53,
	KEY_SP = 49,
	KEY_I = 34,
	KEY_O = 31,
	KEY_E = 14,
	KEY_Q = 12,
	KEY_W = 13,
	KEY_S = 1,
	KEY_A = 0,
	KEY_D = 2,
	KEY_C = 8,
	KEY_J = 38,
	KEY_K = 40,
	KEY_R = 15,
	KEY_L = 37,
	KEY_P = 35
}				t_key;
# endif

typedef struct s_point
{
	int				i;
	int				j;
	int				k;
	double			x;
	double			y;
	double			z;
	unsigned int	color;
	unsigned int	color2;
	bool			visible;
}				t_point;

typedef struct s_ptline
{
	bool	draw;
	double	z0;
	double	z1;
}				t_ptline;

typedef struct s_pts_arr
{
	size_t	r;
	size_t	c;
	size_t	size;
	t_point	*arr;
}				t_pts_arr;

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			bpp;
	int			size;
	int			end;
	int			offset[2];
	bool		refresh;
	int			sp;
	int			center[2];
	float		rx;
	float		ry;
	float		rz;
	float		tx;
	float		ty;
	float		elev;
	bool		normalized;
	t_ptline	*ptslines;
	t_col_type	col_mode;
	char		rot_mode;
	char		tog_lines;
	char		projection;
}				t_img;

typedef struct s_fdata
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_pts_arr	pts;
	int			fd;
	char		*txts[5];
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
void			dynamic_hud(t_fdata *d, bool first);
/*////////////////////////////////// COLORS //////////////////////////////////*/
int				gradient(int c0, int c1, float distance, int ipixel);
void			reset_colors(t_fdata *d);
void			auto_colors(t_fdata *d);
/*//////////////////////////////// ROTATIONS /////////////////////////////////*/
/* void			rotate_x(t_point *p, float angle); */
/* void			rotate_y(t_point *p, float angle); */
/* void			rotate_z(t_point *p, float angle); */
void			rotate_img(t_fdata *d, int axis, bool from_start);
/*////////////////////////////////// PIXELS //////////////////////////////////*/
void			put_pixel_img(t_img *img, int x, int y, int color);
void			init_pixels_arr(t_fdata *d);
bool			is_infront(int xy[2], t_ptline *ptl, t_fdata *d);
bool			pt_infront(t_point *p, t_fdata *d);
/*////////////////////////////////// UTILS ///////////////////////////////////*/
void			config_img(t_fdata *d);
void			create_image(t_fdata *d);
void			normalize_coords(t_fdata *d, t_point *origin);

/******************************* EVENTS HANDLING ******************************/
int				handle_close(t_fdata *data);
int				handle_key(int keycode, t_fdata *data);
int				handle_mouse(int but, int x, int y, t_fdata *d);
int				zoom_in(t_fdata *d);
int				zoom_out(t_fdata *d);
int				rotate(t_fdata *d, int key);
int				toggle_colors(t_fdata *d);
int				change_elevation(t_fdata *d, int key);
int				translate(t_fdata *d, int key);
int				reset(t_fdata *d);
int				toggle_lines(t_fdata *d);
int				toggle_projection(t_fdata *d);

/************************** COMPATIBILITY FUNCTIONS ***************************/
int				mlx2_destroy_display(void *xvar);

/****************************** POINTS FUNCTIONS ******************************/
t_point			*new_point(t_point **res, t_point p, t_fdata *data);
t_point			*dyn_alloc_point_arr(t_pts_arr *pts, t_fdata *d);

/*********************************** UTILS ************************************/
int				ft_atoi_forward(const char *nptr, int *i);
unsigned int	ft_atou_base_forward(const char *nptr, const char *base,
					int *i);
t_list			*ft_lstnew2(void *content, t_list **trash);
int				end_fdf(t_fdata *data, int exit_code);
int				stop_perror(char *msg, t_fdata *data, int error);
int				stop_error(char *msg, t_fdata *data);
int				ft_sign(int n);
float			ft_rad(float angle);

#endif
