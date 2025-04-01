/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:55:02 by trouilla          #+#    #+#             */
/*   Updated: 2025/04/01 10:55:48 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Initialize DDA step and side distance in X direction */
void	init_dda_x(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x)
			* ray->delta_dist_x;
	}
}

/* Initialize DDA step and side distance in Y direction */
void	init_dda_y(t_game *game, t_ray *ray)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y)
			* ray->delta_dist_y;
	}
}

/* Check if ray hit a wall or map boundary */
int	check_ray_hit(t_game *game, t_ray *ray)
{
	if (ray->map_y < 0 || ray->map_y >= game->map.height || ray->map_x < 0
		|| ray->map_x >= game->map.width)
		return (1);
	else if (game->map.map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

/* Perform Digital Differential Analysis algorithm to find wall hits */
void	perform_dda(t_game *game, t_ray *ray)
{
	init_dda_x(game, ray);
	init_dda_y(game, ray);
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (check_ray_hit(game, ray))
			ray->hit = 1;
	}
}
