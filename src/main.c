/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:37:23 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/26 13:51:41 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_cub_file(const char *filename)
{
    const char *ext;
	
	ext = ft_strrchr(filename, '.'); // Find last occurrence of '.'
    
    if (!ext || ext == filename) // Check if '.' exists and is not the first char
        return 0;
    
    return ft_strcmp(ext, ".cub") == 0; // Compare with ".cub"
}

int validate_inputs(int argc, char **argv)
{	
	(void)argv;
	if (argc != 2)
	{
		write(2, "Error\n", 6);
		write(2, "Usage: './cub3D file.cub'\n", 26);
		return (1);	
	}
	

	if (is_cub_file(argv[1]))
		printf("Valid .cub file\n");
	else
		printf("Invalid format\n");
	
	return (0);
}

int main(int argc, char **argv)
{
	if (validate_inputs(argc, argv))
		return (1);
}
