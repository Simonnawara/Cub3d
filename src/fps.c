/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:24:58 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/31 14:26:49 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Optional: Draw FPS counter in the corner of the screen
*/
void	draw_fps_counter(t_game *game)
{
	char	fps_str[20];
	int		fps;

	if (game->time.frame_time > 0)
		fps = (int)(1.0 / game->time.frame_time);
	else
		fps = 0;
	sprintf(fps_str, "FPS: %d", fps);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, fps_str);
}
