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

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define WIDTH 1024
# define HEIGHT 720
# define ROT_SPEED 0.07
# define MOV_SPEED 0.2
# define MIN_DISTANCE_FROM_WALL 0.2
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define MAP_ERROR_1 "Error: Invalid character in the map: "
# define MAP_ERROR_2 "Error: Invalid character in the first or last row: "
# define MAP_ERROR_3 "Error: Invalid character in the first or last column: "
# define MAP_ERROR_4 "Error: Invalid character "
# define RGB_ERROR_1 "Error: Invalid floor or ceiling color: "
# define RGB_ERROR_2 "Error: Invalid RGB value: "

enum				e_texture_type
{
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
	double x;          // Sprite x-coordinate in the world
	double y;          // Sprite y-coordinate in the world
	int texture_index; // Index of the texture for the sprite
	int				order;
	struct s_sprite	*next;
}					t_sprite;

typedef struct s_sprite_info
{
	double distance;  // Distance from the player to the sprite
	int sprite_index; // Index of the sprite in the array
}					t_sprite_info;

typedef struct s_sprite_data
{
	double			spriteX;
	double			spriteY;
	t_sprite		*sprite;
	double			transformX;
	int				spriteScreenX;
	int				spriteHeight;
	int				spriteWidth;
	int				drawStartY;
	int				drawEndY;
	int				drawStartX;
	int				drawEndX;
	int				texX;
	int				texY;
	int				color;
	double			invDet;
	double			transformY;
	int				distance;
	double			*spriteDistance;
	struct s_data	*img;
}					t_sprite_data;

typedef struct s_door
{
	double x;             // Door's x-coordinate
	double y;             // Door's y-coordinate
	double width;         // Door's width
	double height;        // Door's height
	int isOpen;           // Door's state (0 for closed, 1 for open)
	double animationTime; // Time elapsed during the door animation
	int				animation_frame;
	bool			open_;
	bool			opening;
	int				current_anim_frame;
	int				animationspeed;
	int				door_bool;
	int				tex_num;
	unsigned int	tex_x;
	unsigned int	tex_y;
	double			wall_x;
}					t_door;

typedef struct
{
	double			rayDirX0;
	double			rayDirY0;
	double			rayDirX1;
	double			rayDirY1;
	int				p;
	float			posZ;
	float			row_distance;
	float			floor_step_x;
	float			floor_step_y;
	float			floor_x;
	float			floor_y;
	int				tex_width_F;
	int				tex_height_F;
	int				ceil_tex_width_C;
	int				ceil_tex_height_C;
	int				x;
	int				cellX;
	int				cellY;
	int				tx;
	int				ty;
	int				ceil_tx;
	int				ceil_ty;
	int				floor_color;
	int				ceil_color;
}					t_floor_values;

typedef struct images
{
	void			*mlx;
	void			*win;
	void			*image;
	void			*path;
	int				width;
	int				height;
	int				ret;
}					t_img;

typedef struct
{
	double			r;
	double			g;
	double			b;
}					t_color;

typedef struct s_keys
{
	bool			w;
	bool			s;
	bool			a;
	bool			d;
	bool			q;
	bool			left;
	bool			right;
	bool			space;
	struct s_data	*img;
	int				mouse_x;
	int				mouse_y;
	int				prev_mouse_x;
	int				prev_mouse_y;
	int				is_mouse_locked;
}					t_keys;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			floor_x;
	double			floor_y;
	double			old_player_x;
	double			old_player_y;
}					t_player;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	char			*type;
	char			*path;
	unsigned int	rgb;
}					t_texture;

typedef struct s_minimap
{
	int				vis_height;
	int				vis_width;
	int				vis_y;
	int				vis_x;
	int				x;
	int				y;
	int				player_x;
	int				player_y;
	int				line_end_x;
	int				line_end_y;
	int				wall_or_door;
	t_texture		walls;
	t_texture		background;
}					t_minimap;

typedef struct s_data
{
	void			*img;
	void			*mlx;
	void			*mlx_win;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	double			cxmin;
	double			cxmax;
	double			cymax;
	double			cymin;
	int				ix;
	int				iy;
	int				check;
	int				color;
	double			jx;
	double			jy;
	t_player		player;
	t_keys			keys;
	t_texture		textures[23];
	double			z_buffer[WIDTH];
	int				**worldMap;
	int				mapHeight;
	int				mapWidth;
	t_door			doors;
	int				numSprites;
	t_sprite		*sprites;
	t_sprite		*sprite_head;
	int				current_anim_frame;
	unsigned int	animationspeed;
}					t_data;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				side;
	double			side_dist_x;
	double			side_dist_y;
	int				hit;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			floor_x;
	double			floor_y;
	double			floor_x_step;
	double			floor_y_step;
}					t_ray;

void				my_mlx_pixel_put(t_data *img, int x, int y, int color);
int					close_program(t_data *img);
void				free_all(t_data *img);
int					get_texture_color(t_texture texture, int x, int y);

// cast_rays.c
int					cast_rays(t_data *img);
void				calculate_side_distances(t_ray *ray, t_data *img);
void				calculate_perp_wall_dist(t_ray *ray, t_data *img);

// draw.c
void				draw_textured_wall(t_data *img, t_ray *ray, int x);
void				draw_textured_floor(t_data *img);

// key_events.c
int					key_release(int keycode, t_keys *keys);
int					key_hook(t_keys *keys);
int					mouse_motion(int x, int y, t_keys *keys);
int					key_press(int keycode, t_keys *keys);

// utils_colors.c
double				get_scale(t_minimap minimap);
int					get_original_xy(t_data *img, t_minimap *minimap, int x,
						int num);
int					get_texture_color(t_texture texture, int x, int y);
int					darken_color(int color, double distance);
t_color				apply_light(t_color color, double distance);

// utils_textures.c
void				get_file_paths(t_data *img);
void				load_sprites_and_doors(t_data *img);
void				load_minimap_textures(t_data *img, t_texture *bg,
						t_texture *va);
void				load_textures(t_data *img);

// initialize_params.c
void				initialize_ray(t_ray *ray, t_data *img, int x);
void				initialize_mlx_window(t_data *img);
void				initialize_doors(t_data *img);
void				initialize_z_buffer(t_data *img);
void				setup_mlx_hooks(t_data *img, t_keys *keys);

// player_move.c
void				handle_collision(t_data *img, double oldPlayerX,
						double oldPlayerY);
void				move_player(t_data *img, double mov_speed, int direction);
void				strafe_player(t_data *img, double mov_speed, int direction);
void				rotate_player(t_data *img, double rot_speed, int direction);
void				handle_player_movement(t_keys *keys, t_data *img);

// image.c
void				update_image(t_data *img, t_keys *keys);

// sprites.c
int					draw_sprites(t_data *img);

// sprite_utils.c
int					compare_sprite_distance(const void *a, const void *b);
void				sort_sprites(int *order, double *dist, int amount);
void				initialize_sprite_data(t_sprite_data *s, t_sprite *sprite,
						t_data *img);

// doors.c
int					cast_rays_doors(t_data *img);

// draw_doors.c
void				calculate_door_parameters(t_ray *ray, t_data *img,
						t_door *doors);
void				draw_door_lines(t_data *img, t_ray *ray, t_door *doors,
						int x);
void				update_door_animation(t_door *doors);
void				update_door_animation_open(t_door *doors);
int					draw_doors(t_data *img, t_door *doors, int x, t_ray *ray);

// parse_cub_file.c
int					validate_textures(t_data *img, int elems);
int					parse_cub_file(const char *filename, t_data *img);

// parse_map.c
int					assign_character_to_map(t_data *img, char c, int row,
						int col);
int					check_more_map_rules(char *line, int row, int col,
						int prevRowLength);
int					check_map_rules(char *line, int row, int col, t_data *img);
int					parse_loop(t_data *img, char *line, int row,
						int prev_row_length);
int					parse_map(int file, char *start_of_map, t_data *img);

// utils_parse_map.c
char				*allocate_map(int file, char *start_of_map, t_data *img);
char				*get_map_dimensions(int file, t_data *img);
int					add_sprite(t_data *img, int row, int col);
int					validate_map(t_data *img);

// utils_parse_map_2.c
char				*find_first_line(int file);
int					is_valid_map_char(char c);
void				parse_player_pos(t_data *img, char dir, int row, int col);

// parse_textures.c
int					parse_textures(int file, t_data *img);
int					iterate_texture_element(char *line, t_data *img);
int					check_for_map_start(char *line);
int					copy_texture_element(t_texture *element, char *line);
unsigned int		rgb_to_unsigned_int(char *color);

// minimap.c
void				draw_player(t_data *img, t_minimap *minimap);
void				draw_background(t_data *img, t_minimap *minimap);
void				scale_visible_area(t_data *img, t_minimap minimap, int x,
						int y);
void				draw_visible_area(t_data *img, t_minimap *minimap,
						int cell_x, int cell_y);
void				render_minimap(t_data *img);

// utils_minimap.c
void				calculate_visible_area(t_data *img, t_minimap *minimap);
void				draw_line(t_data *img, t_minimap *minimap);
void				get_line_values(t_minimap *minimap, int *d, int *s);

#endif
