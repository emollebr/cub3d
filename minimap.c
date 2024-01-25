/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:02:13 by emollebr          #+#    #+#             */
/*   Updated: 2024/01/25 17:02:15 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/cub3d.h"

void	draw_visible_area(t_data *img, t_minimap *minimap, int cell_x,
		int cell_y)
{
	int	color;
	int	og_x;
	int	og_y;
	int	i;
	int	j;

	i = 0;
	while (i < 180 / minimap->vis_width)
	{
		j = 0;
		while (j < 180 / minimap->vis_height)
		{
			og_x = (i * img->textures[l_MMVA].width) / (180
					/ minimap->vis_width);
			og_y = (j * img->textures[l_MMVA].height) / (180
					/ minimap->vis_height);
			if (!img->textures[l_MMVA].addr)
				color = 0x9e1c1c;
			else
				color = get_texture_color(img->textures[l_MMVA], og_x, og_y);
			my_mlx_pixel_put(img, cell_x + i, cell_y + j, color);
			j++;
		}
		i++;
	}
}

void	calculate_visible_area(t_data *img, t_minimap *minimap)
{
	minimap->vis_width = 10;
	minimap->vis_height = 10;
	minimap->vis_x = img->player.x - minimap->vis_width / 2;
	minimap->vis_y = img->player.y - minimap->vis_height / 2;
	if (minimap->vis_x < 0)
		minimap->vis_x = 0;
	if (minimap->vis_y < 0)
		minimap->vis_y = 0;
	if (minimap->vis_x + minimap->vis_width > img->mapWidth)
		minimap->vis_x = img->mapWidth - minimap->vis_width;
	if (minimap->vis_y + minimap->vis_height > img->mapHeight)
		minimap->vis_y = img->mapHeight - minimap->vis_height;
}

void	draw_background(t_data *img, t_minimap *minimap)
{
	int				og_y;
	int				og_x;
	unsigned int	color;
	int				y;
	int				x;

	y = minimap->y;
	while (y < minimap->y + 180)
	{
		x = minimap->x;
		og_y = (y - minimap->y) * img->textures[l_MMBG].height / 180;
		while (x < minimap->x + 180)
		{
			og_x = (x - minimap->x) * img->textures[l_MMBG].width / 180;
			if (!img->textures[l_MMBG].addr)
				color = 0xebe7c5;
			else
				color = get_texture_color(img->textures[l_MMBG], og_x, og_y);
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *img, t_minimap *minimap)
{
	int	player_minimap_x;
	int	player_minimap_y;
	int	y;
	int	x;

	player_minimap_x = minimap->x + (int)((img->player.x - minimap->vis_x)
			* (double)180 / minimap->vis_width);
	player_minimap_y = minimap->y + (int)((img->player.y - minimap->vis_y)
			* (double)180 / minimap->vis_height);
	y = player_minimap_y - 2;
	while (y <= player_minimap_y + 2)
	{
		x = player_minimap_x - 2;
		while (x <= player_minimap_x + 2)
		{
			my_mlx_pixel_put(img, x, y, 0xff0000);
			x++;
		}
		y++;
	}
}

void	render_minimap(t_data *img)
{
	t_minimap	minimap;
	int			cell_x;
	int			cell_y;
	int			x;
	int			y;

	minimap.x = 36;
	minimap.y = HEIGHT - 185;
	calculate_visible_area(img, &minimap);
	draw_background(img, &minimap);
	draw_player(img, &minimap);
	y = 0;
	while (y < minimap.vis_height)
	{
		x = 0;
		while (x < minimap.vis_width)
		{
			cell_x = minimap.x + (int)(x * (double)180 / minimap.vis_width);
			cell_y = minimap.y + (int)(y * (double)180 / minimap.vis_height);
			if (img->worldMap[minimap.vis_y + y][minimap.vis_x + x] == 1)
				draw_visible_area(img, &minimap, cell_x, cell_y);
			x++;
		}
		y++;
	}
}
