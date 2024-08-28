/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:53:27 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/28 10:35:25 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	find_collision(t_ray *ray, float x_travel, float y_travel, t_data *data)
{
	while (true)
	{
		if (ray->x < 0 || ray->x >= (data->map_width * 64) || ray->y < 0
			|| ray->y >= (data->map_height * 64)
			|| !ft_strchr("0", data->map[(int)ray->y / 64][(int)ray->x / 64]))
			break ;
		ray->x += x_travel;
		ray->y += y_travel;
	}
}

float	horizontal_ray(t_ray *ray, float angle, t_data *data)
{
	float	y_travel;
	float	x_travel;
	float	number_fixer;

	number_fixer = 1 / -tan(angle);
	if (angle > WEST)
	{
		ray->y = (int)data->player.y / 64 * 64 - 0.0001f;
		y_travel = -64;
	}
	else
	{
		ray->y = (int)data->player.y / 64 * 64 + 64;
		y_travel = 64;
	}
	ray->x = (data->player.y - ray->y) * number_fixer + data->player.x;
	x_travel = -y_travel * number_fixer;
	find_collision(ray, x_travel, y_travel, data);
	return (sqrtf(powf((ray->x - data->player.x), 2)
			+ powf((ray->y - data->player.y), 2)));
}

float	vertical_ray(t_ray *ray, float angle, t_data *data)
{
	float	x_travel;
	float	y_travel;
	float	number_fixer;

	number_fixer = -tan(angle);
	if (angle < NORTH || angle > SOUTH)
	{
		ray->x = (int)data->player.x / 64 * 64 + 64;
		x_travel = 64;
	}
	else
	{
		ray->x = (int)data->player.x / 64 * 64 - 0.0001f;
		x_travel = -64;
	}
	ray->y = (data->player.x - ray->x) * number_fixer + data->player.y;
	y_travel = -x_travel * number_fixer;
	find_collision(ray, x_travel, y_travel, data);
	return (sqrtf(powf((ray->x - data->player.x), 2)
			+ powf((ray->y - data->player.y), 2)));
}

void	calculate_ray(t_ray *ray, t_data *data)
{
	t_ray	horizontal;
	t_ray	vertical;
	float	horizontal_distance;
	float	vertical_distance;

	horizontal_distance = horizontal_ray(&horizontal, ray->angle, data);
	vertical_distance = vertical_ray(&vertical, ray->angle, data);
	if (horizontal_distance < vertical_distance)
	{
		ray->distance = horizontal_distance;
		ray->x = horizontal.x;
		ray->y = horizontal.y;
		ray->texture = data->south_texture;
	}
	else
	{
		ray->distance = vertical_distance;
		ray->x = vertical.x;
		ray->y = vertical.y;
		ray->texture = data->east_texture;
	}
}
