/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:37:16 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/26 14:58:07 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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

void	fix_fish_eye(t_ray *ray, t_data *data)
{
	float	angle;

	angle = data->player.rotation_angle;
	angle -= ray->angle;
	if (angle < 0)
		angle += 2 * M_PI;
	ray->distance *= cos(angle);
}

int	ft_err(char *str)
{
	ssize_t __attribute__	((unused)) result;

	result = write(2, "Error\n", 6);
	result = write(2, str, ft_strlen(str));
	return (FAILURE);
}
