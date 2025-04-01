/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:20:04 by trouilla          #+#    #+#             */
/*   Updated: 2025/04/01 11:02:58 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Free map grid
*/
void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->map)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->map[i])
			free(map->map[i]);
		i++;
	}
	free(map->map);
	map->map = NULL;
}

/*
** Free textures resources
*/
void	free_textures(t_game *game)
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
	if (game->textures.color_f_array)
		free(game->textures.color_f_array);
	if (game->textures.color_c_array)
		free(game->textures.color_c_array);
}

/*
** Free MLX image resources
*/
void	free_images(t_game *game)
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

/*
** Clean up all resources and exit
*/
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

/*
** Free array created by ft_split
*/
void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
