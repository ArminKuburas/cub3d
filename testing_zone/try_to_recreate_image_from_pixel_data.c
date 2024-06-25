/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_to_recreate_image_from_pixel_data.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:37:03 by akuburas          #+#    #+#             */
/*   Updated: 2024/06/25 15:03:32 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include "../../MLX42/include/MLX42/MLX42.h"

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	uint8_t			*pixel_data;
}	t_data;

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
	{
		printf("J pressed\n");
		memset(data->image->pixels, 0, sizeof(uint8_t) * (data->image->width * 2) * (data->image->height * 2));
	}
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_PRESS)
	{
		printf("K pressed\n");
		memcpy(data->image->pixels, data->pixel_data, sizeof(uint8_t) * (data->image->width * 2) * (data->image->height * 2));
	}
	if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS)
	{
		printf("H pressed\n");
		int i;
		i = 0;
		int j;
		j = 0;
		while (i < (data->image->width * 2) * (data->image->height * 2))
		{
			data->image->pixels[i] = data->pixel_data[j];
			data->image->pixels[i + 1] = data->pixel_data[j + 1];
			data->image->pixels[i + 2] = data->pixel_data[j + 2];
			data->image->pixels[i + 3] = data->pixel_data[j + 3];
			i += 4;
		}
	}
}

int	main(void)
{
	t_data			data;
	int				i;
	int				j;

	data.mlx = mlx_init(840, 840, "test", true);
	if (!data.mlx)
		return (1);
	data.texture = mlx_load_png("./Color_icon_purple_v2.svg.png");
	i = 0;
	if (!data.texture)
	{
		mlx_close_window(data.mlx);
		printf("Failed to load image\n");
		return (1);
	}
	data.image = mlx_texture_to_image(data.mlx, data.texture);
	if (!data.image)
	{
		mlx_delete_texture(data.texture);
		mlx_close_window(data.mlx);
		printf("Failed to convert texture to image\n");
		return (1);
	}
	printf("image->width = %d\n", data.image->width);
	printf("image->height = %d\n", data.image->height);
	printf("total amount of pixels is %d\n", (data.image->width * 2) * (data.image->height * 2));
	printf("this is pixel 0: %d\n", data.image->pixels[0]);
	data.pixel_data = malloc(sizeof(uint8_t) * (data.image->width * 2) * (data.image->height * 2));
	if (!data.pixel_data)
	{
		mlx_close_window(data.mlx);
		printf("Failed to allocate memory for pixel_data\n");
		return (1);
	}
	memcpy(data.pixel_data, data.image->pixels, sizeof(uint8_t) * (data.image->width * 2) * (data.image->height * 2));
	/*i = 0;
	j = 0;
	while (i < (image->width * 4) + (4 * image->height))
	{
		i += 4;
		printf("pixel_data[%d] = %d\n", j, pixel_data[j]);
		j++;
	}*/
	if (mlx_image_to_window(data.mlx, data.image, 0, 0))
	{
		mlx_close_window(data.mlx);
		printf("Failed to put image to window\n");
		return (1);
	}
	mlx_key_hook(data.mlx, my_keyhook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
