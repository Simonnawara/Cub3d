/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:46:25 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/31 14:53:00 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		return (clean_exit(game, 0));
	else if (keycode == KEY_W)
		move_player(game, MOVE_SPEED);
	else if (keycode == KEY_S)
		move_player(game, -MOVE_SPEED);
	else if (keycode == KEY_A)
		strafe_player(game, -STRAFE_SPEED);
	else if (keycode == KEY_D)
		strafe_player(game, STRAFE_SPEED);
	else if (keycode == KEY_LEFT)
		rotate_player(game, -ROT_SPEED);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, ROT_SPEED);
	render_frame(game);
	return (0);
}

/*
** Continuous key handling for smoother movement
** This function captures key states rather than single presses
*/
int	key_state_handler(t_game *game)
{
	if (game->keys.w)
		move_player(game, MOVE_SPEED);
	if (game->keys.s)
		move_player(game, -MOVE_SPEED);
	if (game->keys.a)
		strafe_player(game, -STRAFE_SPEED);
	if (game->keys.d)
		strafe_player(game, STRAFE_SPEED);
	if (game->keys.left)
		rotate_player(game, -ROT_SPEED);
	if (game->keys.right)
		rotate_player(game, ROT_SPEED);
	if (game->keys.w || game->keys.s || game->keys.a || game->keys.d
		|| game->keys.left || game->keys.right)
		render_frame(game);
	return (0);
}

/*
** Set key state when pressed
*/
int	key_press_state(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		return (clean_exit(game, 0));
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

int	key_release_state(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

int	is_valid_move(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map.width || map_y < 0
		|| map_y >= game->map.height)
		return (0);
	if (game->map.map[map_y][map_x] == '1')
		return (0);
	return (1);
}
