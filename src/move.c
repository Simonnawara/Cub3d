/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:37:31 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/31 11:57:51 by trouilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// /*
// ** Define movement constants
// */
// #define MOVE_SPEED 0.05
// #define ROT_SPEED 0.03
// #define WALL_MARGIN 0.2

// /*
// ** Move player forward or backward
// */
// void move_player(t_game *game, double move_speed)
// {
// 	double new_x;
// 	double new_y;

// 	// Calculate new position
// 	new_x = game->player.pos_x + game->player.dir_x * move_speed;
// 	new_y = game->player.pos_y + game->player.dir_y * move_speed;

// 	// Check collision and update position if valid
// 	if (is_valid_move(game, new_x, game->player.pos_y))
// 		game->player.pos_x = new_x;
// 	if (is_valid_move(game, game->player.pos_x, new_y))
// 		game->player.pos_y = new_y;
// }

// /*
// ** Strafe player left or right
// */
// void strafe_player(t_game *game, double strafe_speed)
// {
// 	double new_x;
// 	double new_y;

// 	// Calculate new position (perpendicular to direction vector)
// 	new_x = game->player.pos_x + game->camera.plane_x * strafe_speed;
// 	new_y = game->player.pos_y + game->camera.plane_y * strafe_speed;

// 	// Check collision and update position if valid
// 	if (is_valid_move(game, new_x, game->player.pos_y))
// 		game->player.pos_x = new_x;
// 	if (is_valid_move(game, game->player.pos_x, new_y))
// 		game->player.pos_y = new_y;
// }

// /*
// ** Rotate player view left or right
// */
// void rotate_player(t_game *game, double rot_speed)
// {
// 	double old_dir_x;
// 	double old_plane_x;

// 	// Save old values
// 	old_dir_x = game->player.dir_x;
// 	old_plane_x = game->camera.plane_x;

// 	// Rotate direction vector using rotation matrix
// 	game->player.dir_x = game->player.dir_x * cos(rot_speed) - 
// 		game->player.dir_y * sin(rot_speed);
// 	game->player.dir_y = old_dir_x * sin(rot_speed) + 
// 		game->player.dir_y * cos(rot_speed);

// 	// Rotate camera plane (must be perpendicular to direction)
// 	game->camera.plane_x = game->camera.plane_x * cos(rot_speed) - 
// 		game->camera.plane_y * sin(rot_speed);
// 	game->camera.plane_y = old_plane_x * sin(rot_speed) + 
// 		game->camera.plane_y * cos(rot_speed);
// }

// /*
// ** Check if a move is valid (no wall collision)
// */
// int is_valid_move(t_game *game, double x, double y)
// {
// 	int map_x;
// 	int map_y;

// 	// Get map coordinates
// 	map_x = (int)x;
// 	map_y = (int)y;

// 	// Check if position is within map bounds
// 	if (map_x < 0 || map_x >= game->map.width || 
// 		map_y < 0 || map_y >= game->map.height)
// 		return (0);

// 	// Check for wall collision
// 	if (game->map.map[map_y][map_x] == '1')
// 		return (0);

// 	// Check for wall collision when close to edges
// 	if (x - map_x < WALL_MARGIN && map_x > 0 && 
// 		game->map.map[map_y][map_x - 1] == '1')
// 		return (0);
// 	if (map_x + 1 - x < WALL_MARGIN && map_x < game->map.width - 1 && 
// 		game->map.map[map_y][map_x + 1] == '1')
// 		return (0);
// 	if (y - map_y < WALL_MARGIN && map_y > 0 && 
// 		game->map.map[map_y - 1][map_x] == '1')
// 		return (0);
// 	if (map_y + 1 - y < WALL_MARGIN && map_y < game->map.height - 1 && 
// 		game->map.map[map_y + 1][map_x] == '1')
// 		return (0);

// 	return (1);
// }

// /*
// ** Handle key press events
// */
// int key_press(int keycode, t_game *game)
// {
// 	if (keycode == KEY_ESC)
// 		return (clean_exit(game, 0));
// 	else if (keycode == KEY_W)
// 		move_player(game, MOVE_SPEED);
// 	else if (keycode == KEY_S)
// 		move_player(game, -MOVE_SPEED);
// 	else if (keycode == KEY_A)
// 		strafe_player(game, -MOVE_SPEED);
// 	else if (keycode == KEY_D)
// 		strafe_player(game, MOVE_SPEED);
// 	else if (keycode == KEY_LEFT)
// 		rotate_player(game, -ROT_SPEED);
// 	else if (keycode == KEY_RIGHT)
// 		rotate_player(game, ROT_SPEED);
	
// 	// Redraw the frame after movement
// 	render_frame(game);
	
// 	return (0);
// }

// // /*
// // ** Handle window close event
// // */
// // int handle_exit(t_game *game)
// // {
// // 	return (clean_exit(game, 0));
// // }


#define MOVE_SPEED 0.05
#define STRAFE_SPEED 0.04
#define ROT_SPEED 0.03
#define WALL_MARGIN 0.2

/*
** Move player forward or backward with improved collision detection
*/
void move_player(t_game *game, double move_speed)
{
    double new_x;
    double new_y;
    
    // Debug print
    //printf("Moving player: speed=%f, pos=(%f,%f), dir=(%f,%f)\n", 
           //move_speed, game->player.pos_x, game->player.pos_y, 
           //game->player.dir_x, game->player.dir_y);

    // Calculate new position
    new_x = game->player.pos_x + game->player.dir_x * move_speed;
    new_y = game->player.pos_y + game->player.dir_y * move_speed;

    // Check collision and update position if valid
    if (is_valid_move(game, new_x, game->player.pos_y))
    {
        game->player.pos_x = new_x;
       // printf("Updated X pos: %f\n", game->player.pos_x);
    }
    
    if (is_valid_move(game, game->player.pos_x, new_y))
    {
        game->player.pos_y = new_y;
        //printf("Updated Y pos: %f\n", game->player.pos_y);
    }
}

/*
** Strafe player left or right with improved handling
*/
void	strafe_player(t_game *game, double strafe_speed)
{
	double	new_x;
	double	new_y;

	// Calculate new position (perpendicular to direction vector)
	new_x = game->player.pos_x + game->camera.plane_x * strafe_speed;
	new_y = game->player.pos_y + game->camera.plane_y * strafe_speed;

	// Check collision and update position if valid, with separate checks for each axis
	// This allows sliding along walls when strafing at an angle
	if (is_valid_move(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_move(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/*
** Rotate player view left or right with improved handling
*/
void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

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
		
	// Normalize vectors to prevent floating-point errors over time
	double dir_length = sqrt(game->player.dir_x * game->player.dir_x + 
							game->player.dir_y * game->player.dir_y);
	game->player.dir_x /= dir_length;
	game->player.dir_y /= dir_length;
	
	// Keep camera plane perpendicular and at proper length for FOV
	double plane_dot_dir = game->camera.plane_x * game->player.dir_x + 
						   game->camera.plane_y * game->player.dir_y;
	game->camera.plane_x -= plane_dot_dir * game->player.dir_x;
	game->camera.plane_y -= plane_dot_dir * game->player.dir_y;
	
	double plane_length = sqrt(game->camera.plane_x * game->camera.plane_x + 
							  game->camera.plane_y * game->camera.plane_y);
	game->camera.plane_x = game->camera.plane_x * 0.66 / plane_length;
	game->camera.plane_y = game->camera.plane_y * 0.66 / plane_length;
}

int is_valid_move(t_game *game, double x, double y)
{
    int map_x;
    int map_y;
    
    // Convert floating point position to integer map coordinates
    map_x = (int)x;
    map_y = (int)y;
    
    // Debug print
    printf("Checking position: (%f,%f) -> map[%d][%d] = %c\n", 
           x, y, map_y, map_x, 
           (map_y >= 0 && map_y < game->map.height && 
            map_x >= 0 && map_x < game->map.width) ? 
           game->map.map[map_y][map_x] : '?');
    
    // Check if position is out of bounds
    if (map_x < 0 || map_x >= game->map.width || 
        map_y < 0 || map_y >= game->map.height)
        return (0);
    
    // Check if position is a wall
    if (game->map.map[map_y][map_x] == '1')
        return (0);
    
    // For debugging, temporarily disable wall margin checks
    return (1);
    
    // Wall margin checks (commented out for debugging)
    /*
    // Additional collision checks near walls
    if (x - map_x < WALL_MARGIN && map_x > 0 && 
        game->map.map[map_y][map_x - 1] == '1')
        return (0);
    ...etc...
    */
}
/*
** Handle key press events with smooth movement
*/
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
	
	// Redraw the frame after movement
	render_frame(game);
	
	return (0);
}

/*
** Continuous key handling for smoother movement
** This function captures key states rather than single presses
*/
int	key_state_handler(t_game *game)
{
	// Store key states in game structure for smooth movement
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
	
	// Render if any key is pressed
	if (game->keys.w || game->keys.s || game->keys.a || game->keys.d || 
		game->keys.left || game->keys.right)
		render_frame(game);
	
	return (0);
}

/*
** Set key state when pressed
*/
int key_press_state(int keycode, t_game *game)
{
    printf("Key pressed: %d\n", keycode);
    
    if (keycode == KEY_ESC)
        return (clean_exit(game, 0));
    else if (keycode == KEY_W)
    {
        printf("W key pressed\n");
        game->keys.w = 1;
    }
    else if (keycode == KEY_S)
    {
        printf("S key pressed\n");
        game->keys.s = 1;
    }
    else if (keycode == KEY_A)
    {
        printf("A key pressed\n");
        game->keys.a = 1;
    }
    else if (keycode == KEY_D)
    {
        printf("D key pressed\n");
        game->keys.d = 1;
    }
    else if (keycode == KEY_LEFT)
    {
        printf("LEFT key pressed\n");
        game->keys.left = 1;
    }
    else if (keycode == KEY_RIGHT)
    {
        printf("RIGHT key pressed\n");
        game->keys.right = 1;
    }
    
    return (0);
}


int key_release_state(int keycode, t_game *game)
{
    // Debug print
    printf("Key released: %d\n", keycode);
    
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
