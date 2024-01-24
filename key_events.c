#include "./includes/cub3d.h"

int key_release(int keycode, t_keys *keys)
{
    if (keycode == 119) // W key
        keys->w = false;
    if (keycode == 115)  // S key
        keys->s = false;
    if (keycode == 97)  // A key
        keys->a = false;
    if (keycode == 100)  // D key
        keys->d = false;
    if (keycode == 65361) // Left arrow key
        keys->left = false;
    if (keycode == 65363) // Right arrow key
        keys->right = false;
    return (0);
}

int key_hook(t_keys *keys)
{
    t_data *img = keys->img; // Assuming keys->img holds a reference to your t_data structure
    double oldPlayerX = img->player.x;
    double oldPlayerY = img->player.y;
    // Handle key presses
    if (keys->w)
    {
        img->player.x += img->player.dir_x * MOV_SPEED;
        img->player.y += img->player.dir_y * MOV_SPEED;
		
    }
    if (keys->s)
    {
        img->player.x -= img->player.dir_x * MOV_SPEED;
        img->player.y -= img->player.dir_y * MOV_SPEED;
    }
    if (keys->a)
    {
        img->player.x -= img->player.plane_x * MOV_SPEED;
        img->player.y -= img->player.plane_y * MOV_SPEED;
    }
    if (keys->d)
    {
        img->player.x += img->player.plane_x * MOV_SPEED;
        img->player.y += img->player.plane_y * MOV_SPEED;
    }

	    // Check for collisions with walls
    if (img->worldMap[(int)oldPlayerY][(int)img->player.x] == 1)
    {
        // Undo the player's movement if there is a wall in the new X position
        img->player.x = oldPlayerX;
    }
    if (img->worldMap[(int)img->player.y][(int)oldPlayerX] == 1)
    {
        // Undo the player's movement if there is a wall in the new Y position
        img->player.y = oldPlayerY;
    }

    double oldDirY = img->player.dir_y;  // Add this line
    double oldPlaneY = img->player.plane_y;
	
    if (keys->left)
    {
        // Handle rotation to the left
        double oldDirX = img->player.dir_x;
        img->player.dir_x = img->player.dir_x * cos(-ROT_SPEED) - img->player.dir_y * sin(-ROT_SPEED);
        img->player.dir_y = oldDirX * sin(-ROT_SPEED) + img->player.dir_y * cos(-ROT_SPEED);

        double oldPlaneX = img->player.plane_x;
        img->player.plane_x = img->player.plane_x * cos(-ROT_SPEED) - img->player.plane_y * sin(-ROT_SPEED);
        img->player.plane_y = oldPlaneX * sin(-ROT_SPEED) + img->player.plane_y * cos(-ROT_SPEED);
		        // Check for collisions with walls after rotation
        if (img->worldMap[(int)oldPlayerY][(int)img->player.x] == 1 || img->worldMap[(int)img->player.y][(int)oldPlayerX] == 1)
        {
            // Undo the rotation if there is a wall
            img->player.dir_x = oldDirX;
            img->player.dir_y = oldDirY;
            img->player.plane_x = oldPlaneX;
            img->player.plane_y = oldPlaneY;
        }

    }
    if (keys->right)
    {
        // Handle rotation to the right
        double oldDirX = img->player.dir_x;
        img->player.dir_x = img->player.dir_x * cos(ROT_SPEED) - img->player.dir_y * sin(ROT_SPEED);
        img->player.dir_y = oldDirX * sin(ROT_SPEED) + img->player.dir_y * cos(ROT_SPEED);

        double oldPlaneX = img->player.plane_x;
        img->player.plane_x = img->player.plane_x * cos(ROT_SPEED) - img->player.plane_y * sin(ROT_SPEED);
        img->player.plane_y = oldPlaneX * sin(ROT_SPEED) + img->player.plane_y * cos(ROT_SPEED);
		        // Check for collisions with walls after rotation
        if (img->worldMap[(int)oldPlayerY][(int)img->player.x] == 1 || img->worldMap[(int)img->player.y][(int)oldPlayerX] == 1)
        {
            // Undo the rotation if there is a wall
            img->player.dir_x = oldDirX;
            img->player.dir_y = oldDirY;
            img->player.plane_x = oldPlaneX;
            img->player.plane_y = oldPlaneY;
        }
    }

    // Continue with rendering logic
    memset(img->addr, 0, WIDTH * HEIGHT * (img->bits_per_pixel / 8));
    if (cast_rays(img) == -1)
        return (free_all(img), -1);
    update_image(img, keys);
    return (0);
}

int mouse_motion(int x, int y, t_keys *keys)
{
    t_data *img = keys->img;

    if (y != -1 && keys->space)
    {
        // Calculate the change in mouse x-coordinate relative to the center of the screen
        int dx = x - WIDTH / 2;

        // Adjust rotation speed based on the change in mouse position
        double rotation_speed = 0.0002 * dx;

        // Update the player's view direction and plane direction
        double oldDirX = img->player.dir_x;
        img->player.dir_x = img->player.dir_x * cos(rotation_speed) - img->player.dir_y * sin(rotation_speed);
        img->player.dir_y = oldDirX * sin(rotation_speed) + img->player.dir_y * cos(rotation_speed);

        double oldPlaneX = img->player.plane_x;
        img->player.plane_x = img->player.plane_x * cos(rotation_speed) - img->player.plane_y * sin(rotation_speed);
        img->player.plane_y = oldPlaneX * sin(rotation_speed) + img->player.plane_y * cos(rotation_speed);

        // Reset the mouse position to the center of the screen
        mlx_mouse_move(keys->img->mlx, keys->img->mlx_win, WIDTH / 2, HEIGHT / 2);
    }
    return (0);
}

int key_press(int keycode, t_keys *keys)
{
    if (keycode == 119) // W key
        keys->w = true;
    if (keycode == 115)  // S key
        keys->s = true;
    if (keycode == 97)  // A key
        keys->a = true;
    if (keycode == 100)  // D key
        keys->d = true;
    if (keycode == 65361) // Left arrow key
        keys->left = true;
    if (keycode == 65363) // Right arrow key
        keys->right = true;
     if (keycode == 32) // Space key
    {
        // Toggle mouse mode
        keys->space = !keys->space;
        keys->img->doors.isOpen = !keys->img->doors.isOpen;

        if (keys->space)
        {
            // Hide the mouse cursor
            mlx_mouse_hide(keys->img->mlx, keys->img->mlx_win);
            // Reset the mouse position to the center of the screen
            mlx_mouse_move(keys->img->mlx, keys->img->mlx_win, WIDTH / 2, HEIGHT / 2);
        }
        else
        {
            // Show the mouse cursor
            mlx_mouse_show(keys->img->mlx, keys->img->mlx_win);
        }
    }
    return (0);
}