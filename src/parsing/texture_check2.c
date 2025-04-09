/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_check2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:38:00 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/02 11:39:24 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_f_color(const char *line, int y, int j, t_textures *textures)
{
	textures->is_f = 1;
	textures->color_f = malloc(sizeof(char) * (j + 1));
	if (!textures->color_f)
		return (1);
	ft_strncpy(textures->color_f, &line[y], j);
	textures->color_f[j] = '\0';
	textures->color_f_array = rgb_split(textures->color_f);
	if (!textures->color_f_array)
	{
		printf("Error with the color codes\n");
		return (1);
	}
	return (0);
}

int	handle_c_color(const char *line, int y, int j, t_textures *textures)
{
	textures->is_c = 1;
	textures->color_c = malloc(sizeof(char) * (j + 1));
	if (!textures->color_c)
		return (1);
	ft_strncpy(textures->color_c, &line[y], j);
	textures->color_c[j] = '\0';
	textures->color_c_array = rgb_split(textures->color_c);
	if (!textures->color_c_array)
	{
		printf("Error with the color codes\n");
		return (1);
	}
	return (0);
}
