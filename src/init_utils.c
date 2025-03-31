/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:33:45 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/31 14:37:44 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_games(t_game *game)
{
	game->textures.is_no = 0;
	game->textures.is_so = 0;
	game->textures.is_ea = 0;
	game->textures.is_we = 0;
	game->textures.is_f = 0;
	game->textures.is_c = 0;
	game->textures.path_no = NULL;
	game->textures.path_so = NULL;
	game->textures.path_ea = NULL;
	game->textures.path_we = NULL;
	game->textures.color_f = NULL;
	game->textures.color_c = NULL;
	game->textures.color_f_array = NULL;
	game->textures.color_c_array = NULL;
}

int	parse_color(char *color_str)
{
	int		r;
	int		g;
	int		b;
	char	**split;
	int		color;

	if (!color_str)
		return (-1);
	split = ft_split(color_str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		if (split)
			free_split(split);
		return (-1);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_split(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

int	load_textures(t_game *game)
{
	if (!load_texture(game, &game->tex_north, game->textures.path_no))
		return (error_handle(game, "Failed to load north texture"));
	if (!load_texture(game, &game->tex_south, game->textures.path_so))
		return (error_handle(game, "Failed to load south texture"));
	if (!load_texture(game, &game->tex_east, game->textures.path_ea))
		return (error_handle(game, "Failed to load east texture"));
	if (!load_texture(game, &game->tex_west, game->textures.path_we))
		return (error_handle(game, "Failed to load west texture"));
	game->floor_color = parse_color(game->textures.color_f);
	if (game->floor_color == -1)
		return (error_handle(game, "Invalid floor color format"));
	game->ceiling_color = parse_color(game->textures.color_c);
	if (game->ceiling_color == -1)
		return (error_handle(game, "Invalid ceiling color format"));
	return (0);
}

void	direction_north(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->camera.plane_x = 0.66;
	game->camera.plane_y = 0;
}
