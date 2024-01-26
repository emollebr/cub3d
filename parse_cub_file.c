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

void	render_minimap(t_data *img)
{
	t_minimap	minimap;
	int			x;
	int			y;

	minimap.x = 36;
	minimap.y = HEIGHT - 185;
	calculate_visible_area(img, &minimap);
	draw_background(img, &minimap);
	draw_player(img, &minimap);
	y = 0;
	while (y < minimap.vis_height && minimap.vis_y + y < img->mapHeight)
	{
		x = 0;
		while (x < minimap.vis_width && minimap.vis_x + x < img->mapWidth)
		{
			scale_visible_area(img, minimap, x, y);
			x++;
		}
		y++;
	}
}

int	parse_cub_file(const char *filename, t_data *img)
{
	int		file;
	char	*start_of_map;

	file = open(filename, O_RDONLY);
	if (!file)
		return (ft_printf("Error: Couldn't open file: %s\n", filename), -1);
	if (parse_textures(file, img) == -1)
		return (-1);
	if (img->textures == NULL)
		return (-1);
	start_of_map = get_map_dimensions(file, img);
	close(file);
	file = open(filename, O_RDONLY);
	if (!file)
		return (ft_printf("Error: Couldn't open file: %s\n", filename), -1);
	if (parse_map(file, start_of_map, img) == -1)
		return (-1);
	if (!validate_map(img))
		return (-1);
	close(file);
	return (0);
}
