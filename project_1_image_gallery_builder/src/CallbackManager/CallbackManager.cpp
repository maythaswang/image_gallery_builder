#include "./CallbackManager.h"

CallbackManager::CallbackManager(GLFWwindow *window, Camera *camera)
{
    this->window = window;
    this->camera = camera;

    // Set callbacks
    this->set_window_resize_callback();
    this->set_keyboard_callback();
    this->set_cursor_position_callback();
}

void CallbackManager::process_input()
{
    this->update_camera_rotate();
}

void CallbackManager::set_keyboard_callback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    glfwSetKeyCallback(this->window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       {
        CallbackManager * callback_manager = reinterpret_cast<CallbackManager *> ( glfwGetWindowUserPointer ( window ));
        if (callback_manager){
            if (action == GLFW_PRESS){
                switch(key){
                    case GLFW_KEY_ESCAPE: 
                        glfwSetWindowShouldClose(callback_manager->window, true);
                        break;
                    case GLFW_KEY_H: 
                        std::cout << "HELP MESSAGE HERE" << std::endl;
                        break;
                }
            }

        } });
}

void CallbackManager::set_window_resize_callback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    // set to call this lambda function everytime the screen gets resized
    // This can be made as a normal function if it was a static function.
    glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow *window, int width, int height)
                                   {
                                       CallbackManager *callback_manager = reinterpret_cast<CallbackManager *>(glfwGetWindowUserPointer(window));
                                       if (callback_manager)
                                           callback_manager->camera->set_aspect(width, height);

                                       glViewport(0, 0, width, height);
                                   });
}

void CallbackManager::set_cursor_position_callback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    glfwSetCursorPosCallback(this->window, [](GLFWwindow *window, double posX, double posY)
                             {
        CallbackManager *callback_manager = reinterpret_cast<CallbackManager *>(glfwGetWindowUserPointer(window));
        if (callback_manager)
        {
            callback_manager->mouse_pos_x = posX;
            callback_manager->mouse_pos_y = posY;
        } });
}

void CallbackManager::update_camera_rotate()
{
    double delta_mouse_pos_x = this->mouse_pos_x - this->old_mouse_pos_x;
    double delta_mouse_pos_y = this->mouse_pos_y - this->old_mouse_pos_y;

    this->camera->free_rotate(delta_mouse_pos_x, delta_mouse_pos_y);

    this->old_mouse_pos_x = this->mouse_pos_x;
    this->old_mouse_pos_y = this->mouse_pos_y;
}