/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:42:28 by lejimene          #+#    #+#             */
/*   Updated: 2024/01/29 16:44:22 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	compare_sprite_distance(const void *a, const void *b)
{
	double	distance_a;
	double	distance_b;

	distance_a = ((t_sprite_info *)a)->distance;
	distance_b = ((t_sprite_info *)b)->distance;
	if (distance_a < distance_b)
		return (-1);
	else if (distance_a > distance_b)
		return (1);
	else
		return (0);
}

void	sort_sprites(int *order, double *dist, int amount)
{
	double	sprites[amount][2];
	int i;

	i = -1;
	while (++i < amount)
	{
		sprites[i][0] = dist[i];
		sprites[i][1] = order[i];
	}
	qsort(sprites, amount, sizeof(sprites[0]), compare_sprite_distance);
	i = -1;
	while (++i < amount)
	{
		dist[i] = sprites[amount - i - 1][0];
		order[i] = (int)sprites[amount - i - 1][1];
	}
}

void	initialize_sprite_data(t_sprite_data *s, t_sprite *sprite, t_data *img)
{
	s->spriteX = sprite->x - img->player.x;
	s->spriteY = sprite->y - img->player.y;
	s->invDet = 1.0 / (img->player.plane_x * img->player.dir_y
			- img->player.dir_x * img->player.plane_y);
	s->transformX = s->invDet * (img->player.dir_y * s->spriteX
			- img->player.dir_x * s->spriteY);
	s->transformY = s->invDet * (-img->player.plane_y * s->spriteX
			+ img->player.plane_x * s->spriteY);
	s->spriteScreenX = (int)((WIDTH / 2) * (1 + s->transformX / s->transformY));
	s->spriteHeight = abs((int)(HEIGHT / s->transformY));
	s->spriteWidth = abs((int)(WIDTH / s->transformY));
	s->drawStartY = -s->spriteHeight / 2 + HEIGHT / 2;
	if (s->drawStartY < 0)
		s->drawStartY = 0;
	s->drawEndY = s->spriteHeight / 2 + HEIGHT / 2;
	if (s->drawEndY >= HEIGHT)
		s->drawEndY = HEIGHT - 1;
	s->drawStartX = -s->spriteWidth / 2 + s->spriteScreenX;
	if (s->drawStartX < 0)
		s->drawStartX = 0;
	s->drawEndX = s->spriteWidth / 2 + s->spriteScreenX;
	if (s->drawEndX > WIDTH)
		s->drawEndX = WIDTH;
}