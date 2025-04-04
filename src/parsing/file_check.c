/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:05:17 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/04 14:44:44 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	colors_present(t_textures *textures)
{
	if (textures->is_c == 1 && textures->is_f == 1)
		return (1);
	return (0);
}

void free_textures1(t_textures *textures)
{
    if (!textures)
        return;

    if (textures->path_no)
        free(textures->path_no);
    if (textures->path_so)
        free(textures->path_so);
    if (textures->path_ea)
        free(textures->path_ea);
    if (textures->path_we)
        free(textures->path_we);

    free(textures);
}

t_textures	*init_textures(void)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	if (!textures)
		return (NULL);
	textures->is_no = 0;
	textures->is_so = 0;
	textures->is_ea = 0;
	textures->is_we = 0;
	textures->path_no = NULL;
    textures->path_so = NULL;
    textures->path_ea = NULL;
    textures->path_we = NULL;
	return (textures);
}

int	dispatch_texture_handler(const char *texture, const char *line,
	int y, t_textures *textures)
{
	int	j;

	j = 0;
	while (line[y + j] && !ft_isspace(line[y + j]))
		j++;
	if (ft_strcmp(texture, "NO") == 0)
		return (handle_no_texture(line, y, j, textures));
	if (ft_strcmp(texture, "SO") == 0)
		return (handle_so_texture(line, y, j, textures));
	if (ft_strcmp(texture, "EA") == 0)
		return (handle_ea_texture(line, y, j, textures));
	if (ft_strcmp(texture, "WE") == 0)
		return (handle_we_texture(line, y, j, textures));
	if (ft_strcmp(texture, "F ") == 0)
		return (handle_f_color(line, y, j, textures));
	if (ft_strcmp(texture, "C ") == 0)
		return (handle_c_color(line, y, j, textures));
	return (0);
}

int	check_textures(const char *line, int i, t_textures *textures)
{
	char	texture[3];
	int		j;
	int		y;

	j = 0;
	y = i + 2;
	while (i < y)
		texture[j++] = line[i++];
	texture[j] = '\0';
	while (line[i] && ft_isspace(line[i]))
		i++;
	y = i;
	return (dispatch_texture_handler(texture, line, y, textures));
}
