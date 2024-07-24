/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 02:30:52 by akuburas          #+#    #+#             */
/*   Updated: 2024/07/25 00:12:07 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include "../other_libraries/libft/libft.h"

# define WIDTH 320
# define HEIGHT 200
# define FOV 60

# define FAILURE 1
# define SUCCESS 0

typedef struct s_ray
{
	float	angle;
	float	distance;
	float	x;
	float	y;
}	t_ray;

typedef struct s_map
{
	int			fd;
	const char	*filename;
	int			name_length;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	t_vec		map_copy;
	int			line_count;
	char		**ceiling;
	char		**floor;
	int			start_pos;
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;
}	t_player;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	int				floor_colour[4];
	int				ceiling_colour[4];
	char			**map;
	t_player		player;
	t_map			parse_data;
	t_ray			*rays;
}	t_data;

typedef struct s_parsing_data
{
	int		fd;
	char	*north_file;
	char	*south_file;
	char	*west_file;
	char	*east_file;
	char	*floor_colour;
	char	*ceiling_colour;
}	t_parsing_data;

int		ft_err(char *str);
double	radian_converter(double degrees);

#endif