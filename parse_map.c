#include "includes/cub3d.h"

void    parse_player_pos(t_data *img, char dir, int row, int col)
{
    img->worldMap[row][col] = 0;
    img->player.x = col;
    img->player.y = row;
    if (dir == 'N')
    {
        img->player.dir_x = 0.0;
        img->player.dir_y = -1.0;
        img->player.plane_x = 0.66;
        img->player.plane_y = 0.0;
    }
    if (dir == 'S')
    {
        img->player.dir_x = 0.0;
        img->player.dir_y = 1.0;
        img->player.plane_x = -0.66;
        img->player.plane_y = 0.0;
    }
    if (dir == 'E')
    {
        img->player.dir_x = 1.0;
        img->player.dir_y = 0.0;
        img->player.plane_x = 0.0;
        img->player.plane_y = 0.66;
    }
    if (dir == 'W')
    {
        img->player.dir_x = -1.0;
        img->player.dir_y = 0.0;
        img->player.plane_x = 0.0;
        img->player.plane_y = -0.66;
    }
    return ;
}

char    *allocate_map(int file, char *start_of_map, t_data *img)
{
    char *line;
    int i;

    i = -1;
    img->worldMap = ft_calloc(sizeof(int *), img->mapHeight);
    while (++i < img->mapHeight)
        img->worldMap[i] = ft_calloc(sizeof(int), img->mapWidth);
    line = get_next_line(file);
    while (ft_strncmp(start_of_map, line, ft_strlen(line) != 0)) {
        free(line);
        line = get_next_line(file);
    }
    free(start_of_map);
    return (line);
}

int check_map_rules(char *line, int row, int col, t_data *img)
{
    char   c;

    c = line[col];
    if (!is_valid_map_char(c)) {
        ft_printf("Error: Invalid character '%c' in the map.", c);
        return (-1);
    }
     if (row == 0 || row == img->mapHeight - 1) {
            if (c != '1' && c != ' ') {
                ft_printf("Error: Invalid character '%c' in the first or last row.\n", c);
            return (-1);
            }
    } else {
        if (col == 0 || col == img->mapWidth - 1) {
            if (c != '1') {
                ft_printf("Error: Invalid character '%c' in the first or last column.\n", c);
                return (-1);
            }
        } else {
            if (c == ' ' && line[col - 1] != ' ' && line[col - 1] != '1' && line[col + 1] != '1' && line[col + 1] != ' ') {
                ft_printf("Error: Invalid character '%c' at row %d, column %d.\n", c, row, col);
                return (-1);
            }
        }
    }
    return (1);
}

int check_more_map_rules(char *line, int row, int col, int prevRowLength)
{
    char   c;

    c = line[col];
    if (row > 0 && (int)ft_strlen(line) > prevRowLength && col >= prevRowLength) {
        if (c != '1') {
            ft_printf("Error: Invalid character '%c' at row %d, column %d.\n", c, row, col);
            return (-1);
        }
    }
    return (1);
}

int assign_character_to_map(t_data *img, char c, int row, int col)
{
    if (c == ' ' || c == '\n')
        img->worldMap[row][col] = 3;
    else if (ft_isalpha(c))
        parse_player_pos(img, c, row, col);
    else if (c == '5')
    {
        if (img->numSprites == 0)
            img->sprite_head = img->sprites;
        add_sprite(img, row, col);
    }
    else
        img->worldMap[row][col] = c - 48;
    if (c == '2' && img->doors.door_bool == 0)
        img->doors.door_bool = 1;
    return (0);
}

int parse_loop(t_data *img, char *line, int row, int prevRowLength)
{
    int col;

    col = 0;
    while (line[col] == ' ')
    {
        img->worldMap[row][col] = 3;
        col++;
    }
    while (col < img->mapWidth && line[col] != 10)
    {
        if (!check_map_rules(line, row, col, img) || !check_more_map_rules(line, row, col, prevRowLength))
            return (-1);
        assign_character_to_map(img, line[col], row, col);
        col++;
    }
    while (col < img->mapWidth && row < img->mapHeight)
    {
        img->worldMap[row][col] = 3;
        col++;
    }
    return (0);
}

int    parse_map(int file, char *start_of_map, t_data *img) 
{
    int         row;
    int         prevRowLength;
    char        *line;

    line = allocate_map(file, start_of_map, img);
    row = 0;
    prevRowLength = 0;
    while (line != NULL)
    {
        if (parse_loop(img, line, row, prevRowLength) == -1)
            return (-1);
        prevRowLength = ft_strlen(line);
        row++;
        free(line);
        line = get_next_line(file);
    }
    free(line);
    if (img->numSprites == 0)
    {
        free(img->sprites);
        img->sprites = NULL;
    }
    img->sprites = img->sprite_head;
    return (0);
}