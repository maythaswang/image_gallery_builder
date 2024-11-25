#ifndef SS_MESH_H
#define SS_MESH_H
#pragma once
#include <lin_alg/lin_alg.h>
#include <vector>

// This struct will use 1 Mesh 1 material method for simplicity before batching due to time constraint
namespace ss
{
    struct Mesh
    {
        std::vector<lin_alg::vec3> vertices;
        std::vector<lin_alg::ivec3> indices;
        std::vector<lin_alg::vec3> normals;
        std::vector<GLfloat> tex_coord;
        float mat_id;
        Mesh() : mat_id(0) {}
        Mesh(const Mesh &other) : vertices(other.vertices), indices(other.indices), normals(other.normals),
                                  tex_coord(other.tex_coord), mat_id(other.mat_id) {}
    };
}

#endif