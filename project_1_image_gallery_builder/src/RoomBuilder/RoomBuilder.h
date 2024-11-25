#ifndef ROOM_BUILDER_H
#define ROOM_BUILDER_H
#pragma once
#include <simple_scene/simple_scene.h>
#include "BatchManager/BatchManager.h"
#include "GeometryBuilder/GeometryBuilder.h"
#include <vector>
#include <string>

/**
 * @brief Tool for building rooms
 *
 */
class RoomBuilder
{
public:
    /**
     * @brief Construct a new RoomBuilder object with no basic setup
     * @note will require scene data to be set first
     *
     */
    RoomBuilder();

    /**
     * @brief Construct a new RoomBuilder object
     *
     * @param batch_manager
     * @param x row
     * @param y column
     */
    RoomBuilder(BatchManager *batch_manager, int x, int y);

    /**
     * @brief Initialize basic materials for the scene batch.
     *
     */
    void init_basic_materials();

    /**
     * @brief Add room to the batch_manager
     *
     * @param row row of the room
     * @param col column of the room
     * @param light_on set if light on or off
     * @param has_wall_N set if north wall exist
     * @param has_wall_S set if south wall exist
     * @param has_wall_E set if east wall exist
     * @param has_wall_W set if west wall exist
     * @param wall_image_N north wall image path. if the path is "" then there is no image.
     * @param wall_image_S south wall image path. if the path is "" then there is no image.
     * @param wall_image_E east wall image path.  if the path is "" then there is no image.
     * @param wall_image_W west wall image path.  if the path is "" then there is no image.
     */
    void build_room(int row, int col, bool light_on, bool has_wall_N, bool has_wall_S, bool has_wall_E, bool has_wall_W, std::string wall_image_N, std::string wall_image_S, std::string wall_image_E, std::string wall_image_W);

    /**
     * @brief Set the scene data
     *
     * @param batch_manager
     * @param row
     * @param col
     */
    void set_scene_data(BatchManager *batch_manager, int row, int col);

private:
    BatchManager *batch_manager;
    GeometryBuilder geometry_builder;
    int x;
    int y;

    /**
     * @brief Transform planes based on given information
     *
     * @param mesh
     * @param row
     * @param col
     * @param translate_vec
     * @param degree
     * @param axis_rot
     */
    void transform_plane(ss::Mesh *mesh, int row, int col, lin_alg::vec3 translate_vec, GLfloat degree, lin_alg::vec3 axis_rot);

    /**
     * @brief Create a canvas material
     *
     * @param texture_path
     * @return material id
     */
    int create_canvas_material(std::string texture_path, GLfloat &, GLfloat &);

    /**
     * @brief Add canvas to the scene
     *
     * @param row
     * @param col
     * @param translate_vec
     * @param degree
     * @param axis_rot
     * @param image_path
     * @param side wall side where the canvas should go {0: north, 1: south, 2: east, 3: west} this will only affect the orientation of the canvas.
     */
    void add_canvas(int row, int col, lin_alg::vec3 translate_vec, GLfloat degree, lin_alg::vec3 axis_rot, std::string image_path, int side);
};

#endif