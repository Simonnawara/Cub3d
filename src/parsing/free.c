/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:06:43 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/01 11:44:14 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_map_array(char **map, int height) {
    if (map) {
        for (int i = 0; i < height; i++) {
            free(map[i]);
        }
        free(map);
    }
}

/*
** Free a map copy
*/
void	free_map_copy(char **map_copy, int rows)
{
	int	row;

	if (!map_copy)
		return;

	row = 0;
	while (row < rows)
	{
		if (map_copy[row])
			free(map_copy[row]);
		row++;
	}
	free(map_copy);
}

/*
** Error handler
*/
int	error_handle(t_game *game, char *error_message)
{
	ft_printf("Error\n%s\n", error_message);
	return (clean_exit(game, 1));
}

int handle_exit(t_game *game)
{
	return (clean_exit(game, 0));
}
