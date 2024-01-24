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
# include "../libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <float.h>

# define WIDTH 1024
# define HEIGHT 720
# define ROT_SPEED 0.07
# define MOV_SPEED 0.1
# define MIN_DISTANCE_FROM_WALL 0.2

enum  e_texture_type {
    l_N,
    l_S,
    l_W,
    l_E,
    l_F,
    l_C,
    l_MMBG,
    l_MMVA
};

typedef struct s_sprite
{
    double x;            // Sprite x-coordinate in the world
    double y;            // Sprite y-coordinate in the world
    int texture_index;   // Index of the texture for the sprite
    int order;
    struct s_sprite *next;
} t_sprite;

typedef struct s_sprite_info
{
    double distance;     // Distance from the player to the sprite
    int sprite_index;    // Index of the sprite in the array
} t_sprite_info;

typedef struct s_door {
    double x;            // Door's x-coordinate
    double y;            // Door's y-coordinate
    double width;        // Door's width
    double height;       // Door's height
    int isOpen;          // Door's state (0 for closed, 1 for open)
    double animationTime; // Time elapsed during the door animation
    int animation_frame;
    bool open_;
    bool opening;
    int currentAnimationFrame;
    int animationspeed;
    int door_bool;
} t_door;

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
    bool space;
    struct s_data *img;
    int mouse_x;
    int mouse_y;
    int prev_mouse_x;
    int prev_mouse_y;
    int is_mouse_locked;
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
    char *type;
    char *path;
    unsigned int    rgb;
} t_texture;

typedef struct s_minimap {
    int visible_height;
    int visible_width;
    int visible_y;
    int visible_x;
    int x;
    int y;
    t_texture walls;
    t_texture background;
} t_minimap;

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
    t_texture	textures[23];
    double z_buffer[WIDTH];
    int   **worldMap;
    int   mapHeight;
    int   mapWidth;
    t_minimap minimap;
    t_door    doors;
    int numSprites;
    t_sprite  *sprites;
    int currentAnimationFrame;
    unsigned int animationspeed;
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
int     get_texture_color(t_texture texture, int x, int y);

//image.c
void    update_image(t_data *img, t_keys *keys);

//sprites.c
int     draw_sprites(t_data *img);

//doors.c
int     cast_rays_doors(t_data *img);

int     parse_cub_file(const char *filename, t_data *img);

int     parse_map(int file, char *start_of_map, t_data *img);

//map utils
int     add_sprite(t_data *img, int row, int col);
int     is_valid_map_char(char c);
int     validate_map(t_data *img);
char    *get_map_dimensions(int file, t_data *img);

int     parse_textures(int file, t_data *img);

void    render_minimap(t_data *img);

#endif