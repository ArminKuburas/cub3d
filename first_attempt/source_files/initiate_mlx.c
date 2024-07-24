/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:23:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/07/25 02:40:53 by akuburas         ###   ########.fr       */
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
	data->rays = ft_calloc(WIDTH, sizeof(t_ray));
	if (!data->rays)
		free_all_and_exit(data);
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
