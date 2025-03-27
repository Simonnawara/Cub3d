/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:09:40 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/27 20:12:59 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#include "../includes/cub3d.h"

// Function to check if the map is enclosed using flood fill
int flood_fill(char **map, int x, int y, int rows, int cols)
{
    if (x < 0 || y < 0 || x >= rows || y >= cols)
        return (0); // Found an opening at the edges, invalid map

    if (map[x][y] == '1' || map[x][y] == 'X')
        return (1); // Wall or already visited

    map[x][y] = 'X'; // Mark as visited

    // Recursive check in all 4 directions
    return (flood_fill(map, x + 1, y, rows, cols) &&
            flood_fill(map, x - 1, y, rows, cols) &&
            flood_fill(map, x, y + 1, rows, cols) &&
            flood_fill(map, x, y - 1, rows, cols));
}

// Function to validate if the map is enclosed by walls
int is_map_enclosed(char **map, int rows, int cols)
{
    int x, y;

    // Find first open space to start flood-fill
    for (x = 0; x < rows; x++)
    {
        for (y = 0; y < cols; y++)
        {
            if (map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E' || map[x][y] == 'W')
            {
                if (!flood_fill(map, x, y, rows, cols))
                {
                    printf("Error: Map is not enclosed by walls!\n");
                    return (0);
                }
                return (1);
            }
        }
    }
    return (1);
}

// Function to validate the characters in the map
int validate_map_content(char **map, int rows, int cols)
{
    int x, y, player_count = 0;

    for (x = 0; x < rows; x++)
    {
        for (y = 0; y < cols; y++)
        {
            char c = map[x][y];
            if (c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '\r')
            {
                printf("Error: Invalid character '%c' in map!\n", c);
                return (0);
            }
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                player_count++;
        }
    }

    if (player_count != 1)
    {
        printf("Error: Map must contain exactly one player start position!\n");
        return (0);
    }

    return (1);
}

// Wrapper function to fully validate the map
int validate_map(char **map, int rows, int cols)
{
    if (!validate_map_content(map, rows, cols))
        return (0);
    if (!is_map_enclosed(map, rows, cols))
        return (0);
    return (1);
}
