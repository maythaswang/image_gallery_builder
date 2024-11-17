#ifndef SS_MESH_H
#define SS_MESH_H
#pragma once
#include <lin_alg/lin_alg.h>
#include <vector>

// TODO: Will be used for generating a scene later when batching.
// This struct will use 1 Mesh 1 material method for simplicity before batching
namespace ss
{
    struct Mesh
    {
        std::vector<lin_alg::vec3> vertices;
        std::vector<lin_alg::vec3> indices;
        std::vector<lin_alg::vec3> normals;
        std::vector<GLfloat> tex_coord;
        int mat_id;
    };
}

#endif