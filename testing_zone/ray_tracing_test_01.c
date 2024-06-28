/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_test_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:39:06 by akuburas          #+#    #+#             */
/*   Updated: 2024/06/28 11:19:56 by akuburas         ###   ########.fr       */
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

int	main(void)
{
	char		map[10][10];
	char 		**map2;
	int			i;
	int			j;
	int			angle;
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			player_position[3];
	int			distance_from_projection_plane;
	double		angle_between_rays;

	i = 0;
	j = 0;
	map2 = calloc(10 * 64, sizeof(char *));
	while (i < 10 * 64)
	{
		map2[i] = calloc(10 * 64, sizeof(char));
		i++;
	}
	i = 0;
	distance_from_projection_plane = (WIDTH / 2) / tan(FOV / 2);
	angle_between_rays = FOV / WIDTH;
	player_position[0] = 4;
	player_position[1] = 4;
	player_position[2] = 0;
	printf("width = %d\n", WIDTH);
	printf("height = %d\n", HEIGHT);
	printf("fov = %f\n", FOV);
	printf("tan(fov / 2) = %f\n", tan(FOV / 2));
	printf("distance_from_projection_plane = %d\n", distance_from_projection_plane);
	printf("angle_between_rays = %f\n", angle_between_rays);
	int k;
	k = 0;
	double m;
	m = 0;
	while (k < WIDTH)
	{
		m += angle_between_rays;
		printf("m = %f\n", m / RADIAN);
		k++;
	}
	mlx = mlx_init(WIDTH * SCALE, HEIGHT * SCALE, "Ray Tracing Test 01", true);
	img = mlx_new_image(mlx, WIDTH * SCALE, HEIGHT * SCALE);
	while (i < img->height * img->width * 4)
	{
		img->pixels[i] = 255;
		img->pixels[i + 1] = 0;
		img->pixels[i + 2] = 0;
		img->pixels[i + 3] = 150;
		i += 4;
	}
	mlx_image_to_window(mlx, img, 0, 0);
	memset(map, 0, sizeof(map));
	i = 0;
	while (i < 10)
	{
		j = 0;
		if (i != 0 && i != 8)
		{
			map[i][0] = '1';
			j = 1;
			while (j < 9)
			{
				map[i][j] = '0';
				j++;
			}
			map[i][8] = '1';
		}
		else
		{
			j = 0;
			while (j < 9)
			{
				map[i][j] = '1';
				j++;
			}
		}
		i++;
	}
	i = 0;
	map[4][4] = 'P';
	while (i < 9)
	{
		printf("map[%d] = %s\n", i ,map[i]);
		i++;
	}
	i = 0;
	int map2_index;
	int map2_index2;
	int end;
	end = 0;
	map2_index = 0;
	map2_index2 = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			map2_index = 0;
			if (map[i][j] == 'P')
			{
				while (map2_index < 64)
				{
					map2_index2 = 0;
					while (map2_index2 < 64)
					{
						map2[i * 64 + map2_index][j * 64 + map2_index2] = '0';
						map2_index2++;
					}
					map2_index++;
				}
				map2[i * 64 + 32][j * 64 + 32] = 'P';
			}
			else
			{
				while (map2_index < 64)
				{
					map2_index2 = 0;
					while (map2_index2 < 64)
					{
						map2[i * 64 + map2_index][j * 64 + map2_index2] = map[i][j];
						map2_index2++;
					}
					map2_index++;
				}
			}
			j++;
		}
		i++;
	}
	i = 0;
	/*while (i < 9 * 64)
	{
		printf("map2[%d] = %s\n", i ,map2[i]);
		i++;
	}*/
	//testing tan with 270 degrees
	printf("tan(270) = %f\n", tan(270 * RADIAN));
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
