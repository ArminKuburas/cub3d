/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_test_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:39:06 by akuburas          #+#    #+#             */
/*   Updated: 2024/07/02 10:59:31 by akuburas         ###   ########.fr       */
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
	int		x;
	int		y;
	int		distance;
	int		a_y;
	int		a_x;
	int		xa;
	int		ya;
}				t_ray;

void	ray_calculation( t_data *data, double ray_angle)
{
	int	turn_positive;

	turn_positive = 1;
	if (ray_angle == 90 || ray_angle == 180
		|| ray_angle == 0 || ray_angle == 270)
	{
		printf("ray_angle = %f\n", ray_angle);
		printf("ray_angle is 90, 180, 0 or 270\n");
		return ;
	}
	if (ray_angle > 180 || ray_angle < 0)
		turn_positive = -1;
	horizontal_ray(data, ray_angle, turn_positive);
	vertical_ray(data, ray_angle, turn_positive);
	if (ray_angle > 0 && ray_angle < 180)
	{
		a_y = (data->player_y / 64) * 64 - 1;
		ya = -64;
	}
	else
	{
		a_y = (data->player_y / 64) * 64 + 64;
		ya = 64;
	}
	printf("a_y = %d\n", a_y);
	a_x = data->player_x + (data->player_y - a_y) / tan(ray_angle);
	printf("a_x = %d\n", a_x);
	xa = 64 / tan(ray_angle) * turn_positive;
	printf("xa = %d\n", xa);
	while (1)
	{
		next_x = a_x + xa;
		next_y = a_y + ya;
		printf("next_x = %d\n", next_x);
		printf("next_y = %d\n", next_y);
		if (next_x < 0 || next_x > 64 * 9 || next_y < 0 || next_y > 64 * 9)
		{
			printf("wall hit but not in horizontal axis\n");
			break ;
		}
		if (data->map[next_y / 64][next_x / 64] == '1')
		{
			printf("wall hit\n");
			printf("wall is [%d][%d]\n", next_y / 64, next_x / 64);
			break ;
		}
		a_x = next_x;
		a_y = next_y;
	}
}

int	main(void)
{
	int			i;
	int			j;
	t_data		data;

	i = 0;
	j = 0;
	data.distance_from_projection_plane = (WIDTH / 2) / tan(FOV / 2);
	data.angle_between_rays = (double)60 / WIDTH;
	data.player_y = 3 * 64 + 32;
	data.player_x = 3 * 64 + 32;
	data.player_angle = 0;
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
	while (i < data.img->height * data.img->width * 4)
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
	while (i < WIDTH)
	{
		ray_calculation(&data, ray_angle);
		ray_angle += data.angle_between_rays;
		i++;
	}
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}
