/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:37:23 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/04 15:29:55 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Validate command line arguments and file format
*/
int	validate_inputs(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Error\n", 6);
		write(2, "Usage: './cub3D file.cub'\n", 26);
		return (1);
	}
	if (!is_cub_file(argv[1]))
	{
		write(2, "Error\n", 6);
		write(2, "Invalid file format. Expected .cub extension.\n", 46);
		return (1);
	}
	if (check_permission(argv[1]))
		return (1);
	return (0);
}

/* Check map validation result and return appropriate error message */
int	check_validation_result(t_game *game, int result)
{
	if (result == -1)
		return (error_handle(game, "Map validation failed: Map not enclosed"));
	else if (result == -2)
		return (error_handle(game,
				"Map validation failed: Invalid characters in map"));
	else if (result == -3)
		return (error_handle(game,
				"Map validation failed: Missing or multiple player positions"));
	else if (result < 0)
		return (error_handle(game, "Map validation failed: Unknown error"));
	return (0);
}

/* Extract and validate the map data */
int	load_map(t_game *game, const char *filename)
{
	int	rows;
	int	cols;
	int	fd;
	int	validation_result;

	if (!validate_map_structure(filename))
		return (error_handle(game, "Invalid map structure"));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (error_handle(game, "Cannot open file"));
	rows = 0;
	cols = 0;
	game->map.map = extract_map(fd, &rows, &cols, &game->textures);
	close(fd);
	if (!game->map.map)
		return (error_handle(game, "Failed to extract map"));
	game->map.height = rows;
	game->map.width = cols;
	validation_result = validate_map(game->map.map, rows, cols, game);
	return (check_validation_result(game, validation_result));
}

/*
** Main function
*/
int	main(int argc, char **argv)
{
	t_game	game;

	if (validate_inputs(argc, argv))
		return (1);
	init_game(&game);
	if (parse_file(&game, argv[1]))
	{
		ft_printf("Error: Failed to parse configuration file\n");
		return (1);
	}
	if (load_map(&game, argv[1]))
	{
		ft_printf("Error: Failed to load or validate map\n");
		return (1);
	}
	if (init_mlx(&game))
		return (1);
	init_player(&game);
	if (load_textures(&game))
	{
		ft_printf("Error: Failed to load textures\n");
		return (1);
	}
	game_loop(&game);
	return (0);
}
