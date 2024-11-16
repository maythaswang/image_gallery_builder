#ifndef CALLBACK_MANAGER_H
#define CALLBACK_MANAGER_H
#pragma once
#include <GLCommon.h>
#include <iostream>
#include <simple_scene/simple_scene.h>

class CallbackManager
{
public:
    /**
     * @brief Construct a new Callback Manager
     *
     * @param window glfw window where we want to use as our display window
     * @param camera the current camera
     */
    CallbackManager(GLFWwindow *, Camera *);

    /**
     * @brief Main function for processing input
     *
     */
    void process_input();

private:
    GLFWwindow *window;
    Camera *camera;

    double old_mouse_pos_x;
    double old_mouse_pos_y;

    double mouse_pos_x;
    double mouse_pos_y;

    /**
     * @brief Handle each mouse and keyboard input accordingly.
     *
     */
    void handle_input();

    /**
     * @brief Set the window and camera aspect ratio when framebuffer gets resized.
     * TODO: Maybe fix this
     */
    void set_window_resize_callback();

    /**
     * @brief Set the keyboard callback.
     *
     */
    void set_keyboard_callback();

    /**
     * @brief Set the cursor position callback.
     *
     */
    void set_cursor_position_callback();

    /**
     * @brief Update camera position
     * 
     */
    void update_camera_rotate();
};
#endif