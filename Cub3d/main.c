/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:15:39 by lejimene          #+#    #+#             */
/*   Updated: 2024/01/07 19:14:17 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/cub3d.h"
#include <math.h>

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int     close_program(t_data *img)
{
    mlx_destroy_window(img->mlx, img->mlx_win);
    exit(0);
}

void    update_image(t_data *img)
{
    mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

void    cast_rays(t_data *img)
{
    int     x;
    t_ray   ray;

    x = 0;
    while (x < WIDTH)
    {
        ray.camera_x = 2 * x / (double)WIDTH - 1;
        ray.ray_dir_x = img->player.dir_x + img->player.plane_x * ray.camera_x;
        ray.ray_dir_y = img->player.dir_y + img->player.plane_y * ray.camera_x;

        // Map coordinates
        ray.map_x = (int)img->player.x;
        ray.map_y = (int)img->player.y;

        // Delta distances
        ray.delta_dist_x = fabs(1 / ray.ray_dir_x);
        ray.delta_dist_y = fabs(1 / ray.ray_dir_y);

        // Step and initial side distances
        if (ray.ray_dir_x < 0)
        {
            ray.step_x = -1;
            ray.side_dist_x = (img->player.x - ray.map_x) * ray.delta_dist_x;
        }
        else
        {
            ray.step_x = 1;
            ray.side_dist_x = (ray.map_x + 1.0 - img->player.x) * ray.delta_dist_x;
        }
        if (ray.ray_dir_y < 0)
        {
            ray.step_y = -1;
            ray.side_dist_y = (img->player.y - ray.map_y) * ray.delta_dist_y;
        }
        else
        {
            ray.step_y = 1;
            ray.side_dist_y = (ray.map_y + 1.0 - img->player.y) * ray.delta_dist_y;
        }

        // Perform DDA (Digital Differential Analyzer) algorithm
        while (ray.hit == 0)
        {
            if (ray.side_dist_x < ray.side_dist_y)
            {
                ray.side_dist_x += ray.delta_dist_x;
                ray.map_x += ray.step_x;
                ray.side = 0;
            }
            else
            {
                ray.side_dist_y += ray.delta_dist_y;
                ray.map_y += ray.step_y;
                ray.side = 1;
            }

            // Check if the ray hits a wall
            if (worldMap[ray.map_x][ray.map_y] == 1)
                ray.hit = 1;
        }

        // Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (ray.side == 0)
            ray.perp_wall_dist = (ray.map_x - img->player.x + (1 - ray.step_x) / 2) / ray.ray_dir_x;
        else
            ray.perp_wall_dist = (ray.map_y - img->player.y + (1 - ray.step_y) / 2) / ray.ray_dir_y;

        // Calculate height of line to draw on screen
        int line_height = (int)(HEIGHT / ray.perp_wall_dist);

        // Calculate lowest and highest pixel to fill in the current stripe
        int draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT)
            draw_end = HEIGHT - 1;

        // Choose wall color based on the side
        int color = (ray.side == 1) ? 0x00FF0000 : 0x0000FF00;

        // Draw the column
        int y = draw_start;
        while (y <= draw_end)
        {
            my_mlx_pixel_put(img, x, y, color);
            y++;
        }

        // Reset for the next column
        ray.hit = 0;
        x++;
    }
}

int     key_hook(int keycode, t_data *img)
{
    printf("%d\n", keycode);
    if (keycode == 53 || keycode == 65307) // ESC key
        close_program(img);
    // Handle other key events if needed
    if (keycode == 119) // W
    {
        // Increase player's speed when moving forward
        img->player.x += img->player.dir_x * MOV_SPEED;
        img->player.y += img->player.dir_y * MOV_SPEED;
    }
    if (keycode == 115) // S
    {
        // Decrease player's speed when moving backward
        img->player.x -= img->player.dir_x * MOV_SPEED;
        img->player.y -= img->player.dir_y * MOV_SPEED;
    }
    if (keycode == 97) // A
      {
        // Decrease player's speed when moving tot he left
        img->player.x -= img->player.plane_x * MOV_SPEED;
        img->player.y -= img->player.plane_y * MOV_SPEED;
    }
    if (keycode == 100) // D
       {
        // Increase player's speed when moving to the right
        img->player.x += img->player.plane_x * MOV_SPEED;
        img->player.y += img->player.plane_y * MOV_SPEED;
    }
    if (keycode == 65363)
    {
         // Rotate the player's direction to the left
        double oldDirX = img->player.dir_x;
        img->player.dir_x = img->player.dir_x * cos(-ROT_SPEED) - img->player.dir_y * sin(-ROT_SPEED);
        img->player.dir_y = oldDirX * sin(-ROT_SPEED) + img->player.dir_y * cos(-ROT_SPEED);
    }
    if (keycode == 65361)
    {
        // Rotate the player's direction to the right
        double oldDirX = img->player.dir_x;
        img->player.dir_x = img->player.dir_x * cos(ROT_SPEED) - img->player.dir_y * sin(ROT_SPEED);
        img->player.dir_y = oldDirX * sin(ROT_SPEED) + img->player.dir_y * cos(ROT_SPEED);
    }
    return (0);
}

int     render_frame(t_data *img)
{
    // Clear the previous frame
    memset(img->addr, 0, WIDTH * HEIGHT * (img->bits_per_pixel / 8));

    // Cast rays and render the frame
    cast_rays(img);

    // Update the image
    update_image(img);

    return (0);
}

int	main()
{
   t_data      img;

    img.mlx = mlx_init();
    img.mlx_win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Raycasting Demo");
    img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

   img.player.x = 22.0;
   img.player.y = 11.5;
   img.player.dir_x = -1.0;
   img.player.dir_y = 0.0;
   img.player.plane_x = 0.0;
   img.player.plane_y = 0.66;
    
    mlx_hook(img.mlx_win, 17, 0, close_program, &img);
    mlx_hook(img.mlx_win, 2, 1L << 0, key_hook, &img);

    mlx_loop_hook(img.mlx, (void *)render_frame, &img);
    mlx_loop(img.mlx);

    return (0);
}