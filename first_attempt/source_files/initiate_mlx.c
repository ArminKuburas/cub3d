/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:23:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/20 17:38:30 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	init_mlx(t_data *data)
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

void	figure_out_texture(int *texture_height, t_ray *ray, t_data *data)
{
	if (ray->texture == data->east_texture)
		ray->x = (int)ray->y % data->east_texture->width;
	else
		ray->x = (int)ray->x % data->south_texture->width;
	if (ray->texture == data->east_texture && ray->angle > NORTH
		&& ray->angle < SOUTH)
		ray->texture = data->west_texture;
	else if (ray->texture == data->south_texture && ray->angle > WEST)
		ray->texture = data->north_texture;
	if (ray->texture == data->west_texture)
		ray->x = data->west_texture->width - ray->x - 1;
	else if (ray->texture == data->south_texture)
		ray->x = data->south_texture->width - ray->x - 1;
	ray->y = 0;
	ray->distance = (float)ray->texture->width / *texture_height;
	if (*texture_height > HEIGHT)
	{
		ray->y = (float)(*texture_height - HEIGHT) / 2 * ray->distance;
		*texture_height = HEIGHT;
	}
}

void	draw_ray(t_ray *ray, int texture_height, int rays_amount, t_data *data)
{
	int32_t	color;
	int		start_point;
	int		end_point;
	int		floor;
	int		roof;

	start_point = HEIGHT / 2 - texture_height / 2;
	end_point = HEIGHT / 2 + texture_height / 2;
	roof = -1;
	while (++roof < start_point)
		modify_pixel(rays_amount, roof, data->ceiling_colour, data);
	floor = HEIGHT + 1;
	while (--floor > end_point)
		modify_pixel(rays_amount, floor, data->floor_colour, data);
	while (start_point < end_point)
	{
		color = texture_pixel_colour(ray->texture, ray->x, ray->y);
		modify_pixel(rays_amount, start_point, color, data);
		ray->y += ray->distance;
		start_point++;
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
		angle += 2 * M_PI;
	amount_of_rays = 0;
	while (amount_of_rays < WIDTH)
	{
		ray.angle = angle;
		calculate_ray(&ray, data);
		fix_fish_eye(&ray, data);
		texture_height = 64 * HEIGHT / ray.distance;
		figure_out_texture(&texture_height, &ray, data);
		draw_ray(&ray, texture_height, amount_of_rays, data);
		amount_of_rays++;
		angle += FOV / WIDTH;
		if (angle >= 2 * M_PI)
			angle -= 2 * M_PI;
	}
}

// For now we will render every frame. 
// If thats too slow we can render per movement.
void	mlx_looping(t_data *data)
{
	init_mlx(data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop_hook(data->mlx, player_controller, data);
	mlx_key_hook(data->mlx, key_press, data);
	mlx_close_hook(data->mlx, close_window, data);
	mlx_loop(data->mlx);
}
