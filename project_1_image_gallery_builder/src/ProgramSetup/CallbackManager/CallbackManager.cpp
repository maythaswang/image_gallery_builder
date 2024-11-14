#include "./CallbackManager.h"

CallbackManager::CallbackManager(GLFWwindow *window)
{
    this->window = window;

    // Set callbacks
    this->set_keyboard_callback();
}

void CallbackManager::listen()
{
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
                                   { glViewport(0, 0, width, height); });
}