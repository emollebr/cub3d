/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:15:39 by lejimene          #+#    #+#             */
/*   Updated: 2024/01/15 16:59:36 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_program(t_data *img)
{
	free_all(img);
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	exit(0);
}

int	render_frame(t_data *img)
{
	memset(img->addr, 0, WIDTH * HEIGHT * (img->bits_per_pixel / 8));
	if (cast_rays(img) == -1)
		return (free_all(img), -1);
	update_image(img, &img->keys);
	key_hook(&img->keys);
	return (0);
}

void	free_all(t_data *img)
{
	int			i;
	t_sprite	*tmp;

	i = -1;
	if (img->worldMap != NULL)
	{
		while (++i < img->mapHeight)
			free(img->worldMap[i]);
		free(img->worldMap);
	}
	i = 0;
	while (i < 23)
	{
		if (img->textures[i].img != NULL)
		{
			mlx_destroy_image(img->mlx, img->textures[i].img);
			free(img->textures[i].path);
		}
		i++;
	}
	while (img->sprites != NULL)
	{
		tmp = img->sprites;
		img->sprites = img->sprites->next;
		free(tmp);
	}
	free(img->sprites);
	return ;
}

int	main(int argc, char **argv)
{
	t_data img;
	t_keys keys = {0};

	if (argc != 2)
		return (ft_printf("Enter .cub file as argument\n"), -1);
	keys.img = &img;
	img.worldMap = NULL;
	initialize_doors(&img);
	if (parse_cub_file(argv[1], &img) == -1)
		return (free_all(&img), -1);
	initialize_mlx_window(&img);
	load_textures(&img);
	img.player.old_player_x = img.player.x;
	img.player.old_player_y = img.player.y;
	initialize_z_buffer(&img);
	setup_mlx_hooks(&img, &keys);
	mlx_loop(img.mlx);
	free_all(&img);
	mlx_destroy_window(img.mlx, img.mlx_win);
	mlx_destroy_image(img.mlx, img.img);
	return (0);
}