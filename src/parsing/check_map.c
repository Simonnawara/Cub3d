/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:43:14 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/27 20:22:16 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Function to check if a line is a map line
int is_map_line(const char *line)
{
    int has_valid_char = 0;

    while (*line)
    {
        if (*line == '0' || *line == '1' || *line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
            has_valid_char = 1;
        else if (!ft_isspace(*line)) // Any invalid character found
            return (0);
        line++;
    }
    return (has_valid_char); // Return true only if at least one valid map character is found
}

// Function to check if a line is a texture/config line
int is_texture_line(const char *line)
{
	while (*line && ft_isspace(*line)) // Skip leading spaces
		line++;

    return (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 ||
            strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0 ||
            strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0);
}

char **allocate_map(int rows, int cols)
{
    char **map = (char **)malloc(sizeof(char *) * rows);
    if (!map)
        return (NULL);
    for (int i = 0; i < rows; i++)
    {
        map[i] = (char *)malloc(sizeof(char) * (cols + 1));
        if (!map[i])
            return (NULL);
		ft_memset(map[i], ' ', cols); // Fill with spaces to avoid garbage values
		map[i][cols] = '\0';
    }
    return (map);
}


char **extract_map(int fd, int *rows, int *cols)
{
    char *line;
    char **map;
    int row = 0, col_len = 0, i;

	(void)cols;
    // First pass: determine dimensions
    while ((line = get_next_line(fd)) != NULL)
    {
        if (is_map_line(line))
        {
            int len = ft_strlen(line);
            if (len > col_len)
                col_len = len; // Get max width of the map
            (*rows)++;
        }
        free(line);
    }
    if (*rows == 0)
        return (NULL);

    // Allocate map
    map = allocate_map(*rows, col_len);
    if (!map)
        return (NULL);

    // Reset file descriptor
    lseek(fd, 0, SEEK_SET);

    // Second pass: fill map array
    row = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (is_map_line(line))
        {
            i = 0;
            while (line[i] && line[i] != '\n')
            {
                map[row][i] = line[i];
                i++;
            }
            while (i < col_len) // Fill remaining spaces with empty spaces
                map[row][i++] = ' ';
            map[row][i] = '\0';
            row++;
        }
        free(line);
    }
    return (map);
}

// Function to check if a file has a valid map structure
int validate_map_structure(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (0);
    }

    char *line;
    int map_started = 0, valid_map_found = 0;
    int rows = 0, cols = 0;
    char **map = NULL;

    // First pass: Identify map section and count rows/cols
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] == '\0' || line[0] == '\n') // Ignore empty lines
        {
            free(line);
            continue;
        }

        if (is_map_line(line)) // Found a map line
        {
            map_started = 1;
            valid_map_found = 1;
            int len = ft_strlen(line);
            if (line[len - 1] == '\n') // Adjust length if newline exists
                len--;
            if (len > cols)
                cols = len; // Find longest row (including leading spaces)
            rows++;
        }
        else if (map_started && is_texture_line(line)) // Config after map
        {
            printf("Error: Configuration lines found after map starts.\n");
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

    // Second pass: Extract the map
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error reopening file");
        return (0);
    }

    map = allocate_map(rows, cols);
    if (!map)
    {
        printf("Error: Failed to allocate memory for map.\n");
        close(fd);
        return (0);
    }

    int row = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_map_line(line))
		{
			int len = ft_strlen(line);
			if (line[len - 1] == '\n') // Remove trailing newline
				line[len - 1] = '\0';

			ft_strcpy(map[row], line); // Copy the line

			// 🔹 Fix: Ensure all rows have the same length
			int actual_len = ft_strlen(line);
			if (actual_len < cols)
				ft_memset(map[row] + actual_len, ' ', cols - actual_len); // Pad with spaces

			row++;
		}
		free(line);
	}
    close(fd);

    // Debugging: Print the processed map
    for (int i = 0; i < rows; i++)
    {
        printf("%s\n", map[i]); // Print normally without extra newlines
    }

    // Validate the extracted map
    if (!validate_map(map, rows, cols))
    {
        printf("Error: Map is invalid (characters or walls issue).\n");
        return (0);
    }

    printf("Map is valid and enclosed by walls.\n");
    return (1);
}
