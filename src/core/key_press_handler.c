#include "../../includes/cub3d.h"

static void handle_movement_keys(int keycode, t_game_data *game_data)
{
    if (keycode == W_KEY)
        game_data->key.move_up = 1;
    else if (keycode == S_KEY)
        game_data->key.move_down = 1;
    else if (keycode == A_KEY)
        game_data->key.move_left = 1;
    else if (keycode == D_KEY)
        game_data->key.move_right = 1;
}

static void handle_rotation_keys(int keycode, t_game_data *game_data)
{
    if (keycode == RIGHT_ARROW)
        game_data->key.rotate_right = 1;
    else if (keycode == LEFT_ARROW)
        game_data->key.rotate_left = 1;
}

int handle_key_press(int keycode, t_game_data *game_data)
{
    if (keycode == ESC_KEY)
    {
        printf("\033[0;32mCub3D closed successfully :)\n\033[0m\n\n");
        exit(0);
    }
    
    handle_movement_keys(keycode, game_data);
    handle_rotation_keys(keycode, game_data);

    return (0);
}

static void reset_movement_keys(int keycode, t_game_data *game_data)
{
    if (keycode == W_KEY)
        game_data->key.move_up = 0;
    else if (keycode == S_KEY)
        game_data->key.move_down = 0;
    else if (keycode == A_KEY)
        game_data->key.move_left = 0;
    else if (keycode == D_KEY)
        game_data->key.move_right = 0;
}

static void reset_rotation_keys(int keycode, t_game_data *game_data)
{
    if (keycode == RIGHT_ARROW)
        game_data->key.rotate_right = 0;
    else if (keycode == LEFT_ARROW)
        game_data->key.rotate_left = 0;
}

int handle_key_release(int keycode, t_game_data *game_data)
{
    reset_movement_keys(keycode, game_data);
    reset_rotation_keys(keycode, game_data);

    return (0);
}
