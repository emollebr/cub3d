#include "includes/cub3d.h"

int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
        || c == 'W' || c == ' ' || c == '5' || c == '2');
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
    while (line != NULL && line[0] != '\n')
    {
        current_width = ft_strlen(line) - 1;
        if (current_width > img->mapWidth)
            img->mapWidth = current_width;
        img->mapHeight++;
        free(line);
        line = get_next_line(file);
    }
    free(line);
    img->sprites = ft_calloc(sizeof(t_sprite), 1);
    return (start_of_map);
}

int add_sprite(t_data *img, int row, int col)
{
    if (img->numSprites > 0)
    {
        img->sprites->next = ft_calloc(sizeof(t_sprite), 1);
        if (!img->sprites->next)
            return (-1);
        img->sprites = img->sprites->next;
    }
    img->numSprites++;
    img->sprites->x = col;
    img->sprites->y = row;
    img->sprites->next = NULL;
    img->worldMap[row][col] = 5;
    return (0);
}

int validate_map(t_data *img)
{
    int i;

    i = -1;
    while (++i < img->mapHeight) 
    {
        if (img->worldMap[i][0] != 1 && img->worldMap[i][0] != 3 && img->worldMap[i][img->mapWidth - 1] != 1 && img->worldMap[i][img->mapWidth - 1] != 3)
            return (ft_printf("Error:\n Map is not surrounded by walls.\n"), 0);
        if (img->worldMap[0][i] != 1 && img->worldMap[img->mapHeight - 1][i] != 1 && img->worldMap[0][i] != 3 && img->worldMap[img->mapHeight - 1][i] != 3)
            return (ft_printf("Error:\n Map is not surrounded by walls.\n"), 0);
    }
    if (!img->player.x || !img->player.y)
        return (ft_printf("Error:\n Missing player position on map.\n"), 0);
    return (1);
}