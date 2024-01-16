#include "includes/cub3d.h"

void    parse_player_pos(t_data *img, char dir, int row, int col)
{
    img->worldMap[row][col] = 0;
    img->player.x = col;
    img->player.y = row;
    if (dir == 'N') {
        img->player.dir_x = 0.0;
        img->player.dir_y = -1.0;
    }
    if (dir == 'S') {
        img->player.dir_x = 0.0;
        img->player.dir_y = 1.0;
    }
    if (dir == 'E'){
        img->player.dir_x = 1.0;
        img->player.dir_y = 0.0;
    }
    if (dir == 'W') {
        img->player.dir_x = -1.0;
        img->player.dir_y = 0.0;
    }
    return ;
}

char    *allocate_map(int file, char *start_of_map, t_data *img) {
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

// Function to parse and validate the map from a file
int    parse_map(int file, char *start_of_map, t_data *img) 
{
    char *line;
    int row;
    int col;
    int prevRowLength;

    line = allocate_map(file, start_of_map, img);
    // Read and parse the map
    row = 0;
    prevRowLength = 0;
    while (line != NULL) {
        if (row >= img->mapHeight) {
            ft_printf("Error: Map size exceeds allowed height.\n");
            return (-1);
        }

        // Ignore leading whitespaces
        col = 0;
        while (line[col] == ' ') {
            img->worldMap[row][col] = 3;
            col++;
        }

        // Validate each character in the row
        while (col < img->mapWidth && line[col] != 10) {
            char c = line[col];

            // Check for valid characters
            if (!is_valid_map_char(c)) {
                ft_printf("Error: Invalid character '%c' in the map.", c);
                return (-1);
            }

            // Validate based on the specified rules
            if (row == 0 || row == img->mapHeight - 1) {
                // If the current row is the 0th row or the final row, only accept '1's and ' 's.
                if (c != '1' && c != ' ') {
                    ft_printf("Error: Invalid character '%c' in the first or last row.\n", c);
                   return (-1);
                }
            } else {
                // The first and final character should always be a '1'.
                if (col == 0 || col == img->mapWidth - 1) {
                    if (c != '1') {
                        ft_printf("Error: Invalid character '%c' in the first or last column.\n", c);
                        return (-1);
                    }
                } else {
                    // In the case of any non-leading whitespaces, adjacent characters should be '1's or ' 's.
                    if (c == ' ' && line[col - 1] != ' ' && line[col - 1] != '1' && line[col + 1] != '1' && line[col + 1] != ' ') {
                       ft_printf("Error: Invalid character '%c' at row %d, column %d.", c, row, col);
                        return (-1);
                    }
                }
            }

            // If strlen(curr_row) > strlen(row_on_top) && current col > strlen(row_on_top), current character should be '1'
            if (row > 0 && (int)ft_strlen(line) > prevRowLength && col >= prevRowLength) {
                if (c != '1') {
                    ft_printf("Error: Invalid character '%c' at row %d, column %d.\n", c, row, col);
                    return (-1);
                }
            }

            // Assign the character to the worldMap
            if (c == ' ' || c == '\n')
                img->worldMap[row][col] = 3;
            else if (ft_isalpha(c))
                parse_player_pos(img, c, row, col);
            else
                img->worldMap[row][col] = c - 48;
            col++;
        }
        while (col < img->mapWidth)
        {
            img->worldMap[row][col] = 3;
            col++;
        }
        prevRowLength = ft_strlen(line);
        row++;
        free(line);
        line = get_next_line(file);
    }
    free(line);
    return (0);
}