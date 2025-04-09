/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:09:40 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/04 15:57:51 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*init_cord(void)
{
	t_cord	*cord;

	cord = malloc(sizeof(t_cord));
	if (!cord)
		return (NULL);
	cord->x = 0;
	cord->y = 0;
	return (cord);
}

int	find_start_position(char **map, int rows, int cols)
{
	t_cord	*cord;

	cord = init_cord();
	cord->y = 0;
	while (cord->y < rows)
	{
		cord->x = 0;
		while (cord->x < cols)
		{
			if (map[cord->y][cord->x] == '0' || map[cord->y][cord->x] == 'N'
				|| map[cord->y][cord->x] == 'S' || map[cord->y][cord->x] == 'E'
				|| map[cord->y][cord->x] == 'W')
				return (flood_fill(map, cord, rows, cols));
			cord->x++;
		}
		cord->y++;
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

int	validate_map_content(char **map, int rows, int cols, t_game *game)
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
				return (print_return_error("Error: Invalid character\n", 0));
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		print_error("Map must contain exactly one player start position!");
		clean_exit(game, 1);
	}
	return (1);
}
