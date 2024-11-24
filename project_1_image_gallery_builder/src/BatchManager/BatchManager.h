#ifndef BATCH_MANAGER_H
#define BATCH_MANAGER_H
#pragma once
#include <lin_alg/lin_alg.h>
#include <simple_scene/simple_scene.h>
#include "../Scene/Scene.h"
#include <vector>
#include <iostream>

struct TextureInformation{
    int id; 
    float width; 
    float height;
    bool valid;
};

class BatchManager
{
public:
    BatchManager();
    ~BatchManager();

    int add_material(ss::Material);

    TextureInformation add_texture(std::string file_path, GLuint lod, GLenum internal_format, GLenum format);

    void add_mesh(ss::Mesh);

    void add_point_light(ss::PointLight);

    void next_batch();

    int get_batch_count();

    int get_max_texture_per_batch();

    void build_all_batches();

    RenderComponents use_current_batch(ss::Shader *);

    void set_dimension(int, int);

    int get_destination_batch(int);

private:
    int current_batch;
    int material_count;
    int row, col;
    std::vector<Scene> scene_storage;
    ss::LightManager light_manager; // We will use this one for all batches.
    
    // Also might need a map to see which material belong to which batch.
    // - This can be mitigated if it is possible to ensure that when user input their textures
    //   - auto-assign along with the image they want to add, if that was done there is no need to implement such??

    // Might need a map for mapping material name to an ID in local batch or at least subtract by an amount
    // Also might need a map for mapping texture ID in global to each local batch
};

#endif