/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   island_excluder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:34:37 by akovalev          #+#    #+#             */
/*   Updated: 2024/08/29 18:27:49 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	parse_cell(t_data *data, int x, int y)
{
	if (y >= data->map_height || x >= data->map_width || y < 0 || x < 0)
		return ;
	if (data->map[y][x] == '2' || data->map[y][x] == '3')
		return ;
	if (data->map[y][x] == '0')
		data->map[y][x] = '2';
	else if (data->map[y][x] == '1')
		data->map[y][x] = '3';
	else
		return ;
	parse_cell(data, x + 1, y);
	parse_cell(data, x - 1, y);
	parse_cell(data, x, y + 1);
	parse_cell(data, x, y - 1);
}

int	check_result(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1' || data->map[y][x] == '0')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	check_islands(t_data *data)
{
	int	x;
	int	y;

	parse_cell(data, data->parse_data->start_x, data->parse_data->start_y);
	if (check_result(data))
		return (1);
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '2')
				data->map[y][x] = '0';
			else if (data->map[y][x] == '3')
				data->map[y][x] = '1';
			x++;
		}
		y++;
	}
	return (0);
}
