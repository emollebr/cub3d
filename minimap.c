
#include "includes/cub3d.h"

void    draw_visible_area(t_data *img, t_minimap *minimap)
{
    int color;
    int original_x;
    int original_y;

    for (int y = 0; y < minimap->visible_height; ++y)
    {
        for (int x = 0; x < minimap->visible_width; ++x)
        {
            int cell_x = minimap->x + (int)(x * (double)180 / minimap->visible_width);
            int cell_y = minimap->y + (int)(y * (double)180 / minimap->visible_height);

            if (img->worldMap[minimap->visible_y + y][minimap->visible_x + x] == 1)
            {
                for (int i = 0; i < 180 / minimap->visible_width; ++i)
                {
                    for (int j = 0; j < 180 / minimap->visible_height; ++j)
                    {
                        original_x = (i * img->textures[l_MMVA].width) / (180 / minimap->visible_width);
                        original_y = (j * img->textures[l_MMVA].height) / (180 / minimap->visible_height);
                        if (!img->textures[l_MMVA].addr)
                            color = 0x9e1c1c;
                        else
                            color = *(unsigned int *)(img->textures[l_MMVA].addr + original_y * img->textures[l_MMVA].line_length + original_x * (img->textures[l_MMVA].bits_per_pixel / 8));
                        my_mlx_pixel_put(img, cell_x + i, cell_y + j, color);
                    }
                }
            }
        }
    }
}

void    calculate_visible_area(t_data *img, t_minimap *minimap) {
    minimap->visible_width = 10; // Adjust the visible width
    minimap->visible_height = 10; // Adjust the visible height
    minimap->visible_x = img->player.x - minimap->visible_width / 2;
    minimap->visible_y = img->player.y - minimap->visible_height / 2;
    if (minimap->visible_x < 0) minimap->visible_x = 0;
    if (minimap->visible_y < 0) minimap->visible_y = 0;
    if (minimap->visible_x + minimap->visible_width > img->mapWidth) minimap->visible_x = img->mapWidth - minimap->visible_width;
    if (minimap->visible_y + minimap->visible_height > img->mapHeight) minimap->visible_y = img->mapHeight - minimap->visible_height;
}

void    draw_background(t_data *img, t_minimap *minimap) {
    int original_y;
    int original_x;
     unsigned int color;

    for (int y = minimap->y; y < minimap->y + 180; ++y)
    {
        original_y = (y - minimap->y) * img->textures[l_MMBG].height / 180;
        for (int x = minimap->x; x < minimap->x + 180; ++x)
        {
            original_x = (x - minimap->x) * img->textures[l_MMBG].width / 180;
            if (!img->textures[l_MMBG].addr)
                            color = 0xebe7c5;
            else
                color = *(unsigned int *)(img->textures[l_MMBG].addr + original_y * img->textures[l_MMBG].line_length + original_x * (img->textures[l_MMBG].bits_per_pixel / 8));
            my_mlx_pixel_put(img, x, y, color); // color for the minimap background
        }
    }
}

void    draw_player(t_data *img, t_minimap *minimap) 
{
    int player_minimap_x;
    int player_minimap_y;

    player_minimap_x = minimap->x + (int)((img->player.x - minimap->visible_x) * (double)180 / minimap->visible_width);
    player_minimap_y = minimap->y + (int)((img->player.y - minimap->visible_y) * (double)180 / minimap->visible_height);
    for (int y = player_minimap_y - 2; y <= player_minimap_y + 2; ++y)
    {
        for (int x = player_minimap_x - 2; x <= player_minimap_x + 2; ++x)
        {
            my_mlx_pixel_put(img, x, y, 0xff0000); // color for the player
        }
    }
}

void render_minimap(t_data *img)
{
    t_minimap   minimap;

    minimap.x = 36; // Adjust the X position
    minimap.y = HEIGHT - 185; // Adjust the Y position
    calculate_visible_area(img, &minimap);
    draw_background(img, &minimap);
    draw_player(img, &minimap);
    draw_visible_area(img, &minimap);
}