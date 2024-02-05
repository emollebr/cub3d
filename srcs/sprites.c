/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:41:48 by lejimene          #+#    #+#             */
/*   Updated: 2024/01/29 16:42:13 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_sprite_column(t_sprite *sprite, t_sprite_data *s, int stripe,
		int i)
{
	int	d;
	int	y;

	s->tex_x = (int)(256 * (stripe - (-s->sprite_width / 2
					+ s->sprite_screen_x))
			* s->img->textures[sprite->tex_idx].width / s->sprite_width) / 256;
	if (s->transform_y > 0 && s->transform_y < s->img->z_buffer[stripe])
	{
		y = s->draw_start_y - 1;
		while (++y < s->draw_end_y)
		{
			d = (y - MOV_SPEED) * 256 - HEIGHT * 128 + s->sprite_height * 128;
			s->tex_y = ((d * s->img->textures[sprite->tex_idx].height)
					/ s->sprite_height) / 256;
			s->color = get_texture_color(s->img->textures[sprite->tex_idx],
					s->tex_x, s->tex_y);
			if (s->color != (int)0xFF000000)
			{
				s->color = darken_color(s->color, s->sprite_distance[i] / 6);
				my_mlx_pixel_put(s->img, stripe, y, s->color);
			}
		}
	}
}

void	calculate_sprite_order_distance(t_data *img, t_sprite sprites[],
		int spriteOrder[], double sprite_distance[])
{
	t_sprite	*tmp_sprites;
	int			i;

	i = -1;
	tmp_sprites = img->sprites;
	while (++i < img->num_sprites)
	{
		sprites[i].tex_idx = 8 + img->current_anim_frame;
		if (!img->textures[sprites[i].tex_idx].addr)
		{
			ft_printf("Error:\n Missing sprite texture\n");
			return ;
		}
		spriteOrder[i] = i;
		sprites[i].x = tmp_sprites->x;
		sprites[i].y = tmp_sprites->y;
		sprite_distance[i] = ((img->player.x - sprites[i].x) * (img->player.x
					- sprites[i].x) + (img->player.y - sprites[i].y)
				* (img->player.y - sprites[i].y));
		tmp_sprites = tmp_sprites->next;
	}
	sort_sprites(spriteOrder, sprite_distance, img->num_sprites);
}

void	draw_sprites_loop(t_data *img, t_sprite_data *s, t_sprite *sprites,
		int *spriteOrder)
{
	int	i;
	int	stripe;

	i = -1;
	while (++i < img->num_sprites)
	{
		s->sprite = &sprites[spriteOrder[i]];
		initialize_sprite_data(s, s->sprite, img);
		stripe = s->draw_start_x - 1;
		while (++stripe < s->draw_end_x)
			draw_sprite_column(s->sprite, s, stripe, i);
	}
}

int	draw_sprites(t_data *img)
{
	int				*sprite_order;
	t_sprite		*sprites;
	t_sprite_data	s;

	sprite_order = ft_calloc(sizeof(int), img->num_sprites + 1);
	sprites = ft_calloc(sizeof(t_sprite), img->num_sprites + 1);
	s.img = img;
	s.sprite_distance = malloc(sizeof(double) * img->num_sprites + 1);
	if (!s.sprite_distance)
		return (free(s.sprite_distance), -1);
	calculate_sprite_order_distance(img, sprites, sprite_order,
		s.sprite_distance);
	draw_sprites_loop(img, &s, sprites, sprite_order);
	img->animationspeed--;
	if (img->animationspeed == 0)
	{
		img->current_anim_frame = (img->current_anim_frame + 1) % 6;
		img->animationspeed = 6;
	}
	free(s.sprite_distance);
	free(sprite_order);
	free(sprites);
	return (0);
}
