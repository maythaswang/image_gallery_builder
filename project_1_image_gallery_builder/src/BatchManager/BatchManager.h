#ifndef BATCH_MANAGER_H
#define BATCH_MANAGER_H
#pragma once
#include <lin_alg/lin_alg.h>
#include <simple_scene/simple_scene.h>
#include "../Scene/Scene.h"
#include <vector>
#include <iostream>

/**
 * @brief Payload for transferring texture information
 *
 */
struct TextureInformation
{
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

    /**
     * @brief Add material to the corresponding batch
     *
     * @param material
     * @return int
     */
    int add_material(ss::Material material);

    /**
     * @brief Add texture to the corresponding batch
     *
     * @param file_path
     * @param lod
     * @param internal_format
     * @param format
     * @return texture information payload
     */
    TextureInformation add_texture(std::string file_path, GLuint lod, GLenum internal_format, GLenum format);

    /**
     * @brief Add mesh to the corresponding batch
     *
     * @param mesh
     */
    void add_mesh(ss::Mesh mesh);

    /**
     * @brief Add point_light to the point light storage
     * 
     * @param point_light 
     */
    void add_point_light(ss::PointLight point_light);

    /**
     * @brief Move the current batch variable to the index of the next batch
     * 
     */
    void next_batch();

    /**
     * @brief Get the batch count 
     * 
     * @return number of batches 
     */
    int get_batch_count();

    /**
     * @brief Get the number of max textures per batch
     * 
     * @return int 
     */
    int get_max_texture_per_batch();

    /**
     * @brief build all batches in preparation of the use phase
     * @note Due to time constraint in implementation, this function should only be called once.
     * @note Any subsequent calls will create unintended effects (since the vector is not rebuilt but appened.)
     * 
     */
    void build_all_batches();

    /**
     * @brief Get the render components of the current batch and use all the corresponding uniforms
     * 
     * @param shader_program 
     * @return RenderComponents 
     */
    RenderComponents use_current_batch(ss::Shader *shader_program);

    /**
     * @brief Set the dimension of the scenes
     * 
     * @param row 
     * @param col 
     */
    void set_dimension(int row, int col);

    /**
     * @brief Get the destination batch based on the id of the item
     * 
     * @param id 
     * @return int 
     */
    int get_destination_batch(int id);

private:
    int current_batch;
    int material_count;
    int row, col;
    std::vector<Scene> scene_storage;
    ss::LightManager light_manager; // We will use this one for all batches.
};

#endif