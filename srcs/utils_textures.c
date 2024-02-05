/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <emollebr@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:08:54 by emollebr          #+#    #+#             */
/*   Updated: 2024/01/25 18:08:56 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_file_paths(t_data *img)
{
	img->textures[8].path = ft_strdup("./images/1c.xpm");
	img->textures[9].path = ft_strdup("./images/2c.xpm");
	img->textures[10].path = ft_strdup("./images/3c.xpm");
	img->textures[11].path = ft_strdup("./images/4c.xpm");
	img->textures[12].path = ft_strdup("./images/5c.xpm");
	img->textures[13].path = ft_strdup("./images/6c.xpm");
	img->textures[14].path = ft_strdup("./images/8c.xpm");
	img->textures[15].path = ft_strdup("./images/9c.xpm");
	img->textures[16].path = ft_strdup("./images/door1.xpm");
	img->textures[17].path = ft_strdup("./images/door2.xpm");
	img->textures[18].path = ft_strdup("./images/door3.xpm");
	img->textures[19].path = ft_strdup("./images/door4.xpm");
	img->textures[20].path = ft_strdup("./images/door5.xpm");
	img->textures[21].path = ft_strdup("./images/door6.xpm");
	img->textures[22].path = NULL;
}

void	load_sprites_and_doors(t_data *img)
{
	int	i;

	i = 0;
	while (i < 22)
	{
		if (img->textures[i].path != NULL && access(img->textures[i].path,
				O_RDONLY) == 0)
		{
			img->textures[i].img = mlx_xpm_file_to_image(img->mlx,
					img->textures[i].path, &img->textures[i].width,
					&img->textures[i].height);
			img->textures[i].addr = mlx_get_data_addr(img->textures[i].img,
					&img->textures[i].bits_per_pixel,
					&img->textures[i].line_length, &img->textures[i].endian);
		}
		i++;
	}
}

void	load_minimap_textures(t_data *img, t_texture *bg, t_texture *va)
{
	bg->addr = NULL;
	va->addr = NULL;
	if (access("./images/11.xpm", O_RDONLY) == 0)
	{
		bg->img = mlx_xpm_file_to_image(img->mlx, "./images/11.xpm", &bg->width,
				&bg->height);
		bg->addr = mlx_get_data_addr(bg->img, &bg->bits_per_pixel,
				&bg->line_length, &bg->endian);
	}
	if (access("./images/4.xpm", O_RDONLY) == 0)
	{
		va->img = mlx_xpm_file_to_image(img->mlx, "./images/4.xpm", &va->width,
				&va->height);
		va->addr = mlx_get_data_addr(va->img, &va->bits_per_pixel,
				&va->line_length, &va->endian);
	}
}

void	load_textures(t_data *img)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (img->textures[i].rgb == 0)
		{
			img->textures[i].img = mlx_xpm_file_to_image(img->mlx,
					img->textures[i].path, &img->textures[i].width,
					&img->textures[i].height);
			img->textures[i].addr = mlx_get_data_addr(img->textures[i].img,
					&img->textures[i].bits_per_pixel,
					&img->textures[i].line_length, &img->textures[i].endian);
			mlx_destroy_image(img->mlx, img->textures[i].img);
		}
		i++;
	}
	load_minimap_textures(img, &img->textures[l_MMBG], &img->textures[l_MMVA]);
	get_file_paths(img);
	load_sprites_and_doors(img);
}
