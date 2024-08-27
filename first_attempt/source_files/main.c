/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:52:48 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/27 15:23:04 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	set_rotation_angle(t_map *map, t_data *data)
{
	if (map->start_dir == 'S')
		data->player.rotation_angle = NORTH;
	if (map->start_dir == 'W')
		data->player.rotation_angle = WEST;
	if (map->start_dir == 'N')
		data->player.rotation_angle = SOUTH;
	if (map->start_dir == 'E')
		data->player.rotation_angle = EAST;
}

int	populate_data(t_map *map, t_data *data)
{
	int	i;

	data->map = malloc((map->line_count + 1) * sizeof(char *));
	if (!data->map)
		return (FAILURE);
	i = 0;
	while (i < map->line_count)
	{
		data->map[i] = ft_strdup(*(char **)vec_get(&map->map_copy, i));
		i++;
	}
	data->map[i] = NULL;
	set_rotation_angle(map, data);
	data->player.x = (64 * map->start_x) + 32;
	data->player.y = (64 * map->start_y) + 32;
	data->ceiling_colour = ft_pixel(ft_atoi(map->ceiling[0]),
			ft_atoi(map->ceiling[1]), ft_atoi(map->ceiling[2]), 255);
	data->floor_colour = ft_pixel(ft_atoi(map->floor[0]),
			ft_atoi(map->floor[1]), ft_atoi(map->floor[2]), 255);
	return (SUCCESS);
}

int	initial_map_validation(t_data *data, char **argv, int argc)
{
	if (vec_new(&data->parse_data->map_copy, 0, sizeof(char *)) == -1)
		return (FAILURE);
	if (check_arguments(argc, argv, data->parse_data))
	{
		free_map_info(data->parse_data);
		return (FAILURE);
	}
	if (validate_map(data->parse_data))
	{
		close(data->parse_data->fd);
		free_map_info(data->parse_data);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_data	data;

	data = (t_data){};
	map = (t_map){};
	data.parse_data = &map;
	if (initial_map_validation(&data, argv, argc) != SUCCESS)
		return (FAILURE);
	if (populate_data(&map, &data))
	{
		free(data.map);
		close(map.fd);
		free_map_info(&map);
		return (FAILURE);
	}
	if (reformat_map(&data) || open_load_textures(&data))
	{
		close(map.fd);
		free_map_info(&map);
		free_array(data.map);
		return (FAILURE);
	}
	close(map.fd);
	mlx_looping(&data);
	return (SUCCESS);
}
