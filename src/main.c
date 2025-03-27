/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:37:23 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/27 11:11:39 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int validate_inputs(int argc, char **argv)
{
	(void)argv;
	if (argc != 2) //check if the amount of argument is correct
	{
		write(2, "Error\n", 6);
		write(2, "Usage: './cub3D file.cub'\n", 26);
		return (1);
	}

	if (!is_cub_file(argv[1])) //check if file is .cub
	{
		write(2, "Error\n", 6);
		write(2, "Invalid file format.\n", 21);
		return (1);
	}

	if (check_permission(argv[1])) //check for file permissions
		return (1);

	return (0);
}

/* int open_file(const char *filename)
{
	int		fd;
	int		i;
	char	*line;
	t_textures *textures;

	fd = open(filename, O_RDONLY);
	textures = init_textures();
	if (!textures)
	{
		close(fd);
		return (0);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		i = 0;
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (check_textures(line, i, textures))
		{
			write(2, "Error\n", 6);
			write(2, "Please enter valid textures\n", 28);
			free(line);
			exit(0);
		}
		free(line);
	}

	if (textures_present(textures))
		printf("All textures have been found\n");
	else
		printf("Error, missing textures\n");

	close(fd);
	return (0);
} */


int parse_textures(int fd, t_textures *textures) {
    char *line;
    int texture_parsing = 1;

    while (texture_parsing && (line = get_next_line(fd)) != NULL) {
        int i = 0;
        
        // Skip leading whitespace
        while (line[i] && ft_isspace(line[i]))
            i++;
        
        // Skip empty lines
        if (line[i] == '\0') {
            free(line);
            continue;
        }
        
        // Stop parsing textures when we encounter a potential map line
        if (is_map_line(line)) {
            texture_parsing = 0;
            free(line);
            break;
        }
        
        // Check and parse texture/color lines
        if (check_textures(line, i, textures)) {
            write(2, "Error\nInvalid texture or color configuration\n", 44);
            free(line);
            return 0;
        }
        
        free(line);
    }
    
    // Check if all required textures are present
    if (!textures_present(textures)) {
        write(2, "Error\nMissing required textures or colors\n", 41);
        return 0;
    }
    
    return 1;
}

int open_file(const char *filename) {
    int fd;
    t_textures *textures;
    t_map map_data;
    int result = 0;

    // Open file
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        write(2, "Error\nCannot open file\n", 23);
        return 0;
    }

    // Initialize textures
    textures = init_textures();
    if (!textures) {
        close(fd);
        return 0;
    }

    // Parse textures first
    if (!parse_textures(fd, textures)) {
        // Free texture paths and structure
        if (textures->path_no) free(textures->path_no);
        if (textures->path_so) free(textures->path_so);
        if (textures->path_ea) free(textures->path_ea);
        if (textures->path_we) free(textures->path_we);
        if (textures->color_f) free(textures->color_f);
        if (textures->color_c) free(textures->color_c);
        free(textures);
        close(fd);
        return 0;
    }

    // Rewind file to parse map
    lseek(fd, 0, SEEK_SET);
    
    // Skip texture lines again
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        int i = 0;
        while (line[i] && ft_isspace(line[i]))
            i++;
        
        if (check_textures(line, i, textures) == 0) {
            free(line);
            continue;
        }
        
        // We've reached beyond texture parsing
        free(line);
        break;
    }

    // Parse map section
    result = parse_map_section(fd, &map_data);

    // Clean up
    close(fd);

    // Free texture resources
    if (textures->path_no) free(textures->path_no);
    if (textures->path_so) free(textures->path_so);
    if (textures->path_ea) free(textures->path_ea);
    if (textures->path_we) free(textures->path_we);
    if (textures->color_f) free(textures->color_f);
    if (textures->color_c) free(textures->color_c);
    free(textures);

    // Free map if parsing failed
    if (!result && map_data.map) {
        free_map_array(map_data.map, map_data.height);
    }

    return result;
}

int main(int argc, char **argv)
{
	if (validate_inputs(argc, argv))
		return (1);

	open_file(argv[1]);
	return (0);
}
