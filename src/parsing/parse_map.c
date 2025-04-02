/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:09:40 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/02 14:12:49 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	flood_fill(char **map, t_cord *cord, int rows, int cols)
{
	int	up;
	int	right;
	int	down;
	int	left;
	t_cord new_cord;

	if (cord->y < 0 || cord->y >= rows || cord->x < 0 || cord->x >= cols)
		return (0);
	if (map[cord->y][cord->x] == '1' || map[cord->y][cord->x] == 'X')
		return (1);
	if (map[cord->y][cord->x] == ' ')
		return (0);
	map[cord->y][cord->x] = 'X';
	new_cord = *cord;
	new_cord.y = cord->y - 1;
	up = flood_fill(map, &new_cord, rows, cols);
	new_cord.y = cord->y + 1;
	down = flood_fill(map, &new_cord, rows, cols);
	new_cord.y = cord->y;
	new_cord.x = cord->x + 1;
	right = flood_fill(map, &new_cord, rows, cols);
	new_cord.x = cord->x - 1;
	left = flood_fill(map, &new_cord, rows, cols);
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
