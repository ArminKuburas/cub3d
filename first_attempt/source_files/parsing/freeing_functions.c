/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:11:39 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/27 19:55:31 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free (arr);
	arr = NULL;
}

void	map_info_helper(t_map *map)
{
	if (map->no)
	{
		free(map->no);
		map->no = NULL;
	}
	if (map->ea)
	{
		free(map->ea);
		map->ea = NULL;
	}
	if (map->we)
	{
		free(map->we);
		map->we = NULL;
	}
	if (map->so)
	{
		free(map->so);
		map->so = NULL;
	}
	if (map->f)
	{
		free(map->f);
		map->f = NULL;
	}
}

void	free_gnl_buffer(t_map *map)
{
	char	*line;

	if (map->fd <= 0)
		return ;
	line = get_next_line(map->fd);
	while (line)
	{
		free(line);
		line = get_next_line(map->fd);
	}
}

void	free_map_info(t_map *map)
{
	map_info_helper(map);
	free_gnl_buffer(map);
	if (map->fd > 0)
		close(map->fd);
	if (map->c)
	{
		free(map->c);
		map->c = NULL;
	}
	if (map->ceiling)
	{
		free_array(map->ceiling);
		map->ceiling = NULL;
	}
	if (map->floor)
	{
		free_array(map->floor);
		map->floor = NULL;
	}
	while (map->line_count--)
	{
		free(*(char **)vec_get(&map->map_copy, map->line_count));
	}
	vec_free(&map->map_copy);
}
