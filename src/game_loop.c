/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:33:15 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/31 10:04:32 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Initialize key states to zero
*/
void	init_key_states(t_game *game)
{
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
}

/*
** Enhanced game loop with smooth movement and proper timing
*/
int	game_loop(t_game *game)
{
	// Initialize time structures
	init_time(game);
	
	// Initialize key states
	init_key_states(game);
	
	// Set up hooks for key events with state tracking for smoother movement
	mlx_hook(game->win, 2, 1L << 0, key_press_state, game);  // Key press
	mlx_hook(game->win, 3, 1L << 1, key_release_state, game); // Key release
	mlx_hook(game->win, 17, 0, handle_exit, game);  // Window close
	
	// Set up loop hook for continuous updates
	mlx_loop_hook(game->mlx, game_update, game);
	
	// Initial render
	render_frame(game);
	
	// Start the MLX loop
	mlx_loop(game->mlx);
	
	return (0);
}

/*
** Game update function called by mlx_loop_hook
*/
int	game_update(t_game *game)
{
	// Update timing information
	update_time(game);
	
	// Handle key states for movement
	// Adjust movement speed based on frame time for consistent movement
	double time_factor = game->time.frame_time * 60.0;
	
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
	
	// Render frame
	render_frame(game);
	
	// Delay to maintain target FPS
	frame_delay(game);
	
	return (0);
}

int	render_frame(t_game *game)
{
	// Clear the screen buffer
	clear_image(&game->img, 0x000000);
	
	// Cast rays and draw 3D view
	cast_rays(game);
	
	// Draw minimap overlay
	draw_minimap(game);
	// Display FPS counter (optional)
	// draw_fps_counter(game);
	
	// Put image to window
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	
	return (0);
}


/*
** Optional: Draw FPS counter in the corner of the screen
*/
void	draw_fps_counter(t_game *game)
{
	char	fps_str[20];
	int		fps;
	
	// Calculate FPS
	if (game->time.frame_time > 0)
		fps = (int)(1.0 / game->time.frame_time);
	else
		fps = 0;
	
	// Format FPS string
	sprintf(fps_str, "FPS: %d", fps);
	
	// Draw string to screen
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, fps_str);
}
