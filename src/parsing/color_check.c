/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:26:56 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/02 14:17:27 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_rgb_component(const char *str)
{
	int	num;
	int	i;

	i = 0;
	if (!str || *str == '\0')
		return (0);
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	num = ft_atoi(str);
	if (num < 0 || num > 255)
		return (0);
	return (1);
}

int	*rgb_split(const char *rgb_str)
{
	int		*rgb;
	char	**split;
	int		i;

	if (!rgb_str)
		return (NULL);
	i = 0;
	while (rgb_str[i])
	{
		if (!isdigit(rgb_str[i]) && rgb_str[i] != ',')
			return (NULL);
		i++;
	}
	split = ft_split(rgb_str, ',');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		free(split);
		return (NULL);
	}
	rgb = (int *)malloc(sizeof(int) * 3);
	if (!rgb)
	{
		free(split);
		return (NULL);
	}
	i = 0;
	while (i < 3)
	{
		if (!is_valid_rgb_component(split[i]))
		{
			free(split);
			free(rgb);
			return (NULL);
		}
		rgb[i] = ft_atoi(split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	if (!rgb)
		print_error("Invalid RGB input!");
	return (rgb);
}
