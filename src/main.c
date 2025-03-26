/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:37:23 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/26 14:52:11 by sinawara         ###   ########.fr       */
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

int validate_inputs(int argc, char **argv)
{	
	(void)argv;
	if (argc != 2)
	{
		write(2, "Error\n", 6);
		write(2, "Usage: './cub3D file.cub'\n", 26);
		return (1);	
	}
	
	if (!is_cub_file(argv[1]))
	{
		write(2, "Error\n", 6);
		write(2, "Invalid file format.\n", 21);
		return (1);
	}
	
	if (open(argv[1], O_RDONLY) == -1)
	{
		printf("Cannot open file\n");
		return (1);
	}
	
	return (0);
}

int main(int argc, char **argv)
{
	if (validate_inputs(argc, argv))
		return (1);
}
