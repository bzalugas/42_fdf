/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:29:57 by bazaluga          #+#    #+#             */
/*   Updated: 2024/05/13 19:25:46 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"

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
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_img;

typedef struct s_frame
{
	void	*mlx;
	void	*win;
}				t_frame;

typedef struct s_all
{
	t_img	*img;
	void	*mlx;
	void	*win;
	t_list	*garbage;
}				t_all;

/************************** GARBAGE COLLECTOR *********************************/

void	*ft_mylloc(size_t size, t_list **garbage);
void	*ft_cylloc(size_t nmemb, size_t size, t_list **garbage);
void	ft_empty_trash(t_list **garbage);

#endif
