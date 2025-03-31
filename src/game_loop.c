/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trouilla <trouilla@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:33:15 by trouilla          #+#    #+#             */
/*   Updated: 2025/03/31 11:58:13 by trouilla         ###   ########.fr       */
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
int game_loop(t_game *game)
{
    // Initialize time structures
    init_time(game);
    
    // Initialize key states
    init_key_states(game);
    
    // Set up key hooks - make sure these are correct
    mlx_hook(game->win, 2, 1L << 0, key_press_state, game);  // Key press
    mlx_hook(game->win, 3, 1L << 1, key_release_state, game); // Key release
    mlx_hook(game->win, 17, 0, handle_exit, game); // Window close
    
    // Set up loop hook
    mlx_loop_hook(game->mlx, game_update, game);
    
    // Initial render
    render_frame(game);
    
    // Start the MLX loop
    mlx_loop(game->mlx);
    
    return (0);
}


// void process_movement(t_game *game, double time_factor)
// {
//     // Try using larger movement speeds for testing
//     double test_move = 0.1 * time_factor;
//     double test_rot = 0.05 * time_factor;
    
//     // Apply movement based on pressed keys
//     if (game->keys.w)
//         move_player(game, test_move);
//     if (game->keys.s)
//         move_player(game, -test_move);
//     if (game->keys.a)
//         strafe_player(game, -test_move);
//     if (game->keys.d)
//         strafe_player(game, test_move);
//     if (game->keys.left)
//         rotate_player(game, -test_rot);
//     if (game->keys.right)
//         rotate_player(game, test_rot);
// }
void process_movement(t_game *game, double time_factor)
{
    // Debug current key states
    // printf("Key states: W:%d S:%d A:%d D:%d LEFT:%d RIGHT:%d\n", 
    //        game->keys.w, game->keys.s, game->keys.a, game->keys.d,
    //        game->keys.left, game->keys.right);
    
    // Apply movement based on pressed keys
    if (game->keys.w)
    {
        move_player(game, MOVE_SPEED * time_factor);
    }
    if (game->keys.s)
    {
        move_player(game, -MOVE_SPEED * time_factor);
    }
    if (game->keys.a)
    {
        strafe_player(game, -STRAFE_SPEED * time_factor);
    }
    if (game->keys.d)
    {
        strafe_player(game, STRAFE_SPEED * time_factor);
    }
    if (game->keys.left)
    {
        rotate_player(game, -ROT_SPEED * time_factor);
    }
    if (game->keys.right)
    {
        rotate_player(game, ROT_SPEED * time_factor);
    }
}
// void test_player_movement(t_game *game, int frame_count)
// {
//     // Every 60 frames, move the player forward
//     if (frame_count % 60 == 0)
//     {
//         printf("Test moving player forward\n");
//         move_player(game, 0.1);
//     }
    
//     // Every 120 frames, rotate the player
//     if (frame_count % 120 == 0)
//     {
//         printf("Test rotating player\n");
//         rotate_player(game, 0.1);
//     }
// }
int game_update(t_game *game)
{
    static int frame_count = 0;
    static time_t last_time = 0;
    time_t current_time;
    
    // Update timing information
    update_time(game);
    
    // Process movement with frame time adjustment
    double time_factor = game->time.frame_time * 60.0;
    
    // Handle key states for smooth movement
    process_movement(game, time_factor);
   // test_player_movement(game, frame_count);
    // Render frame
    render_frame(game);
    
    // Calculate and print FPS every second
    frame_count++;
    time(&current_time);
    if (current_time - last_time >= 1)
    {
        ft_printf("FPS: %d\n", frame_count);
        frame_count = 0;
        last_time = current_time;
    }
    
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
