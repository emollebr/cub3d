#include "includes/cub3d.h"

unsigned int rgbToUnsignedInt(char *color)
{
    int rgb[3];
    int i;
    int j;

    i = 0;
    j = 0;
    color = "123,456,789"; // for test only!! delete!!
    while (j < 3) {
        rgb[j] = 0;
        while (color[i] != '\0' && color[i] != ',') {
            if (ft_isdigit(color[i]) != 1 && color[i] != ',') {
                ft_printf("Error:\n Invalid floor or ceiling color: %s\n", color);
                return (0);
            }
            rgb[j] = rgb[j] * 10 + (color[i] - '0');
            printf("color is %d = %c\n", rgb[j], color[i]);
            i++;
        }
        i++;
        j++;
    }
    for (int k = 0; k < 3; k++) {
        rgb[k] = (rgb[k] < 0) ? 0 : ((rgb[k] > 255) ? 255 : rgb[k]);
    }
    return ((unsigned int)rgb[0] << 16) | ((unsigned int)rgb[1] << 8) | (unsigned int)rgb[2];
}

int check_for_textures(t_tex *element)
{
    int NSWEFC[6];
    int i;

    i = -1;
    while (++i < 6)
        NSWEFC[i] = 0;
    while (element != NULL && element->type != NULL)
    {
        ft_printf("element type is %s path is %s\n", element->type, element->path);
        if (element->type[0] == 'N')
            NSWEFC[0] = 1;
        if (element->type[0] == 'S')
            NSWEFC[1] = 1;
        if (element->type[0] == 'W')
            NSWEFC[2] = 1;
        if (element->type[0] == 'E')
            NSWEFC[3] = 1;
        if (element->type[0] == 'F')
            NSWEFC[4] = 1;
        if (element->type[0] == 'C')
            NSWEFC[5] = 1;
        element = element->next;
    }
    while (++i < 6) {
        if (NSWEFC[i] == 0) {
            ft_printf("Error:\n Missing wall, floor or ceiling info in .cub file\n");
            return (-1);
        }
    }
    return (0);
}

int    copy_texture_element(t_tex *element, char *line)
{
    int i;

    i = 0;
    while (line[i] != ' ')
        i++;
    element->type = ft_substr(line, 0, 1);
    while (line[i] == ' ')
        i++;
    element->path = ft_substr(line, i, ft_strlen(line) - i - 1);
    if (line[0] == 'F' || line[0] == 'C') {
        element->rgb = rgbToUnsignedInt(element->path);
        if (element->rgb== 0)
            return (-1);
        printf("final color is 0x%x\n", element->rgb);
    }
    else if (ft_strchr("NSWE", line[0]) != 0) {
        if (access(element->path, O_RDONLY) < 0)
            return (ft_printf("Error:\n Couldn't access texture file: %s\n", element->path), -1);
    }
    else
        return(ft_printf("Error:\n Invalid line in .cub file: %s\n", line), -1);
    element->next = NULL;
    return (0);
}

int check_for_map_start(char *line)
{
    int i;
    
    i = 0;
    while (line[i] && line[i] == ' ')
        i++;
    if (ft_isdigit(line[i])) {
        ft_printf("map start: %s\n", line);
        free(line);
        return (1);
    }
    return (0);
}

int    parse_textures(int file, t_data *img) {
    t_tex  *head;
    char            *line;
    int             elems;

    elems = 0;
    img->tex = ft_calloc(sizeof(t_tex), 1);
    head = img->tex;
    while (elems < 6) // should check if the line syntax is map, fix later
    {
        line = get_next_line(file);
        if (check_for_map_start(line) == 1) {
            break ;
        }
        if (ft_strlen(line) != 0 && line[0] != '\n')
        {
            if (copy_texture_element(img->tex, line) == -1)
                return (-1);
            ft_printf("Type: %s, Path: %s, elems %d\n", img->tex->type, img->tex->path, elems);   // Print or use the parsed information as needed
            img->tex->next = ft_calloc(sizeof(t_tex), 1);
            if (!img->textures)
                return (-1);
            img->tex = img->tex->next;
            elems++;
        }
        free(line);
    }
    ft_printf("elems is %d\n", elems);
    img->tex = NULL;
    img->tex = head;
    if (check_for_textures(head) == -1)
       return (-1);
    return (0);
}