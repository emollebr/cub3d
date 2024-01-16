
#include "includes/cub3d.h"

void render_minimap(t_data *img)
{
    int minimap_size = 180; // Set the size of the minimap square
    int minimap_x = 36; // Adjust the X position
    int minimap_y = HEIGHT - minimap_size - 3; // Adjust the Y position

  // Calculate the visible area around the player
    int visible_width = 10; // Adjust the visible width
    int visible_height = 10; // Adjust the visible height
    int visible_x = img->player.x - visible_width / 2;
    int visible_y = img->player.y - visible_height / 2;

    // Ensure the visible area is within the bounds of the map
    if (visible_x < 0) visible_x = 0;
    if (visible_y < 0) visible_y = 0;
    if (visible_x + visible_width > img->mapWidth) visible_x = img->mapWidth - visible_width;
    if (visible_y + visible_height > img->mapHeight) visible_y = img->mapHeight - visible_height;

    // Draw the minimap background
    for (int y = minimap_y; y < minimap_y + minimap_size; ++y)
    {
        for (int x = minimap_x; x < minimap_x + minimap_size; ++x)
        {
            my_mlx_pixel_put(img, x, y, 0xcfe2f3); // color for the minimap background
        }
    }
    // Calculate the player's position on the minimap
    int player_minimap_x = minimap_x + (int)((img->player.x - visible_x) * (double)minimap_size / visible_width);
    int player_minimap_y = minimap_y + (int)((img->player.y - visible_y) * (double)minimap_size / visible_height);

    // Draw the player on the minimap
    for (int y = player_minimap_y - 2; y <= player_minimap_y + 2; ++y)
    {
        for (int x = player_minimap_x - 2; x <= player_minimap_x + 2; ++x)
        {
            my_mlx_pixel_put(img, x, y, 0x1e0d0d); // color for the player on the minimacfe2f3p
        }
    }

    // Draw the visible area on the minimap
    for (int y = 0; y < visible_height; ++y)
    {
        for (int x = 0; x < visible_width; ++x)
        {
            int cell_x = minimap_x + (int)(x * (double)minimap_size / visible_width);
            int cell_y = minimap_y + (int)(y * (double)minimap_size / visible_height);

            if (img->worldMap[visible_y + y][visible_x + x] == 1)
            {
                // Draw a filled rectangle for walls in the visible area on the minimap
                for (int i = 0; i < minimap_size / visible_width; ++i)
                {
                    for (int j = 0; j < minimap_size / visible_height; ++j)
                    {
                        my_mlx_pixel_put(img, cell_x + i, cell_y + j, 0xf1c232); //  for walls on the minimap
                    }
                }
            }
        }
    }
}
