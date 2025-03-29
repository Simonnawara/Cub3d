/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:43:14 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/29 14:21:46 by trouilla         ###   ########.fr       */
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
        else if (!ft_isspace(*line))  // Any invalid character found
            return (0);
        line++;
    }
    return (has_valid_char);  // Return true only if at least one valid map character is found
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
    *cols = col_len;    
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

    // Check for correct sequence: textures first, then map
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