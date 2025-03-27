/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:37:51 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/27 11:12:11 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include "../libft/include/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>

typedef struct s_textures
{
	int is_no;
	int is_so;
	int is_ea;
	int is_we;
	int is_f;
	int is_c;
	char *path_no;
	char *path_so;
	char *path_ea;
	char *path_we;
	char *color_f;
	char *color_c;
} t_textures;

// New map structure
typedef struct s_map {
    char **map;      // 2D array of map characters
    int height;      // Number of rows
    int width;       // Max width of map
} t_map;


// file_check.c //
int is_cub_file(const char *filename);
int is_xpm_file(const char *filename);
int check_permission(const char *filename);
int check_textures(const char *line, int i, t_textures *textures);
t_textures  *init_textures(void);
int textures_present(t_textures *textures);

// free.c //
void free_map_array(char **map, int height);


// New map parsing functions
int parse_map_section(int fd, t_map *map_data);
int validate_map(char **map, int height, int width);
int is_map_line(const char *line);
int is_empty_line(const char *line);
void free_map_array(char **map, int height);


#endif