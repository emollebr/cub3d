#include "includes/cub3d.h"

int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

char    *get_map_dimensions(int file, t_data *img)
{
    char    *start_of_map;
    char    *line;
    int     current_width;

    img->mapWidth = 0;
   img->mapHeight = 1;
    line = get_next_line(file);
    while (line[0] == '\n')
    {
        free(line);
        line = get_next_line(file);
    }
    start_of_map = get_next_line(file);
    while (line != NULL)
    {
        current_width = ft_strlen(line) - 1;
        if (current_width > img->mapWidth)
            img->mapWidth = current_width;
        img->mapHeight++;
        free(line);
        line = get_next_line(file);
    }
    free(line);
    return (start_of_map);
}

int validate_map(t_data *img)
{
    int i;

    i = -1;
    while (++i < img->mapHeight) 
    {
        if (img->worldMap[i][0] != 1 && img->worldMap[i][0] != 3 && img->worldMap[i][img->mapWidth - 1] != 1 && img->worldMap[i][img->mapWidth - 1] != 3)
            return (0);
        if (img->worldMap[0][i] != 1 && img->worldMap[img->mapHeight - 1][i] != 1 && img->worldMap[0][i] != 3 && img->worldMap[img->mapHeight - 1][i] != 3)
           return (0); 
    }
    return 1;
}