#ifndef BATCH_MANAGER_H
#define BATCH_MANAGER_H
#pragma once
#include <lin_alg/lin_alg.h>
#include <simple_scene/simple_scene.h>
#include <vector>
#include <iostream>

struct RenderComponents
{
    GLuint VAO[1];
    GLuint VBO[3];
    GLuint EBO[1];
    GLuint n_vert;
    GLuint n_inds;
};

class BatchManager
{
public:
    BatchManager();
    ~BatchManager();

    void add_material(ss::Material);

    void add_mesh(ss::Mesh);

    void next_batch();

    void get_render_components();

    void set_current_batch();

    int get_batch_count();

    int get_max_texture_per_batch();

    void begin_batching();

private:
    int batch_count;
    int current_batch;

    ss::TextureManager texture_manager;
    std::vector<std::vector<lin_alg::vec3>> vertices; // vertices[batch][vertices_index]
    std::vector<std::vector<lin_alg::vec3>> indices;
    std::vector<std::vector<lin_alg::vec3>> normals;
    std::vector<std::vector<GLfloat>> texture_ids;
    std::vector<std::vector<GLfloat>> tex_coords;
    std::vector<std::vector<int>> material_ids;
    std::vector<int> texture_count;

    // Also might need a map to see which material belong to which batch.
    // - This can be mitigated if it is possible to ensure that when user input their textures
    //   - auto-assign along with the image they want to add, if that was done there is no need to implement such??
    
    // Might need a map for mapping material name to an ID in local batch or at least subtract by an amount
    // Also might need a map for mapping texture ID in global to each local batch

    std::vector<int> batch_materials;

    void activate_batch_materials(int);

    /**
     * @brief Initialize buffers using the given information and return it through ptr
     *
     * @param render_components RenderComponent struct to store VAO, VBOs, EBO and number of vertices and indices
     * @param vertices
     * @param indices
     * @param normals
     * @param texture_coords
     * @param texture_ids
     */
    void init_buf(RenderComponents *, GLfloat *, GLuint *, GLfloat *, GLfloat *, GLfloat *);
};

#endif