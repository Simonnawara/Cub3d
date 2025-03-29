/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:25:27 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/29 15:26:45 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Initialize time structure for frame timing
*/
void	init_time(t_game *game)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	
	// Convert to milliseconds for easier calculation
	game->time.old_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	game->time.current_time = game->time.old_time;
	game->time.frame_time = 1.0 / FPS; // Default frame time
}

/*
** Update time and calculate frame time for consistent movement
*/
void	update_time(t_game *game)
{
	struct timeval	current_time;

	// Store old time
	game->time.old_time = game->time.current_time;
	
	// Get current time
	gettimeofday(&current_time, NULL);
	game->time.current_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	
	// Calculate time passed since last frame in seconds
	game->time.frame_time = (game->time.current_time - game->time.old_time) / 1000.0;
	
	// Cap frame time to prevent large jumps on lag
	if (game->time.frame_time > 0.2)
		game->time.frame_time = 0.2;
	
	// Ensure frame time is not zero to prevent division issues
	if (game->time.frame_time < 0.001)
		game->time.frame_time = 0.001;
}

/*
** Get current frame time for frame-rate independent movement
*/
double	get_frame_time(t_game *game)
{
	return (game->time.frame_time);
}

/*
** Sleep function to cap framerate
*/
void	frame_delay(t_game *game)
{
	struct timeval	current_time;
	long			elapsed;
	long			wait_time;

	// Get current time
	gettimeofday(&current_time, NULL);
	
	// Calculate elapsed time since frame start in microseconds
	elapsed = (current_time.tv_sec * 1000000 + current_time.tv_usec) - 
			 (game->time.old_time * 1000);
	
	// If frame rendered faster than target FPS, wait
	if (elapsed < FRAME_TIME)
	{
		// Calculate remaining time to wait
		wait_time = FRAME_TIME - elapsed;
		
		// Wait using usleep
		usleep(wait_time);
	}
}