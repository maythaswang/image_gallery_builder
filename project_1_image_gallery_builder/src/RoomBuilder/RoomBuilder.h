#ifndef ROOM_BUILDER_H
#define ROOM_BUILDER_H
#pragma once
#include <simple_scene/simple_scene.h>
// #include "Scene/Scene.h"
#include "BatchManager/BatchManager.h"
#include "GeometryBuilder/GeometryBuilder.h"
#include <vector>
#include <string>

class RoomBuilder
{
public:
    RoomBuilder();
    RoomBuilder(BatchManager *, int, int);
    void init_basic_materials();
    void build_room(int, int, bool, bool, bool, bool, bool, std::string, std::string, std::string, std::string);
    void set_scene_data(BatchManager *, int, int);

private:
    BatchManager *batch_manager;
    GeometryBuilder geometry_builder;
    int x;
    int y;

    void transform_plane(ss::Mesh *, int row, int col, lin_alg::vec3 translate_vec, GLfloat degree, lin_alg::vec3 axis_rot);

    int create_canvas_material(std::string texture_path, GLfloat &, GLfloat &);

    void add_canvas(int row, int col, lin_alg::vec3 translate_vec, GLfloat degree, lin_alg::vec3 axis_rot, std::string image_path, int side);
};

#endif