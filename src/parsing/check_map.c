/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:43:14 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/02 14:27:08 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map_1(char **map, int rows)
{
	for (int i = 0; i < rows; i++)
		free(map[i]);
	free(map);
}

int	return_char_value(int has_valid_char, int has_invalid_char)
{
	if (has_invalid_char && !has_valid_char)
		return (-2);
	if (has_invalid_char)
		return (-1);
	if (has_valid_char)
		return (1);
	else
		return (0);
}

// Function to check if a line is a map line
int	is_map_line(const char *line)
{
	int	has_valid_char;
	int	has_invalid_char;

	has_valid_char = 0;
	has_invalid_char = 0;
	while (*line && ft_isspace(*line))
		line++;
	if (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0
		|| strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0
		|| strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0)
		return (0);
	while (*line)
	{
		if (*line == '0' || *line == '1' || *line == 'N' || *line == 'S'
			|| *line == 'E' || *line == 'W' || ft_isspace(*line))
		{
			if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
				has_valid_char = 1;
		}
		else
			has_invalid_char = 1;
		line++;
	}
	return (return_char_value(has_valid_char, has_invalid_char));
}

// Function to check if a line is a texture/config line
int	is_texture_line(const char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	return (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0
		|| strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0
		|| strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0);
}

char	**allocate_map(int rows, int cols)
{
	int		i;
	char	**map;

	i = 0;
	map = (char **)malloc(sizeof(char *) * rows);
	if (!map)
		return (NULL);
	while (i < rows)
	{
		map[i] = (char *)malloc(sizeof(char) * (cols + 1));
		if (!map[i])
			return (NULL);
		ft_memset(map[i], ' ', cols);
		map[i][cols] = '\0';
		i++;
	}
	return (map);
}

char	**extract_map(int fd, int *rows, int *cols, t_textures *textures)
{
	char	*line;
	char	**map;
	int		row;
	int		col_len;
	int		line_status;
	int		map_started;
	int		len;
	int		i;

	(void)textures;
	row = 0;
	col_len = 0;
	map_started = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line_status = is_map_line(line);
		if (line_status == 1)
		{
			map_started = 1;
			len = ft_strlen(line);
			if (len > col_len)
				col_len = len;
			(*rows)++;
		}
		else if (map_started && line_status == -1)
		{
			printf("Error: Invalid character in map line: %s", line);
			free(line);
			return (NULL);
		}
		if (line_status == -2)
		{
			printf("Error: Invalid line in map: %s\n", line);
			free(line);
			return (NULL);
		}
		free(line);
	}
	*cols = col_len;
	if (*rows == 0)
	{
		printf("Error: No valid map lines found\n");
		return (NULL);
	}
	map = allocate_map(*rows, col_len);
	if (!map)
		return (NULL);
	lseek(fd, 0, SEEK_SET);
	row = 0;
	map_started = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line_status = is_map_line(line);
		if (line_status == 1)
		{
			map_started = 1;
			i = 0;
			while (line[i] && line[i] != '\n')
			{
				map[row][i] = line[i];
				i++;
			}
			while (i < col_len)
				map[row][i++] = ' ';
			map[row][i] = '\0';
			row++;
		}
		else if (map_started && line_status == -1)
		{
			printf("Error: Invalid character in map line: %s", line);
			free(line);
			free_map_1(map, *rows);
			return (NULL);
		}
		free(line);
	}
	return (map);
}

int	validate_map_structure(const char *filename)
{
	char	*line;
	int		map_started;
	int		valid_map_found;
	int		map_section_ended;
	int		line_status;
	int		fd;
	int		is_empty;
	int		i;

	map_started = 0;
	valid_map_found = 0;
	map_section_ended = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (0);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
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
		if (is_empty)
		{
			if (map_started)
				map_section_ended = 1;
			free(line);
			continue ;
		}
		line_status = is_map_line(line);
		if (line_status == 1)
		{
			if (map_section_ended)
			{
				printf("Error: Empty line found within the map.\n");
				free(line);
				close(fd);
				exit(1);
			}
			map_started = 1;
			valid_map_found = 1;
		}
		else if (map_started && line_status == -1)
		{
			printf("Error: Invalid character in map line: %s", line);
			free(line);
			close(fd);
			return (0);
		}
		else if (map_started && is_texture_line(line))
		{
			printf("Error: Configuration lines found after map starts.\n");
			free(line);
			close(fd);
			return (0);
		}
		else if (line_status == -2)
		{
			printf("Error: Invalid line detected in file: %s\n", line);
			free(line);
			close(fd);
			return (0);
		}
		free(line);
	}
	close(fd);
	if (!valid_map_found)
	{
		printf("Error: No map found in the file.\n");
		return (0);
	}
	return (1);
}
