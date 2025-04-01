/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:00:38 by trouilla          #+#    #+#             */
/*   Updated: 2025/04/01 11:01:29 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Draw a vertical stripe for a wall
void	draw_ceiling(t_game *game, int x, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(&game->img, x, y, game->ceiling_color);
		y++;
	}
}

/* Draw floor part of the wall stripe */
void	draw_floor(t_game *game, int x, t_ray *ray)
{
	int	y;

	y = ray->draw_end;
	while (y < HEIGHT)
	{
		put_pixel(&game->img, x, y, game->floor_color);
		y++;
	}
}

/* Draw textured wall part of the stripe */
void	draw_textured_wall(t_game *game, int x, t_ray *ray, t_tex_pos *tex)
{
	int	y;
	int	color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->img->height - 1);
		tex->pos += tex->step;
		color = get_pixel_color(tex->img, tex->x, tex->y);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&game->img, x, y, color);
		y++;
	}
}

/* Draw a vertical stripe for a wall */
void	draw_wall_stripe(t_game *game, int x, t_ray *ray)
{
	t_tex_pos	tex;

	draw_ceiling(game, x, ray);
	calculate_texture_position(game, ray, &tex);
	draw_textured_wall(game, x, ray, &tex);
	draw_floor(game, x, ray);
}
