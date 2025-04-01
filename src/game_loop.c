/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:33:15 by trouilla          #+#    #+#             */
/*   Updated: 2025/04/01 11:22:20 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Initialize key states to zero
void	init_key_states(t_game *game)
{
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
}

// Enhanced game loop with smooth movement and proper timing
int	game_loop(t_game *game)
{
	init_time(game);
	init_key_states(game);
	mlx_hook(game->win, 2, 1L << 0, key_press_state, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_state, game);
	mlx_hook(game->win, 17, 0, handle_exit, game);
	mlx_loop_hook(game->mlx, game_update, game);
	render_frame(game);
	mlx_loop(game->mlx);
	return (0);
}

void	process_movement(t_game *game, double time_factor)
{
	if (game->keys.w)
		move_player(game, MOVE_SPEED * time_factor);
	if (game->keys.s)
		move_player(game, -MOVE_SPEED * time_factor);
	if (game->keys.a)
		strafe_player(game, -STRAFE_SPEED * time_factor);
	if (game->keys.d)
		strafe_player(game, STRAFE_SPEED * time_factor);
	if (game->keys.left)
		rotate_player(game, -ROT_SPEED * time_factor);
	if (game->keys.right)
		rotate_player(game, ROT_SPEED * time_factor);
}

int	game_update(t_game *game)
{
	static int		frame_count = 0;
	static time_t	last_time = 0;
	time_t			current_time;
	double			time_factor;

	update_time(game);
	time_factor = game->time.frame_time * 60.0;
	process_movement(game, time_factor);
	render_frame(game);
	frame_count++;
	time(&current_time);
	if (current_time - last_time >= 1)
	{
		ft_printf("FPS: %d\n", frame_count);
		frame_count = 0;
		last_time = current_time;
	}
	frame_delay(game);
	return (0);
}

int	render_frame(t_game *game)
{
	clear_image(&game->img, 0x000000);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
