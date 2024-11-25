#ifndef SCENE_H
#define SCENE_H
#pragma once
#include <lin_alg/lin_alg.h>
#include <simple_scene/simple_scene.h>
#include <vector>
#include <iostream>

/**
 * @brief Payload for storing components required for rendering scene.
 *
 */
struct RenderComponents
{
    GLuint VAO[1];
    GLuint VBO[4];
    GLuint EBO[1];
    GLuint n_vert;
    GLuint n_inds;
};

/**
 * @brief Stores scene data and handle creating buffers and sending uniforms
 *
 */
class Scene
{
public:
    Scene();
    ~Scene();

    /**
     * @brief Add material to the material_manager
     *
     * @param material
     */
    void add_material(ss::Material material);

    /**
     * @brief Add texture to the texture manager
     *
     * @param file_path
     * @param lod
     * @param internal_format
     * @param format
     * @return true if success,
     * @return false if failure
     */
    bool add_texture(std::string file_path, GLuint lod, GLenum internal_format, GLenum format);

    /**
     * @brief Add point light to the light manager
     *
     * @param point_light
     */
    void add_point_light(ss::PointLight point_light);

    /**
     * @brief Add mesh to the mesh storage
     *
     * @param mesh
     */
    void add_mesh(ss::Mesh mesh);

    /**
     * @brief Prepare all components for the use stage.
     * @note Due to time constraint in implementation, this function should only be called once.
     * @note Any subsequent calls will create unintended effects (since the vector is not rebuilt but appened.)
     *
     */
    void build_scene();

    /**
     * @brief Use all prepared components
     *
     * @param shader_program
     */
    void use_materials(ss::Shader *shader_program);

    /**
     * @brief Get the render components of the current scene
     *
     * @return RenderComponents
     */
    RenderComponents get_render_components();

    /**
     * @brief Get the texture data
     *
     * @param texture_id
     * @param width
     * @param height
     */
    void get_texture_data(int texture_id, GLfloat &width, GLfloat &height);

    /**
     * @brief Get the texture count
     *
     * @return number of textures
     */
    int get_texture_count();

    /**
     * @brief Get the material count object
     *
     * @return number of materials
     */
    int get_material_count();

private:
    ss::MaterialManager material_manager;
    ss::TextureManager texture_manager;
    ss::LightManager light_manager;
    RenderComponents render_components;

    bool render_components_initialized;
    bool render_components_updated;

    std::vector<ss::Mesh> mesh_storage;

    std::vector<lin_alg::vec3> vertices;
    std::vector<lin_alg::ivec3> indices;
    std::vector<lin_alg::vec3> normals;
    std::vector<GLfloat> tex_coords;
    std::vector<GLfloat> material_ids;

    /**
     * @brief Initialize buffers using the component information and store it in RenderComponents object
     *
     */
    void init_buf();
};

#endif