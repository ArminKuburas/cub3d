/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_test_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:39:06 by akuburas          #+#    #+#             */
/*   Updated: 2024/07/05 04:00:14 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <math.h>
#include "../../MLX42/include/MLX42/MLX42.h"

#define SCALE 5
#define WIDTH 320
#define HEIGHT 200
#define PI 3.14159265358979323846
//One degree is 0.0174533 radians
#define RADIAN 0.0174533
#define FOV 60 * RADIAN

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	char		**map;
	int			player_x;
	int			player_y;
	int			player_angle;
	int			distance_from_projection_plane;
	double		angle_between_rays;
}				t_data;

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
}				t_ray;

void	ft_vertical_ray(t_ray *ray, double ray_angle, int turn_positive)
{
	printf("calculating vertical_ray\n");
	printf("ray angle is %f\n", ray_angle);
	printf("turn_positive is %d\n", turn_positive);
	if (ray_angle > 90 && ray_angle < 270)
	{
		ray->a_x = (ray->player_x / 64) * 64 - 1;
		ray->xa = -64;
	}
	else
	{
		ray->a_x = (ray->player_x / 64) * 64 + 64;
		ray->xa = 64;
	}
	ray->a_y = ray->player_y + ((ray->player_x - ray->a_x)
			* tan(ray_angle * RADIAN));
	ray->ya = 64 * tan(ray_angle * RADIAN) * turn_positive;
	printf("ray->ya = %d\n", ray->ya);
	printf("ray->xa = %d\n", ray->xa);
	printf("ray->a_x = %d\n", ray->a_x);
	printf("ray->a_y = %d\n", ray->a_y);
	ray->next_x = ray->a_x;
	ray->next_y = ray->a_y;
	while (1)
	{
		if (ray->next_x < 0 || ray->next_x / 64 > 9
			|| ray->next_y < 0 || ray->next_y / 64 > 9)
		{
			printf("We hit a wall but not in the map\n");
			break ;
		}
		printf("next_x = %d\n", ray->next_x);
		printf("next_y = %d\n", ray->next_y);
		if (ray->map[ray->next_y / 64][ray->next_x / 64] == '1')
		{
			printf("We hit a wall at x %d, y %d\n", ray->next_x, ray->next_y);
			printf("next_x / 64 = %d\n", ray->next_x / 64);
			printf("next_y / 64 = %d\n", ray->next_y / 64);
			break ;
		}
		ray->next_x = ray->next_x + ray->xa;
		ray->next_y = ray->next_y + ray->ya;
	}
	ray->distance = sqrt(((ray->player_x - ray->a_x) * (ray->player_x - ray->a_x))
			+ ((ray->player_y - ray->a_y) * (ray->player_y - ray->a_y)));
}

void	ft_horizontal_ray(t_ray *ray, double ray_angle, int turn_positive)
{
	printf("calculating horizontal_ray\n");
	printf("ray angle is %f\n", ray_angle);
	printf("turn_positive is %d\n", turn_positive);
	if (ray_angle > 0 && ray_angle < 180)
	{
		ray->a_y = (ray->player_y / 64) * 64 - 1;
		ray->ya = -64;
	}
	else
	{
		ray->a_y = (ray->player_y / 64) * 64 + 64;
		ray->ya = 64;
	}
	printf("this is tan(ray_angle * RADIAN) = %f\n", tan(ray_angle * RADIAN));
	ray->a_x = ray->player_x + ((ray->player_y - ray->a_y)
			/ tan(ray_angle * RADIAN));
	ray->xa = 64 / tan(ray_angle * RADIAN) * turn_positive;
	printf("ray->ya = %d\n", ray->ya);
	printf("ray->xa = %d\n", ray->xa);
	printf("ray->a_x = %d\n", ray->a_x);
	printf("ray->a_y = %d\n", ray->a_y);
	ray->next_x = ray->a_x;
	ray->next_y = ray->a_y;
	while (1)
	{
		printf("next_x = %d\n", ray->next_x);
		printf("next_y = %d\n", ray->next_y);
		if (ray->next_x < 0 || ray->next_x / 64 > 9
			|| ray->next_y < 0 || ray->next_y / 64 > 9)
		{
			printf("We hit a wall but not in the map\n");
			break ;
		}
		if (ray->map[ray->next_y / 64][ray->next_x / 64] == '1')
		{
			printf("We hit a wall at x %d, y %d\n", ray->next_x, ray->next_y);
			printf("next_x / 64 = %d\n", ray->next_x / 64);
			printf("next_y / 64 = %d\n", ray->next_y / 64);
			break ;
		}
		ray->next_x = ray->next_x + ray->xa;
		ray->next_y = ray->next_y + ray->ya;
	}
	ray->distance = sqrt(((ray->player_x - ray->a_x)
				* (ray->player_x - ray->a_x)) + ((ray->player_y - ray->a_y)
				* (ray->player_y - ray->a_y)));
}

void	draw_ray(t_data *data, t_ray ray)
{
	int		x;
	int		y;
	int		k;

	x = ray.player_x;
	y = ray.player_y;
	k = 0;
	while (k < ray.distance)
	{
		data->img->pixels[y * data->img->width * 4 + x * 4] = 0;
		data->img->pixels[y * data->img->width * 4 + x * 4 + 1] = 200;
		data->img->pixels[y * data->img->width * 4 + x * 4 + 2] = 200;
		data->img->pixels[y * data->img->width * 4 + x * 4 + 3] = 200;
		x = x + (ray.next_x - ray.a_x) / ray.distance;
		y = y + (ray.next_y - ray.a_y) / ray.distance;
		k++;
	}
}

void	ray_calculation( t_data *data, double ray_angle)
{
	int		turn_positive;
	t_ray	horizontal_ray;
	t_ray	vertical_ray;

	turn_positive = 1;
	horizontal_ray = (t_ray){};
	vertical_ray = (t_ray){};
	horizontal_ray.player_x = data->player_x;
	horizontal_ray.player_y = data->player_y;
	vertical_ray.player_x = data->player_x;
	vertical_ray.player_y = data->player_y;
	horizontal_ray.map = data->map;
	vertical_ray.map = data->map;
	if (ray_angle == 90 || ray_angle == 180
		|| ray_angle == 0 || ray_angle == 270)
	{
		printf("ray_angle = %f\n", ray_angle);
		printf("ray_angle is 90, 180, 0 or 270\n");
		return ;
	}
	if (ray_angle > 180 || ray_angle < 0)
		turn_positive = -1;
	printf("------------------------------------\n");
	printf("player x = %d which is %d\n", data->player_x, data->player_x / 64);
	printf("player y = %d which is %d\n", data->player_y, data->player_y / 64);
	printf("player angle is %d\n", data->player_angle);
	ft_horizontal_ray(&horizontal_ray, ray_angle, turn_positive);
	turn_positive = 1;
	printf("------------------------------------\n");
	if (ray_angle < 90 || ray_angle > 270)
		turn_positive = -1;
	ft_vertical_ray(&vertical_ray, ray_angle, turn_positive);
	printf("horizontal_distance = %d\n", horizontal_ray.distance);
	printf("vertical_distance = %d\n", vertical_ray.distance);
	if (horizontal_ray.distance < vertical_ray.distance)
	{
		printf("horizontal_distance is smaller\n");
		draw_ray(data, horizontal_ray);
	}
	else
	{
		draw_ray(data, vertical_ray);
		printf("vertical_distance is smaller\n");
	}
}

//to explain. each pixel is 4 bytes. 1 byte for red, 1 byte for green, 1 byte for blue and 1 byte for alpha
//so if we want to set a pixel to red, we set the first byte to 255 and the rest to 0 although we still want the alpha channel to have some value otherwise itll be black.
//the goal of the paint tool will be to initially draw the map. We have a red box so far but with this I am hoping to draw a 2d map of the game. And later make one that draws the ray lines.
void	paint_tool(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	k;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
			{
				x = j * 64;
				y = i * 64;
				k = 0;
				while (k < 64)
				{
					int l = 0;
					while (l < 64)
					{
						data->img->pixels[(y + k) * data->img->width * 4 + (x + l) * 4] = 0;
						data->img->pixels[(y + k) * data->img->width * 4 + (x + l) * 4 + 1] = 50;
						data->img->pixels[(y + k) * data->img->width * 4 + (x + l) * 4 + 2] = 0;
						data->img->pixels[(y + k) * data->img->width * 4 + (x + l) * 4 + 3] = 200;
						l++;
					}
					k++;
				}
			}
			if (data->map[i][j] == 'P')
			{
				x = j * 64;
				y = i * 64;
				k = 0;
				while (k < 64)
				{
					int l = 0;
					while (l < 64)
					{
						data->img->pixels[(y + k) * data->img->width * 4 + (x + l) * 4] = 0;
						data->img->pixels[(y + k) * data->img->width * 4 + (x + l) * 4 + 1] = 0;
						data->img->pixels[(y + k) * data->img->width * 4 + (x + l) * 4 + 2] = 255;
						data->img->pixels[(y + k) * data->img->width * 4 + (x + l) * 4 + 3] = 200;
						l++;
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}
}

int	main(void)
{
	unsigned int	i;
	int				j;
	t_data			data;

	i = 0;
	j = 0;
	data.distance_from_projection_plane = (WIDTH / 2) / tan(FOV / 2);
	data.angle_between_rays = (double)60 / WIDTH;
	data.player_y = 4 * 64 + 32;
	data.player_x = 4 * 64 + 32;
	data.player_angle = 60;
	data.mlx = mlx_init(WIDTH * SCALE, HEIGHT * SCALE, "Ray Tracing Test 01", true);
	data.img = mlx_new_image(data.mlx, WIDTH * SCALE, HEIGHT * SCALE);
	data.map = calloc(10, sizeof(char *));
	data.map[9] = NULL;
	while (i < 9)
	{
		data.map[i] = calloc(10, sizeof(char));
		data.map[i][9] = '\0';
		i++;
	}
	i = 0;
	while (i < (unsigned int)data.img->height * data.img->width * 4)
	{
		data.img->pixels[i] = 255;
		data.img->pixels[i + 1] = 0;
		data.img->pixels[i + 2] = 0;
		data.img->pixels[i + 3] = 150;
		i += 4;
	}
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	printf("distance_from_projection_plane = %d\n", data.distance_from_projection_plane);
	printf("angle_between_rays = %f\n", data.angle_between_rays);
	printf("player_x = %d\n", data.player_x);
	printf("player_y = %d\n", data.player_y);
	printf("player_angle = %d\n", data.player_angle);
	i = 0;
	while (i < 9)
	{
		j = 0;
		if (i != 0 && i != 8)
		{
			data.map[i][0] = '1';
			j = 1;
			while (j < 9)
			{
				data.map[i][j] = '0';
				j++;
			}
			data.map[i][8] = '1';
		}
		else
		{
			j = 0;
			while (j < 9)
			{
				data.map[i][j] = '1';
				j++;
			}
		}
		i++;
	}
	i = 0;
	data.map[4][4] = 'P';
	while (i < 9)
	{
		printf("map[%d] = %s\n", i, data.map[i]);
		i++;
	}
	double ray_angle = data.player_angle - 30;
	i = 0;
	paint_tool(&data);
	while (i < WIDTH)
	{
		ray_calculation(&data, ray_angle);
		ray_angle += data.angle_between_rays;
		i++;
	}
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}
