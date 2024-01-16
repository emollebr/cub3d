/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lejimene <lejimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:16:37 by lejimene          #+#    #+#             */
/*   Updated: 2024/01/15 17:01:11 by lejimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "cub3d.h"
# include "../libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

# define ROT_SPEED 0.05
# define MOV_SPEED 0.2
# define MIN_DISTANCE_FROM_WALL 0.2

typedef struct images
{
	void	*mlx;
	void	*win;
	void	*image;
	void	*path;
	int		width;
	int		height;
	int		ret;
}	t_img;

typedef struct {
    double r;
    double g;
    double b;
} t_color;

typedef struct s_keys {
    bool w;
    bool s;
    bool a;
    bool d;
    bool left;
    bool right;
    struct s_data *img;
} t_keys;

typedef struct s_player {
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double floor_x;
    double floor_y;
	double	old_player_x;
	double	old_player_y;
}				t_player;

typedef struct s_texture
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    int width;
    int height;
} t_texture;

typedef struct s_textures
{
    char *type;
    char *path;
    struct s_textures *next;
} t_tex;

typedef struct s_data {
	void	*img;
	void	*mlx;
	void	*mlx_win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	cxmin;
	double	cxmax;
	double	cymax;
	double	cymin;
	int		ix;
	int		iy;
	int		check;
	int		color;
	double	jx;
	double	jy;
  t_player  player;
  t_keys	keys;
  t_texture	textures[5];
    t_tex *tex;
  int   **worldMap;
  int   mapHeight;
  int   mapWidth;
  void  *minimap_img;
  int minimap_img_height;
  int minimap_img_width;
}	t_data;



typedef struct s_ray
{
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
    int side;
    double side_dist_x;
    double side_dist_y;
    int hit;
    double perp_wall_dist;
    int line_height;
    int draw_start;
    int draw_end;
    double floor_x;
    double floor_y;
    double floor_x_step;
    double floor_y_step;
} t_ray;

void    my_mlx_pixel_put(t_data *img, int x, int y, int color);
void    free_all(t_data *img);

int     parse_cub_file(const char *filename, t_data *img);

int     parse_map(int file, char *start_of_map, t_data *img);

//map utils
int     is_valid_map_char(char c);
int     validate_map(t_data *img);
char    *get_map_dimensions(int file, t_data *img);

int     parse_textures(int file, t_data *img);

void    render_minimap(t_data *img);

# define WIDTH 1024
# define HEIGHT 720



// int worldMap[mapWidth][mapHeight]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

#endif