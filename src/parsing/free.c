/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:06:43 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/04 14:45:32 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map_array(char **map, int height)
{
	int	i;

	i = 0;
	if (map)
	{
		while (i < height)
		{
			free(map[i]);
			i++;
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
		return ;
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

int	handle_exit(t_game *game)
{
	return (clean_exit(game, 0));
}

// cleanup_utils.c or similar


void cleanup_textures(t_textures *textures)
{
    // Free texture paths
    if (textures->path_no)
        free(textures->path_no);
    if (textures->path_so)
        free(textures->path_so);
    if (textures->path_ea)
        free(textures->path_ea);
    if (textures->path_we)
        free(textures->path_we);

    // Free color data
    if (textures->color_f)
        free(textures->color_f);
    if (textures->color_c)
        free(textures->color_c);

    // Free color arrays
    if (textures->color_f_array)
        free(textures->color_f_array);
    if (textures->color_c_array)
        free(textures->color_c_array);
}

void cleanup_map(char **map, int rows)
{
    int i;

    if (!map)
        return;

    // Free each row
    for (i = 0; i < rows; i++)
    {
        if (map[i])
            free(map[i]);
    }

    // Free the array of pointers
    free(map);
}
