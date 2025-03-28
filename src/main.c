/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:37:23 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/28 15:16:54 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int validate_inputs(int argc, char **argv)
{
	(void)argv;
	if (argc != 2) //check if the amount of argument is correct
	{
		write(2, "Error\n", 6);
		write(2, "Usage: './cub3D file.cub'\n", 26);
		return (1);
	}
	if (!is_cub_file(argv[1])) //check if file is .cub
	{
		write(2, "Error\n", 6);
		write(2, "Invalid file format.\n", 21);
		return (1);
	}
	if (check_permission(argv[1])) //check for file permissions
		return (1);
	return (0);
}

/*
** Parse file to load textures and settings
*/
int parse_file(t_game *game, const char *filename)
{
	int		fd;
	char	*line;
	int		i;

	// Store map path for later use
	game->map_path = ft_strdup(filename);
	if (!game->map_path)
		return (error_handle(game, "Memory allocation failed"));

	// Parse textures
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (error_handle(game, "Cannot open file"));

	while ((line = get_next_line(fd)) != NULL)
	{
		i = 0;
		while (line[i] && ft_isspace(line[i]))
			i++;
		
		if (line[i] == '\0')
		{
			free(line);
			continue;
		}
		
		if (check_textures(line, i, &game->textures))
		{
			free(line);
			close(fd);
			return (error_handle(game, "Invalid texture format"));
		}
		free(line);
	}
	close(fd);

	// Verify all textures are present
	if (!textures_present(&game->textures))
		return (error_handle(game, "Missing textures or colors"));

	return (0);
}

/*
** Extract map from file and store in game structure
*/
int load_map(t_game *game, const char *filename)
{
	int		rows = 0;
	int		cols = 0;
	int		fd;

	// Validate overall map structure
	if (!validate_map_structure(filename))
		return (error_handle(game, "Invalid map structure"));

	// Open file to extract the map
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (error_handle(game, "Cannot open file"));

	// Extract the map grid
	game->map.map = extract_map(fd, &rows, &cols);
	close(fd);
	
	if (!game->map.map)
		return (error_handle(game, "Failed to extract map"));

	game->map.height = rows;
	game->map.width = cols;

	// Final validation of the extracted map
	if (!validate_map(game->map.map, rows, cols))
		return (error_handle(game, "Map validation failed"));

	return (0);
}

/*
** Game loop function 
*/
int game_loop(t_game *game)
{
	// Set up hooks for key events
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 17, 0, handle_exit, game);
	
	// Initial render
	render_frame(game);
	
	// Start the MLX loop
	mlx_loop(game->mlx);
	
	return (0);
}

/*
** Key press handler
*/
int key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		return (clean_exit(game, 0));
	
	// Add more key handlers here once movement is implemented
	
	// Redraw the frame after movement
	render_frame(game);
	
	return (0);
}

/*
** Handle window close event
*/
int handle_exit(t_game *game)
{
	return (clean_exit(game, 0));
}

/*
** Render a single frame 
*/
int render_frame(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

/*
** Main function
*/
int main(int argc, char **argv)
{
	t_game game;

	if (validate_inputs(argc, argv))
		return (1);
	init_game(&game);
	if (parse_file(&game, argv[1]))
		return (1);
	if (load_map(&game, argv[1]))
		return (1);
	if (init_mlx(&game))
		return (1);
	init_player(&game);
	if (load_textures(&game))
		return (1);
	game_loop(&game);

	return (0);
}
