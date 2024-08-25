/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:37:16 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/25 16:23:32 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	free_all_and_exit(t_data *data)
{
	(void)data;
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
