#include "includes/cub3d.h"

void    copy_texture_element(t_tex *element, char *line) {
    ft_printf("line: %s\n", line);
    if (line[0] == 'F' || line[0] == 'C') {
        // Floor/ceiling color
        element->type = ft_substr(line, 0, 1);
       element->path = ft_substr(line, 2, ft_strlen(line) - 2);
    } else {
        // NSEW color
        element->type = ft_substr(line, 0, 2);
       element->path = ft_substr(line, 3, ft_strlen(line ) - 3);
    }
    ft_printf("type: %s, path: %s\n", element->type, element->path);
    return ;
}

int    parse_textures(int file, t_data *img) {
    t_tex  *head;
    char            *line;
    int             elems;

    head = img->tex;
    elems = 0;
    img->tex = ft_calloc(sizeof(t_tex), 1);
    while (elems < 6) // should check if the line syntax is map, fix later
    {
        line = get_next_line(file);
        if (ft_strlen(line) != 0 && line[0] != '\n')
        {
            copy_texture_element(img->tex, line);
            ft_printf("Type: %s, Path: %s\n", img->tex->type, img->tex->path);   // Print or use the parsed information as needed
            img->tex->next = ft_calloc(sizeof(t_tex), 1);
            if (!img->textures)
                return (-1);
            img->tex = img->tex->next;
            elems++;
        }
        free(line);
    }
    img->tex = NULL;
    img->tex = head;
    return (0);
}