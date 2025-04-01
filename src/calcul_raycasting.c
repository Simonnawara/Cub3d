/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:57:01 by trouilla          #+#    #+#             */
/*   Updated: 2025/04/01 11:00:00 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Calculate ray direction for a specific x-coordinate

void	calculate_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray->dir_x = game->player.dir_x + game->camera.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->camera.plane_y * camera_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	ray->hit = 0;
}

// Calculate perpendicular distance to the wall
// This avoids fisheye effect

void	calculate_wall_distance(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos_x + (1
					- ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos_y + (1
					- ray->step_y) / 2.0) / ray->dir_y;
	if (ray->perp_wall_dist < 0.1)
		ray->perp_wall_dist = 0.1;
}

// Calculate height of wall stripe on screen

void	calculate_wall_height(t_ray *ray, int screen_height)
{
	ray->line_height = (int)(screen_height / ray->perp_wall_dist);
	if (ray->line_height > 10 * screen_height)
		ray->line_height = 10 * screen_height;
	ray->draw_start = -ray->line_height / 2 + screen_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + screen_height / 2;
	if (ray->draw_end >= screen_height)
		ray->draw_end = screen_height - 1;
}

// Calculate texture coordinates for the wall

void	calculate_texture_position(t_game *game, t_ray *ray, t_tex_pos *tex)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	if (ray->side == 0 && ray->dir_x > 0)
		tex->img = &game->tex_east;
	else if (ray->side == 0 && ray->dir_x <= 0)
		tex->img = &game->tex_west;
	else if (ray->side == 1 && ray->dir_y > 0)
		tex->img = &game->tex_south;
	else
		tex->img = &game->tex_north;
	tex->x = (int)(wall_x * (double)tex->img->width);
	if (tex->x >= tex->img->width)
		tex->x = tex->img->width - 1;
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1
			&& ray->dir_y < 0))
		tex->x = tex->img->width - tex->x - 1;
	tex->step = 1.0 * tex->img->height / ray->line_height;
	tex->pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* tex->step;
}
