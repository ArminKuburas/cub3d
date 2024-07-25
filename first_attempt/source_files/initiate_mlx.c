/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:23:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/07/25 13:03:46 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", FALSE);
	if (!data->mlx)
		free_all_and_exit(data);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
		free_all_and_exit(data);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0)
		free_all_and_exit(data);
}

void	find_collision(t_ray *ray, float x_travel, float y_travel, t_data *data)
{
	while (true)
	{
		if (ray->x < 0 || ray->x >= data->map_width || ray->y < 0
			|| ray->y >= data->map_height
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

	number_fixer = 1 / -tan(radian_converter(angle));
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

	number_fixer = -tan(radian_converter(angle));
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

/*This should be the general frame of reference we can use
To render frames. Very similar to the testing I did
Next step is to actually code all the elements of it.*/
void	render_next_frame(void *main_data)
{
	t_data	*data;
	t_ray	ray;
	float	angle;
	int		amount_of_rays;
	int		texture_height;

	data = (t_data *)main_data;
	angle = data->player.rotation_angle - (FOV / 2);
	if (angle < 0)
		angle += 360;
	amount_of_rays = 0;
	while (amount_of_rays < WIDTH)
	{
		ray.angle = angle;
		calculate_ray(&ray, data);
		fix_fish_eye(&ray, data);
		texture_height = 64 / HEIGHT / ray.distance;
		calculate_texture(&texture_height, &ray, data);
		draw_ray(&ray, texture_height, amount_of_rays, data);
		amount_of_rays++;
		angle += FOV / WIDTH;
		if (angle >= 360)
			angle -= 360;
	}
}

// For now we will render every frame. 
// If thats too slow we can render per movement.
void	mlx_looping(t_data *data)
{
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop_hook(data->mlx, move_player, data);
	mlx_key_hook(data->mlx, key_press, data);
	mlx_close_hook(data->mlx, close_window, data);
	mlx_loop(data->mlx);
}
