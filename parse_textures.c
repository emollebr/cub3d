#include "includes/cub3d.h"

unsigned int rgbToUnsignedInt(char *color) {
    int rgb[3];
    int i;
    int j;

    j = 0;
    while (j < 3) {
        i = 0;
        while (color[i] != '\0' && color[i] != ',') {
            rgb[j] = color[i] + '0' * (pow(10, i));
            i++;
        }
        j++;
    }
       // Ensure RGB values are in the valid range (0-255)
    for (int k = 0; k < 3; k++) {
        rgb[k] = (rgb[k] < 0) ? 0 : ((rgb[k] > 255) ? 255 : rgb[k]);
    }

    return ((unsigned int)rgb[0] << 16) | ((unsigned int)rgb[1] << 8) | (unsigned int)rgb[2];
}
}

void    copy_texture_element(t_tex *element, char *line) {
    int i;

    i = 0;
    while (line[i] != ' ')
        i++;
    element->type = ft_substr(line, 0, 1);
    while (line[i] == ' ')
        i++;
    element->path = ft_substr(line, i, ft_strlen(line) - i - 1);
    //if (line[0] == 'F' || line[0] == 'C') {
      //convert to hex here
  //  }
    ft_printf("type: %s, path: '%s'\n", element->type, element->path);
    return ;
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