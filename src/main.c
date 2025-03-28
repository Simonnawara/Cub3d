/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:37:23 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/28 14:17:29 by trouilla         ###   ########.fr       */
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

int open_file(const char *filename)
{
	int		fd;
	int		i;
	char	*line;
	t_textures *textures;

	fd = open(filename, O_RDONLY);
	textures = init_textures();
	if (!textures)
		return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		i = 0;
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (check_textures(line, i, textures))
		{
			write(2, "Error\n", 6);
			write(2, "Please enter valid textures\n", 28);
			free(line);
			exit(0);
		}
		free(line);
	}

	if (textures_present(textures))
		printf("All textures have been found\n");
	else
		printf("Error, missing textures\n");

	close(fd);
	return (0);
}

int main(int argc, char **argv)
{
	t_game game;
	
	if (validate_inputs(argc, argv))
		return (1);
	init_game(&game);
	open_file(argv[1]);
	if (init_mlx(&game))
		return (1);
	init_player(&game);
	if (load_textures(&game))
		return (1);
	
	return (0);
}
