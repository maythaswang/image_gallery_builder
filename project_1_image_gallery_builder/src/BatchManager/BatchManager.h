#ifndef BATCH_MANAGER_H
#define BATCH_MANAGER_H
#pragma once
#include <lin_alg/lin_alg.h>
#include <simple_scene/simple_scene.h>
#include "../Scene/Scene.h"
#include <vector>
#include <iostream>

class BatchManager
{
public:
    BatchManager();
    ~BatchManager();

    void add_material(ss::Material);

    void add_mesh(ss::Mesh);

    void next_batch();

    void get_render_components();

    int get_batch_count();

    int get_max_texture_per_batch();

    void prepare_all_batches();
    void build_batch();

private:
    int current_batch;
    int material_count;
    int scene_count;
    std::vector<Scene> scenes;
    ss::LightManager light_manager; // We will use this one for all batches.

    // Also might need a map to see which material belong to which batch.
    // - This can be mitigated if it is possible to ensure that when user input their textures
    //   - auto-assign along with the image they want to add, if that was done there is no need to implement such??
    
    // Might need a map for mapping material name to an ID in local batch or at least subtract by an amount
    // Also might need a map for mapping texture ID in global to each local batch
};

#endif