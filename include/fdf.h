#ifndef FDF_H
# define FDF_H

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

#endif
