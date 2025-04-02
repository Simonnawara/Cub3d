/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:43:14 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/02 17:57:37 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**allocate_map(int rows, int cols)
{
	int		i;
	char	**map;

	i = 0;
	map = (char **)malloc(sizeof(char *) * rows);
	if (!map)
		return (NULL);
	while (i < rows)
	{
		map[i] = (char *)malloc(sizeof(char) * (cols + 1));
		if (!map[i])
			return (NULL);
		ft_memset(map[i], ' ', cols);
		map[i][cols] = '\0';
		i++;
	}
	return (map);
}

char	**init_map_data(int rows, int cols)
{
	char	**map;

	map = allocate_map(rows, cols);
	if (!map)
		return (NULL);
	return (map);
}

int	process_map_line_data(char *line, t_map_data *data)
{
	int	line_status;

	line_status = is_map_line(line);
	if (line_status == 1)
	{
		data->map_started = 1;
		process_map_line(data->map, line, data->row, data->cols);
		(data->row)++;
		return (1);
	}
	else if (data->map_started && line_status == -1)
	{
		printf("Error: Invalid character in map line: %s", line);
		return (-1);
	}
	return (0);
}

char	**fill_map_data(int fd, int rows, int cols)
{
	t_map_data	data;
	char		*line;
	int			result;

	data.map = init_map_data(rows, cols);
	if (!data.map)
		return (NULL);
	data.row = 0;
	data.cols = cols;
	data.map_started = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		result = process_map_line_data(line, &data);
		if (result == -1)
		{
			free(line);
			free_map_1(data.map, rows);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (data.map);
}
