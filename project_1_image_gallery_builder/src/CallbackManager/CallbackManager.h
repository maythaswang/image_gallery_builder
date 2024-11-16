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
     * @brief Main function for listening for input and call other methods
     *
     */
    void poll_events();

    bool get_is_focusing();
    void toggle_focusing();

private:
    GLFWwindow *window;
    Camera *camera;
    bool is_focusing;

    double old_mouse_pos_x;
    double old_mouse_pos_y;

    double mouse_pos_x;
    double mouse_pos_y;

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

    /**
     * @brief Set the mouse click callback
     *
     */
    void set_mouse_click_callback();

    void handle_key_move();
};
#endif