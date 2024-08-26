/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:04:23 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/26 15:08:34 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	parse_no(t_map *map, char *line, int *count)
{
	char	*ptr;

	ptr = line;
	if (map->no)
	{
		return (ft_err("Multiple lines referring to one texture\n"));
	}
	ptr++;
	ptr++;
	while (*ptr == ' ')
		ptr++;
	map->no = ft_strdup(ptr);
	if (!map->no)
		return (ft_err("Memory allocation error\n"));
	map->no[ft_strlen(map->no) - 1] = '\0';
	(*count)++;
	return (0);
}

int	parse_so(t_map *map, char *line, int *count)
{
	char	*ptr;

	ptr = line;
	if (map->so)
	{
		return (ft_err("Multiple lines referring to one texture\n"));
	}
	ptr++;
	ptr++;
	while (*ptr == ' ')
		ptr++;
	map->so = ft_strdup(ptr);
	if (!map->so)
		return (ft_err("Memory allocation error\n"));
	map->so[ft_strlen(map->so) - 1] = '\0';
	(*count)++;
	return (0);
}

int	parse_we(t_map *map, char *line, int *count)
{
	char	*ptr;

	ptr = line;
	if (map->we)
	{
		return (ft_err("Multiple lines referring to one texture\n"));
	}
	ptr++;
	ptr++;
	while (*ptr == ' ')
		ptr++;
	map->we = ft_strdup(ptr);
	if (!map->we)
		return (ft_err("Memory allocation error\n"));
	map->we[ft_strlen(map->we) - 1] = '\0';
	(*count)++;
	return (0);
}

int	parse_ea(t_map *map, char *line, int *count)
{
	char	*ptr;

	ptr = line;
	if (map->ea)
	{
		return (ft_err("Multiple lines referring to one texture\n"));
	}
	ptr++;
	ptr++;
	while (*ptr == ' ')
		ptr++;
	map->ea = ft_strdup(ptr);
	if (!map->ea)
		return (ft_err("Memory allocation error\n"));
	map->ea[ft_strlen(map->ea) - 1] = '\0';
	(*count)++;
	return (0);
}

int	parse_directions(t_map *map, char *line, int *count)
{
	if (!strncmp(line, "NO", 2))
	{
		if (parse_no(map, line, count))
			return (1);
	}
	else if (!strncmp(line, "SO", 2))
	{
		if (parse_so(map, line, count))
			return (1);
	}
	else if (!strncmp(line, "WE", 2))
	{
		if (parse_we(map, line, count))
			return (1);
	}
	else if (!strncmp(line, "EA", 2))
	{
		if (parse_ea(map, line, count))
			return (1);
	}
	return (0);
}
