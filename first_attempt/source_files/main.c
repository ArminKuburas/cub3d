/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:52:48 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/25 19:06:48 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"
#include "../other_libraries/libft/libft.h"

int	populate_data(t_map *map, t_data *data)
{
	int	i;

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
	if (map->start_dir == 'S')
		data->player.rotation_angle = NORTH;
	if (map->start_dir == 'W')
		data->player.rotation_angle = WEST;
	if (map->start_dir == 'N')
		data->player.rotation_angle = SOUTH;
	if (map->start_dir == 'E')
		data->player.rotation_angle = EAST;
	data->player.x = (64 * map->start_x) + 32;
	data->player.y = (64 * map->start_y) + 32;
	data->ceiling_colour = ft_pixel(ft_atoi(map->ceiling[0]),
			ft_atoi(map->ceiling[1]), ft_atoi(map->ceiling[2]), 255);
	data->floor_colour = ft_pixel(ft_atoi(map->floor[0]),
			ft_atoi(map->floor[1]), ft_atoi(map->floor[2]), 255);
	return (0);
}

int	realloc_line(char **ptr, int max_len)
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
		if ((int)ft_strlen(*ptr) > max_len)
			max_len = ft_strlen(*ptr);
		ptr++;
	}
	while (*ptr1)
	{
		if (realloc_line(ptr1, max_len))
			return (1);
		ptr1++;
	}
	data->map_width = max_len;
	data->map_height = data->parse_data->line_count;
	return (0);
}

//mlx_delete_texture in case of errors needs to be added
int	load_textures(t_data *data)
{
	data->north_texture = mlx_load_png(data->parse_data->so);
	if (!data->north_texture)
		return (ft_err("Can't load north texture file\n"));
	data->south_texture = mlx_load_png(data->parse_data->no);
	if (!data->south_texture)
		return (ft_err("Can't load south texture file\n"));
	data->east_texture = mlx_load_png(data->parse_data->we);
	if (!data->east_texture)
		return (ft_err("Can't load east texture file\n"));
	data->west_texture = mlx_load_png(data->parse_data->ea);
	if (!data->west_texture)
		return (ft_err("Can't load west texture file\n"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_data	data;

	data = (t_data){};
	map = (t_map){};
	data.parse_data = &map;
	if (vec_new(&map.map_copy, 0, sizeof(char *)) == -1)
		return (FAILURE);
	if (check_arguments(argc, argv, &map))
	{
		free_map_info(&map);
		return (FAILURE);
	}
	if (validate_map(&map))
	{
		close(map.fd);
		free_map_info(&map);
		return (FAILURE);
	}
	if (populate_data(&map, &data))
	{
		free(data.map);
		close(map.fd);
		free_map_info(&map);
		return (FAILURE);
	}
	if (reformat_map(&data) || load_textures(&data))
	{
		close(map.fd);
		free_map_info(&map);
		free_array(data.map);
		return (FAILURE);
	}
	close(map.fd);
	mlx_looping(&data);
	printf("mlx loop has ended\n");
	return(0);
}
