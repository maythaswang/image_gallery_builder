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
};

#endif