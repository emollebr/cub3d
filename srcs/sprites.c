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

	s->texX = (int)(256 * (stripe - (-s->spriteWidth / 2 + s->spriteScreenX))
			* s->img->textures[sprite->texture_index].width / s->spriteWidth)
		/ 256;
	if (s->transformY > 0 && s->transformY < s->img->z_buffer[stripe])
	{
		y = s->drawStartY - 1;
		while (++y < s->drawEndY)
		{
			d = (y - MOV_SPEED) * 256 - HEIGHT * 128 + s->spriteHeight * 128;
			s->texY = ((d * s->img->textures[sprite->texture_index].height)
					/ s->spriteHeight) / 256;
			s->color = get_texture_color(s->img->textures[sprite->texture_index],
					s->texX, s->texY);
			if (s->color != (int)0xFF000000)
			{
				s->color = darken_color(s->color, s->spriteDistance[i] / 6);
				my_mlx_pixel_put(s->img, stripe, y, s->color);
			}
		}
	}
}

void	calculate_sprite_order_distance(t_data *img, t_sprite sprites[],
		int spriteOrder[], double spriteDistance[])
{
	t_sprite	*tmp_sprites;
	int			i;

	i = -1;
	tmp_sprites = img->sprites;
	while (++i < img->numSprites)
	{
		sprites[i].texture_index = 8 + img->current_anim_frame;
		if (!img->textures[sprites[i].texture_index].addr)
		{
			ft_printf("Error:\n Missing sprite texture\n");
			return ;
		}
		spriteOrder[i] = i;
		sprites[i].x = tmp_sprites->x;
		sprites[i].y = tmp_sprites->y;
		spriteDistance[i] = ((img->player.x - sprites[i].x) * (img->player.x
					- sprites[i].x) + (img->player.y - sprites[i].y)
				* (img->player.y - sprites[i].y));
		tmp_sprites = tmp_sprites->next;
	}
	sort_sprites(spriteOrder, spriteDistance, img->numSprites);
}

void	draw_sprites_loop(t_data *img, t_sprite_data *s, t_sprite *sprites,
		int *spriteOrder)
{
	int	i;
	int	stripe;

	i = -1;
	while (++i < img->numSprites)
	{
		s->sprite = &sprites[spriteOrder[i]];
		initialize_sprite_data(s, s->sprite, img);
		stripe = s->drawStartX - 1;
		while (++stripe < s->drawEndX)
			draw_sprite_column(s->sprite, s, stripe, i);
	}
}

int	draw_sprites(t_data *img)
{
	t_sprite sprites[img->numSprites + 1];
	int spriteOrder[img->numSprites + 1];
	t_sprite_data s;

	s.img = img;
	s.spriteDistance = malloc(sizeof(double) * img->numSprites + 1);
	if (!s.spriteDistance)
	{
		free(s.spriteDistance);
		return (-1);
	}
	calculate_sprite_order_distance(img, sprites, spriteOrder,
		s.spriteDistance);
	draw_sprites_loop(img, &s, sprites, spriteOrder);
	img->animationspeed--;
	if (img->animationspeed == 0)
	{
		img->current_anim_frame = (img->current_anim_frame + 1) % 6;
		img->animationspeed = 6;
	}
	free(s.spriteDistance);
	return (0);
}