#ifndef INPUT_COMMAND_ENUM
#define INPUT_COMMAND_ENUM
#pragma once
enum InputCommand
{
    // IGNORE COMMENTS
    IGNORE, // #

    // BASIC SETUP
    DIMENSION, // dimension <row_n> <col_n>

    // ROOM SETUP (these must be done in successions)
    // We will count room id in row-major form. 0,0 is on the top-left corner
    INDEX,  // index <row> <col> (room position)
    LIGHT, // light on/off (0:off, 1:on)
    WALL,  // wall <top> <bottom> <left> <right>  (0: no wall, 1:wall)

    // These are optionals
    // NOTE: THESE FILES MUST BE IN <texture_dir>/<filename>
    IMAGE_TOP,    // image_top <image filename>
    IMAGE_BOTTOM, // image_bottom <image filename>
    IMAGE_LEFT,   // image_left <image filename>
    IMAGE_RIGHT,  // image_right <image filename>

    BUILD_ROOM, // build_room build room with the settings defined before
};
#endif