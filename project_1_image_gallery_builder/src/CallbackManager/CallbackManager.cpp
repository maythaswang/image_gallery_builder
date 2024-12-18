#include "./CallbackManager.h"

CallbackManager::CallbackManager(GLFWwindow *window, ss::Camera *camera)
{
    this->window = window;
    this->camera = camera;
    this->is_focusing = 0;

    // Set callbacks
    this->set_window_resize_callback();
    this->set_keyboard_callback();
    this->set_cursor_position_callback();
    this->set_mouse_click_callback();
}

void CallbackManager::poll_events()
{
    if (this->is_focusing)
    {
        this->update_camera_rotate();
        this->handle_key_move();
    }
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
                        if(callback_manager->get_is_focusing()) 
                        {
                            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                            callback_manager->toggle_focusing();
                        } 
                        else
                        {
                            glfwSetWindowShouldClose(callback_manager->window, true);
                        }
                        break;
                    case GLFW_KEY_H: 
                        std::cout << "HELP MESSAGE HERE" << std::endl; // Do an inline or something
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

                                       glViewport(0, 0, width, height); });
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
            if(!callback_manager->get_is_focusing()) {
                callback_manager->old_mouse_pos_x = posX;
                callback_manager->old_mouse_pos_y = posY;
            }
        } });
}

void CallbackManager::update_camera_rotate()
{
    double delta_mouse_pos_x = this->mouse_pos_x - this->old_mouse_pos_x;
    double delta_mouse_pos_y = this->mouse_pos_y - this->old_mouse_pos_y;
    if (delta_mouse_pos_x != 0 || delta_mouse_pos_y != 0)
    {
        this->camera->free_rotate(delta_mouse_pos_x, delta_mouse_pos_y);
    }
    this->old_mouse_pos_x = this->mouse_pos_x;
    this->old_mouse_pos_y = this->mouse_pos_y;
}

void CallbackManager::set_mouse_click_callback()
{
    glfwSetWindowUserPointer(this->window, reinterpret_cast<void *>(this));

    glfwSetMouseButtonCallback(this->window, [](GLFWwindow *window, int button, int action, int mods)
                               {
        CallbackManager *callback_manager = reinterpret_cast<CallbackManager *>(glfwGetWindowUserPointer(window));
        if (callback_manager)
        {
            if(action == GLFW_PRESS && !callback_manager->get_is_focusing())
            {
                callback_manager->toggle_focusing();
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        } });
}

void CallbackManager::toggle_focusing()
{
    this->is_focusing = !this->is_focusing;
}

bool CallbackManager::get_is_focusing()
{
    return this->is_focusing;
}

void CallbackManager::handle_key_move()
{
    // this so that compound keys can be handled.
    if (glfwGetKey(this->window, GLFW_KEY_W))
    {
        this->camera->free_forward(0.5);
    }
    else if (glfwGetKey(this->window, GLFW_KEY_S))
    {
        this->camera->free_forward(-0.5);
    }

    if (glfwGetKey(this->window, GLFW_KEY_D))
    {
        this->camera->free_side_translate(0.5);
    }
    else if (glfwGetKey(this->window, GLFW_KEY_A))
        this->camera->free_side_translate(-0.5);
    {
    }
}