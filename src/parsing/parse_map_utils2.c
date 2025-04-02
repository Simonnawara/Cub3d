/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:09:40 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/02 13:40:05 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_player_surroundings(char **map, int y, int x)
{
	if (y == 0 || x == 0)
		return (print_return_error(
				"Player starting position cannot be at map boundary", 0));
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' ||
		map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (print_return_error(
				"Player starting position must be enclosed by walls", 0));
	return (1);
}

int	is_player_position_valid(char **map, int rows, int cols)
{
	int	y;
	int	x;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (is_player_char(map[y][x]))
			{
				if (y == rows - 1 || x == cols - 1)
					return (print_return_error(
							"Incorrect player position", 0));
				return (check_player_surroundings(map, y, x));
			}
			x++;
		}
		y++;
	}
	print_error("No player starting position found");
	return (0);
}

int	validate_map(char **map, int rows, int cols)
{
	char	**map_copy;
	int		enclosed;

	print_map(map, rows, cols);
	enclosed = 0;
	if (!validate_map_content(map, rows, cols))
		return (0);
	if (!is_player_position_valid(map, rows, cols))
		return (-3);
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
