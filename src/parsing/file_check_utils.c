/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:30:17 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/02 11:41:21 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_cub_file(const char *filename)
{
	const char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ext == filename)
		return (0);
	return (ft_strcmp(ext, ".cub") == 0);
}

int	is_xpm_file(const char *filename)
{
	const char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ext == filename)
		return (0);
	return (ft_strcmp(ext, ".xpm") == 0);
}

int	check_permission(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	close(fd);
	return (0);
}

int	textures_present(t_textures *textures)
{
	if (textures->is_no == 1 && textures->is_so == 1 && textures->is_ea == 1
		&& textures->is_we == 1 && textures->is_c == 1 && textures->is_c == 1)
		return (1);
	return (0);
}
