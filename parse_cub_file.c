#include "includes/cub3d.h"

// Function to read and parse the .cub file using get_next_line
int parse_cub_file(const char *filename, t_data *img) 
{
    int             file;
    char    *start_of_map;

    file = open(filename, O_RDONLY);
    if (!file)
        return (ft_printf("Error opening file: %s\n", filename), -1);
    parse_textures(file, img);
    if (img->textures == NULL)
        return (-1);
   start_of_map =  get_map_dimensions(file, img);
   close (file);
   file = open(filename, O_RDONLY);
   if (!file)
        return (ft_printf("Error opening file: %s\n", filename), -1);
    parse_map(file, start_of_map, img);
    close(file);
    return 0;
}