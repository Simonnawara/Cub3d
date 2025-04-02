/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:43:14 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/02 17:57:43 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	process_map_line(char **map, char *line, int row, int col_len)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		map[row][i] = line[i];
		i++;
	}
	while (i < col_len)
		map[row][i++] = ' ';
	map[row][i] = '\0';
}

int	process_map_row_data(char *line, int *cols, int *map_started)
{
	int	line_status;
	int	len;

	line_status = is_map_line(line);
	if (line_status == 1)
	{
		*map_started = 1;
		len = ft_strlen(line);
		if (len > *cols)
			*cols = len;
		return (1);
	}
	else if (*map_started && line_status == -1)
	{
		print_return_free("Invalid character in map line", -1, line);
		return (-1);
	}
	else if (line_status == -2)
	{
		print_return_free("Invalid line in map", -1, line);
		return (-1);
	}
	return (0);
}

int	count_map_rows(int fd, int *cols)
{
	char	*line;
	int		rows;
	int		map_started;
	int		result;

	rows = 0;
	*cols = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		result = process_map_row_data(line, cols, &map_started);
		if (result == 1)
			rows++;
		else if (result == -1)
			return (-1);
		free(line);
		line = get_next_line(fd);
	}
	return (rows);
}
