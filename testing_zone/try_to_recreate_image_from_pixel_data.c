/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_to_recreate_image_from_pixel_data.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:37:03 by akuburas          #+#    #+#             */
/*   Updated: 2024/06/22 06:43:40 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "../../MLX42/include/MLX42/MLX42.h"

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	uint8_t			*pixel_data;
}

int	main(void)
{
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	uint8_t			*pixel_data;
	int				i;
	int				j;

	mlx = mlx_init(840, 840, "test", true);
	if (!mlx)
		return (1);
	texture = mlx_load_png("./Color_icon_purple_v2.svg.png");
	i = 0;
	if (!texture)
	{
		mlx_close_window(mlx);
		printf("Failed to load image\n");
		return (1);
	}
	image = mlx_texture_to_image(mlx, texture);
	if (!image)
	{
		mlx_delete_texture(texture);
		mlx_close_window(mlx);
		printf("Failed to convert texture to image\n");
		return (1);
	}
	printf("image->width = %d\n", image->width);
	printf("image->height = %d\n", image->height);
	printf
	/*i = 0;
	while (i < image->width * image->height)
	{
		printf("image->pixels[%d] = %d\n", i, image->pixels[i]);
		i++;
	}*/
	pixel_data = malloc(sizeof(uint8_t) * image->width * image->height);
	if (!pixel_data)
	{
		mlx_close_window(mlx);
		printf("Failed to allocate memory for pixel_data\n");
		return (1);
	}
	memcpy(pixel_data, image->pixels, sizeof(uint8_t) * image->width * image->height);
	/*i = 0;
	j = 0;
	while (i < (image->width * 4) + (4 * image->height))
	{
		pixel_data[j] = ft_pixel(image->pixels[i], image->pixels[i + 1], image->pixels[i + 2], image->pixels[i + 3]);
		i += 4;
		printf("pixel_data[%d] = %d\n", j, pixel_data[j]);
		j++;
	}*/
	if (mlx_image_to_window(mlx, image, 0, 0))
	{
		mlx_close_window(mlx);
		printf("Failed to put image to window\n");
		return (1);
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
