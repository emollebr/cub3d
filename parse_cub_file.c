/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:08:36 by emollebr          #+#    #+#             */
/*   Updated: 2024/01/25 17:08:38 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	parse_cub_file(const char *filename, t_data *img)
{
	int		file;
	char	*start_of_map;

	file = open(filename, O_RDONLY);
	if (!file)
		return (ft_printf("Error:\n Couldn't open file: %s\n", filename), -1);
	if (parse_textures(file, img) == -1)
		return (-1);
	if (img->textures == NULL)
		return (-1);
	start_of_map = get_map_dimensions(file, img);
	close(file);
	file = open(filename, O_RDONLY);
	if (!file)
		return (ft_printf("Error:\n Couldn't open file: %s\n", filename), -1);
	if (parse_map(file, start_of_map, img) == -1)
		return (free_all(img), -1);
	if (!validate_map(img))
	{
		free_all(img);
		return (-1);
	}
	close(file);
	return (0);
}
