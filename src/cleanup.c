/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:20:04 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/28 13:29:49 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    free_map(t_map *map)
{
    int    i;
    if (!map->grid)
        return ;

    i = 0;
    while (i < map->height)
    {
        if (map->grid[i])
            free(map->grid[i]);
        i++;
    }
    free(map->grid);
    map->grid = NULL;
}

void free_textures(t_game *game)
{
    if (game->textures.path_no)
        free(game->textures.path_no);
    if (game->textures.path_so)
        free(game->textures.path_so);
    if (game->textures.path_ea)
        free(game->textures.path_ea);
    if (game->textures.path_we)
        free(game->textures.path_we);
    if (game->textures.color_f)
        free(game->textures.color_f);
    if (game->textures.color_c)
        free(game->textures.color_c);
}
void    free_images(t_game *game)
{
    if (game->mlx)
    {
        if (game->img.img)
            mlx_destroy_image(game->mlx, game->img.img);
        if (game->tex_north.img)
            mlx_destroy_image(game->mlx, game->tex_north.img);
        if (game->tex_south.img)
            mlx_destroy_image(game->mlx, game->tex_south.img);
        if (game->tex_east.img)
            mlx_destroy_image(game->mlx, game->tex_east.img);
        if (game->tex_west.img)
            mlx_destroy_image(game->mlx, game->tex_west.img);
        if (game->win)
            mlx_destroy_window(game->mlx, game->win);
    }
}

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

int	error_handle(t_game *game, char *error_message)
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
