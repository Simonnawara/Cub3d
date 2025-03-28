/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:37:31 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/28 16:39:32 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Define movement constants
*/
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.03
#define WALL_MARGIN 0.2

/*
** Move player forward or backward
*/
void move_player(t_game *game, double move_speed)
{
	double new_x;
	double new_y;

	// Calculate new position
	new_x = game->player.pos_x + game->player.dir_x * move_speed;
	new_y = game->player.pos_y + game->player.dir_y * move_speed;

	// Check collision and update position if valid
	if (is_valid_move(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_move(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/*
** Strafe player left or right
*/
void strafe_player(t_game *game, double strafe_speed)
{
	double new_x;
	double new_y;

	// Calculate new position (perpendicular to direction vector)
	new_x = game->player.pos_x + game->camera.plane_x * strafe_speed;
	new_y = game->player.pos_y + game->camera.plane_y * strafe_speed;

	// Check collision and update position if valid
	if (is_valid_move(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_move(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/*
** Rotate player view left or right
*/
void rotate_player(t_game *game, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	// Save old values
	old_dir_x = game->player.dir_x;
	old_plane_x = game->camera.plane_x;

	// Rotate direction vector using rotation matrix
	game->player.dir_x = game->player.dir_x * cos(rot_speed) - 
		game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + 
		game->player.dir_y * cos(rot_speed);

	// Rotate camera plane (must be perpendicular to direction)
	game->camera.plane_x = game->camera.plane_x * cos(rot_speed) - 
		game->camera.plane_y * sin(rot_speed);
	game->camera.plane_y = old_plane_x * sin(rot_speed) + 
		game->camera.plane_y * cos(rot_speed);
}

/*
** Check if a move is valid (no wall collision)
*/
int is_valid_move(t_game *game, double x, double y)
{
	int map_x;
	int map_y;

	// Get map coordinates
	map_x = (int)x;
	map_y = (int)y;

	// Check if position is within map bounds
	if (map_x < 0 || map_x >= game->map.width || 
		map_y < 0 || map_y >= game->map.height)
		return (0);

	// Check for wall collision
	if (game->map.map[map_y][map_x] == '1')
		return (0);

	// Check for wall collision when close to edges
	if (x - map_x < WALL_MARGIN && map_x > 0 && 
		game->map.map[map_y][map_x - 1] == '1')
		return (0);
	if (map_x + 1 - x < WALL_MARGIN && map_x < game->map.width - 1 && 
		game->map.map[map_y][map_x + 1] == '1')
		return (0);
	if (y - map_y < WALL_MARGIN && map_y > 0 && 
		game->map.map[map_y - 1][map_x] == '1')
		return (0);
	if (map_y + 1 - y < WALL_MARGIN && map_y < game->map.height - 1 && 
		game->map.map[map_y + 1][map_x] == '1')
		return (0);

	return (1);
}

/*
** Handle key press events
*/
int key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		return (clean_exit(game, 0));
	else if (keycode == KEY_W)
		move_player(game, MOVE_SPEED);
	else if (keycode == KEY_S)
		move_player(game, -MOVE_SPEED);
	else if (keycode == KEY_A)
		strafe_player(game, -MOVE_SPEED);
	else if (keycode == KEY_D)
		strafe_player(game, MOVE_SPEED);
	else if (keycode == KEY_LEFT)
		rotate_player(game, -ROT_SPEED);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, ROT_SPEED);
	
	// Redraw the frame after movement
	render_frame(game);
	
	return (0);
}

// /*
// ** Handle window close event
// */
// int handle_exit(t_game *game)
// {
// 	return (clean_exit(game, 0));
// }