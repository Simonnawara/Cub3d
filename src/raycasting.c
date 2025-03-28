/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:02:11 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/28 16:24:42 by trouilla         ###   ########.fr       */
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

void calculate_ray(t_game *game, t_ray *ray, int x)
{
	double camera_x;

	// Calculate x-coordinate in camera space (from -1 to 1)
	camera_x = 2 * x / (double)WIDTH - 1;
	
	// Calculate ray direction
	ray->dir_x = game->player.dir_x + game->camera.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->camera.plane_y * camera_x;
	
	// Initialize map position (which box of the map we're in)
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	
	// Calculate delta distance (distance between x or y sides)
	// Avoid division by zero
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	
	ray->hit = 0;  // Initialize hit to 0 (no wall hit yet)
}


// Perform DDA algorithm to find wall hits

void perform_dda(t_game *game, t_ray *ray)
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
	
	// Perform DDA
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
		
		// Check if ray has hit a wall
		if (game->map.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}


// Calculate perpendicular distance to the wall
// This avoids fisheye effect

void calculate_wall_distance(t_ray *ray, t_game *game)
{
	// Calculate perpendicular wall distance
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos_x + 
			(1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos_y + 
			(1 - ray->step_y) / 2) / ray->dir_y;
}


// Calculate height of wall stripe on screen

void calculate_wall_height(t_ray *ray, int screen_height)
{
	// Calculate height of the wall on screen
	ray->line_height = (int)(screen_height / ray->perp_wall_dist);
	
	// Calculate lowest and highest pixel to fill in current stripe
	ray->draw_start = -ray->line_height / 2 + screen_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	
	ray->draw_end = ray->line_height / 2 + screen_height / 2;
	if (ray->draw_end >= screen_height)
		ray->draw_end = screen_height - 1;
}


// Calculate texture coordinates for the wall

void calculate_texture_position(t_game *game, t_ray *ray, int x, t_tex_pos *tex)
{
	double wall_x;
	
	(void)x; // Unused parameter
	
	// Calculate value of wall_x (where exactly the wall was hit)
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	
	// Select which texture to use based on wall direction
	if (ray->side == 0 && ray->dir_x > 0)
		tex->img = &game->tex_east;
	else if (ray->side == 0 && ray->dir_x <= 0)
		tex->img = &game->tex_west;
	else if (ray->side == 1 && ray->dir_y > 0)
		tex->img = &game->tex_south;
	else
		tex->img = &game->tex_north;
	
	// Calculate x coordinate on the texture
	tex->x = (int)(wall_x * (double)tex->img->width);
	
	// Calculate y-coordinate stepping for the texture
	tex->step = 1.0 * tex->img->height / ray->line_height;
	
	// Calculate starting position for the texture
	tex->pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * tex->step;
}


// Draw a vertical stripe for a wall

void draw_wall_stripe(t_game *game, int x, t_ray *ray)
{
	int y;
	t_tex_pos tex;
	int color;
	
	// Draw ceiling from 0 to draw_start
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(&game->img, x, y, game->ceiling_color);
		y++;
	}
	
	// Calculate texture position
	calculate_texture_position(game, ray, x, &tex);
	
	// Draw the textured wall
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		// Calculate texture y coordinate
		tex.y = (int)tex.pos & (tex.img->height - 1);
		tex.pos += tex.step;
		
		// Get color from texture
		color = get_pixel_color(tex.img, tex.x, tex.y);
		
		// Make color darker for y-sides
		if (ray->side == 1)
			color = (color >> 1) & 8355711; // Divide by 2 using bit shifting
		
		// Draw pixel
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

int get_pixel_color(t_img *img, int x, int y)
{
	char *dst;
	
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}


// Put a pixel in an image at specified coordinates

void put_pixel(t_img *img, int x, int y, int color)
{
	char *dst;
	
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


// Render a single frame

int render_frame(t_game *game)
{
	// Clear the screen buffer
	clear_image(&game->img, 0x000000);
	
	// Cast rays and draw walls
	cast_rays(game);
	
	// Put image to window
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	
	return (0);
}

//Clear image with a specific color

void clear_image(t_img *img, int color)
{
	int x;
	int y;
	
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
