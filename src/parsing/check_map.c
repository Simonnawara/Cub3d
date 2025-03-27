/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:08:01 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/27 11:22:56 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Check if a line contains only map-valid characters
int is_map_line(const char *line) {
    if (!line) return 0;
    
    while (*line) {
        if (*line != ' ' && *line != '0' && *line != '1' && 
            *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W') {
            return 0;
        }
        line++;
    }
    return 1;
}

// Check if a line is empty or contains only whitespace
int is_empty_line(const char *line) {
    if (!line) return 1;
    
    while (*line) {
        if (!ft_isspace(*line)) {
            return 0;
        }
        line++;
    }
    return 1;
}

// Count player start positions
int count_player_starts(char **map, int height, int width) {
    int player_count = 0;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == 'N' || map[y][x] == 'S' || 
                map[y][x] == 'E' || map[y][x] == 'W') {
                player_count++;
            }
        }
    }
    
    return player_count;
}

// Flood fill to check map enclosure (simplified version)
int flood_fill_check(char **map, int height, int width, int y, int x) {
    // Boundary checks
    if (y < 0 || y >= height || x < 0 || x >= width) return 0;
    
    // Cannot flood through walls
    if (map[y][x] == '1') return 1;
    
    // Prevent infinite recursion
    if (map[y][x] == 'F') return 1;
    
    // Mark as visited
    map[y][x] = 'F';
    
    // Try to flood in 4 directions
    int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    for (int i = 0; i < 4; i++) {
        int new_y = y + directions[i][0];
        int new_x = x + directions[i][1];
        
        // If flood fails in any direction, map is not enclosed
        if (!flood_fill_check(map, height, width, new_y, new_x)) {
            return 0;
        }
    }
    
    return 1;
}

// Validate map integrity
int validate_map(char **map, int height, int width) {
    // Check if map is empty
    if (height == 0 || width == 0) {
        write(2, "Error\nEmpty map\n", 16);
        return 0;
    }
    
    // Check player start positions
    int player_count = count_player_starts(map, height, width);
    if (player_count != 1) {
        write(2, "Error\nInvalid number of player start positions\n", 46);
        return 0;
    }
    
    // Create a copy of the map for flood fill (to avoid modifying original)
    char **map_copy = malloc(height * sizeof(char *));
    for (int y = 0; y < height; y++) {
        map_copy[y] = strdup(map[y]);
    }
    
    // Find a zero or player start position to begin flood fill
    int start_y = -1, start_x = -1;
    for (int y = 0; y < height && start_y == -1; y++) {
        for (int x = 0; x < width; x++) {
            if (map_copy[y][x] == '0' || 
                map_copy[y][x] == 'N' || map_copy[y][x] == 'S' || 
                map_copy[y][x] == 'E' || map_copy[y][x] == 'W') {
                start_y = y;
                start_x = x;
                break;
            }
        }
    }
    
    // If no valid start found, map is invalid
    if (start_y == -1) {
        free_map_array(map_copy, height);
        write(2, "Error\nNo valid map area found\n", 31);
        return 0;
    }
    
    // Perform flood fill check with slightly modified approach
    int is_enclosed = 1;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map_copy[y][x] == '0' || 
                map_copy[y][x] == 'N' || map_copy[y][x] == 'S' || 
                map_copy[y][x] == 'E' || map_copy[y][x] == 'W') {
                // Additional checks for surrounding walls
                if (y == 0 || y == height-1 || x == 0 || x == width-1) {
                    is_enclosed = 0;
                    break;
                }
                
                // Check immediate surrounding cells
                if (map_copy[y-1][x] == ' ' || map_copy[y+1][x] == ' ' ||
                    map_copy[y][x-1] == ' ' || map_copy[y][x+1] == ' ') {
                    is_enclosed = 0;
                    break;
                }
            }
        }
        if (!is_enclosed) break;
    }
    
    // Perform flood fill as a secondary check
    if (is_enclosed) {
        is_enclosed = flood_fill_check(map_copy, height, width, start_y, start_x);
    }
    
    // Free copy and check result
    free_map_array(map_copy, height);
    
    if (!is_enclosed) {
        write(2, "Error\nMap is not fully enclosed\n", 32);
        return 0;
    }
    
    return 1;
}

// Reallocate map lines array
char **realloc_map_lines(char **map_lines, int current_count, const char *new_line) {
    char **new_map_lines = realloc(map_lines, (current_count + 1) * sizeof(char *));
    if (!new_map_lines) {
        write(2, "Error\nMemory allocation failed\n", 31);
        free_map_array(map_lines, current_count);
        exit(1);
    }
    
    new_map_lines[current_count] = strdup(new_line);
    if (!new_map_lines[current_count]) {
        write(2, "Error\nMemory allocation failed\n", 31);
        free_map_array(new_map_lines, current_count);
        exit(1);
    }
    
    return new_map_lines;
}

// Parse map section
int parse_map_section(int fd, t_map *map_data) {
    char *line;
    char **map_lines = NULL;
    int line_count = 0;
    int map_started = 0;
    int max_width = 0;

    // Reset map data
    map_data->map = NULL;
    map_data->height = 0;
    map_data->width = 0;

    // Read file line by line
    while ((line = get_next_line(fd)) != NULL) {
        // Skip leading empty lines
        if (!map_started && is_empty_line(line)) {
            free(line);
            continue;
        }

        // Check if line is a map line
        if (is_map_line(line)) {
            map_started = 1;
            
            // Track max width for rectangular map
            int current_line_len = strlen(line);
            max_width = current_line_len > max_width ? current_line_len : max_width;
            
            // Add line to map lines
            map_lines = realloc_map_lines(map_lines, line_count, line);
            line_count++;
        }
        else if (map_started) {
            // If we've started the map and encounter a non-map line, it's an error
            write(2, "Error\nInvalid content after map started\n", 40);
            free(line);
            free_map_array(map_lines, line_count);
            return 0;
        }

        free(line);
    }

    // Validate and pad map lines to be rectangular
    for (int i = 0; i < line_count; i++) {
        int current_len = strlen(map_lines[i]);
        if (current_len < max_width) {
            map_lines[i] = realloc(map_lines[i], max_width + 1);
            memset(map_lines[i] + current_len, ' ', max_width - current_len);
            map_lines[i][max_width] = '\0';
        }
    }

    // Final map validation
    if (!validate_map(map_lines, line_count, max_width)) {
        free_map_array(map_lines, line_count);
        return 0;
    }

    // Set map data
    map_data->map = map_lines;
    map_data->height = line_count;
    map_data->width = max_width;

    return 1;
}