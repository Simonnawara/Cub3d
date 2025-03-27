/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:20:04 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/27 14:52:06 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	clean_exit(t_game *game, int status)
{
	free_textures(game);
	free_map(&game->map);
	if (game->map_path)
		free(game->map_path);
	free_images(game);
	exit(status);
	return (status);
}

int	error_handler(t_game *game, char *error_message)
{
	ft_printf("Error\n%s\n", error_message);
	return (clean_exit(game, 1));
}

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
