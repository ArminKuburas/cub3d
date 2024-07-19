/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 02:30:52 by akuburas          #+#    #+#             */
/*   Updated: 2024/07/19 11:34:03 by akuburas         ###   ########.fr       */
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

# define WIDTH 320
# define HEIGHT 200
# define RADIAN 0.0174533
# define FOV 60 * 0.0174533

typedef struct s_ray
{
	int		player_x;
	int		player_y;
	int		distance;
	int		a_y;
	int		a_x;
	int		xa;
	int		ya;
	int		next_x;
	int		next_y;
	char	**map;
}

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	int				floor_colour;
	int				ceiling_colour;
	char			**map;
	int				player_position[3];
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

#endif