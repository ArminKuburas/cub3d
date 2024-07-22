/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:23:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/07/22 16:38:48 by akuburas         ###   ########.fr       */
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

void	mlx_looping(t_data *data)
{
	
}
