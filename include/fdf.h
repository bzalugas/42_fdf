/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:29:57 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/20 11:36:59 by bazaluga         ###   ########.fr       */
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
	t_list	*garbage;
}				t_fdata;

/************************** GARBAGE COLLECTOR *********************************/
void	*ft_mylloc(size_t size, t_list **garbage);
void	*ft_cylloc(size_t nmemb, size_t size, t_list **garbage);
void	ft_empty_trash(t_list **garbage);

/*********************************** COLORS ***********************************/
int		trgb_to_i(int t, int r, int g, int b);
int		i_to_trgb(int color, int *r, int *g, int *b);

/************************** COMPATIBILITY FUNCTIONS ***************************/
int		mlx2_destroy_display(void *xvar);

#endif
