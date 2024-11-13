#include "./ProgramInit.h"

bool ProgramInit::initialize_glfw()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize glfw.";
        return 0;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error_callback);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    return 1;
}


bool ProgramInit::initialize_glad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 0;
    }
    return 1;
}

void ProgramInit::error_callback(int error, const char *description)
{
    fprintf(stderr, "Error %s\n", description);
}
