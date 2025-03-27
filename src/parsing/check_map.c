/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:43:14 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/27 15:05:19 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Function to check if a line is a map line

/* int is_map_line(const char *line)
{
    // Skip leading spaces
    while (*line && isspace(*line))
        line++;

    // Check if it's a valid map line
    while (*line)
    {
        if (*line != '0' && *line != '1' &&
            *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W' &&
            *line != ' ')
            return (0); // Not a valid map line
        line++;
    }
    return (1);
} */

int is_map_line(const char *line)
{
    // Skip leading spaces
    while (*line && ft_isspace(*line))
        line++;

    // If the line is empty after trimming, it's NOT a valid map line
    if (*line == '\0')
        return (0);

    // Check if it's a valid map line (only contains map characters)
    while (*line)
    {
        if (*line != '0' && *line != '1' &&
            *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W' &&
            *line != ' ')
            return (0); // Not a valid map line
        line++;
    }
    return (1);
}

// Function to check if a line is a texture/config line
int is_texture_line(const char *line)
{
    return (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 ||
            strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0 ||
            strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0);
}

// Function to check if a file has a valid map structure
int validate_map_structure(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        return (0);
    }

    char buffer[BUFFER_SIZE_MAP];
    int map_started = 0; // Track if we've entered the map section
    int map_ended = 0;   // Track if a non-map line appears after the map starts

	
	while (fgets(buffer, BUFFER_SIZE_MAP, file))
	{
		// Trim leading whitespace
		int i = 0;
		while (buffer[i] && ft_isspace(buffer[i]))
			i++;

		// If it's an empty line, skip it
		if (buffer[i] == '\0' || buffer[i] == '\n')
		{
			if (map_started) // Allow empty lines *within* the map
				continue;
			else
				continue; // Ignore empty lines before the map starts
		}

		// If we find a texture/config line *after* the map has started, it's invalid
		if (map_started && is_texture_line(buffer + i))
		{
			printf("SOSOSS\n");
			map_ended = 1;
			break;
		}

		// If we find a map line, set `map_started`
		if (is_map_line(buffer + i))
		{
			printf("map has been started\n");
			map_started = 1;
			continue;
		}

		// If a non-map, non-config line is found, mark map as ended
		if (map_started && !is_map_line(buffer + i))
		{
			printf("BUFFER + I : %s\n", buffer + i);
			printf("AOAOAO\n");
			map_ended = 1;
			break;
		}
	}

    fclose(file);
    
    if (!map_started)
    {
        printf("Error: No map found in the file.\n");
        return (0);
    }

    if (map_ended)
    {
        printf("Error: Configuration lines found after map starts.\n");
        return (0);
    }

    return (1); // File structure is valid
}
