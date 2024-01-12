/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levijimenezrufes <levijimenezrufes@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:15:39 by lejimene          #+#    #+#             */
/*   Updated: 2024/01/12 13:31:17 by levijimenez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

void update_image(t_data *img)
{
    // Load overlay image
    int img_width;
    int img_height;
    char *relative_path = "./images/hbhbjhb.xpm";
    void *overlay_img = mlx_xpm_file_to_image(img->mlx, relative_path, &img_width, &img_height);

    if (overlay_img != NULL)
    {


        // Update the window
        mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
		        // Put the overlay image to the window at position (0, 0)
        mlx_put_image_to_window(img->mlx, img->mlx_win, overlay_img, 0, 0);
        mlx_do_sync(img->mlx);
    }
    else
    {
        // Handle error, e.g., print an error message or exit the program
        fprintf(stderr, "Error loading overlay image.\n");
        exit(EXIT_FAILURE);
    }
}

void cast_rays(t_data *img)
{
    int x;
    t_ray ray;

    x = 0;
    while (x < WIDTH)
    {
        ray.camera_x = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
        ray.ray_dir_x = img->player.dir_x + img->player.plane_x * ray.camera_x;
        ray.ray_dir_y = img->player.dir_y + img->player.plane_y * ray.camera_x;

        ray.map_x = (int)img->player.x;
        ray.map_y = (int)img->player.y;

 		ray.delta_dist_x = (ray.ray_dir_x == 0) ? 1e30 : fabs(1 / ray.ray_dir_x);
		ray.delta_dist_y = (ray.ray_dir_y == 0) ? 1e30 : fabs(1 / ray.ray_dir_y);

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
        ray.hit = 0;
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
            printf("%d\n", img->worldMap[ray.map_x][ray.map_y]);
            if (img->worldMap[ray.map_x][ray.map_y] == 1)
                ray.hit = 1;
        }

        if (ray.side == 0)
			ray.perp_wall_dist = (ray.map_x - img->player.x + (1 - ray.step_x) / 2) / ray.ray_dir_x;
        else
            ray.perp_wall_dist = (ray.map_y - img->player.y + (1 - ray.step_y) / 2) / ray.ray_dir_y;

        int line_height = (int)(HEIGHT / ray.perp_wall_dist);
        int draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT)
            draw_end = HEIGHT - 1;

        int color = (ray.side == 1) ? 0x00FF0000 : 0x0000FF00;

        int y = draw_start;
        while (y <= draw_end)
        {
            my_mlx_pixel_put(img, x, y, color);
            y++;
        }

        ray.hit = 0;
        x++;
    }
}


int key_press(int keycode, t_keys *keys)
{
   if (keycode == 119) // W key
        keys->w = true;
    if (keycode == 115)  // S key
        keys->s = true;
    if (keycode == 97)  // A key
        keys->a = true;
    if (keycode == 100)  // D key
        keys->d = true;
    if (keycode == 65361) // Left arrow key
        keys->left = true;
    if (keycode == 65363) // Right arrow key
        keys->right = true;

    return (0);
}

int key_release(int keycode, t_keys *keys)
{
    if (keycode == 119) // W key
        keys->w = false;
    if (keycode == 115)  // S key
        keys->s = false;
    if (keycode == 97)  // A key
        keys->a = false;
    if (keycode == 100)  // D key
        keys->d = false;
    if (keycode == 65361) // Left arrow key
        keys->left = false;
    if (keycode == 65363) // Right arrow key
        keys->right = false;

    return (0);
}
int key_hook(t_data *img)
{
    t_keys  *keys;

    keys = &img->keys;
    double oldPlayerX = img->player.x;
    double oldPlayerY = img->player.y;
    // Handle key presses
    if (keys->w)
    {
		printf("whaatttttt\n\n\n\n\n");
        img->player.x += img->player.dir_x * MOV_SPEED;
        img->player.y += img->player.dir_y * MOV_SPEED;
    }
    if (keys->s)
    {
        img->player.x -= img->player.dir_x * MOV_SPEED;
        img->player.y -= img->player.dir_y * MOV_SPEED;
    }
    if (keys->a)
    {
        img->player.x -= img->player.plane_x * MOV_SPEED;
        img->player.y -= img->player.plane_y * MOV_SPEED;
    }
    if (keys->d)
    {
        img->player.x += img->player.plane_x * MOV_SPEED;
        img->player.y += img->player.plane_y * MOV_SPEED;
    }
	    // Check for collisions with walls
    if (img->worldMap[(int)oldPlayerY][(int)img->player.x] == 1 || img->worldMap[(int)oldPlayerY][(int)img->player.x] == 3)
    {
        // Undo the player's movement if there is a wall in the new X position
        img->player.x = oldPlayerX;
    }
    if (img->worldMap[(int)img->player.y][(int)oldPlayerX] == 1)
    {
        // Undo the player's movement if there is a wall in the new Y position
        img->player.y = oldPlayerY;
    }

    double oldDirY = img->player.dir_y;
    double oldPlaneY = img->player.plane_y;
    if (keys->right)
    {
        // Handle rotation to the right
        double oldDirX = img->player.dir_x;
        img->player.dir_x = img->player.dir_x * cos(-ROT_SPEED) - img->player.dir_y * sin(-ROT_SPEED);
        img->player.dir_y = oldDirX * sin(-ROT_SPEED) + img->player.dir_y * cos(-ROT_SPEED);

        double oldPlaneX = img->player.plane_x;
        img->player.plane_x = img->player.plane_x * cos(-ROT_SPEED) - img->player.plane_y * sin(-ROT_SPEED);
        img->player.plane_y = oldPlaneX * sin(-ROT_SPEED) + img->player.plane_y * cos(-ROT_SPEED);
		        // Check for collisions with walls after rotation
        if (img->worldMap[(int)oldPlayerY][(int)img->player.x] == 1 || img->worldMap[(int)img->player.y][(int)oldPlayerX] == 1)
        {
            // Undo the rotation if there is a wall
            img->player.dir_x = oldDirX;
            img->player.dir_y = oldDirY;
            img->player.plane_x = oldPlaneX;
            img->player.plane_y = oldPlaneY;
        }

    }
    if (keys->left)
    {
        // Handle rotation to the left
        double oldDirX = img->player.dir_x;
        img->player.dir_x = img->player.dir_x * cos(ROT_SPEED) - img->player.dir_y * sin(ROT_SPEED);
        img->player.dir_y = oldDirX * sin(ROT_SPEED) + img->player.dir_y * cos(ROT_SPEED);

        double oldPlaneX = img->player.plane_x;
        img->player.plane_x = img->player.plane_x * cos(ROT_SPEED) - img->player.plane_y * sin(ROT_SPEED);
        img->player.plane_y = oldPlaneX * sin(ROT_SPEED) + img->player.plane_y * cos(ROT_SPEED);
		        // Check for collisions with walls after rotation
        if (img->worldMap[(int)img->player.x][(int)oldPlayerY] == 1 || img->worldMap[(int)oldPlayerX][(int)img->player.y] == 1)
        {
            // Undo the rotation if there is a wall
            img->player.dir_x = oldDirX;
            img->player.dir_y = oldDirY;
            img->player.plane_x = oldPlaneX;
            img->player.plane_y = oldPlaneY;
        }
    }
	//printf ("player x : %f\n", img->player.x);
	//printf ("player y : %f\n", img->player.y);

    // Continue with rendering logic
    memset(img->addr, 0, WIDTH * HEIGHT * (img->bits_per_pixel / 8));
    cast_rays(img);
    update_image(img);

    return (0);
}


int render_frame(t_data *img)
{
    memset(img->addr, 0, WIDTH * HEIGHT * (img->bits_per_pixel / 8));

    cast_rays(img);
	
    update_image(img);
	key_hook(img);
	
    return (0);
}

int main(int argc, char **argv)
{
    t_data img;
   //t_keys keys = {0};

    img.mlx = mlx_init();
    img.mlx_win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Raycasting Demo");
    img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
   //keys.img = &img;


    if (argc != 2)
        return (ft_printf("Error: enter valid .cub file as argument\n"), -1);

    img.player.x = 26.0;
    img.player.y = 11.0;
    img.player.dir_x = -1.0;
    img.player.dir_y = 0.0;
    img.player.plane_x = 0.0;
    img.player.plane_y = 0.66;
    img.textures = malloc(sizeof(t_textures));
    img.textures->type = NULL;
    img.keys.w = false;
    img.keys.s = false;
    img.keys.a = false;
    img.keys.d = false;
    img.keys.left = false;
    img.keys.right = false;
        
    img.textures->path = NULL;
    parse_cub_file(argv[1], &img);
    

    mlx_hook(img.mlx_win, 17, 0, close_program, &img);
    mlx_hook(img.mlx_win, 2, 1L << 0, key_press, &img.keys);
    mlx_hook(img.mlx_win, 3, 1L << 1, key_release, &img.keys);
    mlx_loop_hook(img.mlx, (void *)key_hook, &img); // Hook the key_hook function

    mlx_loop(img.mlx);

    //freeing
    while (img.textures != NULL) {
        free(img.textures->type);
        free(img.textures->path);
        img.textures = img.textures->next;
    }
    free(img.textures);
    int i = 0;
    while (i < img.mapHeight)
    {
        free(img.worldMap[i]);
        i++;
    }
    free(img.worldMap);
    return (0);
}