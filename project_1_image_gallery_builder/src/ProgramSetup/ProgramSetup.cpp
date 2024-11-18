#include "ProgramSetup.h"

/**
 * @brief Initialize glfw and glad
 *
 * @return GLFWwindow* if success
 * @return NULL if failure
 */
GLFWwindow *init_glfw_glad(const unsigned int width, const unsigned int height , const char* name )
{
    bool glfw_initialized = ProgramInit::initialize_glfw();
    if (!glfw_initialized)
        return NULL;
    WindowFactory window_factory = WindowFactory();
    GLFWwindow *window = window_factory.create_window(width, height, name);

    if (!window)
    {
        glfwTerminate();
        return NULL;
    }

    bool glad_initialized = ProgramInit::initialize_glad();
    if (!glad_initialized)
        return NULL;

    return window;
}
