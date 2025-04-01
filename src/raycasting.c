/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:02:11 by trouilla          #+#    #+#             */
/*   Updated: 2025/04/01 11:01:18 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Cast rays for the entire screen and render the result

void	cast_rays(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		calculate_ray(game, &ray, x);
		perform_dda(game, &ray);
		calculate_wall_distance(&ray, game);
		calculate_wall_height(&ray, HEIGHT);
		draw_wall_stripe(game, x, &ray);
		x++;
	}
}

// Get color from an image at specified coordinates

int	get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;

	if (!img || !img->addr || x < 0 || y < 0 || x >= img->width
		|| y >= img->height)
		return (0x000000);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

/*
** Put a pixel in an image at specified coordinates with bounds checking
*/
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr || x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// Clear image with a specific color

void	clear_image(t_img *img, int color)
{
	int	i;
	int	*dst;
	int	pixel_count;

	if (!img || !img->addr)
		return ;
	dst = (int *)img->addr;
	pixel_count = WIDTH * HEIGHT;
	i = 0;
	while (i < pixel_count)
	{
		dst[i] = color;
		i++;
	}
}
