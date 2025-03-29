/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:37:51 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/29 15:12:45 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include "../libft/include/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <ctype.h>

/* Key codes for events */
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

/* Window dimensions */
# define WIDTH 1024
# define HEIGHT 768

/* Existing texture structure */
typedef struct s_textures
{
	int		is_no;
	int		is_so;
	int		is_ea;
	int		is_we;
	int		is_f;
	int		is_c;
	char	*path_no;
	char	*path_so;
	char	*path_ea;
	char	*path_we;
	char	*color_f;
	int		*color_f_array;
	char	*color_c;
	int		*color_c_array;
}	t_textures;

/* MLX image structure */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* Map structure */
/* typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		has_player;
}	t_map; */

/* Player structure */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	char	direction;
}	t_player;

/* Camera structure */
typedef struct s_camera
{
	double	plane_x;
	double	plane_y;
}	t_camera;

/* Ray structure */
typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

/* Texture position for rendering */
typedef struct s_tex_pos
{
	t_img	*img;
	int		x;
	int		y;
	double	pos;
	double	step;
}	t_tex_pos;

// New map structure
typedef struct s_map {
    char **map;      // 2D array of map characters
    int height;      // Number of rows
    int width;       // Max width of map
} t_map;

/* Main game structure */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_camera	camera;
	t_map		map;
	t_textures	textures;
	t_img		img;
	t_img		tex_north;
	t_img		tex_south;
	t_img		tex_east;
	t_img		tex_west;
	int			floor_color;
	int			ceiling_color;
	char		*map_path;
}	t_game;



// file_check.c //
int is_cub_file(const char *filename);
int is_xpm_file(const char *filename);
int check_permission(const char *filename);
int check_textures(const char *line, int i, t_textures *textures);
t_textures  *init_textures(void);
int textures_present(t_textures *textures);

//main.c//
int render_frame(t_game *game);
int handle_exit(t_game *game);
int key_press(int keycode, t_game *game);
int game_loop(t_game *game);
int load_map(t_game *game, const char *filename);
int parse_file(t_game *game, const char *filename);
int validate_inputs(int argc, char **argv);

//init.c//
void init_game(t_game *game);
int init_mlx(t_game *game);
void init_player(t_game *game);
void setup_player_direction(t_game *game);
int	load_texture(t_game *game, t_img *texture, char *path);
int	load_textures(t_game *game);
int parse_color(char *color_str);

//cleanup.c//
void    free_map(t_map *map);
void free_textures(t_game *game);
void    free_images(t_game *game);
int	clean_exit(t_game *game, int status);
int	error_handle(t_game *game, char *error_message);
void free_split(char **split);

//check_map.c//
int is_map_line(const char *line);
int is_texture_line(const char *line);
char **allocate_map(int rows, int cols);
char **extract_map(int fd, int *rows, int *cols);
int validate_map_structure(const char *filename);

//color_check.c//
int is_valid_rgb_component(const char *str);
int *rgb_split(const char *rgb_str);

//parse_map.c//
int flood_fill(char **map, int x, int y, int rows, int cols);
int is_map_enclosed(char **map, int rows, int cols);
int validate_map_content(char **map, int rows, int cols);
int validate_map(char **map, int rows, int cols);

//raycasting.c//
void cast_rays(t_game *game);
void calculate_ray(t_game *game, t_ray *ray, int x);
void perform_dda(t_game *game, t_ray *ray);
void calculate_wall_distance(t_ray *ray, t_game *game);
void calculate_wall_height(t_ray *ray, int screen_height);
void draw_wall_stripe(t_game *game, int x, t_ray *ray);
void calculate_texture_position(t_game *game, t_ray *ray, int x, t_tex_pos *tex);
int get_pixel_color(t_img *img, int x, int y);
void put_pixel(t_img *img, int x, int y, int color);
int render_frame(t_game *game);
void clear_image(t_img *img, int color);

//move.c//
void move_player(t_game *game, double move_speed);
void strafe_player(t_game *game, double strafe_speed);
void rotate_player(t_game *game, double rot_speed);
int is_valid_move(t_game *game, double x, double y);
int key_press(int keycode, t_game *game);
#endif