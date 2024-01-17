/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levijimenezrufes <levijimenezrufes@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:15:39 by lejimene          #+#    #+#             */
/*   Updated: 2024/01/12 13:41:05 by levijimenez      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/cub3d.h"

int darken_color(int color, double distance)
{
    // Extract color channels (assuming 32-bit color with 8 bits per channel)
    int red = (color >> 16) & 0xFF;
    int green = (color >> 8) & 0xFF;
    int blue = color & 0xFF;

    // Darken the color based on the distance (you can customize this logic)
    int darken_factor = (int)(distance * 6);  // Adjust the multiplier based on your preference
    red -= darken_factor;
    green -= darken_factor;
    blue -= darken_factor;

    // Ensure color channels stay within the valid range (0-255)
    red = (red < 0) ? 0 : (red > 255) ? 255 : red;
    green = (green < 0) ? 0 : (green > 255) ? 255 : green;
    blue = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;

    // Combine the modified color channels
    int darkened_color = (red << 16) | (green << 8) | blue;

    return darkened_color;
}

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

void update_image(t_data *img, t_keys *keys)
{
    // Load overlay images
    int img_width, img_height;
    void *overlay_img2;
    char *relative_path = "./images/hbhbjhb.xpm";
    char *relative_path2 = "./images/headed1.xpm";
    char *relative_path3 = "./images/headed2.xpm";
	char *relative_path_left = "./images/headedleft.xpm";
	char *relative_path_right = "./images/headedright.xpm";

    printf("%f\n", img->player.x);
    // Check if player.x is even or odd
    if (keys->w || keys->s)
        overlay_img2 = mlx_xpm_file_to_image(img->mlx, relative_path3, &img_width, &img_height);
    else if (keys->a)
        overlay_img2 = mlx_xpm_file_to_image(img->mlx, relative_path_left, &img_width, &img_height);
	else if (keys->d)
        overlay_img2 = mlx_xpm_file_to_image(img->mlx, relative_path_right, &img_width, &img_height);
	else
		overlay_img2 = mlx_xpm_file_to_image(img->mlx, relative_path2, &img_width, &img_height);

	img->player.old_player_x = img->player.x;
	img->player.old_player_y = img->player.y;
    void *overlay_img = mlx_xpm_file_to_image(img->mlx, relative_path, &img_width, &img_height);

    if (overlay_img != NULL && overlay_img2 != NULL)
    {
        // Update the window
        mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
        // Put the overlay image to the window at position (0, 0)
        mlx_put_image_to_window(img->mlx, img->mlx_win, overlay_img2, 0, 0);
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

// Define the apply_light function
t_color apply_light(t_color color, double distance) {
    // Apply lighting effects based on the distance or any other criteria
    // For example, you can reduce the intensity of the color based on distance
    // This is a simple illustration, adjust it based on your needs

    // Assuming distance-based attenuation
    double attenuation_factor = 1.0 / distance;  // Adjust this factor based on your needs

    // Apply attenuation to each color component
    color.r *= attenuation_factor;
    color.g *= attenuation_factor;
    color.b *= attenuation_factor;

    // Ensure that the color components are within the valid range (0.0 to 1.0)
    color.r = fmax(0.0, fmin(1.0, color.r));
    color.g = fmax(0.0, fmin(1.0, color.g));
    color.b = fmax(0.0, fmin(1.0, color.b));

    return color;
}

void load_textures(t_data *img)
{
    // Load textures into textures array
    char *texture_paths[5] = {
        "./images/1.xpm",
        "./images/2.xpm",
        "./images/1.xpm",
        "./images/2.xpm",
		"./images/4.xpm"};

    for (int i = 0; i < 5; i++)
    {
        img->textures[i].img = mlx_xpm_file_to_image(img->mlx, texture_paths[i], &img->textures[i].width, &img->textures[i].height);
        img->textures[i].addr = mlx_get_data_addr(img->textures[i].img, &img->textures[i].bits_per_pixel, &img->textures[i].line_length, &img->textures[i].endian);
    }
}

void draw_textured_wall(t_data *img, t_ray *ray, int x)
{
    int tex_num;
    double wall_x;

    if (ray->side == 0)
    {
        wall_x = img->player.y + ray->perp_wall_dist * ray->ray_dir_y;
        tex_num = (ray->ray_dir_x > 0) ? 2 : 3;
    }
    else
    {
        wall_x = img->player.x + ray->perp_wall_dist * ray->ray_dir_x;
        tex_num = (ray->ray_dir_y > 0) ? 0 : 1;
    }

    wall_x -= floor(wall_x);

    int tex_x = (int)(wall_x * (double)img->textures[tex_num].width);
    if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
        tex_x = img->textures[tex_num].width - tex_x - 1;

    for (int y = ray->draw_start; y < ray->draw_end; y++)
    {
        int tex_y = (((y * 256 - HEIGHT * 128 + ray->line_height * 128) * img->textures[tex_num].height) / ray->line_height) / 256;
        int color = *(unsigned int *)(img->textures[tex_num].addr + (tex_y * img->textures[tex_num].line_length + tex_x * (img->textures[tex_num].bits_per_pixel / 8)));

        // Darken the color for perspective
        color = darken_color(color, ray->perp_wall_dist);

        my_mlx_pixel_put(img, x, y, color);
    }
}

// Helper function to get the color from a texture at specified coordinates
int get_texture_color(t_texture texture, int x, int y)
{
    return *(unsigned int *)(texture.addr + (y * texture.line_length + x * (texture.bits_per_pixel / 8)));
}


void draw_textured_floor(t_data *img, int x)
{
    int floor_tex_num = 4; // Choose the appropriate floor texture index
    int ceil_tex_num = 4;  // Choose the appropriate ceiling texture index

    for (int y = HEIGHT / 2 + 1; y < HEIGHT; ++y)
    {
        float rayDirX0 = img->player.dir_x - img->player.plane_x;
        float rayDirY0 = img->player.dir_y - img->player.plane_y;
        float rayDirX1 = img->player.dir_x + img->player.plane_x;
        float rayDirY1 = img->player.dir_y + img->player.plane_y;

        int p = y - HEIGHT / 2;
        float posZ = 0.5 * HEIGHT;
        float row_distance = posZ / p;

        float floor_step_x = row_distance * (rayDirX1 - rayDirX0) / WIDTH;
        float floor_step_y = row_distance * (rayDirY1 - rayDirY0) / WIDTH;

        float floor_x = img->player.x + row_distance * rayDirX0;
        float floor_y = img->player.y + row_distance * rayDirY0;

        int tex_width = img->textures[floor_tex_num].width;
        int tex_height = img->textures[floor_tex_num].height;

        int ceil_tex_width = img->textures[ceil_tex_num].width;
        int ceil_tex_height = img->textures[ceil_tex_num].height;

        for (x = 0; x < WIDTH; ++x)
        {
            int cellX = (int)floor_x;
            int cellY = (int)floor_y;

            int tx = (int)((floor_x - cellX) * tex_width) & (tex_width - 1);
            int ty = (int)((floor_y - cellY) * tex_height) & (tex_height - 1);

            int ceil_tx = (int)((floor_x - cellX) * ceil_tex_width) & (ceil_tex_width - 1);
            int ceil_ty = (int)((floor_y - cellY) * ceil_tex_height) & (ceil_tex_height - 1);

            floor_x += floor_step_x;
            floor_y += floor_step_y;

            int floor_color = get_texture_color(img->textures[floor_tex_num], tx, ty);
            int ceil_color = get_texture_color(img->textures[ceil_tex_num], ceil_tx, ceil_ty);

            my_mlx_pixel_put(img, x, y, floor_color);
            my_mlx_pixel_put(img, x, HEIGHT - y - 1, ceil_color);
        }
    }
}




void cast_rays(t_data *img)
{
    int x;
    t_ray ray;

    x = 0;
	draw_textured_floor(img, x);
	
    while (x < WIDTH)
    {
        ray.camera_x = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
        ray.ray_dir_x = img->player.dir_x + img->player.plane_x * ray.camera_x;
        ray.ray_dir_y = img->player.dir_y + img->player.plane_y * ray.camera_x;

        ray.map_x = (int)img->player.x;
        ray.map_y = (int)img->player.y;

        ray.delta_dist_x = (ray.ray_dir_x == 0) ? 1e30 : fabs(1 / ray.ray_dir_x);
        ray.delta_dist_y = (ray.ray_dir_y == 0) ? 1e30 : fabs(1 / ray.ray_dir_y);
		
    	ray.floor_x_step = ray.perp_wall_dist * (ray.ray_dir_y + ray.floor_y);
    	ray.floor_y_step = ray.perp_wall_dist * (ray.ray_dir_x + ray.floor_x);
		

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

            if (worldMap[ray.map_x][ray.map_y] == 1)
                ray.hit = 1;
        }

        if (ray.side == 0)
            ray.perp_wall_dist = (ray.map_x - img->player.x + (1 - ray.step_x) / 2) / ray.ray_dir_x;
        else
            ray.perp_wall_dist = (ray.map_y - img->player.y + (1 - ray.step_y) / 2) / ray.ray_dir_y;

        ray.line_height = (int)(HEIGHT / ray.perp_wall_dist);
        ray.draw_start = -ray.line_height / 2 + HEIGHT / 2;
        if (ray.draw_start < 0)
            ray.draw_start = 0;
        ray.draw_end = ray.line_height / 2 + HEIGHT / 2;
        if (ray.draw_end >= HEIGHT)
            ray.draw_end = HEIGHT - 1;

        // Draw textured walls
        draw_textured_wall(img, &ray, x);
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
int key_hook(t_keys *keys)
{
    t_data *img = keys->img; // Assuming keys->img holds a reference to your t_data structure

    double oldPlayerX = img->player.x;
    double oldPlayerY = img->player.y;
    // Handle key presses
    if (keys->w)
    {
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
    if (worldMap[(int)oldPlayerX][(int)img->player.y] == 1)
    {
        // Undo the player's movement if there is a wall in the new Y position
        img->player.y = oldPlayerY;
    }

    double oldDirY = img->player.dir_y;  // Add this line
    double oldPlaneY = img->player.plane_y;
	
    if (keys->left)
    {
        // Handle rotation to the left
        double oldDirX = img->player.dir_x;
        img->player.dir_x = img->player.dir_x * cos(-ROT_SPEED) - img->player.dir_y * sin(-ROT_SPEED);
        img->player.dir_y = oldDirX * sin(-ROT_SPEED) + img->player.dir_y * cos(-ROT_SPEED);

        double oldPlaneX = img->player.plane_x;
        img->player.plane_x = img->player.plane_x * cos(-ROT_SPEED) - img->player.plane_y * sin(-ROT_SPEED);
        img->player.plane_y = oldPlaneX * sin(-ROT_SPEED) + img->player.plane_y * cos(-ROT_SPEED);
		        // Check for collisions with walls after rotation
        if (worldMap[(int)img->player.x][(int)oldPlayerY] == 1 || worldMap[(int)oldPlayerX][(int)img->player.y] == 1)
        {
            // Undo the rotation if there is a wall
            img->player.dir_x = oldDirX;
            img->player.dir_y = oldDirY;
            img->player.plane_x = oldPlaneX;
            img->player.plane_y = oldPlaneY;
        }

    }
    if (keys->right)
    {
        // Handle rotation to the right
        double oldDirX = img->player.dir_x;
        img->player.dir_x = img->player.dir_x * cos(ROT_SPEED) - img->player.dir_y * sin(ROT_SPEED);
        img->player.dir_y = oldDirX * sin(ROT_SPEED) + img->player.dir_y * cos(ROT_SPEED);

        double oldPlaneX = img->player.plane_x;
        img->player.plane_x = img->player.plane_x * cos(ROT_SPEED) - img->player.plane_y * sin(ROT_SPEED);
        img->player.plane_y = oldPlaneX * sin(ROT_SPEED) + img->player.plane_y * cos(ROT_SPEED);
		        // Check for collisions with walls after rotation
        if (worldMap[(int)img->player.x][(int)oldPlayerY] == 1 || worldMap[(int)oldPlayerX][(int)img->player.y] == 1)
        {
            // Undo the rotation if there is a wall
            img->player.dir_x = oldDirX;
            img->player.dir_y = oldDirY;
            img->player.plane_x = oldPlaneX;
            img->player.plane_y = oldPlaneY;
        }
    }

    // Continue with rendering logic
    memset(img->addr, 0, WIDTH * HEIGHT * (img->bits_per_pixel / 8));
    cast_rays(img);
    update_image(img, keys);

    return (0);
}

void render_minimap(t_data *img)
{
    int tile_size = 5;
    int scale_factor = 10;

    // Draw the game world on the minimap
    for (int i = 0; i < img->mapWidth; i++)
    {
        for (int j = 0; j < img->mapHeight; j++)
        {
            int color = (img->worldMap[i][j] == 1) ? 0xFFFFFF : 0x000000;

            for (int x = 0; x < tile_size; x++)
            {
                for (int y = 0; y < tile_size; y++)
                {
                    int pixel_x = i * tile_size * scale_factor + x * scale_factor;
                    int pixel_y = j * tile_size * scale_factor + y * scale_factor;

                    my_mlx_pixel_put(img, pixel_x, pixel_y, color);
                }
            }
        }
    }

    // Draw the player position using the loaded image
    int player_x = floor(img->player.x * scale_factor);
    int player_y = floor(img->player.y * scale_factor);

    mlx_put_image_to_window(img->mlx, img->mlx_win, img->player_img, player_x, player_y);
}

int render_frame(t_data *img)
{
    memset(img->addr, 0, WIDTH * HEIGHT * (img->bits_per_pixel / 8));

    cast_rays(img);
	
    update_image(img);
	key_hook(img);
    render_minimap(img);
	
    return (0);
}

int main()
{
    t_data img;
   //t_keys keys = {0};

    img.mlx = mlx_init();
    img.mlx_win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Raycasting Demo");
    img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
   //keys.img = &img;

	load_textures(&img);
    img.player.x = 22.0;
    img.player.y = 12;
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
    mlx_hook(img.mlx_win, 2, 1L << 0, key_press, &keys);
    mlx_hook(img.mlx_win, 3, 1L << 1, key_release, &keys);

    mlx_loop_hook(img.mlx, (void *)key_hook, &keys); // Hook the key_hook function

    mlx_loop(img.mlx);

    return (0);
}