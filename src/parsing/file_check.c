/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:05:17 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/27 10:37:07 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_cub_file(const char *filename)
{
    const char *ext;

	ext = ft_strrchr(filename, '.');

    if (!ext || ext == filename)
        return 0;

    return ft_strcmp(ext, ".cub") == 0;
}

int is_xpm_file(const char *filename)
{
    const char *ext;

	ext = ft_strrchr(filename, '.');

    if (!ext || ext == filename)
        return 0;

    return ft_strcmp(ext, ".xpm") == 0;
}

int check_permission(const char *filename)
{
	if (open(filename, O_RDONLY) == -1) //check for file permissions
	{
		printf("Cannot open file\n");
		return (1);
	}

	return (0);
}

int textures_present(t_textures *textures)
{
	if (textures->is_no == 1 && textures->is_so == 1
		&& textures->is_ea == 1 && textures->is_we == 1
		&& textures->is_c == 1 && textures->is_c == 1)
		return (1);
	return (0);
}

t_textures  *init_textures(void)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	if (!textures)
		return (NULL);
	textures->is_no = 0;
	textures->is_so = 0;
	textures->is_ea = 0;
	textures->is_we = 0;
	return (textures);
}

int check_textures(const char *line, int i, t_textures *textures)
{
	char texture[3];
	int j;
	int y;

	j = 0;
	y = i + 2;

	while (i < y)
		texture[j++] = line[i++];
	texture[j] = '\0';

	while (line[i] && ft_isspace(line[i])) //skips whitespace between NO && path
		i++;

	y = i;
	j = 0;

	while (line[i] && !ft_isspace(line[i])) // Get size of path
    {
        i++;
        j++;
    }

    if (ft_strcmp(texture, "NO") == 0)
    {
        textures->is_no = 1;
        textures->path_no = malloc(sizeof(char) * (j + 1)); // Allocate +1 for '\0'
        if (!textures->path_no)
            return (1);
        ft_strncpy(textures->path_no, &line[y], j);
        textures->path_no[j] = '\0';
        printf("path->no = %s\n", textures->path_no);
    }
    if (ft_strcmp(texture, "SO") == 0)
    {
        textures->is_so = 1;
        textures->path_so = malloc(sizeof(char) * (j + 1));
        if (!textures->path_so)
            return (1);
        ft_strncpy(textures->path_so, &line[y], j);
        textures->path_so[j] = '\0';
        printf("path->so = %s\n", textures->path_so);
    }
    if (ft_strcmp(texture, "EA") == 0)
    {
        textures->is_ea = 1;
        textures->path_ea = malloc(sizeof(char) * (j + 1));
        if (!textures->path_ea)
            return (1);
        ft_strncpy(textures->path_ea, &line[y], j);
        textures->path_ea[j] = '\0';
        printf("path->ea = %s\n", textures->path_ea);
    }
    if (ft_strcmp(texture, "WE") == 0)
    {
        textures->is_we = 1;
        textures->path_we = malloc(sizeof(char) * (j + 1));
        if (!textures->path_we)
            return (1);
        ft_strncpy(textures->path_we, &line[y], j);
        textures->path_we[j] = '\0';
        printf("path->we = %s\n", textures->path_we);
    }
	if (ft_strcmp(texture, "F ") == 0)
    {
        textures->is_f = 1;
        textures->color_f = malloc(sizeof(char) * (j + 1));
        if (!textures->color_f)
            return (1);
        ft_strncpy(textures->color_f, &line[y], j);
        textures->color_f[j] = '\0';
        printf("color->f = %s\n", textures->color_f);
    }
	if (ft_strcmp(texture, "C ") == 0)
    {
        textures->is_c = 1;
        textures->color_c = malloc(sizeof(char) * (j + 1));
        if (!textures->color_c)
            return (1);
        ft_strncpy(textures->color_c, &line[y], j);
        textures->color_c[j] = '\0';
        printf("color->c = %s\n", textures->color_c);
    }
	
	return (0);
}
