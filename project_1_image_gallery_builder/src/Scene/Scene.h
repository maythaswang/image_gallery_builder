#ifndef SCENE_H
#define SCENE_H
#pragma once
#include <lin_alg/lin_alg.h>
#include <simple_scene/simple_scene.h>
#include <vector>
#include <iostream>

struct RenderComponents
{
    GLuint VAO[1];
    GLuint VBO[4];
    GLuint EBO[1];
    GLuint n_vert;
    GLuint n_inds;
};

class Scene
{
public:
    Scene();
    ~Scene();

    void add_material(ss::Material);
    void add_texture(std::string file_path, GLuint lod, GLenum internal_format, GLenum format);
    void add_point_light(ss::PointLight);
    void add_mesh(ss::Mesh);
    void build_scene();
    void use_materials(ss::Shader*);

    RenderComponents get_render_components();

private:
    ss::MaterialManager material_manager;
    ss::TextureManager texture_manager;
    ss::LightManager light_manager;
    RenderComponents render_components;

    bool render_components_initialized;
    bool render_components_updated;

    std::vector<ss::Mesh> mesh_storage; // Maybe for rebuilding scene.

    std::vector<lin_alg::vec3> vertices;
    std::vector<lin_alg::ivec3> indices;
    std::vector<lin_alg::vec3> normals;
    std::vector<GLfloat> tex_coords;
    std::vector<GLfloat> material_ids;
    
    int material_count; // Bound everything to material count
    int texture_count;  

    /**
     * @brief Initialize buffers using the given information
     * 
     */
    void init_buf();
};

#endif