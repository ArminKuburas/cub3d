/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_test_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:39:06 by akuburas          #+#    #+#             */
/*   Updated: 2024/06/26 15:41:46 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include "../../MLX42/include/MLX42/MLX42.h"

#define SCALE 5
#define WIDTH 320
#define HEIGHT 200

int	main(void)
{
	char		map[10][10];
	int			i;
	int			j;
	int			angle;
	mlx_t		*mlx;
	mlx_image_t	*img;

	i = 0;
	j = 0;
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
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
