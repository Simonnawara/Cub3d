/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:09:40 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/02 11:59:03 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	flood_fill(char **map, int y, int x, int rows, int cols)
{
	int	up;
	int	right;
	int	down;
	int	left;

	if (y < 0 || y >= rows || x < 0 || x >= cols)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (1);
	if (map[y][x] == ' ')
		return (0);
	map[y][x] = 'X';
	up = flood_fill(map, y - 1, x, rows, cols);
	right = flood_fill(map, y, x + 1, rows, cols);
	down = flood_fill(map, y + 1, x, rows, cols);
	left = flood_fill(map, y, x - 1, rows, cols);
	return (up && right && down && left);
}

char	**allocate_map_copy(int rows, int cols)
{
	char	**map_copy;
	int		row;

	map_copy = (char **)malloc(sizeof(char *) * rows);
	if (!map_copy)
		return (NULL);
	row = 0;
	while (row < rows)
	{
		map_copy[row] = (char *)malloc(sizeof(char) * (cols + 1));
		if (!map_copy[row])
		{
			while (--row >= 0)
				free(map_copy[row]);
			free(map_copy);
			return (NULL);
		}
		row++;
	}
	return (map_copy);
}

char	**duplicate_map(char **map, int rows, int cols)
{
	char	**map_copy;
	int		row;
	int		col;

	map_copy = allocate_map_copy(rows, cols);
	if (!map_copy)
		return (NULL);
	row = 0;
	while (row < rows)
	{
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

void	print_map(char **map, int rows, int cols)
{
	int	y;
	int	x;

	if (!map)
	{
		print_error("Null map received.");
		return ;
	}
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			printf("%c", map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}
