/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:02:38 by emollebr          #+#    #+#             */
/*   Updated: 2024/01/25 18:02:39 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

char	*allocate_map(int file, char *start_of_map, t_data *img)
{
	char	*line;
	int		i;

	i = -1;
	img->worldMap = ft_calloc(sizeof(int *), img->mapHeight);
	while (++i < img->mapHeight)
		img->worldMap[i] = ft_calloc(sizeof(int), img->mapWidth);
	line = get_next_line(file);
	while (ft_strncmp(start_of_map, line, ft_strlen(line) != 0))
	{
		free(line);
		line = get_next_line(file);
	}
	free(start_of_map);
	return (line);
}

char	*get_map_dimensions(int file, t_data *img)
{
	char	*start_of_map;
	char	*line;
	int		current_width;

	img->mapWidth = 0;
	img->mapHeight = 0;
	line = get_next_line(file);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(file);
	}
	start_of_map = ft_strdup(line);
	while (line != NULL && line[0] != '\n')
	{
		current_width = ft_strlen(line) - 1;
		if (current_width > img->mapWidth)
			img->mapWidth = current_width;
		img->mapHeight++;
		free(line);
		line = get_next_line(file);
	}
	free(line);
	img->sprites = ft_calloc(sizeof(t_sprite), 1);
	return (start_of_map);
}

int	add_sprite(t_data *img, int row, int col)
{
	if (img->numSprites > 0)
	{
		img->sprites->next = ft_calloc(sizeof(t_sprite), 1);
		if (!img->sprites->next)
			return (-1);
		img->sprites = img->sprites->next;
	}
	img->numSprites++;
	img->sprites->x = col;
	img->sprites->y = row;
	img->sprites->next = NULL;
	img->worldMap[row][col] = 5;
	return (0);
}

int	validate_map(t_data *img)
{
	int	i;

	i = -1;
	while (++i < img->mapHeight)
	{
		if (img->worldMap[i][0] != 1 && img->worldMap[i][0] != 3
			&& img->worldMap[i][img->mapWidth - 1] != 1
			&& img->worldMap[i][img->mapWidth - 1] != 3)
			return (ft_printf("Error: Map is not surrounded by walls.\n"), 0);
		if (img->worldMap[0][i] != 1 && img->worldMap[img->mapHeight
			- 1][i] != 1 && img->worldMap[0][i] != 3
			&& img->worldMap[img->mapHeight - 1][i] != 3)
			return (ft_printf("Error: Map is not surrounded by walls.\n"), 0);
	}
	if (!img->player.x || !img->player.y)
		return (ft_printf("Error: Missing player position on map.\n"), 0);
	return (1);
}
