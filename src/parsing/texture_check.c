/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:38:00 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/02 11:41:30 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_no_texture(const char *line, int y, int j, t_textures *textures)
{
	textures->is_no = 1;
	textures->path_no = malloc(sizeof(char) * (j + 1));
	if (!textures->path_no)
		return (1);
	ft_strncpy(textures->path_no, &line[y], j);
	textures->path_no[j] = '\0';
	if (check_permission(textures->path_no)
		&& is_xpm_file(textures->path_no))
		return (1);
	return (0);
}

int	handle_so_texture(const char *line, int y, int j, t_textures *textures)
{
	textures->is_so = 1;
	textures->path_so = malloc(sizeof(char) * (j + 1));
	if (!textures->path_so)
		return (1);
	ft_strncpy(textures->path_so, &line[y], j);
	textures->path_so[j] = '\0';
	if (check_permission(textures->path_so)
		&& is_xpm_file(textures->path_so))
		return (1);
	return (0);
}

int	handle_ea_texture(const char *line, int y, int j, t_textures *textures)
{
	textures->is_ea = 1;
	textures->path_ea = malloc(sizeof(char) * (j + 1));
	if (!textures->path_ea)
		return (1);
	ft_strncpy(textures->path_ea, &line[y], j);
	textures->path_ea[j] = '\0';
	if (check_permission(textures->path_ea)
		&& is_xpm_file(textures->path_ea))
		return (1);
	return (0);
}

int	handle_we_texture(const char *line, int y, int j, t_textures *textures)
{
	textures->is_we = 1;
	textures->path_we = malloc(sizeof(char) * (j + 1));
	if (!textures->path_we)
		return (1);
	ft_strncpy(textures->path_we, &line[y], j);
	textures->path_we[j] = '\0';
	if (check_permission(textures->path_we)
		&& is_xpm_file(textures->path_we))
		return (1);
	return (0);
}
