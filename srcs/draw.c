/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:55:36 by emollebr          #+#    #+#             */
/*   Updated: 2024/01/29 17:55:37 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_wall_values(t_ray *ray, t_data *img, int *tex_num,
		double *wall_x, unsigned int *tex_x)
{
	if (ray->side == 0)
	{
		*wall_x = img->player.y + ray->perp_wall_dist * ray->ray_dir_y;
		*tex_num = (ray->ray_dir_x > 0) * 2 + (ray->ray_dir_x <= 0) * 3;
	}
	else
	{
		*wall_x = img->player.x + ray->perp_wall_dist * ray->ray_dir_x;
		*tex_num = (ray->ray_dir_y > 0) * 0 + (ray->ray_dir_y <= 0) * 1;
	}
	*wall_x -= floor(*wall_x);
	*tex_x = (unsigned int)(*wall_x * img->textures[*tex_num].width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		*tex_x = img->textures[*tex_num].width - *tex_x - 1;
}

void	draw_textured_wall(t_data *img, t_ray *ray, int x)
{
	int				tex_num;
	double			wall_x;
	int				y;
	unsigned int	tex[2];
	unsigned int	color;

	calculate_wall_values(ray, img, &tex_num, &wall_x, &tex[0]);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex[1] = (((y * 256 - HEIGHT * 128 + ray->line_height * 128)
					* img->textures[tex_num].height) / ray->line_height) / 256;
		tex[1] = fmin(fmax(tex[1], 0), img->textures[tex_num].height - 1);
		color = get_texture_color(img->textures[tex_num], (int)tex[0],
				(int)tex[1]);
		color = darken_color(color, ray->perp_wall_dist);
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
}

void	initialize_floor_values(t_data *img, int y,
		t_floor_values *floor_values)
{
	floor_values->rayDirX0 = img->player.dir_x - img->player.plane_x;
	floor_values->rayDirY0 = img->player.dir_y - img->player.plane_y;
	floor_values->rayDirX1 = img->player.dir_x + img->player.plane_x;
	floor_values->rayDirY1 = img->player.dir_y + img->player.plane_y;
	floor_values->p = y - HEIGHT / 2;
	floor_values->posZ = 0.5 * HEIGHT;
	floor_values->row_distance = floor_values->posZ / floor_values->p;
	floor_values->floor_step_x = floor_values->row_distance
		* (floor_values->rayDirX1 - floor_values->rayDirX0) / WIDTH;
	floor_values->floor_step_y = floor_values->row_distance
		* (floor_values->rayDirY1 - floor_values->rayDirY0) / WIDTH;
	floor_values->floor_x = img->player.x + floor_values->row_distance
		* floor_values->rayDirX0;
	floor_values->floor_y = img->player.y + floor_values->row_distance
		* floor_values->rayDirY0;
	floor_values->tex_width_F = img->textures[l_F].width;
	floor_values->tex_height_F = img->textures[l_F].height;
	floor_values->ceil_tex_width_C = img->textures[l_C].width;
	floor_values->ceil_tex_height_C = img->textures[l_C].height;
	floor_values->x = 0;
}

void	calculate_floor_values(t_floor_values *floor_values)
{
	floor_values->cellX = (int)floor_values->floor_x;
	floor_values->cellY = (int)floor_values->floor_y;
	floor_values->tx = (int)((floor_values->floor_x - floor_values->cellX)
			* floor_values->tex_width_F) & (floor_values->tex_width_F - 1);
	floor_values->ty = (int)((floor_values->floor_y - floor_values->cellY)
			* floor_values->tex_height_F) & (floor_values->tex_height_F - 1);
	floor_values->ceil_tx = (int)((floor_values->floor_x - floor_values->cellX)
			* floor_values->ceil_tex_width_C) & (floor_values->ceil_tex_width_C
			- 1);
	floor_values->ceil_ty = (int)((floor_values->floor_y - floor_values->cellY)
			* floor_values->ceil_tex_height_C)
		& (floor_values->ceil_tex_height_C - 1);
	floor_values->floor_x += floor_values->floor_step_x;
	floor_values->floor_y += floor_values->floor_step_y;
}

void	draw_floor_pixel(t_data *img, t_floor_values *floor_values)
{
	if (img->textures[l_F].rgb != 0)
		floor_values->floor_color = img->textures[l_F].rgb;
	else
		floor_values->floor_color = get_texture_color(img->textures[l_F],
				floor_values->tx, floor_values->ty);
	if (img->textures[l_C].rgb != 0)
		floor_values->ceil_color = img->textures[l_C].rgb;
	else
		floor_values->ceil_color = get_texture_color(img->textures[l_C],
				floor_values->ceil_tx, floor_values->ceil_ty);
	floor_values->floor_color = darken_color(floor_values->floor_color,
			(double)floor_values->row_distance);
	floor_values->ceil_color = darken_color(floor_values->ceil_color,
			(double)floor_values->row_distance);
}

void	draw_textured_floor(t_data *img)
{
	int				y;
	t_floor_values	floor_values;

	y = HEIGHT / 2 + 1;
	while (y < HEIGHT)
	{
		initialize_floor_values(img, y, &floor_values);
		while (floor_values.x < WIDTH)
		{
			calculate_floor_values(&floor_values);
			draw_floor_pixel(img, &floor_values);
			my_mlx_pixel_put(img, floor_values.x, y, floor_values.floor_color);
			my_mlx_pixel_put(img, floor_values.x, HEIGHT - y - 1,
				floor_values.ceil_color);
			floor_values.x++;
		}
		y++;
	}
}
