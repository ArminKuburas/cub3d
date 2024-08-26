/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_validators.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:23:33 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/26 12:23:52 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	split_floor(t_map *map)
{
	int		i;
	int		j;

	map->floor = ft_split(map->f, ',');
	if (!map->floor)
		return (ft_err("Memory allocation error\n"));
	i = 0;
	while (map->floor[i] != NULL)
	{
		if (ft_atoi(map->floor[i]) > 255)
			return (ft_err("Color format > 255\n"));
		j = 0;
		while (map->floor[i][j])
		{
			if (map->floor[i][j] >= '0' && map->floor[i][j] <= '9')
				j++;
			else
				return (ft_err("Non-numeric characters in the color format\n"));
		}
		i++;
	}
	if (i != 3)
		return (ft_err("Incorrect floor color format: \
			exactly three numbers required\n"));
	return (0);
}

int	validate_floor(t_map *map)
{
	char	*f;

	f = map->f;
	if (*f == ',')
		return (ft_err("Incorrect floor color format\n"));
	while (*f)
	{
		if (*f == ',')
		{	
			f++;
			if (*f == ',' || *f == '\0')
				return (ft_err("Incorrect floor color format\n"));
		}
		else
			f++;
	}
	if (split_floor(map))
		return (1);
	return (0);
}

int	split_ceiling(t_map *map)
{
	int		i;
	int		j;

	map->ceiling = ft_split(map->c, ',');
	i = 0;
	while (map->ceiling[i] != NULL)
	{
		if (ft_atoi(map->ceiling[i]) > 255)
			return (ft_err("Color format > 255\n"));
		j = 0;
		while (map->ceiling[i][j])
		{
			if (map->ceiling[i][j] >= '0' && map->ceiling[i][j] <= '9')
				j++;
			else
				return (ft_err("Non-numeric characters in the color format\n"));
		}
		i++;
	}
	if (i != 3)
		return (ft_err("Incorrect ceiling color format: \
			exactly three numbers required\n"));
	return (0);
}

int	validate_ceiling(t_map *map)
{
	char	*c;

	c = map->c;
	if (*c == ',')
		return (ft_err("Incorrect ceiling color format\n"));
	while (*c)
	{
		if (*c == ',')
		{	
			c++;
			if (*c == ',' || *c == '\0')
				return (ft_err("Incorrect ceiling color format\n"));
		}
		else
			c++;
	}
	if (split_ceiling(map))
		return (1);
	return (0);
}
