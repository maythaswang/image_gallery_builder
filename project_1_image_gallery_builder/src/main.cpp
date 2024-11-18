#include <GLCommon.h>
#include <simple_scene/simple_scene.h>
#include <lin_alg/lin_alg.h>

#include "./ProgramSetup/ProgramSetup.h"
#include "./CallbackManager/CallbackManager.h"

#include "./GeometryBuilder/GeometryBuilder.h"
#include "./Scene/Scene.h"
#include "./RoomBuilder/RoomBuilder.h"

#include <iostream>

// Forward Declarations
// ---------------------------------------------------------------
void render_routine(GLFWwindow *, ss::Shader *, Scene *, GLuint, GLuint, CallbackManager *, ss::Camera *);
void termination_routine(RenderComponents *render_components, ss::Shader *shader_program);

// CONSTANTS
// ---------------------------------------------------------------

const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
const char *SCREEN_NAME = "Image Gallery in OGL";

// class Sandbox
// {
// public:
//     Sandbox(Scene *scene) {
//         this->scene = scene;
//     };

//     void add_box_test()
//     {
//         ss::Mesh mesh = this->geometry_builder.init_plane(2, 2, 1);

//         this->scene->add_mesh(mesh);
//     }

// private:
//     GeometryBuilder geometry_builder;
//     Scene * scene;
// };

int main()
{
    // Initialize program and window
    GLFWwindow *window = init_glfw_glad(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME);
    if (!window)
    {
        std::cerr << "Failed at program initialization stage." << std::endl;
        return -1;
    }

    // Setup Camera
    ss::Camera camera = ss::Camera();

    CallbackManager callback_manager = CallbackManager(window, &camera);

    // Setup Shader
    ss::Shader shader_program = ss::Shader();
    GLuint vertex_shader = shader_program.compile_shader("./resources/shader_source/simple_shader.vert", GL_VERTEX_SHADER);
    GLuint fragment_shader = shader_program.compile_shader("./resources/shader_source/simple_shader.frag", GL_FRAGMENT_SHADER);
    shader_program.link_shader(vertex_shader);
    shader_program.link_shader(fragment_shader);

    // Draw in wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Add mesh
    /// SANDBOX REGION

    // Setup Textures
    // ss::TextureManager texture_manager = ss::TextureManager();
    // texture_manager.create_texture("resources/textures/container.jpg", 0, GL_RGB, GL_RGB);
    // texture_manager.create_texture("resources/textures/brick.jpg", 0, GL_RGB, GL_RGB);
    // texture_manager.create_texture("resources/textures/diamond_grip_steel.jpg", 0, GL_RGB, GL_RGB);
    // texture_manager.create_texture("resources/textures/ground.jpg", 0, GL_RGB, GL_RGB);
    // texture_manager.create_texture("resources/textures/wall.jpg", 0, GL_RGB, GL_RGB);
    // texture_manager.use_all_textures(&shader_program);
    // texture_manager.activate_all_textures();

    // ss::Material material_zero;
    // material_zero.ambient = lin_alg::vec3(1, 1, 1);
    // material_zero.diffuse = lin_alg::vec3(1, 1, 1);
    // material_zero.specular = lin_alg::vec3(1, 1, 1);
    // material_zero.shininess = 0.7f;
    // material_zero.texture_id = 0;

    ss::Material material_one;
    material_one.ambient = lin_alg::vec3();
    material_one.diffuse = lin_alg::vec3();
    material_one.specular = lin_alg::vec3();
    material_one.shininess = 0.5f;
    material_one.texture_id = 1;

    GeometryBuilder geometry_builder = GeometryBuilder();
    std::vector<GLfloat> center = {0.0f, 0, 0}; // Let's have the center at origin.
    ss::Mesh box_mesh = geometry_builder.init_box(center, 1, 1, 1);
    Scene scene = Scene();

    // scene.add_material(material_zero);
    // scene.add_mesh(plane_mesh);

    RoomBuilder room_builder = RoomBuilder(&scene, 1, 1);
    room_builder.init_basic_materials();
    room_builder.build_room(0, 0, 0, 1, 1, 1, 1, "", "", "", "");

    scene.add_material(material_one);
    scene.add_texture("resources/textures/container.jpg", 0, GL_RGB, GL_RGB);
    scene.add_mesh(box_mesh);

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

/**
 * @brief Render a frame.
 *
 * @param window
 * @param shaderProgram
 * @param VAO
 * @param n_inds number of indices
 */
void render_routine(GLFWwindow *window, ss::Shader *shader_program, Scene *scene, GLuint VAO, GLuint n_inds, CallbackManager *callback_manager, ss::Camera *camera)
{
    callback_manager->poll_events();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shader_program->use();

    shader_program->set_mat4("modelview", camera->get_view_matrix());
    shader_program->set_mat4("projection", camera->get_projection_matrix());

    scene->use_materials(shader_program);

    // texture_manager->activate_all_textures();
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 3 * n_inds, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // no need to unbind it every time

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
