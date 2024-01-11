#include "includes/cub3d.h"

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

int isValidMapChar(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int validateMap(t_data *img)
{
    int i;

    i = -1;
    // Check if the map is surrounded by walls
   while (++i < img->mapHeight) 
   {
        if (img->worldMap[i][0] != 1 && img->worldMap[i][0] != 3 && img->worldMap[i][img->mapWidth - 1] != 1 && img->worldMap[i][img->mapWidth - 1] != 3)
            return (0);
        if (img->worldMap[0][i] != 1 && img->worldMap[img->mapHeight - 1][i] != 1 && img->worldMap[0][i] != 3 && img->worldMap[img->mapHeight - 1][i] != 3)
           return (0); 
    }
    return 1;
}

// Function to parse and validate the map from a file
int    parseAndValidateMap(int file, char *start_of_map, t_data *img) 
{
    char *line;
    int i;

    i = -1;
    img->worldMap = ft_calloc(sizeof(int *), img->mapHeight);
    while (++i < img->mapHeight)
        img->worldMap[i] = ft_calloc(sizeof(int), img->mapWidth);
    // Read and parse the map
    int row = 0;
    int prevRowLength = 0;
    line = get_next_line(file);
    while (ft_strncmp(start_of_map, line, ft_strlen(line) != 0)) {
        free(line);
        line = get_next_line(file);
    }
    free(start_of_map);
    while (line != NULL) {
        if (row >= img->mapHeight) {
            ft_printf("Error: Map size exceeds allowed height.\n");
            return (-1);
        }

        // Ignore leading whitespaces
        int col = 0;
        while (line[col] == ' ') {
            img->worldMap[row][col] = 3;
            col++;
        }

        // Validate each character in the row
        while (col < img->mapWidth && line[col] != 10) {
            char c = line[col];

            // Check for valid characters
            if (!isValidMapChar(c)) {
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
            else if (ft_isalpha(c)) {
                img->worldMap[row][col] = 0;
                img->player.x = col;
                img->player.y = row;
                //put direction here as well
            } 
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
    //Check if the map is surrounded by walls
    if (!validateMap(img)) {
        ft_printf("Error: Map is not surrounded by walls.\n");
       return (-1);
    }
    return (0);
}

void    parse_map(int file, char *start_of_map, t_data *img) 
{

    parseAndValidateMap(file, start_of_map, img);

    return ;
}