/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:21:29 by emollebr          #+#    #+#             */
/*   Updated: 2024/01/25 18:21:30 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

double	get_scale(t_minimap minimap)
{
	if (minimap.vis_width < minimap.vis_height)
		return (180.0 / minimap.vis_width);
	else
		return (180.0 / minimap.vis_height);
}

int	get_original_xy(t_data *img, t_minimap *minimap, int x)
{
	return ((x * img->textures[minimap->wall_or_door].width) / (180
			/ minimap->vis_width));
}

int	get_texture_color(t_texture texture, int x, int y)
{
	return (*(unsigned int *)(texture.addr + (y * texture.line_length + x
			* (texture.bits_per_pixel / 8))));
}

int	darken_color(int color, double distance)
{
	int	red;
	int	green;
	int	blue;
	int	darken_factor;
	int	darkened_color;

	darken_factor = (int)(distance * 10);
	red = ((color >> 16) & 0xFF) - darken_factor;
	green = ((color >> 8) & 0xFF) - darken_factor;
	blue = (color & 0xFF) - darken_factor;
	if (red < 0)
		red = 0;
	else if (red > 255)
		red = 255;
	if (green < 0)
		green = 0;
	else if (green > 255)
		green = 255;
	if (blue < 0)
		blue = 0;
	else if (blue > 255)
		blue = 255;
	darkened_color = (red << 16) | (green << 8) | blue;
	return (darkened_color);
}

t_color	apply_light(t_color color, double distance)
{
	double	attenuation_factor;

	attenuation_factor = 1.0 / distance;
	color.r *= attenuation_factor;
	color.g *= attenuation_factor;
	color.b *= attenuation_factor;
	color.r = fmax(0.0, fmin(1.0, color.r));
	color.g = fmax(0.0, fmin(1.0, color.g));
	color.b = fmax(0.0, fmin(1.0, color.b));
	return (color);
}
