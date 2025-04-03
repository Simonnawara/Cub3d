/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:26:56 by sinawara          #+#    #+#             */
/*   Updated: 2025/04/03 10:46:19 by sinawara         ###   ########.fr       */
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

int	check_rgb_format(const char *rgb_str)
{
	int	i;

	i = 0;
	if (!rgb_str)
		return (0);
	while (rgb_str[i])
	{
		if (!isdigit(rgb_str[i]) && rgb_str[i] != ',')
			return (0);
		i++;
	}
	return (1);
}

int	count_rgb_components(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	*populate_rgb_array(char **split)
{
	int	*rgb;
	int	i;

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
	return (rgb);
}
