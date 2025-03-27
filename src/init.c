/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:46:30 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/27 14:54:44 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//Initialize Game structure with default values 
void init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.has_player = 0;
	game->floor_color = 0;
	game->ceiling_color = 0;
	game->map_path = NULL;
	game->img.img = NULL;
	game->tex_north.img = NULL;
	game->tex_south.img = NULL;
	game->tex_east.img = NULL;
	game->tex_west.img = NULL;
}

//Initialize mlx window and connection
int init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_handle(game, "Mlx initialization failed"));
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		return (error_handle(game, "Window intialization failed"));
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if(!game->img.img)
		return (error_handle(game, "Image creation failed"));
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	return (0);
}

//Initialize player position & direction 
void init_player(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (ft_strchr("NSEW", game->map.grid[y][x]))
			{
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				game->player.direction = game->map.grid[y][x];
				game->map.grid[y][x] = '0';
				setup_player_direction(game);
				return;
			}
			x++;
		}
		y++;
	}
}

//définir le vecteur de direction du joueur en fonction 
//du caractère de direction de départ

void setup_player_direction(t_game *game)
{
	if (game->player.direction == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->camera.plane_x = 0.66;
		game->camera.plane_y = 0;
	}
	else if (game->player.direction = "S")
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->camera.plane_x = -0.66;
		game->camera.plane_y = 0;
	}
	else if (game->player.direction = "E")
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->camera.plane_x = 0;
		game->camera.plane_y = 0.66;
	}
	else if (game->player.direction = "W")
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->camera.plane_x = 0;
		game->camera.plane_y = -0.66;
	}
}
//Charger les textures murales (nord, sud, est, ouest) et les couleurs du sol 
//et du plafond depuis les chemins définis dans la structure t_game.
int	load_textures(t_game *game)
{
	game->tex_north.img = mlx_xpm_file_to_image(game->mlx, game->textures.path_no,
		&game->tex_north.width, &game->tex_north.height);
	if (!game->tex_north.img)
		return (error_handler(game, "Failed to load north texture"));
	game->tex_north.addr = mlx_get_data_addr(game->tex_north.img,
		&game->tex_north.bits_per_pixel, &game->tex_north.line_length, 
		&game->tex_north.endian);

	game->tex_south.img = mlx_xpm_file_to_image(game->mlx, game->textures.path_so,
		&game->tex_south.width, &game->tex_south.height);
	if (!game->tex_south.img)
		return (error_handler(game, "Failed to load south texture"));
	game->tex_south.addr = mlx_get_data_addr(game->tex_south.img,
		&game->tex_south.bits_per_pixel, &game->tex_south.line_length, 
		&game->tex_south.endian);
	
	game->tex_east.img = mlx_xpm_file_to_image(game->mlx, game->textures.path_ea,
		&game->tex_east.width, &game->tex_east.height);
	if (!game->tex_east.img)
		return (error_handler(game, "Failed to load east texture"));
	game->tex_east.addr = mlx_get_data_addr(game->tex_east.img,
		&game->tex_east.bits_per_pixel, &game->tex_east.line_length, 
		&game->tex_east.endian);
	
	game->tex_west.img = mlx_xpm_file_to_image(game->mlx, game->textures.path_we,
		&game->tex_west.width, &game->tex_west.height);
	if (!game->tex_west.img)
		return (error_handler(game, "Failed to load west texture"));
	game->tex_west.addr = mlx_get_data_addr(game->tex_west.img,
		&game->tex_west.bits_per_pixel, &game->tex_west.line_length, 
		&game->tex_west.endian);
	
	game->floor_color = parse_color(game->textures.color_f);
	game->ceiling_color = parse_color(game->textures.color_c);
	return (0);
}

// Parse color string "R,G,B" into a single integer
int parse_color(char *color_str)
{
	int r;
	int g;
	int b;
	char **split;

	split = ft_split(color_str, ',');
	if (!split)
		return (0);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_split(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (r << 16 | (g << 8) | b);
}
