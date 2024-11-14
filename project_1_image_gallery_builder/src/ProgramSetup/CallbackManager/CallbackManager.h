#ifndef CALLBACK_MANAGER_H
#define CALLBACK_MANAGER_H
#pragma once
#include <GLCommon.h>
#include <iostream>

class CallbackManager
{
public:
    /**
     * @brief Construct a new Callback Manager
     *
     * @param window glfw window where we want to use as our display window
     */
    CallbackManager(GLFWwindow *);

    /**
     * @brief Main function for processing input
     *
     */
    void process_input();

private:
    GLFWwindow *window;

    /**
     * @brief Handle each mouse and keyboard input accordingly.
     *
     */
    void handle_input();

    /**
     * @brief Listen to inputs
     * 
     */
    void listen();

    /**
     * @brief Set the window and camera aspect ratio when framebuffer gets resized.
     *
     */
    void set_window_resize_callback();

    /**
     * @brief Set the keyboard callback.
     *
     */
    void set_keyboard_callback();
};
#endif