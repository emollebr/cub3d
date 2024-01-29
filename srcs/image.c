/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:34:09 by lejimene          #+#    #+#             */
/*   Updated: 2024/01/26 17:34:13 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_sprintf(char *relative_path, int current_anim_frame)
{
	char	*base_path;
	char	*num_str;
	int		j;
	int		k;

	base_path = ft_strdup("./images/bicho/bicho");
	if (current_anim_frame < 5)
		num_str = ft_itoa(current_anim_frame + 1);
	else
		num_str = ft_itoa(1);
	j = 0;
	k = -1;
	while (base_path[++k] != '\0')
		relative_path[j++] = base_path[k];
	k = -1;
	while (num_str[++k] != '\0')
		relative_path[j++] = num_str[k];
	relative_path[j++] = '.';
	relative_path[j++] = 'x';
	relative_path[j++] = 'p';
	relative_path[j++] = 'm';
	relative_path[j] = '\0';
}

void	draw_overlay_image(t_data *img, void *overlay_img, int overlay_width,
		int overlay_height)
{
	int	*overlay_data;
	int	color;
	int	x;
	int	y;

	overlay_data = (int *)mlx_get_data_addr(overlay_img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	y = 0;
	while (++y < overlay_height)
	{
		x = 0;
		while (++x < overlay_width)
		{
			color = overlay_data[y * overlay_width + x];
			if ((color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(img, x, y, color);
		}
	}
}

void	*tumor_anim(t_data *img, int *img_width, int *img_height)
{
	void	*image;
	char	relative_path[50];

	ft_sprintf(relative_path, img->current_anim_frame + 1);
	image = mlx_xpm_file_to_image(img->mlx, relative_path, img_width,
			img_height);
	return (image);
}

void	*load_overlay_image(t_data *img, t_keys *keys, int *img_width,
		int *img_height)
{
	char	*relative_path;

	if (keys->q)
		relative_path = "./images/divine.xpm";
	else if (keys->w || keys->s)
		relative_path = "./images/headed2.xpm";
	else if (keys->a)
		relative_path = "./images/headedleft.xpm";
	else if (keys->d)
		relative_path = "./images/headedright.xpm";
	else
		relative_path = "./images/headed1.xpm";
	return (mlx_xpm_file_to_image(img->mlx, relative_path, img_width,
			img_height));
}

void	update_image(t_data *img, t_keys *keys)
{
	int img_width;
	int img_height;
	void *overlay_img[3];

	overlay_img[0] = load_overlay_image(img, keys, &img_width, &img_height);
	overlay_img[1] = mlx_xpm_file_to_image(img->mlx, "./images/hbhbjhb.xpm",
			&img_width, &img_height);
	overlay_img[2] = tumor_anim(img, &img_width, &img_height);
	if (overlay_img != NULL)
	{
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
		draw_overlay_image(img, overlay_img[0], img_width, img_height);
		render_minimap(img);
		draw_overlay_image(img, overlay_img[1], img_width, img_height);
		draw_overlay_image(img, overlay_img[2], img_width, img_height);
		mlx_do_sync(img->mlx);
		mlx_destroy_image(img->mlx, overlay_img[0]);
		mlx_destroy_image(img->mlx, overlay_img[1]);
		mlx_destroy_image(img->mlx, overlay_img[2]);
	}
	else
	{
		perror("Error loading overlay image.\n");
		free_all(img);
		exit(EXIT_FAILURE);
	}
}