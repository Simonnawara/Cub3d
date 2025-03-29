/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:02:11 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/29 15:38:10 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


// Cast rays for the entire screen and render the result

void cast_rays(t_game *game)
{
	t_ray ray;
	int x;

	x = 0;
	while (x < WIDTH)
	{
		// Calculate ray position and direction
		calculate_ray(game, &ray, x);
		
		// Perform DDA algorithm to find wall hits
		perform_dda(game, &ray);
		
		// Calculate distance to the wall
		calculate_wall_distance(&ray, game);
		
		// Calculate height of the wall on screen
		calculate_wall_height(&ray, HEIGHT);
		
		// Draw the wall stripe for this x-coordinate
		draw_wall_stripe(game, x, &ray);
		
		x++;
	}
}


// Calculate ray direction for a specific x-coordinate

void	calculate_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	// Calculate x-coordinate in camera space (from -1 to 1)
	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	
	// Calculate ray direction
	ray->dir_x = game->player.dir_x + game->camera.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->camera.plane_y * camera_x;
	
	// Initialize map position (which box of the map we're in)
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	
	// Calculate delta distance (distance between x or y sides)
	// Improved handling of division by zero cases
	ray->delta_dist_x = (ray->dir_x == 0) ? 1e30 : fabs(1.0 / ray->dir_x);
	ray->delta_dist_y = (ray->dir_y == 0) ? 1e30 : fabs(1.0 / ray->dir_y);
	
	ray->hit = 0;  // Initialize hit to 0 (no wall hit yet)
}


// Perform DDA algorithm to find wall hits

void	perform_dda(t_game *game, t_ray *ray)
{
	// Calculate step direction and initial side distance
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
	}
	
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y;
	}
	
	// Perform DDA with improved boundary checking
	while (ray->hit == 0)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;  // X-side hit (NS wall)
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;  // Y-side hit (EW wall)
		}
		
		// Check if ray has hit a wall with boundary check
		if (ray->map_y < 0 || ray->map_y >= game->map.height || 
			ray->map_x < 0 || ray->map_x >= game->map.width)
			ray->hit = 1;  // Hit map boundary, stop the loop
		else if (game->map.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;  // Hit a wall, stop the loop
	}
}


// Calculate perpendicular distance to the wall
// This avoids fisheye effect

void	calculate_wall_distance(t_ray *ray, t_game *game)
{
	// Calculate perpendicular wall distance to avoid fisheye effect
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos_x + 
			(1 - ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos_y + 
			(1 - ray->step_y) / 2.0) / ray->dir_y;
	
	// Ensure we don't have negative distances
	if (ray->perp_wall_dist < 0.1)
		ray->perp_wall_dist = 0.1;
}


// Calculate height of wall stripe on screen

void	calculate_wall_height(t_ray *ray, int screen_height)
{
	// Calculate height of the wall on screen
	ray->line_height = (int)(screen_height / ray->perp_wall_dist);
	
	// Avoid excessively large line heights that could cause integer overflow
	if (ray->line_height > 10 * screen_height)
		ray->line_height = 10 * screen_height;
	
	// Calculate lowest and highest pixel to fill in current stripe
	ray->draw_start = -ray->line_height / 2 + screen_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	
	ray->draw_end = ray->line_height / 2 + screen_height / 2;
	if (ray->draw_end >= screen_height)
		ray->draw_end = screen_height - 1;
}


// Calculate texture coordinates for the wall

void	calculate_texture_position(t_game *game, t_ray *ray, t_tex_pos *tex)
{
	double	wall_x;
	
	// Calculate value of wall_x (where exactly the wall was hit)
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	
	// Select which texture to use based on wall direction (N, S, E, W)
	if (ray->side == 0 && ray->dir_x > 0)
		tex->img = &game->tex_east;
	else if (ray->side == 0 && ray->dir_x <= 0)
		tex->img = &game->tex_west;
	else if (ray->side == 1 && ray->dir_y > 0)
		tex->img = &game->tex_south;
	else
		tex->img = &game->tex_north;
	
	// Calculate x coordinate on the texture with bounds checking
	tex->x = (int)(wall_x * (double)tex->img->width);
	if (tex->x >= tex->img->width)
		tex->x = tex->img->width - 1;
	
	// Flip texture x-coordinate for east/west walls to maintain consistency
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex->x = tex->img->width - tex->x - 1;
	
	// Calculate y-coordinate stepping for the texture
	tex->step = 1.0 * tex->img->height / ray->line_height;
	
	// Calculate starting position for the texture
	tex->pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * tex->step;
}


// Draw a vertical stripe for a wall

void	draw_wall_stripe(t_game *game, int x, t_ray *ray)
{
	int			y;
	t_tex_pos	tex;
	int			color;
	
	// Draw ceiling from 0 to draw_start
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(&game->img, x, y, game->ceiling_color);
		y++;
	}
	
	// Calculate texture position
	calculate_texture_position(game, ray, &tex);
	
	// Draw the textured wall with improved texture coordinate handling
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		// Calculate texture y coordinate with bounds checking
		tex.y = (int)tex.pos & (tex.img->height - 1);
		tex.pos += tex.step;
		
		// Get color from texture with error checking
		color = get_pixel_color(tex.img, tex.x, tex.y);
		
		// Make color darker for y-sides to create a shadow effect
		if (ray->side == 1)
			color = (color >> 1) & 8355711; // Divide by 2 using bit shifting
		
		// Draw pixel with bounds checking
		put_pixel(&game->img, x, y, color);
		y++;
	}
	
	// Draw floor from draw_end to bottom
	y = ray->draw_end;
	while (y < HEIGHT)
	{
		put_pixel(&game->img, x, y, game->floor_color);
		y++;
	}
}


// Get color from an image at specified coordinates

int	get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;
	
	if (!img || !img->addr || x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0x000000); // Return black for invalid coordinates
	
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

/*
** Put a pixel in an image at specified coordinates with bounds checking
*/
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;
	
	if (!img || !img->addr || x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return;
	
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


//Clear image with a specific color

void	clear_image(t_img *img, int color)
{
	int	i;
	int	*dst;
	int	pixel_count;

	if (!img || !img->addr)
		return;
	
	// Optimize by treating image as int array
	dst = (int*)img->addr;
	pixel_count = WIDTH * HEIGHT;
	
	i = 0;
	while (i < pixel_count)
	{
		dst[i] = color;
		i++;
	}
}
