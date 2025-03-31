/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:29:28 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/31 12:19:04 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	blend_colors(int color1, int color2, double alpha)
{
	int	r1;
	int	g1;
	int	b1;
	int	r2;
	int	g2;
	int	b2;
	int	r;
	int	g;
	int	b;

	// Extract RGB components
	r1 = (color1 >> 16) & 0xFF;
	g1 = (color1 >> 8) & 0xFF;
	b1 = color1 & 0xFF;
	
	r2 = (color2 >> 16) & 0xFF;
	g2 = (color2 >> 8) & 0xFF;
	b2 = color2 & 0xFF;
	
	// Blend colors using alpha
	r = (int)(r1 * alpha + r2 * (1 - alpha));
	g = (int)(g1 * alpha + g2 * (1 - alpha));
	b = (int)(b1 * alpha + b2 * (1 - alpha));
	
	// Combine back into RGB
	return ((r << 16) | (g << 8) | b);
}

/*
** Draw a filled rectangle on the screen with transparency
*/
void	draw_rect(t_game *game, int x, int y, int size, int color)
{
	int	i;
	int	j;
	int	current_color;
	int	screen_color;

	// Ensure rectangle is within screen bounds
	if (x < 0 || y < 0 || x + size >= WIDTH || y + size >= HEIGHT)
		return;
	
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			// Get current screen color for blending
			screen_color = get_pixel_color(&game->img, x + i, y + j);
			
			// Apply transparency
			current_color = blend_colors(color, screen_color, MINIMAP_ALPHA);
			
			// Draw pixel
			put_pixel(&game->img, x + i, y + j, current_color);
			j++;
		}
		i++;
	}
}

/*
** Draw the player on the minimap
*/
void	draw_player(t_game *game, int minimap_x, int minimap_y)
{
	int	player_x;
	int	player_y;
	int	dir_x;
	int	dir_y;
	int	player_size;
	
	// Calculate player position on minimap
	player_x = minimap_x + (int)(game->player.pos_x * MINIMAP_SCALE);
	player_y = minimap_y + (int)(game->player.pos_y * MINIMAP_SCALE);
	
	// Draw player dot (red)
	player_size = 4;
	draw_rect(game, player_x - player_size / 2, player_y - player_size / 2, 
			player_size, 0xFF0000);
	
	// Draw direction line
	dir_x = player_x + (int)(game->player.dir_x * 10);
	dir_y = player_y + (int)(game->player.dir_y * 10);
	
	// Draw line from player to direction
	draw_line(game, player_x, player_y, dir_x, dir_y, 0xFF0000);
}

/*
** Draw a line using Bresenham's algorithm
*/
void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	screen_color;
	int	current_color;

	// Calculate direction and steps
	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx + dy;
	
	// Draw line
	while (1)
	{
		// Check if point is within screen bounds
		if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT)
		{
			// Get current screen color for blending
			screen_color = get_pixel_color(&game->img, x0, y0);
			
			// Apply transparency
			current_color = blend_colors(color, screen_color, MINIMAP_ALPHA);
			
			// Draw pixel
			put_pixel(&game->img, x0, y0, current_color);
		}
		
		// Check if we reached end point
		if (x0 == x1 && y0 == y1)
			break;
		
		// Calculate next point
		e2 = 2 * err;
		if (e2 >= dy)
		{
			if (x0 == x1)
				break;
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			if (y0 == y1)
				break;
			err += dx;
			y0 += sy;
		}
	}
}

/*
** Draw minimap in the top-right corner of the screen
*/
// void	draw_minimap(t_game *game)
// {
// 	int	minimap_width;
// 	int	minimap_height;
// 	int	minimap_x;
// 	int	minimap_y;
// 	int	x;
// 	int	y;
// 	int	map_x;
// 	int	map_y;
// 	int	cell_size;
// 	int	cell_color;
	
// 	// Calculate minimap dimensions and position
// 	minimap_width = MINIMAP_SIZE;
// 	minimap_height = MINIMAP_SIZE;
// 	minimap_x = WIDTH - minimap_width - MINIMAP_MARGIN;
// 	minimap_y = MINIMAP_MARGIN;
	
// 	// Draw minimap background (semi-transparent black)
// 	draw_rect(game, minimap_x, minimap_y, minimap_width, 0x000000);
	
// 	// Draw map cells
// 	cell_size = MINIMAP_SCALE;
// 	y = 0;
// 	while (y < game->map.height)
// 	{
// 		x = 0;
// 		while (x < game->map.width)
// 		{
// 			// Calculate position on minimap
// 			map_x = minimap_x + x * cell_size;
// 			map_y = minimap_y + y * cell_size;
			
// 			// Skip cells outside the minimap area
// 			if (map_x + cell_size < minimap_x || map_x >= minimap_x + minimap_width ||
// 				map_y + cell_size < minimap_y || map_y >= minimap_y + minimap_height)
// 			{
// 				x++;
// 				continue;
// 			}
			
// 			// Choose color based on cell type
// 			if (game->map.map[y][x] == '1')
// 				cell_color = 0xFFFFFF; // White for walls
// 			else if (game->map.map[y][x] == '0')
// 				cell_color = 0x555555; // Gray for floors
// 			else
// 				cell_color = 0x000000; // Black for other (shouldn't happen)
			
// 			// Draw cell
// 			draw_rect(game, map_x, map_y, cell_size, cell_color);
// 			x++;
// 		}
// 		y++;
// 	}
	
// 	// Draw player on minimap
// 	draw_player(game, minimap_x, minimap_y);
	
// 	// Draw minimap border
// 	draw_line(game, minimap_x, minimap_y, minimap_x + minimap_width, minimap_y, 0xFFFFFF);
// 	draw_line(game, minimap_x + minimap_width, minimap_y, minimap_x + minimap_width, minimap_y + minimap_height, 0xFFFFFF);
// 	draw_line(game, minimap_x + minimap_width, minimap_y + minimap_height, minimap_x, minimap_y + minimap_height, 0xFFFFFF);
// 	draw_line(game, minimap_x, minimap_y + minimap_height, minimap_x, minimap_y, 0xFFFFFF);
// }
void draw_minimap(t_game *game)
{
    int minimap_width;
    int minimap_height;
    int minimap_x;
    int minimap_y;
    int x, y;
    int map_x, map_y;
    int cell_size;
    int cell_color;
    
    // Calculate minimap dimensions and position
    minimap_width = MINIMAP_SIZE;
    minimap_height = MINIMAP_SIZE;
    minimap_x = WIDTH - minimap_width - MINIMAP_MARGIN;
    minimap_y = MINIMAP_MARGIN;
    
    // Draw minimap background (semi-transparent black)
    draw_rect(game, minimap_x, minimap_y, minimap_width, 0x000000);
    
    // Calculate the range of map cells to draw
    // This centers the view on the player
    int player_cell_x = (int)game->player.pos_x;
    int player_cell_y = (int)game->player.pos_y;
    
    // Calculate how many cells fit in each direction
    int cells_in_view_x = minimap_width / MINIMAP_SCALE / 2;
    int cells_in_view_y = minimap_height / MINIMAP_SCALE / 2;
    
    // Calculate the start and end positions for drawing
    int start_x = player_cell_x - cells_in_view_x;
    int end_x = player_cell_x + cells_in_view_x;
    int start_y = player_cell_y - cells_in_view_y;
    int end_y = player_cell_y + cells_in_view_y;
    
    // Draw map cells
    cell_size = MINIMAP_SCALE;
    
    for (y = start_y; y <= end_y; y++)
    {
        for (x = start_x; x <= end_x; x++)
        {
            // Calculate position on minimap
            map_x = minimap_x + (x - start_x) * cell_size;
            map_y = minimap_y + (y - start_y) * cell_size;
            
            // Skip cells outside map bounds
            if (y < 0 || y >= game->map.height || x < 0 || x >= game->map.width)
            {
                // Draw out of bounds cells as dark gray
                draw_rect(game, map_x, map_y, cell_size, 0x222222);
                continue;
            }
            
            // Choose color based on cell type
            if (game->map.map[y][x] == '1')
                cell_color = 0xFFFFFF;  // White for walls
            else if (game->map.map[y][x] == '0')
                cell_color = 0x555555;  // Gray for floors
            else
                cell_color = 0x000000;  // Black for other
            
            // Draw cell
            draw_rect(game, map_x, map_y, cell_size, cell_color);
        }
    }
    
    // Draw player on minimap (always at center)
    int player_x = minimap_x + minimap_width / 2;
    int player_y = minimap_y + minimap_height / 2;
    
    // Draw player dot (red)
    int player_size = 4;
    draw_rect(game, player_x - player_size / 2, player_y - player_size / 2, 
            player_size, 0xFF0000);
    
    // Draw direction line
    int dir_x = player_x + (int)(game->player.dir_x * 10);
    int dir_y = player_y + (int)(game->player.dir_y * 10);
    
    // Draw line from player to direction
    draw_line(game, player_x, player_y, dir_x, dir_y, 0xFF0000);
    
    // Draw minimap border
    draw_line(game, minimap_x, minimap_y, minimap_x + minimap_width, minimap_y, 0xFFFFFF);
    draw_line(game, minimap_x + minimap_width, minimap_y, minimap_x + minimap_width, minimap_y + minimap_height, 0xFFFFFF);
    draw_line(game, minimap_x + minimap_width, minimap_y + minimap_height, minimap_x, minimap_y + minimap_height, 0xFFFFFF);
    draw_line(game, minimap_x, minimap_y + minimap_height, minimap_x, minimap_y, 0xFFFFFF);
}