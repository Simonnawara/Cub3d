/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:37:51 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/04 14:46:27 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include "../libft/include/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

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
# define MINIMAP_SIZE 200
# define MINIMAP_SCALE 10
# define MINIMAP_MARGIN 20
# define MINIMAP_ALPHA 0.7

/* Existing texture structure */
typedef struct s_textures
{
	int			is_no;
	int			is_so;
	int			is_ea;
	int			is_we;
	int			is_f;
	int			is_c;
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	char		*color_f;
	int			*color_f_array;
	char		*color_c;
	int			*color_c_array;
}				t_textures;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_keys;
/* MLX image structure */
typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_map_data
{
	char		**map;
	int			row;
	int			cols;
	int			map_started;
}				t_map_data;

/* Structure for rectangle coordinates and size */
typedef struct s_rect
{
	int			x;
	int			y;
	int			size;
}				t_rect;

/* Player structure */
typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	char		direction;
}				t_player;

/* Camera structure */
typedef struct s_camera
{
	double		plane_x;
	double		plane_y;
}				t_camera;

/* Ray structure */
typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			hit;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct s_time
{
	long		old_time;
	long		current_time;
	double		frame_time;
}				t_time;

/* Texture position for rendering */
typedef struct s_tex_pos
{
	t_img		*img;
	int			x;
	int			y;
	double		pos;
	double		step;
}				t_tex_pos;

// New map structure
typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
}				t_map;

typedef struct s_cord
{
	int			x;
	int			y;
}				t_cord;

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
}				t_game;

// file_check.c //
int				is_cub_file(const char *filename);
int				is_xpm_file(const char *filename);
int				check_permission(const char *filename);
int				check_textures(const char *line, int i, t_textures *textures);
t_textures		*init_textures(void);
int				textures_present(t_textures *textures);
int				colors_present(t_textures *textures);
int				textures_present(t_textures *textures);

// texture_check.c //
int				handle_no_texture(const char *line, int y, int j,
					t_textures *textures);
int				handle_so_texture(const char *line, int y, int j,
					t_textures *textures);
int				handle_ea_texture(const char *line, int y, int j,
					t_textures *textures);
int				handle_we_texture(const char *line, int y, int j,
					t_textures *textures);

// texture_check2.c //
int				handle_f_color(const char *line, int y, int j,
					t_textures *textures);
int				handle_c_color(const char *line, int y, int j,
					t_textures *textures);

// main.c//
int				key_press(int keycode, t_game *game);
int				check_validation_result(t_game *game, int result);
int				load_map(t_game *game, const char *filename);
int				validate_inputs(int argc, char **argv);

// parse_files.c //
int				skip_whitespace(char *line);
int				process_config_line(t_game *game, char *line, int fd);
int				parse_file(t_game *game, const char *filename);

// init.c//
void			init_game(t_game *game);
int				init_mlx(t_game *game);
void			init_player(t_game *game);
void			setup_player_direction(t_game *game);
int				load_texture(t_game *game, t_img *texture, char *path);

// init_utils.c //
void			init_games(t_game *game);
int				parse_color(char *color_str);
int				load_textures(t_game *game);
void			direction_north(t_game *game);

// cleanup.c//
void			free_map(t_map *map);
void			free_textures(t_game *game);
void 			cleanup_textures(t_textures *textures);
void			cleanup_map(char **map, int rows);
void			free_images(t_game *game);
int				clean_exit(t_game *game, int status);
int				error_handle(t_game *game, char *error_message);
void			free_split(char **split);

// check_map.c//
char			**extract_map(int fd, int *rows, int *cols,
					t_textures *textures);
int				check_empty_line(char *line);
int				handle_map_section(char *line, int *map_started,
					int *map_section_ended, int *valid_map_found);
int				validate_map_structure(const char *filename);

// check_map_utils.c //
void			free_map_1(char **map, int rows);
int				return_char_value(int has_valid_char, int has_invalid_char);
int				is_map_line(const char *line);
int				is_texture_line(const char *line);

// check_map_utils2.c //
char			**allocate_map(int rows, int cols);
char			**init_map_data(int rows, int cols);
int				process_map_line_data(char *line, t_map_data *data);
char			**fill_map_data(int fd, int rows, int cols);

// check_map_utils3.c //
void			process_map_line(char **map, char *line, int row, int col_len);
int				process_map_row_data(char *line, int *cols, int *map_started);
int				count_map_rows(int fd, int *cols);

// check_map_utils4.c //
void			init_map_status(int map_stat[3]);
int				close_return(int fd, int ret_value);
int				close_return_stat(int fd, int map_stat);

// color_check.c//
int				is_valid_rgb_component(const char *str);
int				*rgb_split(const char *rgb_str);

// color_check_utils1.c //
int				is_valid_rgb_component(const char *str);
int				check_rgb_format(const char *rgb_str);
int				count_rgb_components(char **split);
int				*populate_rgb_array(char **split);

// error.c //
void			print_error(char *error_message);
int				print_return_error(char *error_message, int return_value);
int				print_return_free(char *error_message, int return_value,
					char *line);

// color_check.c//
int				is_valid_rgb_component(const char *str);
int				*rgb_split(const char *rgb_str);

// parse_map.c//
int				flood_fill(char **map, t_cord *cord, int rows, int cols);
char			**allocate_map_copy(int rows, int cols);
char			**duplicate_map(char **map, int rows, int cols);
void			print_map(char **map, int rows, int cols);

// parse_map_utils.c //
int				find_start_position(char **map, int rows, int cols);
int				is_map_enclosed(char **map, int rows, int cols);
int				check_valid_char(char c, int *player_count);
int				validate_map_content(char **map, int rows, int cols, t_textures *textures);

// parse_map_utils2.c //
int				is_player_char(char c);
int				check_player_surroundings(char **map, int y, int x);
int				is_player_position_valid(char **map, int rows, int cols);
int				validate_map(char **map, int rows, int cols, t_textures *textures);

// free.c //
void			free_map_copy(char **map_copy, int rows);
int				handle_exit(t_game *game);
// free.c //
void			free_map_copy(char **map_copy, int rows);
int				handle_exit(t_game *game);

// raycasting.c//
void			cast_rays(t_game *game);
void			calculate_ray(t_game *game, t_ray *ray, int x);
void			init_dda_x(t_game *game, t_ray *ray);
void			init_dda_y(t_game *game, t_ray *ray);
int				check_ray_hit(t_game *game, t_ray *ray);
void			perform_dda(t_game *game, t_ray *ray);
void			calculate_wall_distance(t_ray *ray, t_game *game);
void			calculate_wall_height(t_ray *ray, int screen_height);
void			draw_wall_stripe(t_game *game, int x, t_ray *ray);
void			draw_ceiling(t_game *game, int x, t_ray *ray);
void			draw_floor(t_game *game, int x, t_ray *ray);
void			draw_textured_wall(t_game *game, int x, t_ray *ray,
					t_tex_pos *tex);
void			calculate_texture_position(t_game *game, t_ray *ray,
					t_tex_pos *tex);
int				get_pixel_color(t_img *img, int x, int y);
void			put_pixel(t_img *img, int x, int y, int color);
void			clear_image(t_img *img, int color);

// move.c//
void			move_player(t_game *game, double move_speed);
void			strafe_player(t_game *game, double strafe_speed);
void			adjust_camera_plane(t_player *player, t_camera *camera);
void			normalize_dir_vector(t_player *player);
void			rotate_player(t_game *game, double rot_speed);

// move_utils.c //
int				key_press(int keycode, t_game *game);
int				key_state_handler(t_game *game);
int				key_release_state(int keycode, t_game *game);
int				key_press_state(int keycode, t_game *game);
int				is_valid_move(t_game *game, double x, double y);

// time.c//
void			init_time(t_game *game);
void			update_time(t_game *game);
double			get_frame_time(t_game *game);
void			frame_delay(t_game *game);

// game_loop.c //
void			init_key_states(t_game *game);
int				game_loop(t_game *game);
int				game_update(t_game *game);
int				render_frame(t_game *game);
void			process_movement(t_game *game, double time_factor);
void			test_player_movement(t_game *game, int frame_count);

// fps.c //
void			draw_fps_counter(t_game *game);

#endif