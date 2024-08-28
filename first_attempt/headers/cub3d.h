/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 02:30:52 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/28 18:38:12 by akovalev         ###   ########.fr       */
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

# define WIDTH 1920
# define HEIGHT 1080
# define FOV 1.0471975512f
# define FAILURE 1
# define SUCCESS 0
# define WEST 3.1415926535898f
# define NORTH 1.57079632679f
# define EAST 0
# define SOUTH 4.71238898038f
# define MOVE_SPEED 3.0f
# define ROTATE_SPEED 0.2f
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
	char		start_dir;
	int			start_x;
	int			start_y;
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
	t_map			*parse_data;
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
void	mlx_looping(t_data *data);
int32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void	calculate_ray(t_ray *ray, t_data *data);
void	player_controller(void *param);
void	key_press(mlx_key_data_t key_data, void *param);
void	fix_fish_eye(t_ray *ray, t_data *data);
void	free_all_and_exit(t_data *data);
int32_t	texture_pixel_colour(mlx_texture_t *image, int x, int y);
void	modify_pixel(int x, int y, int32_t colour, t_data *data);
int		ft_err(char *str);
int		parse_directions(t_map *map, char *line, int *count);
int		parse_f(t_map *map, char *line, int *count);
int		parse_c(t_map *map, char *line, int *count);
int		check_lines(t_map *map);
int		validate_floor(t_map *map);
int		validate_ceiling(t_map *map);
int		reformat_map(t_data *data);
int		open_load_textures(t_data *data);
int		check_islands(t_data *data);

#endif