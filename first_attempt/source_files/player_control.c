/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:26:42 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/20 17:59:40 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	close_window(void *param)
{
	t_data	*data;

	data = param;
	free_all_and_exit(data);
}

void	key_press(mlx_key_data_t key_data, void *param)
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

	y_movement = sin(data->player.rotation_angle) * MOVE_SPEED;
	x_movement = cos(data->player.rotation_angle) * MOVE_SPEED;
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
			data->player.rotation_angle += 2 * M_PI;
	}
	else if (direction == TURN_RIGHT)
	{
		data->player.rotation_angle += ROTATE_SPEED;
		if (data->player.rotation_angle >= 2 * M_PI)
			data->player.rotation_angle -= 2 * M_PI;
	}
}

void	player_controller(void *param)
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
