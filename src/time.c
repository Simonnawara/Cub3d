/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:25:27 by trouilla          #+#    #+#             */
/*   Updated: 2025/04/01 11:07:19 by trouilla         ###   ########.fr       */
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
	game->time.old_time = current_time.tv_sec * 1000 + current_time.tv_usec
		/ 1000;
	game->time.current_time = game->time.old_time;
	game->time.frame_time = 1.0 / FPS;
}

/*
** Update time and calculate frame time for consistent movement
*/
void	update_time(t_game *game)
{
	struct timeval	current_time;

	game->time.old_time = game->time.current_time;
	gettimeofday(&current_time, NULL);
	game->time.current_time = current_time.tv_sec * 1000 + current_time.tv_usec
		/ 1000;
	game->time.frame_time = (game->time.current_time - game->time.old_time)
		/ 1000.0;
	if (game->time.frame_time > 0.2)
		game->time.frame_time = 0.2;
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

	gettimeofday(&current_time, NULL);
	elapsed = (current_time.tv_sec * 1000000 + current_time.tv_usec)
		- (game->time.old_time * 1000);
	if (elapsed < FRAME_TIME)
	{
		wait_time = FRAME_TIME - elapsed;
		usleep(wait_time);
	}
}
