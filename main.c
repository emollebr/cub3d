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
#include "includes/cub3d.h"

void my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int close_program(t_data *img)
{
    mlx_destroy_window(img->mlx, img->mlx_win);
    exit(0);
}

int render_frame(t_data *img)
{
    memset(img->addr, 0, WIDTH * HEIGHT * (img->bits_per_pixel / 8));
    if (cast_rays(img) == -1)
        return (free_all(img), -1);
    update_image(img, &img->keys);
    key_hook(&img->keys);
    return (0);
}

void    free_all(t_data *img)
{
    int i;
    t_sprite *tmp;

    i = -1;
    if (img->worldMap != NULL) {
        while (++i < img->mapHeight)
            free(img->worldMap[i]);
        free (img->worldMap);
    }
    i = -1;
    while (img->textures[++i].path != NULL)
        free(img->textures[i].path);
    while (img->sprites != NULL)
    {
        tmp = img->sprites;
        img->sprites = img->sprites->next;
        free(tmp);
    }
    free(img->sprites);
    return ;
}

int main(int argc, char **argv)
{
    t_data img;
    t_keys keys = {0};

    if (argc != 2 || access(argv[1], O_RDONLY) != 0)
        return (ft_printf("Enter valid .cub file as argument\n"), -1);
    img.mlx = mlx_init();
    img.mlx_win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Raycasting Demo");
    img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    keys.img = &img;
    img.worldMap = NULL;
    img.numSprites = 0;
    img.doors.door_bool = 0;
    // Parse the .cub file
    if (parse_cub_file(argv[1], &img) == -1)
        return (free_all(&img), -1);
    load_textures(&img);
    // Set player and other initializations
    img.player.old_player_x = img.player.x;
    img.player.old_player_y = img.player.y;
        img.doors.animation_frame = 0;
    img.doors.open_ = false;
    img.currentAnimationFrame = 0;
    img.animationspeed = 6;
    img.doors.currentAnimationFrame = 0;
    img.doors.animationspeed = 3000;
    img.doors.isOpen = 0;
    for (int i = 0; i < WIDTH; i++)
    {
        img.z_buffer[i] = DBL_MAX;
    }
    // Set up event hooks
    mlx_hook(img.mlx_win, 17, 0, close_program, &img);
    mlx_hook(img.mlx_win, 2, 1L << 0, key_press, &keys);
    mlx_hook(img.mlx_win, 3, 1L << 1, key_release, &keys);
    mlx_hook(img.mlx_win, 06, 1L << 6, mouse_motion, &keys);
    mlx_loop_hook(img.mlx, (void *)key_hook, &keys);

    // Start the main loop
    mlx_loop(img.mlx);
    mlx_destroy_window(img.mlx, img.mlx_win);
    mlx_destroy_image(img.mlx, img.img);
    free_all(&img);
    return (0);
}