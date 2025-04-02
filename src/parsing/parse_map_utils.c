/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:09:40 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/02 13:34:42 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	find_start_position(char **map, int rows, int cols)
{
	int	x;
	int	y;

	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				return (flood_fill(map, y, x, rows, cols));
			x++;
		}
		y++;
	}
	return (1);
}

int	is_map_enclosed(char **map, int rows, int cols)
{
	int	is_enclosed;

	is_enclosed = find_start_position(map, rows, cols);
	if (!is_enclosed)
		printf("Error: Map is not enclosed by walls\n");
	return (is_enclosed);
}

int	check_valid_char(char c, int *player_count)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*player_count)++;
	if (c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S' && c != 'E'
		&& c != 'W' && c != '\r' && c != '\0')
		return (0);
	return (1);
}

int	validate_map_content(char **map, int rows, int cols)
{
	int	y;
	int	x;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			if (!check_valid_char(map[y][x], &player_count))
			{
				print_return_error("Error: Invalid character\n", 0);
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		print_error("Map must contain exactly one player start position!");
		exit(1);
	}
	return (1);
}
