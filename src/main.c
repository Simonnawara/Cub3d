/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:37:23 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/26 22:40:41 by sinawara         ###   ########.fr       */
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

void open_file(const char *filename)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		i = 0;
		while (line[i] && ft_isspace(line[i]))
			i++;
		check_textures(line, i);
		free(line);
	}

	close(fd);
}

int main(int argc, char **argv)
{
	if (validate_inputs(argc, argv))
		return (1);

	open_file(argv[1]);
	return (0);
}
