#include "./includes/cub3d.h"

void draw_overlay_image(t_data *img, void *overlay_img, int overlay_width, int overlay_height, int x_offset, int y_offset)
{
    int x, y;
    int *overlay_data = (int *)mlx_get_data_addr(overlay_img, &img->bits_per_pixel, &img->line_length, &img->endian);

    for (y = 0; y < overlay_height; ++y)
    {
        for (x = 0; x < overlay_width; ++x)
        {
            int color = overlay_data[y * overlay_width + x];
            if ((color & 0x00FFFFFF) != 0) // Check if the pixel is not fully transparent
            {
                int img_x = x + x_offset;
                int img_y = y + y_offset;
                my_mlx_pixel_put(img, img_x, img_y, color);
            }
        }
    }
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

    // Check if player.x is even or odd
    if (keys->w || keys->s)
        overlay_img2 = mlx_xpm_file_to_image(img->mlx, relative_path3, &img_width, &img_height);
    else if (keys->a)
        overlay_img2 = mlx_xpm_file_to_image(img->mlx, relative_path_left, &img_width, &img_height);
    else if (keys->d)
        overlay_img2 = mlx_xpm_file_to_image(img->mlx, relative_path_right, &img_width, &img_height);
    else
        overlay_img2 = mlx_xpm_file_to_image(img->mlx, relative_path2, &img_width, &img_height);

    void *overlay_img = mlx_xpm_file_to_image(img->mlx, relative_path, &img_width, &img_height);

    img->player.old_player_x = img->player.x;
    img->player.old_player_y = img->player.y;


    if (overlay_img != NULL && overlay_img2 != NULL)
    {
        // Update the window
        mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
        // Draw overlay images onto the window
        draw_overlay_image(img, overlay_img2, img_width, img_height, 0, 0);
        draw_overlay_image(img, overlay_img, img_width, img_height, 0, 0);
        render_minimap(img);
        mlx_do_sync(img->mlx);
       mlx_destroy_image(img->mlx, overlay_img2);
        mlx_destroy_image(img->mlx, overlay_img);
    }
    else
    {
        // Handle error, e.g., print an error message or exit the program
        fprintf(stderr, "Error loading overlay image.\n");
        free_all(img);
        exit(EXIT_FAILURE);
    }
}