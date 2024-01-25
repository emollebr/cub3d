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

# define MAP_ERROR_1 "Error: Invalid character in the map: "
# define MAP_ERROR_2 "Error: Invalid character in the first or last row: "
# define MAP_ERROR_3 "Error: Invalid character in the first or last column: "
# define MAP_ERROR_4 "Error: Invalid character "

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
    int vis_height;
    int vis_width;
    int vis_y;
    int vis_x;
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
    t_door    doors;
    int numSprites;
    t_sprite  *sprites;
    t_sprite    *sprite_head;
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

void            my_mlx_pixel_put(t_data *img, int x, int y, int color);
void            free_all(t_data *img);
int             get_texture_color(t_texture texture, int x, int y);

//cast_rays.c
int             cast_rays(t_data *img);

//draw.c
void            draw_textured_wall(t_data *img, t_ray *ray, int x);
void            draw_textured_floor(t_data *img, int x);

//key_events.c
int             key_release(int keycode, t_keys *keys);
int             key_hook(t_keys *keys);
int             mouse_motion(int x, int y, t_keys *keys);
int             key_press(int keycode, t_keys *keys);

//utils_textures.c
int             darken_color(int color, double distance);
t_color         apply_light(t_color color, double distance);
void            load_textures(t_data *img);
int             get_texture_color(t_texture texture, int x, int y);

//image.c
void            update_image(t_data *img, t_keys *keys);

//sprites.c
int             draw_sprites(t_data *img);

//doors.c
int             cast_rays_doors(t_data *img);

int             parse_cub_file(const char *filename, t_data *img);

//parse_map.c
int             assign_character_to_map(t_data *img, char c, int row, int col);
int             check_more_map_rules(char *line, int row, int col, int prevRowLength);
int             check_map_rules(char *line, int row, int col, t_data *img);
int             parse_loop(t_data *img, char *line, int row, int prev_row_length);
int             parse_map(int file, char *start_of_map, t_data *img);

//utils_parse_map.c
char            *allocate_map(int file, char *start_of_map, t_data *img);
char            *get_map_dimensions(int file, t_data *img);
int             add_sprite(t_data *img, int row, int col);
int             validate_map(t_data *img);

//utils_parse_map_2.c
int             is_valid_map_char(char c);
void            parse_player_pos(t_data *img, char dir, int row, int col);

//parse_textures.c
int             parse_textures(int file, t_data *img);
int             iterate_texture_element(char *line, t_data *img);
int             check_for_map_start(char *line);
int             copy_texture_element(t_texture *element, char *line);
unsigned int    rgbToUnsignedInt(char *color);


void            render_minimap(t_data *img);
void            draw_player(t_data *img, t_minimap *minimap);
void            draw_background(t_data *img, t_minimap *minimap);
void            calculate_visible_area(t_data *img, t_minimap *minimap);
void            draw_visible_area(t_data *img, t_minimap *minimap, int cell_x, int cell_y);

#endif