/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:50:50 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/12 14:50:50 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*c;
	char	*buffer;

	buffer = malloc(10000);
	c = buffer;
	while (read(fd, c, 1) > 0 && *c++ != '\n')
		;
	if (c > buffer)
	{
		*c = 0;
		return (buffer);
	}
	else
	{
		free(buffer);
		return (NULL);
	}
}
