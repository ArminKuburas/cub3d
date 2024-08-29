/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:37:16 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/29 13:39:20 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * @brief Frees all the allocated memory and exits the program.
 * @param data Pointer to the data structure.
 */
void	free_all_and_exit(t_data *data)
{
	free_map_info(data->parse_data);
	if (data->east_texture)
		mlx_delete_texture(data->east_texture);
	if (data->west_texture)
		mlx_delete_texture(data->west_texture);
	if (data->north_texture)
		mlx_delete_texture(data->north_texture);
	if (data->south_texture)
		mlx_delete_texture(data->south_texture);
	if (data->map)
		free_array(data->map);
	exit(0);
}


/**
 * @brief Fixes the fish eye effect.
 * @param ray Pointer to the ray structure.
 * @param data Pointer to the data structure.
 * @paragraph The fish eye effect is caused
 * by the rays hitting the walls at an angle.
 */
void	fix_fish_eye(t_ray *ray, t_data *data)
{
	float	angle;

	angle = data->player.rotation_angle;
	angle -= ray->angle;
	if (angle < 0)
		angle += 2 * M_PI;
	ray->distance *= cos(angle);
}


/**
 * @brief writes an error message to the standard error output.
 * @param str The error message to be written.
 * @return int Returns 1.
 */
int	ft_err(char *str)
{
	ssize_t __attribute__	((unused)) result;

	result = write(2, "Error\n", 6);
	result = write(2, str, ft_strlen(str));
	return (FAILURE);
}
