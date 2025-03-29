/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:09:40 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/29 14:12:37 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#include "../includes/cub3d.h"

// // Function to check if the map is enclosed using flood fill
// int flood_fill(char **map, int x, int y, int rows, int cols)
// {
//     if (x < 0 || y < 0 || x >= rows || y >= cols)
//         return (0); // Found an opening at the edges, invalid map

//     if (map[x][y] == '1' || map[x][y] == 'X')
//         return (1); // Wall or already visited

//     map[x][y] = 'X'; // Mark as visited

//     // Recursive check in all 4 directions
//     return (flood_fill(map, x + 1, y, rows, cols) &&
//             flood_fill(map, x - 1, y, rows, cols) &&
//             flood_fill(map, x, y + 1, rows, cols) &&
//             flood_fill(map, x, y - 1, rows, cols));
// }

// // Function to validate if the map is enclosed by walls
// int is_map_enclosed(char **map, int rows, int cols)
// {
//     int x, y;

//     // Find first open space to start flood-fill
//     for (x = 0; x < rows; x++)
//     {
//         for (y = 0; y < cols; y++)
//         {
//             if (map[x][y] == '0' || map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E' || map[x][y] == 'W')
//             {
//                 if (!flood_fill(map, x, y, rows, cols))
//                 {
//                     printf("Error: Map is not enclosed by walls!\n");
//                     return (0);
//                 }
//                 return (1);
//             }
//         }
//     }
//     return (1);
// }

// // Function to validate the characters in the map
// int validate_map_content(char **map, int rows, int cols)
// {
//     int x, y, player_count = 0;

//     for (x = 0; x < rows; x++)
//     {
//         for (y = 0; y < cols; y++)
//         {
//             char c = map[x][y];
//             if (c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '\r')
//             {
//                 printf("Error: Invalid character '%c' in map!\n", c);
//                 return (0);
//             }
//             if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
//                 player_count++;
//         }
//     }
//     printf("nb player : %d\n", player_count);
//     if (player_count != 1)
//     {
//         printf("Error: Map must contain exactly one player start position!\n");
//         return (0);
//     }

//     return (1);
// }

// // Wrapper function to fully validate the map
// int validate_map(char **map, int rows, int cols)
// {
//     if (!validate_map_content(map, rows, cols))
//         return (0);
//     if (!is_map_enclosed(map, rows, cols))
//         return (0);
//     return (1);
// }
int flood_fill(char **map, int x, int y, int rows, int cols)
{
	// Base cases
	if (x < 0 || y < 0 || x >= rows || y >= cols)
		return (0);  // Found an opening
	
	if (map[x][y] == '1' || map[x][y] == 'X')
		return (1);  // Wall or already visited
	
	// Mark as visited
	map[x][y] = 'X';
	
	// Check all four adjacent cells
	int up = flood_fill(map, x - 1, y, rows, cols);
	int right = flood_fill(map, x, y + 1, rows, cols);
	int down = flood_fill(map, x + 1, y, rows, cols);
	int left = flood_fill(map, x, y - 1, rows, cols);
	
	// If any direction leads to an opening, the map is not enclosed
	return (up && right && down && left);
}

/*
** Check if map is enclosed by walls
*/
int is_map_enclosed(char **map, int rows, int cols)
{
	int x, y;
	int is_enclosed = 1;

	
	// Find a starting point (player or empty space)
	x = 0;
	while (x < rows && is_enclosed)
	{
		y = 0;
		while (y < cols && is_enclosed)
		{
			if (map[x][y] == '0' || map[x][y] == 'N' || 
				map[x][y] == 'S' || map[x][y] == 'E' || map[x][y] == 'W')
			{
				is_enclosed = flood_fill(map, x, y, rows, cols);
				if (!is_enclosed)
					printf("Error: Map is not enclosed by walls at or near position [%d,%d]\n", x, y);
				// Continue checking the rest of the map
			}
			y++;
		}
		x++;
	}
	
	return (is_enclosed);
}

int validate_map_content(char **map, int rows, int cols)
{
    int y, x;  // y for rows, x for columns
    int player_count = 0;
    
    printf("Validating map content: %d rows, %d cols\n", rows, cols);
    
    y = 0;  // Iterate through rows
    while (y < rows)
    {
        x = 0;  // Iterate through columns
        while (x < cols)
        {
            printf("Checking position [%d,%d]: '%c'\n", y, x, map[y][x]);
            
            // Check for valid characters
            if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != ' ' && 
                map[y][x] != 'N' && map[y][x] != 'S' && map[y][x] != 'E' && 
                map[y][x] != 'W' && map[y][x] != '\r' && map[y][x] != '\0')
            {
                printf("Error: Invalid character '%c' at position [%d,%d]\n", map[y][x], y, x);
                return (0);
            }
            
            // Count player positions
            if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
            {
                player_count++;
                printf("Found player at [%d,%d]: %c\n", y, x, map[y][x]);
            }
            
            x++;
        }
        y++;
    }
    
    // Check player count
    printf("Player positions found: %d\n", player_count);
    if (player_count != 1)
    {
        printf("Error: Map must contain exactly one player start position!\n");
        return (0);
    }
    
    return (1);  // Valid map content
}

/*
** Complete map validation
*/
int validate_map(char **map, int rows, int cols)
{
	// First check the map content for valid characters and player count
	if (!validate_map_content(map, rows, cols))
		return (0);
	
	// Then check if the map is enclosed by walls
	if (!is_map_enclosed(map, rows, cols))
		return (0);
	
	// If both checks pass, the map is valid
	printf("Map validation successful!\n");
	return (1);
}