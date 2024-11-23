#include <GLCommon.h>
#include <simple_scene/simple_scene.h>
#include <lin_alg/lin_alg.h>

#include "./ProgramSetup/ProgramSetup.h"
#include "./CallbackManager/CallbackManager.h"

#include "./GeometryBuilder/GeometryBuilder.h"
#include "./Scene/Scene.h"
#include "./RoomBuilder/RoomBuilder.h"

#include "InputParser/InputParser.h"

#include <iostream>

// Forward Declarations
// ---------------------------------------------------------------
void use_wireframe();
void render_routine(GLFWwindow *, ss::Shader *, Scene *, GLuint, GLuint, CallbackManager *, ss::Camera *);
void termination_routine(RenderComponents *render_components, ss::Shader *shader_program);

// CONSTANTS
// ---------------------------------------------------------------

const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
const char *SCREEN_NAME = "Image Gallery in OGL";

int main(int argc, char *argv[])
{
    // Initialize program and window
    // ----------------------------------------------------------------------------
    GLFWwindow *window = init_glfw_glad(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);
    if (!window)
    {
        std::cerr << "Failed at program initialization stage." << std::endl;
        return -1;
    }

    // Setup Camera
    // ----------------------------------------------------------------------------
    ss::Camera camera = ss::Camera();

    // Setup Callbacks
    // ----------------------------------------------------------------------------
    CallbackManager callback_manager = CallbackManager(window, &camera);

    // Setup Shader
    // ----------------------------------------------------------------------------
    ss::Shader shader_program = ss::Shader();
    GLuint vertex_shader = shader_program.compile_shader("./resources/shader_source/simple_shader.vert", GL_VERTEX_SHADER);
    GLuint fragment_shader = shader_program.compile_shader("./resources/shader_source/simple_shader.frag", GL_FRAGMENT_SHADER);
    shader_program.link_shader(vertex_shader);
    shader_program.link_shader(fragment_shader);

    // Init Scene
    // ----------------------------------------------------------------------------
    Scene scene = Scene();

    // Get input and setup scene
    // ----------------------------------------------------------------------------
    bool load_file_success = 0;

    if (argc == 1)
    {
        std::cout << "No argument provided, loading default sample..." << '\n';
        load_file_success = 1;

        RoomBuilder room_builder = RoomBuilder(&scene, 2, 2);
        room_builder.init_basic_materials();
        room_builder.build_room(0, 0, 1, 0, 1, 1, 0, "", "resources/textures/container.jpg", "resources/textures/wall.jpg", "");
        room_builder.build_room(0, 1, 0, 1, 0, 1, 0, "resources/textures/brick.jpg", "", "", "");
        room_builder.build_room(1, 0, 0, 0, 1, 0, 1, "1", "", "", "resources/textures/wood.png");
        room_builder.build_room(1, 1, 0, 1, 0, 0, 1, "1", "", "", "resources/textures/diamond_grip_steel.jpg");
    }
    else if (argc == 3)
    {
        std::string scene_data = argv[1];
        std::string texture_dir = argv[2];
        std::cout << "Scene data path: " << scene_data << '\n';
        std::cout << "Texture directory path: " << texture_dir << "\n\n";

        std::cout << "Parsing file..." << '\n';
        InputParser input_parser = InputParser();
        load_file_success = input_parser.parse_file(scene_data, texture_dir, &scene);
    }

    if (!load_file_success)
    {
        std::cout << "Failed to read input file, exitting..." << '\n';
        return -1;
    } else {
        std::cout << "Successfully loaded the scene." << '\n';
    }

    // Prepare for render
    // ----------------------------------------------------------------------------
    scene.build_scene();

    RenderComponents render_components = scene.get_render_components();

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
        render_routine(window, &shader_program, &scene, VAO, n_inds, &callback_manager, &camera);
    }

    // Terminate
    termination_routine(&render_components, &shader_program);
}

// SUBROUTINES
// ---------------------------------------------------------------

void render_routine(GLFWwindow *window, ss::Shader *shader_program, Scene *scene, GLuint VAO, GLuint n_inds, CallbackManager *callback_manager, ss::Camera *camera)
{
    callback_manager->poll_events();

    glClearColor(0.05f, 0.05f, 0.07f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader_program->use();

    // A polling function might be good here.
    shader_program->set_vec3("eye_position", camera->get_eye());
    shader_program->set_mat4("view", camera->get_view_matrix());
    shader_program->set_mat4("projection", camera->get_projection_matrix());

    scene->use_materials(shader_program);

    glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 3 * n_inds, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void termination_routine(RenderComponents *render_components, ss::Shader *shader_program)
{
    glDeleteVertexArrays(1, render_components->VAO);
    glDeleteBuffers(4, render_components->VBO);
    glDeleteBuffers(1, render_components->EBO);
    shader_program->delete_shader();

    glfwTerminate();
}

void use_wireframe()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}