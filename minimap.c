
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
// void    draw_visible_area(t_data *img)
// {
//     // int original_x;
//     // int original_y;
//     int cell_x;
//     int cell_y;
//     int color = 0x1eff33;

//     ft_printf("draw minimap area\n");
//     for (int y = 0; y < img->minimap.visible_height; ++y)
//     {
//         for (int x = 0; x < img->minimap.visible_width; ++x)
//         {
//             cell_x = img->minimap.x + (int)(x * (double)180 / img->minimap.visible_width);
//             cell_y = img->minimap.y + (int)(y * (double)180 / img->minimap.visible_height);

//             if (img->worldMap[img->minimap.visible_y + y][img->minimap.visible_x + x] == 1)
//             {
//                 for (int i = 0; i < 180 / img->minimap.visible_width; ++i)
//                 {
//                     for (int j = 0; j < 180 / img->minimap.visible_height; ++j)
//                     {
//                         // original_x = (i * img->minimap.walls.width) / (180 / img->minimap.visible_width);
//                         // original_y = (j * img->minimap.walls.height) / (180 / img->minimap.visible_height);
//                         // color = *(unsigned int *)(img->textures[0].addr + original_y * img->textures[0].line_length + original_x * (img->textures[0].bits_per_pixel / 8));
//                         my_mlx_pixel_put(img, cell_x + i, cell_y + j, color);
//                     }
//                 }
//             }
//         }
//     }
// }

// void    calculate_visible_area(t_data *img)
// {
//     img->minimap.visible_width = 10;
//     img->minimap.visible_height = 10;
//     img->minimap.visible_x = img->player.x - img->minimap.visible_width / 2;
//     img->minimap.visible_y = img->player.y - img->minimap.visible_height / 2;
//     if (img->minimap.visible_x < 0) 
//         img->minimap.visible_x = 0;
//     if (img->minimap.visible_y < 0)
//         img->minimap.visible_y = 0;
//     if (img->minimap.visible_x + img->minimap.visible_width > img->mapWidth)
//         img->minimap.visible_x = img->mapWidth - img->minimap.visible_width;
//     if (img->minimap.visible_y + img->minimap.visible_height > img->mapHeight)
//         img->minimap.visible_y = img->mapHeight - img->minimap.visible_height;
// }

// void    draw_background(t_data *img)
// {
//     // int original_y;
//     // int original_x;
//     int color = 0x000000;

//     ft_printf("draw minimap background\n");
//     for (int y = img->minimap.y; y < img->minimap.y + 180; ++y)
//     {
//         for (int x = img->minimap.x; x < img->minimap.x + 180; ++x)
//         {
//             // original_y = (y - img->minimap.y) * img->minimap.background.height / 180;
//             // original_x = (x - img->minimap.x) * img->minimap.background.width / 180;
//             // color = *(unsigned int *)(img->minimap.background.addr + original_y * img->minimap.background.line_length + original_x * (img->minimap.background.bits_per_pixel / 8));
//             my_mlx_pixel_put(img, x, y, color);
//         }
//     }
// }

// void    draw_player(t_data *img) 
// {
//     int player_minimap_x;
//     int player_minimap_y;

//     player_minimap_x = img->minimap.x + (int)((img->player.x - img->minimap.visible_x) * (double)180 / img->minimap.visible_width);
//     player_minimap_y = img->minimap.y + (int)((img->player.y - img->minimap.visible_y) * (double)180 / img->minimap.visible_height);
//     for (int y = player_minimap_y - 2; y <= player_minimap_y + 2; ++y)
//     {
//         for (int x = player_minimap_x - 2; x <= player_minimap_x + 2; ++x)
//         {
//             my_mlx_pixel_put(img, x, y, 0x1e0d0d); // color for the player
//         }
//     }
// }

// void render_minimap(t_data *img)
// {
//     img->minimap.x = 36;
//     img->minimap.y = HEIGHT - 185;
//     img->minimap.walls.img = mlx_xpm_file_to_image(img->mlx,  "./images/4.xpm", &img->minimap.walls.width, &img->minimap.walls.height);
//     img->minimap.walls.addr = mlx_get_data_addr(img->minimap.walls.img, &img->minimap.walls.bits_per_pixel, &img->minimap.walls.line_length, &img->minimap.walls.endian);
//     img->minimap.background.img = mlx_xpm_file_to_image(img->mlx,  "./images/4.xpm", &img->minimap.background.width, &img->minimap.background.height);
//     img->minimap.background.addr = mlx_get_data_addr(img->minimap.background.img, &img->minimap.background.bits_per_pixel, &img->minimap.background.line_length, &img->minimap.background.endian);
//     calculate_visible_area(img);
//     //draw_background(img, &img->minimap);
//     draw_player(img);
//     draw_visible_area(img);
// }
