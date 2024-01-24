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

int darken_color(int color, double distance)
{
    // Extract color channels (assuming 32-bit color with 8 bits per channel)
    int red = (color >> 16) & 0xFF;
    int green = (color >> 8) & 0xFF;
    int blue = color & 0xFF;

    // Darken the color based on the distance (you can customize this logic)
    int darken_factor = (int)(distance * 10);  // Adjust the multiplier based on your preference
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

// Define the apply_light function
t_color apply_light(t_color color, double distance) {
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
    for (int i = 0; i < 6; i++)
    {
        if (img->textures[i].rgb == 0) {
            img->textures[i].img = mlx_xpm_file_to_image(img->mlx, img->textures[i].path, &img->textures[i].width, &img->textures[i].height);
            img->textures[i].addr = mlx_get_data_addr(img->textures[i].img, &img->textures[i].bits_per_pixel, &img->textures[i].line_length, &img->textures[i].endian);
        }
    }
    img->textures[l_MMBG].addr = NULL;
    img->textures[l_MMVA].addr = NULL;
    if (access("./images/11.xpm", O_RDONLY) == 0) {
        img->textures[l_MMBG].img = mlx_xpm_file_to_image(img->mlx, "./images/11.xpm", &img->textures[l_MMBG].width, &img->textures[l_MMBG].height);
        img->textures[l_MMBG].addr = mlx_get_data_addr(img->textures[l_MMBG].img, &img->textures[l_MMBG].bits_per_pixel, &img->textures[l_MMBG].line_length, &img->textures[l_MMBG].endian);
    }
    if (access("./images/4.xpm", O_RDONLY) == 0) {
        img->textures[l_MMVA].img = mlx_xpm_file_to_image(img->mlx, "./images/4.xpm", &img->textures[l_MMVA].width, &img->textures[l_MMVA].height);
        img->textures[l_MMVA].addr = mlx_get_data_addr(img->textures[l_MMVA].img, &img->textures[l_MMVA].bits_per_pixel, &img->textures[l_MMVA].line_length, &img->textures[l_MMVA].endian);
    }
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
    for (int i = 8; i < 22; i++)
    {
        if (access(img->textures[i].path, O_RDONLY) == 0) {
            ft_printf("loading %s\n", img->textures[i].path);
            img->textures[i].img = mlx_xpm_file_to_image(img->mlx, img->textures[i].path, &img->textures[i].width, &img->textures[i].height);
            img->textures[i].addr = mlx_get_data_addr(img->textures[i].img, &img->textures[i].bits_per_pixel, &img->textures[i].line_length, &img->textures[i].endian);
        }
    }
}

int get_texture_color(t_texture texture, int x, int y)
{
    return *(unsigned int *)(texture.addr + (y * texture.line_length + x * (texture.bits_per_pixel / 8)));
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

    unsigned int tex_x = (int)(wall_x * img->textures[tex_num].width);
    if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
        tex_x = img->textures[tex_num].width - tex_x - 1;

    for (int y = ray->draw_start; y < ray->draw_end; y++)
    {
        unsigned int tex_y = (((y * 256 - HEIGHT * 128 + ray->line_height * 128) * img->textures[tex_num].height) / ray->line_height) / 256;
        tex_y = fmin(fmax(tex_y, 0), img->textures[tex_num].height - 1);
        unsigned int color = get_texture_color(img->textures[tex_num], (int)tex_x, (int)tex_y);
        color = darken_color(color, ray->perp_wall_dist);
        my_mlx_pixel_put(img, x, y, color);
    }
}

void draw_textured_floor(t_data *img, int x)
{
   int floor_color;
    int ceil_color;

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

        int tex_width = img->textures[l_F].width;
        int tex_height = img->textures[l_F].height;

        int ceil_tex_width = img->textures[l_C].width;
        int ceil_tex_height = img->textures[l_C].height;

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
            if (img->textures[l_F].rgb != 0)
                floor_color = img->textures[l_F].rgb;
            else
                floor_color = get_texture_color(img->textures[l_F], tx, ty);
            if (img->textures[l_C].rgb != 0)
                ceil_color = img->textures[l_C].rgb;
            else
                ceil_color = get_texture_color(img->textures[l_C], ceil_tx, ceil_ty);
			
			floor_color = darken_color(floor_color,	(double)row_distance);
			ceil_color = darken_color(ceil_color,	(double)row_distance);

            my_mlx_pixel_put(img, x, y, floor_color);
            my_mlx_pixel_put(img, x, HEIGHT - y - 1, ceil_color);
        }
    }
}

int cast_rays(t_data *img)
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

            if (img->worldMap[ray.map_y][ray.map_x] == 1)
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
        img->z_buffer[x] = ray.perp_wall_dist;
        x++;
    }
    if (img->doors.door_bool == 1) {
        if (cast_rays_doors(img) == -1)
            return (-1);
    }
    if (img->sprites) {
        if (draw_sprites(img) == -1)
            return (-1);
    }
    return (0);
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
     if (keycode == 32) // Space key
    {
        // Toggle mouse mode
        keys->space = !keys->space;
        keys->img->doors.isOpen = !keys->img->doors.isOpen;

        if (keys->space)
        {
            // Hide the mouse cursor
            mlx_mouse_hide(keys->img->mlx, keys->img->mlx_win);
            // Reset the mouse position to the center of the screen
            mlx_mouse_move(keys->img->mlx, keys->img->mlx_win, WIDTH / 2, HEIGHT / 2);
        }
        else
        {
            // Show the mouse cursor
            mlx_mouse_show(keys->img->mlx, keys->img->mlx_win);
        }
    }
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
    if (img->worldMap[(int)oldPlayerY][(int)img->player.x] == 1)
    {
        // Undo the player's movement if there is a wall in the new X position
        img->player.x = oldPlayerX;
    }
    if (img->worldMap[(int)img->player.y][(int)oldPlayerX] == 1)
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
        if (img->worldMap[(int)oldPlayerY][(int)img->player.x] == 1 || img->worldMap[(int)img->player.y][(int)oldPlayerX] == 1)
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
        if (img->worldMap[(int)oldPlayerY][(int)img->player.x] == 1 || img->worldMap[(int)img->player.y][(int)oldPlayerX] == 1)
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
    if (cast_rays(img) == -1)
        return (free_all(img), -1);
    update_image(img, keys);
    return (0);
}

int mouse_motion(int x, int y, t_keys *keys)
{
    t_data *img = keys->img;

    if (y != -1 && keys->space)
    {
        // Calculate the change in mouse x-coordinate relative to the center of the screen
        int dx = x - WIDTH / 2;

        // Adjust rotation speed based on the change in mouse position
        double rotation_speed = 0.0002 * dx;

        // Update the player's view direction and plane direction
        double oldDirX = img->player.dir_x;
        img->player.dir_x = img->player.dir_x * cos(rotation_speed) - img->player.dir_y * sin(rotation_speed);
        img->player.dir_y = oldDirX * sin(rotation_speed) + img->player.dir_y * cos(rotation_speed);

        double oldPlaneX = img->player.plane_x;
        img->player.plane_x = img->player.plane_x * cos(rotation_speed) - img->player.plane_y * sin(rotation_speed);
        img->player.plane_y = oldPlaneX * sin(rotation_speed) + img->player.plane_y * cos(rotation_speed);

        // Reset the mouse position to the center of the screen
        mlx_mouse_move(keys->img->mlx, keys->img->mlx_win, WIDTH / 2, HEIGHT / 2);
    }

    return (0);
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

    if (argc != 2)
        return (ft_printf("Enter .cub file as argument\n"), -1);
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