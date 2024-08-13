/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:23:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/13 01:28:30 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	free_all_and_exit(t_data *data)
{
	exit(0);
}

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

	number_fixer = 1 / -tan(rad_convert(angle));
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

	number_fixer = -tan(rad_convert(angle));
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
	ray->y = 0;
	ray->distance = (float)ray->texture->width / *texture_height;
	if (*texture_height > HEIGHT)
	{
		ray->y = (float)(*texture_height - HEIGHT) / 2 * ray->distance;
		*texture_height = HEIGHT;
	}
}

int32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

//each pixel is 4 uint8_ts. 
int32_t pixel_colour(mlx_image_t *image, int x, int y)
{
	int	start;

	if (x >= image->width || x < 0 || y >= image->height
		|| y < 0)
		return (DEFAULT_COLOUR);
	start = (y * image->width + x) * 4;
	return (ft_pixel(image->pixels[start], image->pixels[start + 1]	
			, image->pixels[start + 2], image->pixels[start + 3]));
}

void	modify_pixel(int x, int y, int32_t colour, t_data *data)
{
	if (x >= data->image->width || x < 0 || y >= data->image->height
		|| y < 0 || pixel_colour(data->image, x, y) == colour)
		return ;
	mlx_put_pixel(data->image, x, y, colour);
}

void	draw_ray(t_ray *ray, int texture_height, int amount_of_rays, t_data *data)
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
		modify_pixel(amount_of_rays, roof, data->ceiling_colour, data);
	floor = HEIGHT + 1;
	while (--floor > end_point)
		modify_pixel(amount_of_rays, floor, data->floor_colour, data);
	while (start_point < end_point)
	{
		color = get_pixel_color(ray->texture, ray->x, ray->y);
		modify_pixel(amount_of_rays, start_point, color, data);
		ray->y += ray->distance;
		start_point++;
	}
}

void	fix_fish_eye(t_ray *ray, t_data *data)
{
	float	angle;

	angle = data->player.rotation_angle;
	angle -= ray->angle;
	if (angle < 0)
		angle += 360;
	ray->distance *= cos(rad_convert(angle));
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
		figure_out_texture(&texture_height, &ray, data);
		draw_ray(&ray, texture_height, amount_of_rays, data);
		amount_of_rays++;
		angle += FOV / WIDTH;
		if (angle >= 360)
			angle -= 360;
	}
}

void	*close_window(void *param)
{
	t_data	*data;

	data = param;
	delete_everything_exit(data);
}

void	*key_press(mlx_key_data_t key_data, void *param)
{
	t_data	*data;

	data = param;
	if (key_data.action == MLX_PRESS && key_data.key == MLX_KEY_ESCAPE)
		free_all_and_exit(data);
}

void	move_player(t_data *data, enum e_direction direction)
{
	float	y_movement;
	float	x_movement;

	y_movement = sin(rad_convert(data->player.rotation_angle)) * MOVE_SPEED;
	x_movement = cos(rad_convert(data->player.rotation_angle)) * MOVE_SPEED;
	if (direction == GO_FORWARDS)
	{
		data->player.y += y_movement;
		data->player.x += x_movement;
	}
	else if (direction == GO_BACKWARDS)
	{
		data->player.y -= y_movement;
		data->player.x -= x_movement;
	}
	else if (direction == STRAFE_LEFT)
	{
		data->player.y -= x_movement;
		data->player.x += y_movement;
	}
	else
	{
		data->player.y += x_movement;
		data->player.x -= y_movement;
	}
}

void	turn_player(t_data *data, enum e_direction direction)
{
	if (direction == TURN_LEFT)
	{
		data->player.rotation_angle -= ROTATE_SPEED;
		if (data->player.rotation_angle < 0)
			data->player.rotation_angle += 360;
		else if (direction == TURN_RIGHT)
		{
			data->player.rotation_angle += ROTATE_SPEED;
			if (data->player.rotation_angle >= 360)
				data->player.rotation_angle -= 360;
		}
	}
}

void	*player_controller(void *param)
{
	t_data	*data;

	data = param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player(data, GO_FORWARDS);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, STRAFE_LEFT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, GO_BACKWARDS);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, STRAFE_RIGHT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		turn_player(data, TURN_LEFT);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		turn_player(data, TURN_RIGHT);
}

// For now we will render every frame. 
// If thats too slow we can render per movement.
void	mlx_looping(t_data *data)
{
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop_hook(data->mlx, player_controller, data);
	mlx_key_hook(data->mlx, key_press, data);
	mlx_close_hook(data->mlx, close_window, data);
	mlx_loop(data->mlx);
}
