/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:26:56 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/29 14:03:04 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_valid_rgb_component(const char *str)
{
	int num;

	// Check if the string is empty
	if (!str || *str == '\0')
		return (0);

	// Check if the string contains only digits
	for (int i = 0; str[i]; i++)
	{
		if (!isdigit(str[i]))
			return (0);
	}

	// Convert to integer and check range
	num = ft_atoi(str);
	if (num < 0 || num > 255)
		return (0);

	return (1);
}

int *rgb_split(const char *rgb_str)
{
	int *rgb;
	char **split;
	int i;

	// Null check
	if (!rgb_str)
		return (NULL);

	// Check for invalid characters (only digits, commas allowed)
	for (int i = 0; rgb_str[i]; i++)
	{
		if (!isdigit(rgb_str[i]) && rgb_str[i] != ',')
			return (NULL);
	}

	// Split the input string
	split = ft_split(rgb_str, ',');
	if (!split)
		return (NULL);

	// Count the number of elements
	for (i = 0; split[i]; i++);
	if (i != 3) // Must be exactly 3 components
	{
		free(split);
		return (NULL);
	}

	// Allocate memory for RGB values
	rgb = (int *)malloc(sizeof(int) * 3);
	if (!rgb)
	{
		free(split);
		return (NULL);
	}

	// Validate and convert each part
	for (i = 0; i < 3; i++)
	{
		if (!is_valid_rgb_component(split[i]))
		{
			free(split);
			free(rgb);
			return (NULL);
		}
		rgb[i] = ft_atoi(split[i]);
		free(split[i]);
	}

	free(split);

	if (rgb)
		printf("R: %d, G: %d, B: %d\n", rgb[0], rgb[1], rgb[2]);
	else
		printf("Invalid RGB input!\n");

	return (rgb);
}
