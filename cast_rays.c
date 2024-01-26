#include "./includes/cub3d.h"

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
    if (img->sprites != NULL) {
        if (draw_sprites(img) == -1)
            return (-1);
    }
    return (0);
}