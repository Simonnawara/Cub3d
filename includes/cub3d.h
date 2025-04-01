/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:37:51 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/01 10:54:36 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include "../libft/include/libft.h"
# include <sys/time.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <ctype.h>
# include <time.h>

/* Key codes for events */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
/* Window dimensions */
# define WIDTH 1024
# define HEIGHT 768

# define MOVE_SPEED 0.06
# define STRAFE_SPEED 0.08
# define ROT_SPEED 0.03
# define WALL_MARGIN 0.2

/* FPS Control */
# define FPS 60
# define FRAME_TIME (1000000 / FPS)

/* minimap constant*/
#define MINIMAP_SIZE 200
#define MINIMAP_SCALE 10
#define MINIMAP_MARGIN 20
#define MINIMAP_ALPHA 0.7

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

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_keys;
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

typedef struct s_time
{
	long	old_time;
	long	current_time;
	double	frame_time;
}	t_time;

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
	t_keys		keys;
	t_time		time;
}	t_game;



// file_check.c //
int is_cub_file(const char *filename);
int is_xpm_file(const char *filename);
int check_permission(const char *filename);
int check_textures(const char *line, int i, t_textures *textures);
t_textures  *init_textures(void);
int textures_present(t_textures *textures);

//main.c//
//int render_frame(t_game *game);
int handle_exit(t_game *game);
int key_press(int keycode, t_game *game);
//int game_loop(t_game *game);
int load_map(t_game *game, const char *filename);
int parse_file(t_game *game, const char *filename);
int validate_inputs(int argc, char **argv);

//init.c//
void init_game(t_game *game);
int init_mlx(t_game *game);
void init_player(t_game *game);
void setup_player_direction(t_game *game);
int	load_texture(t_game *game, t_img *texture, char *path);

// init_utils.c //
void init_games(t_game *game);
int parse_color(char *color_str);
int	load_textures(t_game *game);
void direction_north(t_game *game);

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
char	**duplicate_map(char **map, int rows, int cols);

// free.c // 
void	free_map_copy(char **map_copy, int rows);

//raycasting.c//
void cast_rays(t_game *game);
void calculate_ray(t_game *game, t_ray *ray, int x);
void	init_dda_x(t_game *game, t_ray *ray);
void	init_dda_y(t_game *game, t_ray *ray);
int	check_ray_hit(t_game *game, t_ray *ray);
void perform_dda(t_game *game, t_ray *ray);
void calculate_wall_distance(t_ray *ray, t_game *game);
void calculate_wall_height(t_ray *ray, int screen_height);
void draw_wall_stripe(t_game *game, int x, t_ray *ray);
void	draw_ceiling(t_game *game, int x, t_ray *ray);
void	draw_floor(t_game *game, int x, t_ray *ray);
void	draw_textured_wall(t_game *game, int x, t_ray *ray, t_tex_pos *tex);
void	calculate_texture_position(t_game *game, t_ray *ray, t_tex_pos *tex);
int get_pixel_color(t_img *img, int x, int y);
void put_pixel(t_img *img, int x, int y, int color);
void clear_image(t_img *img, int color);

//move.c//
void move_player(t_game *game, double move_speed);
void strafe_player(t_game *game, double strafe_speed);
void	adjust_camera_plane(t_player *player, t_camera *camera);
void	normalize_dir_vector(t_player *player);
void rotate_player(t_game *game, double rot_speed);

// move_utils.c //
int key_press(int keycode, t_game *game);
int	key_state_handler(t_game *game);
int	key_release_state(int keycode, t_game *game);
int	key_press_state(int keycode, t_game *game);
int is_valid_move(t_game *game, double x, double y);

//time.c//
void	init_time(t_game *game);
void	update_time(t_game *game);
double	get_frame_time(t_game *game);
void	frame_delay(t_game *game);

// minimap.c //
int	blend_colors(int color1, int color2, double alpha);
void	draw_rect(t_game *game, int x, int y, int size, int color);
void	draw_player(t_game *game, int minimap_x, int minimap_y);
void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color);
void	draw_minimap(t_game *game);

// game_loop.c //
void	init_key_states(t_game *game);
int	game_loop(t_game *game);
int	game_update(t_game *game);
int	render_frame(t_game *game);
void process_movement(t_game *game, double time_factor);
void test_player_movement(t_game *game, int frame_count);

// fps.c //
void	draw_fps_counter(t_game *game);

#endif