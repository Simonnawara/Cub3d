/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:37:23 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/29 15:38:53 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Validate command line arguments and file format
*/
int	validate_inputs(int argc, char **argv)
{
	if (argc != 2) // Check if the amount of argument is correct
	{
		write(2, "Error\n", 6);
		write(2, "Usage: './cub3D file.cub'\n", 26);
		return (1);
	}
	if (!is_cub_file(argv[1])) // Check if file is .cub
	{
		write(2, "Error\n", 6);
		write(2, "Invalid file format. Expected .cub extension.\n", 46);
		return (1);
	}
	if (check_permission(argv[1])) // Check for file permissions
		return (1);
	return (0);
}

/*
** Parse file to load textures and settings with enhanced error handling
*/
int	parse_file(t_game *game, const char *filename)
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

	// Verify all textures are present and valid
	if (!textures_present(&game->textures))
		return (error_handle(game, "Missing textures or colors"));

	return (0);
}

/*
** Extract map from file and store in game structure with enhanced validation
*/
int	load_map(t_game *game, const char *filename)
{
	int	rows;
	int	cols;
	int	fd;

	// Validate overall map structure
	if (!validate_map_structure(filename))
		return (error_handle(game, "Invalid map structure"));

	// Open file to extract the map
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (error_handle(game, "Cannot open file"));

	// Extract the map grid
	rows = 0;
	cols = 0;
	game->map.map = extract_map(fd, &rows, &cols);
	close(fd);
	
	if (!game->map.map)
		return (error_handle(game, "Failed to extract map"));

	game->map.height = rows;
	game->map.width = cols;

	// Final validation of the extracted map with more detailed errors
	int validation_result = validate_map(game->map.map, rows, cols);
	if (validation_result == -1)
		return (error_handle(game, "Map validation failed: Map not enclosed"));
	else if (validation_result == -2)
		return (error_handle(game, "Map validation failed: Invalid characters in map"));
	else if (validation_result == -3)
		return (error_handle(game, "Map validation failed: Missing or multiple player positions"));
	else if (validation_result < 0)
		return (error_handle(game, "Map validation failed: Unknown error"));

	return (0);
}

/*
** Main function
*/
int	main(int argc, char **argv)
{
	t_game	game;

	// Validate input arguments
	if (validate_inputs(argc, argv))
		return (1);

	// Initialize game structure
	init_game(&game);

	// Parse textures and settings
	if (parse_file(&game, argv[1]))
	{
		ft_printf("Error: Failed to parse configuration file\n");
		return (1);
	}
	
	// Load and validate map
	if (load_map(&game, argv[1]))
	{
		ft_printf("Error: Failed to load or validate map\n");
		return (1);
	}

	// Initialize MLX
	if (init_mlx(&game))
	{
		ft_printf("Error: Failed to initialize graphics system\n");
		return (1);
	}

	// Initialize player based on map data
	init_player(&game);

	// Load textures
	if (load_textures(&game))
	{
		ft_printf("Error: Failed to load textures\n");
		return (1);
	}

	// Print welcome message
	ft_printf("\n--- cub3D Game Started ---\n");
	ft_printf("Controls: W/A/S/D to move, Arrow keys to turn\n");
	ft_printf("Press ESC to exit\n\n");

	// Start enhanced game loop with smooth movement and framerate control
	game_loop(&game);

	return (0);
}

// int validate_inputs(int argc, char **argv)
// {
// 	(void)argv;
// 	if (argc != 2) //check if the amount of argument is correct
// 	{
// 		write(2, "Error\n", 6);
// 		write(2, "Usage: './cub3D file.cub'\n", 26);
// 		return (1);
// 	}
// 	if (!is_cub_file(argv[1])) //check if file is .cub
// 	{
// 		write(2, "Error\n", 6);
// 		write(2, "Invalid file format.\n", 21);
// 		return (1);
// 	}
// 	if (check_permission(argv[1])) //check for file permissions
// 		return (1);
// 	return (0);
// }

// /*
// ** Parse file to load textures and settings
// */
// int parse_file(t_game *game, const char *filename)
// {
// 	int fd;
// 	char *line;
// 	int i;

// 	// Store map path for later use
// 	game->map_path = ft_strdup(filename);
// 	if (!game->map_path)
// 		return (error_handle(game, "Memory allocation failed"));

// 	// Parse textures
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		return (error_handle(game, "Cannot open file"));

// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		i = 0;
// 		while (line[i] && ft_isspace(line[i]))
// 			i++;
		
// 		if (line[i] == '\0')
// 		{
// 			free(line);
// 			continue;
// 		}
		
// 		if (check_textures(line, i, &game->textures))
// 		{
// 			free(line);
// 			close(fd);
// 			return (error_handle(game, "Invalid texture format"));
// 		}
// 		free(line);
// 	}
// 	close(fd);

// 	// Verify all textures are present
// 	if (!textures_present(&game->textures))
// 		return (error_handle(game, "Missing textures or colors"));

// 	return (0);
// }

// /*
// ** Extract map from file and store in game structure
// */
// int load_map(t_game *game, const char *filename)
// {
// 	int rows = 0;
// 	int cols = 0;
// 	int fd;

// 	// Validate overall map structure
// 	if (!validate_map_structure(filename))
// 		return (error_handle(game, "Invalid map structure"));

// 	// Open file to extract the map
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		return (error_handle(game, "Cannot open file"));

// 	// Extract the map grid
// 	game->map.map = extract_map(fd, &rows, &cols);
// 	close(fd);
	
// 	if (!game->map.map)
// 		return (error_handle(game, "Failed to extract map"));

// 	game->map.height = rows;
// 	game->map.width = cols;

// 	// Final validation of the extracted map
// 	if (!validate_map(game->map.map, rows, cols))
// 		return (error_handle(game, "Map validation failed"));

// 	return (0);
// }

// /*
// ** Game loop function
// */
// int game_loop(t_game *game)
// {
// 	// Set up hooks for key events
// 	mlx_hook(game->win, 2, 1L << 0, key_press, game);
// 	mlx_hook(game->win, 17, 0, handle_exit, game);
	
// 	// Initial render
// 	render_frame(game);
	
// 	// Start the MLX loop
// 	mlx_loop(game->mlx);
	
// 	return (0);
// }

// /*
// ** Handle window close event
// */
int handle_exit(t_game *game)
{
	return (clean_exit(game, 0));
}

// /*
// ** Main function
// */
// int main(int argc, char **argv)
// {
// 	t_game game;

// 	// Validate input arguments
// 	if (validate_inputs(argc, argv))
// 		return (1);

// 	// Initialize game structure
// 	init_game(&game);

// 	// Parse textures and settings
// 	if (parse_file(&game, argv[1]))
// 		return (1);
	
// 	// Load and validate map
// 	if (load_map(&game, argv[1]))
// 		return (1);

// 	// Initialize MLX
// 	if (init_mlx(&game))
// 		return (1);

// 	// Initialize player based on map data
// 	init_player(&game);

// 	// Load textures
// 	if (load_textures(&game))
// 		return (1);

// 	// Start game loop
// 	game_loop(&game);

// 	return (0);
// }
