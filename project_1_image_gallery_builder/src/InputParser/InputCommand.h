#ifndef INPUT_COMMAND_ENUM
#define INPUT_COMMAND_ENUM
#pragma once
enum InputCommand
{
    // IGNORE COMMENTS
    IGNORE, // #

    // BASIC SETUP
    SIZE, // size <row_n> <col_n>
    PLAN, // for the next n row, we will take in the floor plan
          // <1> <1> <0> <0> <1> each separated by space
          // <0> <1> <0> <0> <1> each separated by space until row n (1: have room, 0:no room)

    // ROOM SETUP (these must be done in successions)
    // We will count room id in row-major form. 0,0 is on the top-left corner
    ROOM,  // room <row> <col>
    LIGHT, // light on/off (0:off, 1:on)
    WALL,  // wall <top> <bottom> <left> <right>  (0: no wall, 1:wall)

    // These are optionals
    // NOTE: THESE FILES MUST BE IN ./scene/<scene_name>/textures/<filename>
    IMAGE_TOP,    // image_top <image filename>
    IMAGE_BOTTOM, // image_bottom <image filename>
    IMAGE_LEFT,   // image_left <image filename>
    IMAGE_RIGHT,  // image_right <image filename>
};
#endif