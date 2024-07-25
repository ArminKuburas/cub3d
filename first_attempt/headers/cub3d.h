/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 02:30:52 by akuburas          #+#    #+#             */
/*   Updated: 2024/07/25 17:57:41 by akovalev         ###   ########.fr       */
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
	int				player_position[3];
	t_map			*parse_data;
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
int		check_arguments(int argc, char **argv, t_map *map);
void	free_map_info(t_map *map);
int		validate_map(t_map *map);
void	free_array(char **arr);

#endif