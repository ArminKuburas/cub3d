/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:17:10 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/29 13:45:53 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

/**
 * @brief sets the rest of the data to spaces.
 * @param len Pointer to the length of the line.
 * @param max_len The maximum length of the line.
 * @param ptr1 Pointer to the line.
 */
void	set_empty_data(int *len, int max_len, char *ptr1)
{
	while (len[0] < max_len - 1)
	{
		*ptr1 = ' ';
		ptr1++;
		len[0]++;
	}
	if (*len == max_len - 1)
		*ptr1 = '\n';
	if (*ptr1 != '\0')
	{
		ptr1++;
		*ptr1 = '\0';
	}
}

/**
 * @reallocates the line to the max_len.
 * @param ptr Pointer to the line.
 * @param max_len The maximum length of the line.
 * @return int Returns 0 if the line is reallocated successfully.
 */
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
	set_empty_data(&len, max_len, ptr1);
	free (parking);
	return (0);
}

/**
 * @brief reformats the map to a rectangle and into a 2D-array.
 * @param data Pointer to the data structure.
 * @return int Returns 0 if the map is reformatted successfully.
 */
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
			return (ft_err("Map reallocation failed\n"));
		ptr1++;
	}
	data->map_width = max_len;
	data->map_height = data->parse_data->line_count;
	if (check_islands(data))
		return (ft_err("Islands in the map are not allowed\n"));
	return (0);
}

/**
 * @brief Loads the images into textures.
 * @param data Pointer to the data structure.
 * @return int Returns 0 if the textures are loaded successfully.
 */
int	load_textures(t_data *data)
{
	data->north_texture = mlx_load_png(data->parse_data->so);
	if (!data->north_texture)
		return (ft_err("Can't load north texture file\n"));
	data->south_texture = mlx_load_png(data->parse_data->no);
	if (!data->south_texture)
	{
		mlx_delete_texture(data->north_texture);
		return (ft_err("Can't load south texture file\n"));
	}
	data->east_texture = mlx_load_png(data->parse_data->we);
	if (!data->east_texture)
	{
		mlx_delete_texture(data->north_texture);
		mlx_delete_texture(data->south_texture);
		return (ft_err("Can't load east texture file\n"));
	}
	data->west_texture = mlx_load_png(data->parse_data->ea);
	if (!data->west_texture)
	{
		mlx_delete_texture(data->north_texture);
		mlx_delete_texture(data->south_texture);
		mlx_delete_texture(data->east_texture);
		return (ft_err("Can't load west texture file\n"));
	}
	return (0);
}

/**
 * @brief Opens and loads the textures.
 * @param data Pointer to the data structure.
 * @return int Returns 0 if the textures are loaded successfully.
 */
int	open_load_textures(t_data *data)
{
	int	fd;

	fd = open(data->parse_data->so, O_RDONLY);
	if (fd == -1)
		return (ft_err("Can't load south texture file\n"));
	close(fd);
	fd = open(data->parse_data->no, O_RDONLY);
	if (fd == -1)
		return (ft_err("Can't load north texture file\n"));
	close(fd);
	fd = open(data->parse_data->ea, O_RDONLY);
	if (fd == -1)
		return (ft_err("Can't load east texture file\n"));
	close(fd);
	fd = open(data->parse_data->we, O_RDONLY);
	if (fd == -1)
		return (ft_err("Can't load west texture file\n"));
	close(fd);
	return (load_textures(data));
}
