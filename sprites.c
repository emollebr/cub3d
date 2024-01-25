#include "includes/cub3d.h"


// Function to compare the distances between two sprites for sorting
int compare_sprite_distance(const void *a, const void *b)
{
    double distance_a = ((t_sprite_info *)a)->distance;
    double distance_b = ((t_sprite_info *)b)->distance;

    if (distance_a < distance_b)
        return 1;
    else if (distance_a > distance_b)
        return -1;
    else
        return 0;
}

double calculate_sprite_screen_size(double sprite_x, double sprite_y, double player_x, double player_y, double dir_x, double dir_y, double plane_x, double plane_y)
{
    double sprite_screen_x = sprite_x - player_x;
    double sprite_screen_y = sprite_y - player_y;

    double inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);

   // double transform_x = inv_det * (dir_y * sprite_screen_x - dir_x * sprite_screen_y);
    double transform_y = inv_det * (-plane_y * sprite_screen_x + plane_x * sprite_screen_y);

    int sprite_screen_size = abs((int)(HEIGHT / transform_y));

    return sprite_screen_size;
}

int draw_sprites(t_data *img)
{
    t_sprite sprites[img->numSprites];
    t_sprite_info sprite_info[img->numSprites];
    int spriteOrder[img->numSprites];
    double spriteDistance[img->numSprites];

    // Assuming you have an array of sprites named 'sprites' and each sprite has x, y, and texture_index
    for (int i = 0; i < img->numSprites; i++)
    {
        sprites[i].texture_index = 6 + img->currentAnimationFrame; // Adjust the starting Y position of the first sprite
        if (!img->textures[sprites[i].texture_index].addr)
            return (ft_printf("Error:\n Missing sprite texture\n"), -1);
        spriteOrder[i] = i;
        sprites[i].x = img->sprites->x;
        sprites[i].y = img->sprites->y;
        spriteDistance[i] = ((img->player.x - sprites[i].x) * (img->player.x - sprites[i].x) + (img->player.y - sprites[i].y) * (img->player.y - sprites[i].y));
        sprite_info[i].sprite_index = i;
        img->sprites = img->sprites->next;
    }
    img->sprites = img->sprite_head;

 // Sort the sprites based on distance
    qsort(sprite_info, img->numSprites, sizeof(t_sprite_info), compare_sprite_distance);

    // Now, iterate through the sorted sprites and draw them
    for (int i = 0; i < img->numSprites; i++)
    {
        double spriteX = sprites[spriteOrder[i]].x - img->player.x;
        double spriteY = sprites[spriteOrder[i]].y - img->player.y;

        t_sprite *sprite = &sprites[spriteOrder[i]];

        double invDet = 1.0 / (img->player.plane_x * img->player.dir_y - img->player.dir_x * img->player.plane_y); //required for correct matrix multiplication

        double transformX = invDet * (img->player.dir_y * spriteX - img->player.dir_x * spriteY);
        double transformY = invDet * (-img->player.plane_y * spriteX + img->player.plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

        int spriteScreenX = (int)((WIDTH / 2) * (1 + transformX / transformY));

        // Calculate height of the sprite on screen
        int spriteHeight = abs((int)(HEIGHT / transformY));
        // Calculate width of the sprite
        int spriteWidth = abs((int)(WIDTH / transformY));

        int drawStartY = -spriteHeight / 2 + HEIGHT / 2;
        if (drawStartY < 0)
            drawStartY = 0;
        int drawEndY = spriteHeight / 2 + HEIGHT / 2;
        if (drawEndY >= HEIGHT)
            drawEndY = HEIGHT - 1;

        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if (drawStartX < 0)
            drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if (drawEndX > WIDTH)
            drawEndX = WIDTH;

        for (int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            // Calculate the texture coordinates using spritePixelX
            int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * img->textures[sprite->texture_index].width / spriteWidth) / 256;
            

            // Check if the sprite pixel is not fully transparent
            if (transformY > 0 && transformY < img->z_buffer[stripe])
            {
                
                for (int y = drawStartY; y < drawEndY; y++) // For every pixel of the current stripe
                {
                    int d = (y-MOV_SPEED) * 256 - HEIGHT * 128 + spriteHeight * 128;  //256 and 128 factors to avoid floats
                    int texY = ((d * img->textures[sprite->texture_index].height) / spriteHeight) / 256;
                    int color = get_texture_color(img->textures[sprite->texture_index], texX, texY);

                    if (color != (int)0xFF000000)
                    {
                        // Darken the color for perspective
                        color = darken_color(color, spriteDistance[i] / 6);

                        // Draw the sprite pixel
                        my_mlx_pixel_put(img, stripe, y, color);
                    }
                }
            }
        }
    }
    img->animationspeed--;
    if (img->animationspeed == 0)
    {
    img->currentAnimationFrame = (img->currentAnimationFrame + 1) % 6;
    img->animationspeed = 6;
    }
    return (0);
}