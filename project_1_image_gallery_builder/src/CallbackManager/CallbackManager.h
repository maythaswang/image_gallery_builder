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
    CallbackManager(GLFWwindow *, ss::Camera *);

    /**
     * @brief Main function for listening for input and call other methods
     *
     */
    void poll_events();

    /**
     * @brief Get the is_focusing status
     * 
     * @return true 
     * @return false 
     */
    bool get_is_focusing();

    /**
     * @brief toggle is_focusing on-off 
     * 
     */
    void toggle_focusing();

private:
    GLFWwindow *window;
    ss::Camera *camera;

    /**
     * The idea is we start with a screen with cursor (non-focus mode).
     * - In this mode we cannot move
     * 
     * To focus, we click any mouse button
     * - This allows rotation and stuffs
     * - If we press esc in this mode, we return to the non-focus mode where another esc click will leave the app
     */
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

    /**
     * @brief Handle movement keys for WASD
     * 
     */
    void handle_key_move();
};
#endif