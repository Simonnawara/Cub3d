/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:26:56 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/12 14:35:23 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_split1(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	*rgb_split(const char *rgb_str)
{
	int		*rgb;
	char	**split;
	int		count;

	if (!check_rgb_format(rgb_str))
		return (NULL);
	split = ft_split(rgb_str, ',');
	if (!split)
		return (NULL);
	count = count_rgb_components(split);
	if (count != 3)
	{
		free_split1(split);
		return (NULL);
	}
	rgb = populate_rgb_array(split);
	free_split1(split);
	if (!rgb)
		print_error("Invalid RGB input!");
	return (rgb);
}
