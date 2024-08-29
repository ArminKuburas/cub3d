/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_helper_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:24:21 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/29 13:41:37 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * @brief Creates a pixel from the given colour values.
 * @param r The red value of the pixel.
 * @param g The green value of the pixel.
 * @param b The blue value of the pixel.
 * @param a The alpha value of the pixel.
 * @return int32_t Returns the colour in int32_t format.
 */
int32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * @brief attemps to find the pixel at the given coordinates.
 * @param image Pointer to the image structure.
 * @param x The x coordinate of the pixel.
 * @param y The y coordinate of the pixel.
 * @return int32_t Returns the colour of the pixel.
 */
int32_t	pixel_colour(mlx_image_t *image, int x, int y)
{
	int	start;

	if (x >= (int)image->width || x < 0 || y >= (int)image->height
		|| y < 0)
		return (DEFAULT_COLOUR);
	start = (y * image->width + x) * 4;
	return (ft_pixel(image->pixels[start], image->pixels[start + 1]
			, image->pixels[start + 2], image->pixels[start + 3]));
}

/**
 * @brief attemps to find the pixel at the given coordinates.
 * @param image Pointer to the texture structure.
 * @param x The x coordinate of the pixel.
 * @param y The y coordinate of the pixel.
 */
int32_t	texture_pixel_colour(mlx_texture_t *image, int x, int y)
{
	int	start;

	if (x >= (int)image->width || x < 0 || y >= (int)image->height
		|| y < 0)
		return (DEFAULT_COLOUR);
	start = (y * image->width + x) * 4;
	return (ft_pixel(image->pixels[start], image->pixels[start + 1]
			, image->pixels[start + 2], image->pixels[start + 3]));
}

/**
 * @brief Modifies the pixel at the given coordinates.
 * @param x The x coordinate of the pixel.
 * @param y The y coordinate of the pixel.
 * @param colour The colour to be set.
 * @param data Pointer to the data structure.
 */
void	modify_pixel(int x, int y, int32_t colour, t_data *data)
{
	if (x >= (int)data->image->width || x < 0 || y >= (int)data->image->height
		|| y < 0 || pixel_colour(data->image, x, y) == colour)
		return ;
	mlx_put_pixel(data->image, x, y, colour);
}
