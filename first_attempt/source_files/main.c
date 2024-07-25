/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:52:48 by akuburas          #+#    #+#             */
/*   Updated: 2024/07/25 17:50:14 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../other_libraries/libft/libft.h"

int	ft_err(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	return (FAILURE);
}

// int	check_map_name(char *str)
// {
// 	char	*find_last_slash;
// 	char	*find_dot;

// 	if (str == "")
// 		return (FAILURE);
// 	find_last_slash = ft_strchr(str, '/');
// 	if (!find_last_slash)
// 		find_dot = ft_strchr(str, '.');
// 	else
// 	{
// 		find_last_slash = ft_strrchr(str, '/');
// 		find_dot = ft_strrchr(find_last_slash, '.');
// 	}
// 	if (!find_dot)
// 		return (FAILURE);
// 	if (ft_strcmp(find_dot, ".cub") != 0)
// 		return (FAILURE);
// 	return (SUCCESS);
// }

// void	validate_map(char *filename, t_data *data)
// {
// 	t_parsing_data	parse;

// 	parse = (t_parsing_data){};
// 	parse.fd = open(filename, O_RDONLY);
// 	if (parse.fd == -1)
// 	{
// 		perror("error\n");
// 		exit (FAILURE);
// 	}
// }

// int	initial_checks(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (ft_err("Wrong number of arguments\nUsage: ./cub3D <map>.cub\n"));
// 	if (check_map_name(argv[1]) == FAILURE)
// 		return (ft_err("Given incorrect file format\n"));
// }

/**
 * This message is for my teammate. I know you did a lot of map handling already
 * But I decided I wanted to do this small bit as a starting point for this file
 * We can modify/remove if needed.
 */
// int	main(int argc, char **argv)
// {
// 	t_data	data;

// 	data = (t_data){};
// 	if (initial_checks(argc, argv) == FAILURE)
// 		return (FAILURE);
// 	validate_map(argv[1], &data);
// 	init_mlx(&data);
// 	(void)argc;
// 	(void)argv;
// 	return (0);
// }
int	populate_data(t_map *map, t_data *data)
{
	int	i;

	data->ceiling_colour[0] = ft_atoi(map->ceiling[0]);
	data->ceiling_colour[1] = ft_atoi(map->ceiling[1]);
	data->ceiling_colour[2] = ft_atoi(map->ceiling[2]);
	data->ceiling_colour[3] = 255;
	data->floor_colour[0] = ft_atoi(map->floor[0]);
	data->floor_colour[1] = ft_atoi(map->floor[1]);
	data->floor_colour[2] = ft_atoi(map->floor[2]);
	data->floor_colour[3] = 255;
	data->map = malloc((map->line_count + 1) * sizeof(char *));
	if (!data->map)
		return (1);
	i = 0;
	while (i < map->line_count)
	{
		data->map[i] = ft_strdup(*(char **)vec_get(&map->map_copy, i));
		i++;
	}
	data->map[i] = NULL;
	return (0);
}

int	realloc_line(t_data *data, char **ptr, int max_len)
{
	char	*temp;
	char	*parking;
	char	*ptr1;
	int		len;

	temp = *ptr;
	parking = *ptr;
	*ptr = ft_calloc(max_len + 1, sizeof(char));
	if (!*ptr)
		return (1);
	ptr1 = *ptr;
	len = 0;
	while (*temp)
	{
		if (*temp == '\n' && len != max_len - 1)
			*ptr1 = ' ';
		else
			*ptr1 = *temp;
		temp++;
		ptr1++;
		len++;
	}
	while (len < max_len - 1)
	{
		*ptr1 = ' ';
		ptr1++;
		len++;
	}
	if (len == max_len - 1)
		*ptr1 = '\n';
	if (*ptr1 != '\0')
	{
		ptr1++;
		*ptr1 = '\0';
	}
	free (parking);
	parking = NULL;
	ft_printf("reallocated line len is %d and it is %s", ft_strlen(*ptr), *ptr);
	return (0);
}

int	reformat_map(t_data *data)
{
	char	**ptr;
	char	**ptr1;
	int		max_len;

	max_len = 0;
	ptr = data->map;
	ptr1 = ptr;
	while (*ptr)
	{
		if (ft_strlen(*ptr) > max_len)
			max_len = ft_strlen(*ptr);
		ptr++;
	}
	//ft_printf("\nmax len is found to be %d\n", max_len);
	while (*ptr1)
	{
		//if (ft_strlen(*ptr) < max_len)
		if (realloc_line(data, ptr1, max_len))
			return (1);
		ptr1++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_data	data;

	data = (t_data){};
	map = (t_map){};
	if (vec_new(&map.map_copy, 0, sizeof(char *)) == -1)
		return (FAILURE);
	if (check_arguments (argc, argv, &map))
	{
		//exit (EXIT_FAILURE);
		free_map_info(&map);
		return (FAILURE);
	}
	if (validate_map(&map))
	{
		//exit (EXIT_FAILURE);
		close(map.fd);
		free_map_info(&map);
		return (FAILURE);
	}
	if (populate_data(&map, &data))
	{
		//exit (EXIT_FAILURE);
		free(data.map);
		close(map.fd);
		free_map_info(&map);
		return (FAILURE);
	}
	if (reformat_map(&data))
	{
		//exit (EXIT_FAILURE);
		close(map.fd);
		free_map_info(&map);
		free_array(data.map);
		return (FAILURE);
	}
	printf("Map validated successfully\n");
	close(map.fd);
	free_map_info(&map);
	//free(data.map);
	free_array(data.map);
	return (SUCCESS);
	//exit(EXIT_SUCCESS);
}
