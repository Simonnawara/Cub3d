/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:43:14 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/03 10:25:27 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**extract_map(int fd, int *rows, int *cols, t_textures *textures)
{
	char	**map;

	(void)textures;
	*rows = count_map_rows(fd, cols);
	if (*rows <= 0)
	{
		if (*rows == 0)
			printf("Error: No valid map lines found\n");
		return (NULL);
	}
	lseek(fd, 0, SEEK_SET);
	map = fill_map_data(fd, *rows, *cols);
	return (map);
}

int	check_empty_line(char *line)
{
	int	is_empty;
	int	i;

	is_empty = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
		{
			is_empty = 0;
			break ;
		}
		i++;
	}
	return (is_empty);
}

int	handle_map_section(char *line, int *map_started, int *map_section_ended,
		int *valid_map_found)
{
	int	line_status;

	line_status = is_map_line(line);
	if (line_status == 1)
	{
		if (*map_section_ended)
			return (print_return_free("Empty line found in the map.", 0, line));
		*map_started = 1;
		*valid_map_found = 1;
	}
	else if (*map_started && line_status == -1)
		return (print_return_free("Invalid character in map line", 0, line));
	else if (*map_started && is_texture_line(line))
		return (print_return_free
			("Configuration lines found after map starts.", 0, line));
	else if (line_status == -2)
		return (print_return_free("Invalid line detected in file", 0, line));
	return (1);
}

int	validate_map_structure(const char *filename)
{
	char	*line;
	int		fd;
	int		map_stat[3];

	init_map_status(map_stat);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_return_error("Error opening file", 0));
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (check_empty_line(line))
		{
			if (map_stat[0])
				map_stat[2] = 1;
			free(line);
			continue ;
		}
		if (!handle_map_section(line, &map_stat[0], &map_stat[2], &map_stat[1]))
			return (close_return(fd, 0));
		free(line);
	}
	return (close_return_stat(fd, map_stat[1]));
}
