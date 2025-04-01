/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:43:14 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/01 12:40:08 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_map_1(char **map, int rows)
{
    for (int i = 0; i < rows; i++)
        free(map[i]);
    free(map);
}

// Function to check if a line is a map line
int is_map_line(const char *line)
{
    int has_valid_char = 0;
    int has_invalid_char = 0;

    // First check if this is a texture line
    while (*line && ft_isspace(*line)) // Skip leading spaces
        line++;

    // Check if this is a texture identifier line
    if (strncmp(line, "NO ", 3) == 0 || strncmp(line, "SO ", 3) == 0 ||
        strncmp(line, "WE ", 3) == 0 || strncmp(line, "EA ", 3) == 0 ||
        strncmp(line, "F ", 2) == 0 || strncmp(line, "C ", 2) == 0)
        return (0); // Not a map line, but a valid texture line

    // If not a texture line, check if it's a valid map line
    while (*line)
    {
        if (*line == '0' || *line == '1' || *line == 'N' || *line == 'S' ||
            *line == 'E' || *line == 'W' || ft_isspace(*line))
        {
            if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
                has_valid_char = 1;
        }
        else
        {
            has_invalid_char = 1;
        }
        line++;
    }

    if (has_invalid_char)
        return (-1);  // Invalid map line (contains characters that are not valid)
    return (has_valid_char ? 1 : 0);  // 1 if valid map line, 0 if blank/whitespace line
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

char **extract_map(int fd, int *rows, int *cols, t_textures *textures)
{
	(void)textures;
    char *line;
    char **map;
    int row = 0, col_len = 0, i;
    int line_status;
    int map_started = 0;

    // First pass: determine dimensions and check for invalid characters
    while ((line = get_next_line(fd)) != NULL)
    {
        line_status = is_map_line(line);

        if (line_status == 1)  // Valid map line
        {
            map_started = 1;
            int len = ft_strlen(line);
            if (len > col_len)
                col_len = len; // Get max width of the map
            (*rows)++;
        }
        else if (map_started && line_status == -1)  // Invalid map character, but only if we're in the map section
        {
            printf("Error: Invalid character in map line: %s", line);
            free(line);
            return (NULL);
        }
        // Skip non-map lines
        free(line);
    }
    *cols = col_len;
    if (*rows == 0)
    {
        printf("Error: No valid map lines found\n");
        return (NULL);
    }

    // Allocate map
    map = allocate_map(*rows, col_len);
    if (!map)
        return (NULL);

    // Reset file descriptor
    lseek(fd, 0, SEEK_SET);

    // Second pass: fill map array
    row = 0;
    map_started = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        line_status = is_map_line(line);

        if (line_status == 1)  // Valid map line
        {
            map_started = 1;
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
        else if (map_started && line_status == -1)  // Invalid map character after map started
        {
            printf("Error: Invalid character in map line: %s", line);
            free(line);
            free_map_1(map, *rows);
            return (NULL);
        }
        // Skip non-map lines
        free(line);
    }
    return (map);
}

int validate_map_structure(const char *filename, t_textures *textures)
{
	(void)textures;
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (0);
    }

    char *line;
    int map_started = 0, valid_map_found = 0;
    int line_status;
    int map_section_ended = 0;  // Flag to track if we've exited the map section

    // Check for correct sequence: textures first, then map
    while ((line = get_next_line(fd)) != NULL)
    {
        int is_empty = (line[0] == '\0' || (line[0] == '\n' && line[1] == '\0'));

        if (is_empty) // Handle empty lines
        {
            if (map_started)
                map_section_ended = 1;
            free(line);
            continue;
        }

        line_status = is_map_line(line);

        if (line_status == 1) // Found a valid map line
        {
            // Check for empty lines within the map
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
        else if (map_started && line_status == -1) // Invalid character only matters in the map section
        {
            printf("Error: Invalid character in map line: %s", line);
            free(line);
            close(fd);
            return (0);
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

    return (1);
}