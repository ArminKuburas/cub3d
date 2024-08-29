/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:26:42 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/29 13:47:28 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * @brief Closes the window when the escape key is pressed.
 * @param key_data The key data.
 * @param param Pointer to the data structure.
 */
void	key_press(mlx_key_data_t key_data, void *param)
{
	t_data	*data;

	data = param;
	if (key_data.action == MLX_PRESS && key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
}

/**
 * @brief Moves the player.
 * @param data Pointer to the data structure.
 * @param direction The direction to move.
 */
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

/**
 * @brief Turns the player.
 * @param data Pointer to the data structure.
 * @param direction The direction to turn.
 */
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

/**
 * @brief Controls the player movement.
 * @param param Pointer to the data structure.
 */
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
