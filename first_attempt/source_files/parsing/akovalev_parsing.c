/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   akovalev_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:08:41 by akovalev          #+#    #+#             */
/*   Updated: 2024/08/29 14:14:57 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	check_arguments(int argc, char **argv, t_map *map)
{
	if (argc < 2)
		return (ft_err("Please provide a map file\n"));
	else if (argc > 2)
		return (ft_err("Please provide only one map file\n"));
	map->filename = argv[1];
	map->name_length = ft_strlen(map->filename);
	if (ft_strncmp(&map->filename[map->name_length - 4], ".cub", 4))
		return (ft_err("Incorrect map format\n"));
	map->fd = open(map->filename, O_RDONLY);
	if (map->fd == -1)
	{
		perror("Error\nError Type");
		return (1);
	}
	return (0);
}

int	parse_map_data_lines(t_map *map, char *line, int *count)
{
	if (!strncmp(line, "NO", 2) || !strncmp(line, "SO", 2)
		|| !strncmp(line, "EA", 2) || !strncmp(line, "WE", 2))
	{
		if (parse_directions(map, line, count))
			return (1);
	}
	else if (!strncmp(line, "F", 1))
	{
		if (parse_f(map, line, count))
			return (1);
	}
	else if (!strncmp(line, "C", 1))
	{
		if (parse_c(map, line, count))
			return (1);
	}
	else if (strncmp(line, "\n", 1) && *count != 6)
	{
		return (ft_err("Incorrect or missing map lines\n"));
	}
	if (*count == 6)
		free(line);
	return (0);
}

/**
 * @brief Parses the map lines.
 * @param map Pointer to the map structure.
 * @param line The current line in the map.
 * @return int Returns 0 if the function runs successfully.
 */
int	parse_map_lines(t_map *map, char *line)
{
	line = get_next_line(map->fd);
	if (!line)
		return (ft_err("Incorrect or missing map lines\n"));
	while (line && !ft_strncmp(line, "\n", 1))
	{
		free(line);
		line = get_next_line(map->fd);
	}
	if (!line)
		return (ft_err("Incorrect or missing map lines\n"));
	while (line)
	{
		if (vec_push(&map->map_copy, &line) == -1)
			return (ft_err("Memory allocation error\n"));
		line = get_next_line(map->fd);
		map->line_count++;
	}
	if (check_lines(map))
		return (1);
	return (0);
}

/**
 * @brief Validates the initial lines of the map.
 * @param map Pointer to the map structure.
 * @param line The current line in the map.
 * @param count The count of the lines parsed.
 * @return int Returns 0 if the function runs successfully.
 */
int	validate_initial_lines(t_map *map, char *line, int *count)
{
	int	n;

	n = 0;
	while (line != NULL && *count != 6)
	{
		free(line);
		line = get_next_line(map->fd);
		if (!line)
			break ;
		if (parse_map_data_lines(map, line, count))
		{
			free (line);
			return (FAILURE);
		}
		n++;
	}
	return (SUCCESS);
}

/**
 * @brief Validates the map.
 * @param map Pointer to the map structure.
 * @return int Returns 0 if the map is valid.
 */
int	validate_map(t_map *map)
{
	char	*line;
	int		count;

	count = 0;
	line = ft_strdup("");
	if (!line)
		return (ft_err("Memory allocation error\n"));
	if (validate_initial_lines(map, line, &count) != SUCCESS)
		return (FAILURE);
	if (count != 6)
	{
		if (line)
			free(line);
		return (ft_err("Incorrect or missing map lines\n"));
	}
	if (parse_map_lines(map, line))
		return (1);
	if (validate_floor(map) || validate_ceiling(map))
		return (1);
	if (map->start_pos != 1)
		return (ft_err("Exactly one starting position marker required\n"));
	return (0);
}
