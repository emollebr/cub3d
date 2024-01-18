#include "includes/cub3d.h"

// Function to read and parse the .cub file using get_next_line
int parse_cub_file(const char *filename, t_data *img) 
{
    int             file;
    char    *start_of_map;

    file = open(filename, O_RDONLY);
    if (!file)
        return (ft_printf("Error:\n Couldn't open file: %s\n", filename), -1);
    if (parse_textures(file, img) == -1)
        return (-1);
    if (img->textures == NULL)
        return (-1);
   start_of_map =  get_map_dimensions(file, img);
   close (file);
   file = open(filename, O_RDONLY);
   if (!file)
        return (ft_printf("Error:\n Couldn't open file: %s\n", filename), -1);
    if (parse_map(file, start_of_map, img) == -1)
        return (free_all(img), -1);
    if (!validate_map(img)) {
        free_all(img);
        ft_printf("Error:\n Map is not surrounded by walls.\n");
       return (-1);
    }
    // Print the parsed map for debugging
    printf("Parsed Map:\n");
    for (int i = 0; i < img->mapHeight; i++)
    {
        for (int j = 0; j < img->mapWidth; j++)
        {
            printf("%d ", img->worldMap[i][j]);
        }
        printf("\n");
    }
    close(file);
    return 0;
}