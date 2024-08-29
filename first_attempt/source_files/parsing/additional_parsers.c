/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_parsers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:19:15 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/28 17:00:03 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	parse_f(t_map *map, char *line, int *count)
{
	char	*ptr;

	ptr = line;
	if (map->f)
	{
		return (ft_err("Multiple lines referring to one texture\n"));
	}
	ptr++;
	while (*ptr == ' ')
		ptr++;
	map->f = ft_strdup(ptr);
	if (!map->f)
		return (ft_err("Memory allocation error\n"));
	map->f[ft_strlen(map->f) - 1] = '\0';
	(*count)++;
	return (0);
}

int	parse_c(t_map *map, char *line, int *count)
{
	char	*ptr;

	ptr = line;
	if (map->c)
	{
		return (ft_err("Multiple lines referring to one texture\n"));
	}
	ptr++;
	while (*ptr == ' ')
		ptr++;
	map->c = ft_strdup(ptr);
	if (!map->c)
		return (ft_err("Memory allocation error\n"));
	map->c[ft_strlen(map->c) - 1] = '\0';
	(*count)++;
	return (0);
}

int	check_around_pos(t_map *map, char *str, size_t x, size_t y)
{
	if (y)
		map->pr_str = *(char **)vec_get(&map->map_copy, y - 1);
	if (y < map->map_copy.len - 1)
		map->nxt_str = *(char **)vec_get(&map->map_copy, y + 1);
	if (str[x + 1] == ' ' || str[x + 1] == '\n')
		return (1);
	if ((map->pr_str && x >= ft_strlen (map->pr_str)) || \
		(y && (map->pr_str[x] == ' ' || map->pr_str[x] == '\n')) || y == 0)
	{
		return (1);
	}
	if ((x && str[x - 1] == ' ') || x == 0)
		return (1);
	if ((map->nxt_str && x >= ft_strlen (map->nxt_str))
		|| (y < map->map_copy.len - 1
			&& (map->nxt_str [x] == ' ' || map->nxt_str [x] == '\n'
				|| map->nxt_str [x] == '\0')) || y == map->map_copy.len - 1)
	{
		return (1);
	}
	return (0);
}

int	check_cur_pos(t_map *map, char *str, size_t x, size_t y)
{
	if (str[x] != 'N' && str[x] != 'S' && str[x] != 'E' && str[x] != 'W'
		&& str[x] != '1' && str[x] != ' ' && str[x] != '0' && str[x] != '\n')
		return (ft_err("Disallowed characters in the map\n"));
	else if (str[x] == 'N' || str[x] == 'S' || str[x] == 'E' || str[x] == 'W')
	{
		map->start_pos++;
		map->start_dir = str[x];
		str[x] = '0';
		map->start_x = x;
		map->start_y = y;
		if (map->start_pos > 1)
			return (ft_err("Only one starting position marker allowed\n"));
	}
	if (str[x] == '0' || str[x] == 'N' || str[x] == 'S' \
		|| str[x] == 'E' || str[x] == 'W')
	{
		if (check_around_pos(map, str, x, y))
			return (ft_err("Incorrectly formatted map lines\n"));
	}
	return (0);
}

int	check_lines(t_map *map)
{
	size_t	y;
	size_t	x;
	char	*str;

	y = 0;
	while (y < map->map_copy.len)
	{
		str = *(char **)vec_get(&map->map_copy, y);
		if (!ft_strncmp(str, "\n", 1))
		{
			return (ft_err("Empty lines in the map\n"));
		}			
		x = 0;
		if (str[x] == ' ')
			x++;
		while (str[x])
		{
			if (check_cur_pos(map, str, x, y))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
