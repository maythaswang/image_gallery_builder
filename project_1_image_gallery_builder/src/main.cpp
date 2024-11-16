#include <GLCommon.h>
#include <simple_scene/simple_scene.h>
#include <lin_alg/lin_alg.h>

#include "./ProgramSetup/ProgramSetup.h"
#include "./CallbackManager/CallbackManager.h"

#include "Lab4_textured_box.h"

#include <iostream>

// TO RUN DIFFERENT FILES, PLEASE UNCOMMENT ONE OF THE LINES BELOW
// ---------------------------------------------------------------

#define CURRENT_MAIN build_box

// ------------ PLEASE MODIFY THE LINES ABOVE TO TEST ------------

// Forward Declarations
// ---------------------------------------------------------------
GLFWwindow *init_glfw_glad();
unsigned int compile_shader();
void render_routine(GLFWwindow *, Shader *, TextureManager *, GLuint, GLuint, CallbackManager *, Camera * );
void termination_routine(RenderComponents *render_components, Shader *shader_program);

// CONSTANTS
// ---------------------------------------------------------------

const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
const char *SCREEN_NAME = "Image Gallery in OGL";

int main()
{   
    // Initialize program and window
    GLFWwindow *window = init_glfw_glad();
    if (!window)
    {
        std::cerr << "Failed at program initialization stage." << std::endl;
        return -1;
    }

    // Setup Camera
    Camera camera = Camera();

    Camera test_cam = Camera();
    test_cam.free_rotate(-15,-15);

    CallbackManager callback_manager = CallbackManager(window, &camera);

    // Setup Shader
    Shader shader_program = Shader();
    GLuint vertex_shader = shader_program.compile_shader("./resources/shader_source/simple_shader.vert", GL_VERTEX_SHADER);
    GLuint fragment_shader = shader_program.compile_shader("./resources/shader_source/simple_shader.frag", GL_FRAGMENT_SHADER);
    shader_program.link_shader(vertex_shader);
    shader_program.link_shader(fragment_shader);

    // Setup Textures
    TextureManager texture_manager = TextureManager();
    texture_manager.create_texture("resources/textures/container.jpg", 0, GL_RGB, GL_RGB);
    texture_manager.create_texture("resources/textures/brick.jpg", 0, GL_RGB, GL_RGB);
    texture_manager.create_texture("resources/textures/diamond_grip_steel.jpg", 0, GL_RGB, GL_RGB);
    texture_manager.create_texture("resources/textures/ground.jpg", 0, GL_RGB, GL_RGB);
    texture_manager.create_texture("resources/textures/wall.jpg", 0, GL_RGB, GL_RGB);
    texture_manager.use_all_textures(&shader_program);
    texture_manager.activate_all_textures();

    // Draw in wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Add mesh
    RenderComponents render_components = CURRENT_MAIN();

    GLuint VAO = render_components.VAO[0];
    GLuint VBO = render_components.VBO[0];
    GLuint EBO = render_components.EBO[0];
    GLuint n_inds = render_components.n_inds;

    glEnable(GL_DEPTH_TEST);

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
        render_routine(window, &shader_program, &texture_manager, VAO, n_inds, &callback_manager, &camera);
    }

    // Terminate
    termination_routine(&render_components, &shader_program);
}

// SUBROUTINES
// ---------------------------------------------------------------

/**
 * @brief Initialize glfw and glad
 *
 * @return GLFWwindow* if success
 * @return NULL if failure
 */
GLFWwindow *init_glfw_glad()
{
    bool glfw_initialized = ProgramInit::initialize_glfw();
    if (!glfw_initialized)
        return NULL;
    WindowFactory window_factory = WindowFactory();
    GLFWwindow *window = window_factory.create_window(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);

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

/**
 * @brief Render a frame.
 *
 * @param window
 * @param shaderProgram
 * @param VAO
 * @param n_inds number of indices
 */
void render_routine(GLFWwindow *window, Shader *shader_program, TextureManager *texture_manager, GLuint VAO, GLuint n_inds, CallbackManager * callback_manager, Camera * camera)
{
    callback_manager->poll_events();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_program->use();
    texture_manager->use_all_textures(shader_program);
    shader_program->set_mat4("modelview", camera->get_view_matrix());
    shader_program->set_mat4("projection", camera->get_projection_matrix());

    // texture_manager->activate_all_textures();
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 3 * n_inds, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // no need to unbind it every time

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void termination_routine(RenderComponents *render_components, Shader *shader_program)
{
    glDeleteVertexArrays(1, render_components->VAO);
    glDeleteBuffers(3, render_components->VBO);
    glDeleteBuffers(1, render_components->EBO);
    shader_program->delete_shader();

    glfwTerminate();
}
