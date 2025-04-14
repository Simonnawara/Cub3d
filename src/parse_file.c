/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:35:45 by trouilla          #+#    #+#             */
/*   Updated: 2025/04/14 11:01:07 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	skip_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

/* Process a single line from the config file */
int	process_config_line(t_game *game, char *line, int fd)
{
	int	i;

	i = skip_whitespace(line);
	if (line[i] == '\0')
	{
		free(line);
		return (0);
	}
	if (check_textures(line, i, &game->textures))
	{
		free(line);
		close(fd);
		return (error_handle(game, "Invalid texture format"));
	}
	free(line);
	return (0);
}

/* Parse the configuration file to load textures and settings */
int	parse_file(t_game *game, const char *filename)
{
	int		fd;
	char	*line;
	int		result;

	game->map_path = ft_strdup(filename);
	if (!game->map_path)
		return (error_handle(game, "Memory allocation failed"));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (error_handle(game, "Cannot open file"));
	line = get_next_line(fd);
	while (line != NULL)
	{
		result = process_config_line(game, line, fd);
		if (result != 0)
			return (result);
		line = get_next_line(fd);
	}
	close(fd);
	if (!textures_present(&game->textures))
		return (error_handle(game, "Missing textures or colors"));
	return (0);
}
