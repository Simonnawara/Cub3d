/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:43:14 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/02 17:19:56 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map_1(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
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
