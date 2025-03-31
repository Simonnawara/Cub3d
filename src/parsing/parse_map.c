/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:09:40 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/31 10:50:25 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int flood_fill(char **map, int y, int x, int rows, int cols)
{
    // Base cases
    if (y < 0 || y >= rows || x < 0 || x >= cols)
        return (0);  // Found an opening
    
    if (map[y][x] == '1' || map[y][x] == 'X')
        return (1);  // Wall or already visited
    
    if (map[y][x] == ' ')
        return (0);  // Found an opening
    
    // Mark as visited
    map[y][x] = 'X';
    
    // Check all four adjacent cells - ORDER IS IMPORTANT: y is the row, x is the column
    int up = flood_fill(map, y - 1, x, rows, cols);
    int right = flood_fill(map, y, x + 1, rows, cols);
    int down = flood_fill(map, y + 1, x, rows, cols);
    int left = flood_fill(map, y, x - 1, rows, cols);
    
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
    y = 0;
    while (y < rows && is_enclosed)
    {
        x = 0;
        while (x < cols && is_enclosed)
        {
            if (map[y][x] == '0' || map[y][x] == 'N' || 
                map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
            {
                // Call flood_fill with correct parameter order (y, x)
                is_enclosed = flood_fill(map, y, x, rows, cols);
                if (!is_enclosed)
                    printf("Error: Map is not enclosed by walls at or near position [%d,%d]\n", y, x);
                return (is_enclosed); // Return immediately after finding a position
            }
            x++;
        }
        y++;
    }
    
    return (is_enclosed);
}

int validate_map_content(char **map, int rows, int cols)
{
    int y, x;  // y for rows, x for columns
    int player_count = 0;
    
    y = 0;  // Iterate through rows
    while (y < rows)
    {
        x = 0;  // Iterate through columns
        while (x < cols)
        {
            
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
                player_count++;
            x++;
        }
        y++;
    }
	printf("Player count: %d\n", player_count);
    if (player_count != 1)
    {
        printf("Error: Map must contain exactly one player start position!\n");
        return (0);
    }
    return (1);  // Valid map content
}
char	**duplicate_map(char **map, int rows, int cols)
{
	char	**map_copy;
	int		row;
	int		col;

	map_copy = (char **)malloc(sizeof(char *) * rows);
	if (!map_copy)
		return (NULL);

	row = 0;
	while (row < rows)
	{
		map_copy[row] = (char *)malloc(sizeof(char) * (cols + 1));
		if (!map_copy[row])
		{
			// Free previously allocated rows
			while (--row >= 0)
				free(map_copy[row]);
			free(map_copy);
			return (NULL);
		}

		col = 0;
		while (col < cols)
		{
			map_copy[row][col] = map[row][col];
			col++;
		}
		map_copy[row][col] = '\0';
		row++;
	}
	return (map_copy);
}


/*
** Complete map validation
*/
int validate_map(char **map, int rows, int cols)
{
	char **map_copy;
	int enclosed;

	enclosed = 0;
	if (!validate_map_content(map, rows, cols))
		return (0);
	map_copy = duplicate_map(map, rows, cols);
	if (!map_copy)
		return (0);
	enclosed = is_map_enclosed(map_copy, rows, cols);
	free_map_copy(map_copy, rows);
	if (!enclosed)
		return (-1);
	printf("Map validation successful!\n");
	return (1);
}
