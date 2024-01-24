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