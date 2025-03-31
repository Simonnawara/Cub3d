/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:37:31 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/31 14:52:22 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Move player forward or backward with improved collision detection
*/
void	move_player(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * move_speed;
	new_y = game->player.pos_y + game->player.dir_y * move_speed;
	if (is_valid_move(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_move(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/*
** Strafe player left or right with improved handling
*/
void	strafe_player(t_game *game, double strafe_speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->camera.plane_x * strafe_speed;
	new_y = game->player.pos_y + game->camera.plane_y * strafe_speed;
	if (is_valid_move(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_move(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/* Normalize direction vector */
void	normalize_dir_vector(t_player *player)
{
	double	dir_length;

	dir_length = sqrt(player->dir_x * player->dir_x + player->dir_y
			* player->dir_y);
	player->dir_x /= dir_length;
	player->dir_y /= dir_length;
}

/* Orthogonalize and scale camera plane */
void	adjust_camera_plane(t_player *player, t_camera *camera)
{
	double	plane_dot_dir;
	double	plane_length;

	plane_dot_dir = camera->plane_x * player->dir_x + camera->plane_y
		* player->dir_y;
	camera->plane_x -= plane_dot_dir * player->dir_x;
	camera->plane_y -= plane_dot_dir * player->dir_y;
	plane_length = sqrt(camera->plane_x * camera->plane_x + camera->plane_y
			* camera->plane_y);
	camera->plane_x = camera->plane_x * 0.66 / plane_length;
	camera->plane_y = camera->plane_y * 0.66 / plane_length;
}

/* Rotate player view left or right */
void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->camera.plane_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y
		* cos(rot_speed);
	game->camera.plane_x = game->camera.plane_x * cos(rot_speed)
		- game->camera.plane_y * sin(rot_speed);
	game->camera.plane_y = old_plane_x * sin(rot_speed) + game->camera.plane_y
		* cos(rot_speed);
	normalize_dir_vector(&game->player);
	adjust_camera_plane(&game->player, &game->camera);
}
