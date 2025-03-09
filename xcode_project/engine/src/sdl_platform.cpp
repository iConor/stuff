#include "sdl_platform.h"


#include <SDL2/SDL_rwops.h>


char* sdl_read_entire_file(const char* file_name)
{
    SDL_RWops* file_handle = SDL_RWFromFile(file_name, "r");

    if(!file_handle)
    {
        printf("SDL_RWFromFile failed: %s\n", SDL_GetError());
        return NULL;
    }

    Sint64 file_size = SDL_RWsize(file_handle);
    char* file_data = (char*)malloc(file_size + 1);

    Sint64 total_bytes_read = 0;
    Sint64 bytes_read = 1;
    char* file_pointer = file_data;

    while(total_bytes_read < file_size && bytes_read != 0)
    {
        bytes_read = SDL_RWread(file_handle, file_pointer, 1, (file_size - total_bytes_read));
        total_bytes_read += bytes_read;
        file_pointer += bytes_read;
    }
    SDL_RWclose(file_handle);
    file_data[total_bytes_read] = '\0';

    return file_data;
}


//static const float X_AXIS_MAX =  32767.0f;
//static const float Y_AXIS_MAX = -32767.0f;
//
//gamepad_state update_gamepad(SDL_GameController* controller)
//{
//    gamepad_state gamepad = {};
//
//    gamepad.left_x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) / X_AXIS_MAX;
//    gamepad.left_y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) / Y_AXIS_MAX;
//
//    gamepad.right_x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX) / X_AXIS_MAX;
//    gamepad.right_y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY) / Y_AXIS_MAX;
//
//    gamepad.left_trigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / X_AXIS_MAX;
//    gamepad.right_trigger = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / X_AXIS_MAX;
//
//    gamepad.up = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
//    gamepad.down = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
//    gamepad.left = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
//    gamepad.right = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
//
//    gamepad.a = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
//    gamepad.b = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
//    gamepad.x = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X);
//    gamepad.y = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y);
//
//    gamepad.left_stick = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSTICK);
//    gamepad.right_stick = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
//    gamepad.left_shoulder = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
//    gamepad.right_shoulder = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
//
//    gamepad.back = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK);
//    gamepad.guide = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_GUIDE);
//    gamepad.start = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
//    return gamepad;
//}
