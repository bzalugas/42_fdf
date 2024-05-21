/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:29:57 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/21 13:58:37 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"

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
	ESC = 65307
}			t_key_linux;

typedef enum e_key_macos
{
	ESCM = 53
}			t_key_macos;

typedef struct s_point
{
	int				h;
	int				x;
	int				y;
	int				z;
	unsigned int	color;
}				t_point;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp; //bits_per_pixel
	int		size_line;
	int		endian;
}				t_img;

typedef struct s_fdata
{
	t_img	img;
	void	*mlx;
	void	*win;
	t_list	*trash;
}				t_fdata;

/************************** GARBAGE COLLECTOR *********************************/
void	*ft_mylloc(size_t size, t_list **trash);
void	*ft_cylloc(size_t nmemb, size_t size, t_list **trash);
void	*ft_add_garbage(t_list **trash, void *ptr);
void	ft_empty_trash(t_list **trash);

/*********************************** COLORS ***********************************/
int		trgb_to_i(int t, int r, int g, int b);
int		i_to_trgb(int color, int *r, int *g, int *b);

/************************** COMPATIBILITY FUNCTIONS ***************************/
int		mlx2_destroy_display(void *xvar);

/****************************** POINTS FUNCTIONS ******************************/
/* t_point	*new_point(t_point p, t_fdata *data); */
t_point	*new_point(t_point **res, t_point p, t_fdata *data);

/*********************************** UTILS ************************************/
int		ft_atoi_forward(const char *nptr, int *i);
t_list	*ft_lstnew2(void *content, t_list **trash);

#endif
