/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:52:48 by akuburas          #+#    #+#             */
/*   Updated: 2024/07/22 13:45:23 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../other_libraries/libft/libft.h"

#define FAILURE 1
#define SUCCESS 0

int	ft_err(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	return (FAILURE);
}

int	check_map_name(char *str)
{
	char	*find_last_slash;
	char	*find_dot;

	if (str == "")
		return (FAILURE);
	find_last_slash = ft_strchr(str, '/');
	if (!find_last_slash)
		find_dot = ft_strchr(str, '.');
	else
	{
		find_last_slash = ft_strrchr(str, '/');
		find_dot = ft_strrchr(find_last_slash, '.');
	}
	if (!find_dot)
		return (FAILURE);
	if (ft_strcmp(find_dot, ".cub") != 0)
		return (FAILURE);
	return (SUCCESS);
}

void	validate_map(char *filename, t_data *data)
{
	t_parsing_data	parse;

	parse = (t_parsing_data){};
	parse.fd = open(filename, O_RDONLY);
	if (parse.fd == -1)
	{
		perror("error\n");
		exit (FAILURE);
	}
}

int	initial_checks(int argc, char **argv)
{
	if (argc != 2)
		return (ft_err("Wrong number of arguments\nUsage: ./cub3D <map>.cub\n"));
	if (check_map_name(argv[1]) == FAILURE)
		return (ft_err("Given incorrect file format\n"));
}

/**
 * This message is for my teammate. I know you did a lot of map handling already
 * But I decided I wanted to do this small bit as a starting point for this file
 * We can modify/remove if needed.
 */
int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){};
	if (initial_checks(argc, argv) == FAILURE)
		return (FAILURE);
	validate_map(argv[1], &data);
	init_mlx(&data);
	(void)argc;
	(void)argv;
	return (0);
}
