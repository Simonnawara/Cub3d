/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:46:30 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/31 14:38:02 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Initialize Game structure with default values
void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map.map = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->floor_color = 0;
	game->ceiling_color = 0;
	game->map_path = NULL;
	game->img.img = NULL;
	game->tex_north.img = NULL;
	game->tex_south.img = NULL;
	game->tex_east.img = NULL;
	game->tex_west.img = NULL;
	init_games(game);
}

// Initialize mlx window and connection
int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_handle(game, "Mlx initialization failed"));
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		return (error_handle(game, "Window intialization failed"));
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img.img)
		return (error_handle(game, "Image creation failed"));
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	return (0);
}

// Initialize player position & direction
void	init_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (ft_strchr("NSEW", game->map.map[y][x]))
			{
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				game->player.direction = game->map.map[y][x];
				game->map.map[y][x] = '0';
				setup_player_direction(game);
				return ;
			}
			x++;
		}
		y++;
	}
}

// définir le vecteur de direction du joueur en fonction
// du caractère de direction de départ
void	setup_player_direction(t_game *game)
{
	if (game->player.direction == 'N')
		direction_north(game);
	else if (game->player.direction == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->camera.plane_x = -0.66;
		game->camera.plane_y = 0;
	}
	else if (game->player.direction == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->camera.plane_x = 0;
		game->camera.plane_y = 0.66;
	}
	else if (game->player.direction == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->camera.plane_x = 0;
		game->camera.plane_y = -0.66;
	}
}

// Charger les textures murales (nord, sud, est, ouest) et les couleurs du sol
// et du plafond depuis les chemins définis dans la structure t_game.
int	load_texture(t_game *game, t_img *texture, char *path)
{
	if (!path || access(path, F_OK | R_OK) != 0)
	{
		ft_printf("Error: Cannot access texture file: %s\n", path);
		return (0);
	}
	if (!is_xpm_file(path))
	{
		ft_printf("Error: Not an XPM file: %s\n", path);
		return (0);
	}
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (0);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->addr)
	{
		ft_printf("Error: Failed to get texture data: %s\n", path);
		return (0);
	}
	ft_printf("Texture loaded successfully: %s (%dx%d)\n", path, texture->width,
		texture->height);
	return (1);
}
