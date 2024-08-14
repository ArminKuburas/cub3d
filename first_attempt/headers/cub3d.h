/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 02:30:52 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/14 11:58:16 by akuburas         ###   ########.fr       */
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
# define WEST 180
# define NORTH 90
# define EAST 0
# define SOUTH 270
# define MOVE_SPEED 5.0f
# define ROTATE_SPEED 0.5f
# define DEFAULT_COLOUR 0xFF000000

typedef struct s_ray
{
	float			angle;
	float			distance;
	float			x;
	float			y;
	mlx_texture_t	*texture;
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
	char		*pr_str;
	char		*nxt_str;
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	rotation_angle;
}	t_player;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	int32_t			floor_colour;
	int32_t			ceiling_colour;
	char			**map;
	int				map_height;
	int				map_width;
	t_player		player;
	t_map			parse_data;
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

int		check_arguments(int argc, char **argv, t_map *map);
void	free_map_info(t_map *map);
int		validate_map(t_map *map);
void	free_array(char **arr);
enum e_direction
{
	GO_FORWARDS,
	GO_BACKWARDS,
	STRAFE_LEFT,
	STRAFE_RIGHT,
	TURN_LEFT,
	TURN_RIGHT
};

int		ft_err(char *str);
double	rad_convert(double degrees);
void	mlx_looping(t_data *data);

#endif