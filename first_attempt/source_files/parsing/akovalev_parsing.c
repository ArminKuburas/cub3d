/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   akovalev_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:08:41 by akovalev          #+#    #+#             */
/*   Updated: 2024/07/22 18:06:54 by akovalev         ###   ########.fr       */
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
		i++;
	}
	free (arr);
}

void	free_map_info(t_map *map)
{
	printf("About to free everything\n");
	free(map->no);
	free(map->ea);
	free(map->we);
	free(map->so);
	free(map->f);
	free(map->c);
	if (map->ceiling)
		free_array(map->ceiling);
	if (map->floor)
		free_array(map->floor);
	while (map->line_count--)
		free(*(char **)(vec_get(&map->map_copy, map->line_count)));
	vec_free(&map->map_copy);
	printf("Freeing done\n");
}

int	check_arguments(int argc, char **argv, t_map *map)
{
	if (argc < 2)
		return(ft_err("Please provide a map file\n"));
	else if (argc > 2)
		return(ft_err("Please provide only one map file\n"));
	map->filename = argv[1];
	map->name_length = ft_strlen(map->filename);
	if (ft_strncmp(&map->filename[map->name_length - 4], ".cub", 4))
		return(ft_err("Incorrect map format\n"));
	map->fd = open(map->filename, O_RDONLY);
	if (map->fd == -1)
	{
		perror("Error\n");
		close(map->fd);
		return (1);
	}
	return (0);
}

int split_floor(t_map *map)
{
	int		i;
	int		j;

	map->floor = ft_split(map->f, ',');
	i = 0;
	while (map->floor[i] != NULL)
	{
		if (ft_atoi(map->floor[i]) > 255)
			return(ft_err("Color format > 255\n"));
		j = 0;
		while (map->floor[i][j])
		{
			if (map->floor[i][j] >= '0' &&  map->floor[i][j] <= '9')
				j++;
			else
				return(ft_err("Non-numeric characters in the color format\n"));
		}
		i++;
	}
	if (i != 3)
		return(ft_err("Incorrect floor color format: exactly three numbers required\n"));
	return (0);
}
int	validate_floor(t_map *map)
{
	char	*f;

	f = map->f;
	if (*f == ',')
		return(ft_err("Incorrect floor color format\n"));
	while (*f)
	{
		if (*f == ',')
		{	
			f++;
			if (*f == ',' || *f == '\0')
				return(ft_err("Incorrect floor color format\n"));
		}
		else
			f++;
	}
	if (split_floor(map))
		return (1);
	return (0);
}
int split_ceiling(t_map *map)
{
	int		i;
	int		j;

	map->ceiling = ft_split(map->c, ',');
	i = 0;
	while (map->ceiling[i] != NULL)
	{
		if (ft_atoi(map->ceiling[i]) > 255)
			return(ft_err("Color format > 255\n"));
		j = 0;
		while (map->ceiling[i][j])
		{
			if (map->ceiling[i][j] >= '0' &&  map->ceiling[i][j] <= '9')
				j++;
			else
				return(ft_err("Non-numeric characters in the color format\n"));
		}
		i++;
	}
	if (i != 3)
		return(ft_err("Incorrect ceiling color format: exactly three numbers required\n"));
	return (0);
}

int	validate_ceiling(t_map *map)
{
	char	*c;

	c = map->c;
	if (*c == ',')
		return(ft_err("Incorrect ceiling color format\n"));
	while (*c)
	{
		if (*c == ',')
		{	
			c++;
			if (*c == ',' || *c == '\0')
				return(ft_err("Incorrect ceiling color format\n"));
		}
		else
			c++;
	}
	if (split_ceiling(map))
		return (1);
	return (0);
}

int	check_cur_pos(t_map *map, char *str, size_t x, size_t y)
{
	char	*pr_str;
	char	*nxt_str;
	
	nxt_str = NULL;
	pr_str = NULL;
	if (str[x] != 'N' && str[x] != 'S' && str[x] != 'E' && str[x] != 'W' && str[x] != '1' && str[x] != ' ' && str[x] != '0' && str[x] != '\n')
		return(ft_err("Disallowed characters in the map\n"));
	// if (str[x] == ' ')
	// {
	// 	if ((str[x - 1] != '1' && str[x - 1] != ' ') || (str[x + 1] != '1' && str[x + 1] != ' ' && str[x + 1] != '\0' && str[x + 1] != '\n'))
	// 		printf("Wrong character at %s\n", &str[x]);
	// }
	else if (str[x] == 'N' || str[x] == 'S' || str[x] == 'E' || str[x] == 'W')
	{
		map->start_pos++;
		if (map->start_pos > 1)
			return(ft_err("Only one starting position marker allowed\n"));
	}
	if (str[x] == '0' || str[x] == 'N' || str[x] == 'S' || str[x] == 'E' || str[x] == 'W')
	{
		if (y)
			pr_str = *(char **)vec_get(&map->map_copy, y - 1);
		if (y < map->map_copy.len - 1)
		{
			nxt_str = *(char **)vec_get(&map->map_copy, y + 1);
			//printf("y is %ld, and map->map_copy.len - 1 is %ld\n", y, map->map_copy.len - 1);
		}
		if (str[x + 1] == ' ' || str[x + 1] == '\n')
		{
			printf("Wrong character after %s\n", &str[x]);
			return (1);
		}
		if ((pr_str && x >= ft_strlen (pr_str)) || (y && (pr_str[x] == ' ' || pr_str[x] == '\n')) || y == 0)
		{
			printf("Wrong character above %s\n", &str[x]);
			return (1);
		}
		if ((x && str[x - 1] == ' ') || x == 0)
		{
			printf("Wrong character before %s\n", &str[x]);
			return (1);
		}
		if ((nxt_str && x >= ft_strlen (nxt_str)) || (y < map->map_copy.len - 1 && (nxt_str [x] == ' ' || nxt_str [x] == '\n'|| nxt_str [x] == '\0')) || y == map->map_copy.len - 1)
		{
			printf("Wrong character below %s\n", &str[x]);
			return (1);
		}
	}
	return (0);
}

int	check_lines(t_map *map)
{
	size_t	y;
	size_t	x;
	char	*str;

	y = 0;
	printf("\nAbout to check lines\n");
	while (y < map->map_copy.len)
	{
		str = *(char **)vec_get(&map->map_copy, y);
		if (!strncmp(str, "\n", 1))
		{
			printf("Empty lines in the map\n");
			return (1);
		}			
		//printf("%s", *(char **)(vec_get(&map->map_copy, n)));
		//need to account for empty lines or lines containing only spaces and a newline
		x = 0;
		if (str[x] == ' ')
			x++;
		//printf("we are now at %s", *(char **)(vec_get(&map->map_copy, y)));
		while (str[x])
		{
			if(check_cur_pos(map, str, x, y))
				return (1);
			x++;
		}
		y++;
	}
	if (access(map->no, O_RDONLY) || access(map->so, O_RDONLY) || access(map->we, O_RDONLY) || access(map->ea, O_RDONLY)) //access not allowed, so later check with the MLX mlx_load_png
	{
		printf("Can't access texture file\n");
		return (1);
	}
	return (0);
}

int	validate_map(t_map *map)
{
	char	*line;
	char	*line_copy;
	char	*ptr;
	int		n;
	int		count;

	n = 0;
	count = 0;
	line = ft_strdup("");
	while (line != NULL)
	{
		free(line);
		line = get_next_line(map->fd);
		if (!line)
			break ;
		ptr = line;
		if (!strncmp(line, "NO", 2))
		{
			if (map->no)
			{
				free (line);
				return(ft_err("Multiple lines referring to one texture\n"));
			}
			ptr++;
			ptr++;
			while (*ptr == ' ')
				ptr++;
			map->no = ft_strdup(ptr);
			map->no[ft_strlen(map->no) - 1] = '\0';
			count++;
		}
		else if (!strncmp(line, "SO", 2))
		{
			if (map->so)
			{
				free (line);
				return(ft_err("Multiple lines referring to one texture\n"));
			}
			ptr++;
			ptr++;
			while (*ptr == ' ')
				ptr++;
			map->so = ft_strdup(ptr);
			map->so[ft_strlen(map->so) - 1] = '\0';
			count++;
		}
		else if (!strncmp(line, "WE", 2))
		{
			if (map->we)
			{
				free (line);
				return(ft_err("Multiple lines referring to one texture\n"));
			}
			ptr++;
			ptr++;
			while (*ptr == ' ')
				ptr++;
			map->we = ft_strdup(ptr);
			map->we[ft_strlen(map->we) - 1] = '\0';
			count++;
		}
		else if (!strncmp(line, "EA", 2))
		{
			if (map->ea)
			{
				free (line);
				return(ft_err("Multiple lines referring to one texture\n"));
			}
			ptr++;
			ptr++;
			while (*ptr == ' ')
				ptr++;
			map->ea = ft_strdup(ptr);
			map->ea[ft_strlen(map->ea) - 1] = '\0';
			count++;
		}
		else if (!strncmp(line, "F", 1))
		{
			if (map->f)
			{
				free (line);
				return(ft_err("Multiple lines referring to one texture\n"));
			}
			ptr++;
			while (*ptr == ' ')
				ptr++;
			map->f = ft_strdup(ptr);
			map->f[ft_strlen(map->f) - 1] = '\0';
			count++;
		}
		else if (!strncmp(line, "C", 1))
		{
			if (map->c)
			{
				free (line);
				return(ft_err("Multiple lines referring to one texture\n"));
			}
			ptr++;
			while (*ptr == ' ')
				ptr++;
			map->c = ft_strdup(ptr);
			map->c[ft_strlen(map->c) - 1] = '\0';
			count++;
		}
		else if (strncmp(line, "\n", 1) && count != 6)
		{
			free (line);
			return(ft_err("Incorrect or missing map lines\n"));
		}
		if (count == 6)
		{
			free(line);
			break ;
		}
		//ft_putstr_fd("line %d read successfully and is %s\n", n, line);	
		n++;
	}
	if (count != 6)
		return(ft_err("Incorrect or missing map lines\n"));
	// if (!map->no || !map->so ||!map->we ||!map->ea || !map->f || !map->c)
	// {
	// 	ft_putstr_fd("Map file missing necessary data\n", 2);
	// 	return (1);
	// }
	printf("Path to NO texture is %s\n", map->no);
	printf("Path to SO texture is %s\n", map->so);
	printf("Path to WE texture is %s\n", map->we);
	printf("Path to EA texture is %s\n", map->ea);
	printf("Floor color is %s\n", map->f);
	printf("Ceiling color is %s\n", map->c);
	line = get_next_line(map->fd);
	if (!line)
		return(ft_err("Incorrect or missing map lines\n"));
	while (line && !ft_strncmp(line, "\n", 1))
	{
		free(line);
		line = get_next_line(map->fd);
	}
	if (!line)
		return(ft_err("Incorrect or missing map lines\n"));
	while (line)
	{
		printf("copied line is %s", line);
		vec_push(&map->map_copy, &line);
		line = get_next_line(map->fd);
		map->line_count++;
	}
	//printf("\nLine 0 is\n%s\n", *(char **)(vec_get(&map->map_copy, 0)))
	if (check_lines(map))
		return (1);
	printf("\nLines checked successfully\n");
	if (validate_floor(map) || validate_ceiling(map))
		return (1);
	if (map->start_pos != 1)
		return(ft_err("Exactly one starting position marker required\n"));
	printf("\nColors checked successfully\n");
	printf("\nMap size is %d lines\n", map->line_count);
	printf("\nDone reading file\n");
	return (0);
}

// void	initialize_map_values(t_map *map)
// {
// 	map->no = NULL;
// 	map->so = NULL;
// 	map->ea = NULL;
// 	map->we = NULL;
// 	map->f = NULL;
// 	map->c = NULL;
// 	map->floor = NULL;
// 	map->ceiling = NULL;
// 	vec_new(&map->map_copy, 0, sizeof(char *));
// 	map->line_count = 0;
// 	map->start_pos = 0;
// }

// int	main(int argc, char **argv)
// {
// 	t_map	map;

// 	initialize_map_values(&map);
// 	if (check_arguments (argc, argv, &map))
// 	{
// 		//exit (EXIT_FAILURE);
// 		free_map_info(&map);
// 		return (1);
// 	}
// 	if (validate_map(&map))
// 	{
// 		//exit (EXIT_FAILURE);
// 		close(map.fd);
// 		free_map_info(&map);
// 		return (1);
// 	}
// 	printf("Map validated successfully\n");
// 	close(map.fd);
// 	free_map_info(&map);
// 	return (0);
// 	//exit(EXIT_SUCCESS);
// }
