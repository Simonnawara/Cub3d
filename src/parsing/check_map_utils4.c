/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:43:14 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/03 10:26:19 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_map_status(int map_stat[3])
{
	map_stat[0] = 0;
	map_stat[1] = 0;
	map_stat[2] = 0;
}

int	close_return(int fd, int ret_value)
{
	close(fd);
	return (ret_value);
}

int	close_return_stat(int fd, int map_stat)
{
	close(fd);
	if (!map_stat)
		return (print_return_error("No map found in the file", 0));
	return (1);
}
