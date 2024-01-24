#include "./includes/cub3d.h"

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