#include "./includes/cub3d.h"

int draw_doors(t_data *img, t_door *doors, int x, t_ray *ray)
{

   // doors->isOpen = 1;
    
    if (!doors->isOpen)
    {
        int tex_num;
        double wall_x;

        if (ray->side == 0)
        {
            wall_x = img->player.y + ray->perp_wall_dist * ray->ray_dir_y;
            tex_num = 16 + doors->currentAnimationFrame;
        }
        else
        {
            wall_x = img->player.x + ray->perp_wall_dist * ray->ray_dir_x;
            tex_num = 16 + doors->currentAnimationFrame;
        }
        wall_x -= floor(wall_x);

        if (!img->textures[tex_num].addr)
            return (ft_printf("Error:\n Missing door texture\n"), -1);

        int tex_x = (int)(wall_x * (double)img->textures[tex_num].width);
        if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
            tex_x = img->textures[tex_num].width - tex_x - 1;

        for (int y = ray->draw_start; y < ray->draw_end; y++)
        {
            int tex_y = (((y * 256 - HEIGHT * 128 + ray->line_height * 128) * img->textures[tex_num].height) / ray->line_height) / 256;
            int color = *(unsigned int *)(img->textures[tex_num].addr + (tex_y * img->textures[tex_num].line_length + tex_x * (img->textures[tex_num].bits_per_pixel / 8)));

            if (color != (int)0xFF000000)
            {
            color = darken_color(color, ray->perp_wall_dist);
            my_mlx_pixel_put(img, x, y, color);
            }
        }
        if(doors->animationspeed > 0)
            doors->animationspeed--;
        if(doors->animationspeed == 0 && doors->currentAnimationFrame > 0)
        {
            doors->currentAnimationFrame--;
            doors->animationspeed = 4000;
        }
        doors->open_ = false;
        }
        else if (doors->isOpen)
        {
            int tex_num;
            double wall_x;
            if (ray->side == 0)
            {
                wall_x = img->player.y + ray->perp_wall_dist * ray->ray_dir_y;
                tex_num = 16 + doors->currentAnimationFrame;
            }
            else
            {
                wall_x = img->player.x + ray->perp_wall_dist * ray->ray_dir_x;
                tex_num = 16 + doors->currentAnimationFrame;
            }
            wall_x -= floor(wall_x);

            if (!img->textures[tex_num].addr)
                return (ft_printf("Error:\n Missing door texture\n"), -1);

            int tex_x = (int)(wall_x * (double)img->textures[tex_num].width);
            if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
                tex_x = img->textures[tex_num].width - tex_x - 1;

            for (int y = ray->draw_start; y < ray->draw_end; y++)
            {
                int tex_y = (((y * 256 - HEIGHT * 128 + ray->line_height * 128) * img->textures[tex_num].height) / ray->line_height) / 256;
                int color = *(unsigned int *)(img->textures[tex_num].addr + (tex_y * img->textures[tex_num].line_length + tex_x * (img->textures[tex_num].bits_per_pixel / 8)));

            if (color != (int)0xFF000000)
                {
                color = darken_color(color, ray->perp_wall_dist);

                my_mlx_pixel_put(img, x, y, color);
                }
            }
            if (doors->animationspeed > 0)
                doors->animationspeed--;
            if (doors->animationspeed == 0 &&  !doors->open_)
            {
                doors->animationspeed = 3000;
                doors->currentAnimationFrame = (doors->currentAnimationFrame + 1) % 6;
            }
            if (doors->currentAnimationFrame == 5)
                doors->open_ = true;
    }
    return (0);
}

int cast_rays_doors(t_data *img)
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
        while (ray.hit == 0 && ray.map_x > 0 && ray.map_y > 0)
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
            if (img->worldMap[ray.map_y][ray.map_x] == 2)
                ray.hit = 2;
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
        if (ray.hit == 2)
        if (draw_doors(img, &img->doors, x, &ray) == -1)
            return (-1);
        ray.hit = 0;
        img->z_buffer[x] = ray.perp_wall_dist;
        x++;
  
    }
    return (0);
}